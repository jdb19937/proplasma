#!/usr/bin/env python3
import argparse
import base64
import io
import subprocess
import sys
from pathlib import Path

from openai import OpenAI
from PIL import Image


def run_promptum(promptum_path: Path, modus: str, rudis: bool,
                 extra: list) -> str:
    """Invoke ./promptum --modus <modus> [--rudis] [extra...] and return
    its prompt (the trailing `[semen: N]` line is stripped). `extra`
    is forwarded verbatim so per-modus suboptions (--species, --fundus,
    --artifex, etc.) can pin or bias the generator across cells."""
    argv = [str(promptum_path), '--modus', modus]
    if rudis:
        argv.append('--rudis')
    argv.extend(extra)
    result = subprocess.run(argv, capture_output=True, text=True)
    if result.returncode != 0:
        print(f'promptum failed (exit {result.returncode}): '
              f'{" ".join(argv)}', file=sys.stderr)
        if result.stderr:
            print(result.stderr.rstrip(), file=sys.stderr)
        sys.exit(result.returncode)
    out = result.stdout
    lines = [ln for ln in out.splitlines() if not ln.startswith('[semen:')]
    return '\n'.join(ln for ln in lines if ln.strip()).strip()


ROW_NAMES = {
    2: {1: 'top',    2: 'bottom'},
    3: {1: 'top',    2: 'middle', 3: 'bottom'},
}
COL_NAMES = {
    2: {1: 'left',   2: 'right'},
    3: {1: 'left',   2: 'center', 3: 'right'},
}


def lcps(strs):
    """Longest common prefix, trimmed back to a sentence boundary so we
    never split mid-sentence — important when the common preamble is
    shown once and per-cell tails are shown after it."""
    if not strs:
        return ''
    prefix = strs[0]
    for s in strs[1:]:
        n = min(len(prefix), len(s))
        i = 0
        while i < n and prefix[i] == s[i]:
            i += 1
        prefix = prefix[:i]
        if not prefix:
            return ''
    j = max(prefix.rfind('. '), prefix.rfind('! '),
            prefix.rfind('? '), prefix.rfind('.\n'),
            prefix.rfind('!\n'), prefix.rfind('?\n'))
    if j < 0:
        return ''
    return prefix[:j + 2]


def cell_label(n: int, r: int, c: int) -> str:
    """Positional label for N<4; numeric (row,col) for N=4."""
    if n in ROW_NAMES:
        return f'{ROW_NAMES[n][r]} {COL_NAMES[n][c]}'
    return f'({r},{c})'


def system_prompt(n: int) -> str:
    if n == 1:
        return (
            "You are an image generator. The user will send a single portrait "
            "prompt. Generate a single square image showing exactly that "
            "portrait. No text anywhere in the image."
        )

    if n in ROW_NAMES:
        labels = [
            cell_label(n, r, c)
            for r in range(1, n + 1)
            for c in range(1, n + 1)
        ]
        labels_list = ', '.join(f'"{l}"' for l in labels)
        scheme = (
            f"Each cell is named by its position in the grid: {labels_list}. "
            f'So "top left" is the upper-left corner and '
            f'"{labels[-1]}" is the lower-right corner.'
        )
    else:
        scheme = (
            f"Cell labels use the form (row,col) with row 1 at the top and "
            f"row {n} at the bottom, and col 1 at the left and col {n} at "
            f"the right — so (1,1) is the top-left corner and ({n},{n}) is "
            f"the bottom-right corner."
        )

    return (
        f"You are an image generator. The user will send a single message "
        f"containing {n*n} portrait prompts, each labeled with its cell in "
        f"an {n}x{n} grid. {scheme} Generate a SINGLE square image arranged "
        f"as an {n}x{n} grid of {n*n} portraits, placing each portrait in "
        f"the cell named by its label. Each cell must contain exactly one "
        f"of the {n*n} portraits and must follow its own prompt's framing "
        f"and subject-description rules independently. The {n*n} cells "
        f"depict {n*n} distinctly different people — no two cells may "
        f"repeat the same face, pose, clothing, or composition, and no "
        f"cell may be a near-duplicate of another. Treat each prompt as "
        f"describing a unique individual and follow the per-cell details "
        f"literally so the differences between cells are visible. "
        f"Consistency applies only to overall photographic style and "
        f"lighting so the grid reads as a coherent set; it must NOT "
        f"collapse the subjects into look-alikes. No text anywhere in "
        f"the image; no borders, gutters, or labels between cells — "
        f"just the {n*n} portraits tiled edge-to-edge."
    )


def generate_image(client, sys_msg: str, user_msg: str):
    print('OpenAI responses.create with image_generation tool', file=sys.stderr)
    try:
        resp = client.responses.create(
            model='gpt-5.4',
            input=[
                {'role': 'system', 'content': sys_msg},
                {'role': 'user', 'content': user_msg},
            ],
            tools=[{'type': 'image_generation', 'size': '1024x1024'}],
        )
    except Exception as e:
        print(f'image generation failed, substituting black: {e}',
              file=sys.stderr)
        return Image.new('RGB', (1024, 1024), 'black'), None
    image_b64 = None
    for item in resp.output:
        if getattr(item, 'type', None) == 'image_generation_call':
            image_b64 = getattr(item, 'result', None)
            if image_b64:
                break
    if not image_b64:
        print('no image returned in response, substituting black',
              file=sys.stderr)
        return Image.new('RGB', (1024, 1024), 'black'), None
    img = Image.open(io.BytesIO(base64.b64decode(image_b64)))
    u = getattr(resp, 'usage', None)
    usage = None
    if u is not None:
        it = getattr(u, 'input_tokens', 0) or 0
        ot = getattr(u, 'output_tokens', 0) or 0
        tt = getattr(u, 'total_tokens', 0) or 0
        det = getattr(u, 'input_tokens_details', None)
        itx = getattr(det, 'text_tokens', 0) if det else 0
        iim = getattr(det, 'image_tokens', 0) if det else 0
        usage = (it, itx, iim, ot, tt)
    return img, usage


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('-o', required=True, help='output PNG path')
    ap.add_argument('-d', type=int, default=1024,
                    help='square image side length (default 1024)')
    ap.add_argument('-n', type=int, default=1,
                    help='grid side length; total cells = N*N (default 1, max 4)')
    ap.add_argument('--modus', choices=('persona', 'artista', 'bestia'),
                    default='persona',
                    help='which generator to call in promptum (default persona)')
    ap.add_argument('-r', '--rudis', action='store_true',
                    help='pass -r to promptum (rudis variant: echoes params)')
    ap.add_argument('-1', '--singulatim', action='store_true',
                    help='generate each cell independently with -n 1 and '
                    'recompose into an NxN grid locally')
    args, extra = ap.parse_known_args()

    if args.n < 1 or args.n > 4:
        print(f'-n must be in 1..4, got {args.n}', file=sys.stderr)
        sys.exit(2)

    here = Path(__file__).resolve().parent
    promptum_bin = here / 'promptum'
    if not promptum_bin.exists():
        print(f'promptum binary not found at {promptum_bin}; '
              f'build with: make -f Faceplica',
              file=sys.stderr)
        sys.exit(1)

    cells = [(r, c) for r in range(1, args.n + 1) for c in range(1, args.n + 1)]
    prompts = [run_promptum(promptum_bin, args.modus, args.rudis, extra)
               for _ in cells]

    client = OpenAI()

    if args.singulatim and args.n > 1:
        sys1 = system_prompt(1)
        tiles = []
        usus_in = usus_inx = usus_iim = usus_out = usus_tot = 0
        for (r, c), p in zip(cells, prompts):
            print(f'--- cell {cell_label(args.n, r, c)} ---', file=sys.stderr)
            print(p, file=sys.stderr)
            print('', file=sys.stderr)
            tile, u = generate_image(client, sys1, p)
            tiles.append(tile)
            if u:
                usus_in += u[0]; usus_inx += u[1]; usus_iim += u[2]
                usus_out += u[3]; usus_tot += u[4]
        tile_side = tiles[0].width
        grid_side = tile_side * args.n
        img = Image.new('RGB', (grid_side, grid_side))
        for (r, c), t in zip(cells, tiles):
            if t.width != tile_side or t.height != tile_side:
                t = t.resize((tile_side, tile_side), Image.LANCZOS)
            img.paste(t, ((c - 1) * tile_side, (r - 1) * tile_side))
        if args.d != img.width or args.d != img.height:
            img = img.resize((args.d, args.d), Image.LANCZOS)
        img.save(args.o, format='PNG')
        print(f'usus: input={usus_in} (text={usus_inx} image={usus_iim}) '
              f'output={usus_out} total={usus_tot}', file=sys.stderr)
        print(f'wrote {args.o} ({args.d}x{args.d}) n={args.n} '
              f'cells={args.n*args.n} modus={args.modus} rudis={args.rudis} '
              f'singulatim=True extra={extra}', file=sys.stderr)
        return

    sys_msg = system_prompt(args.n)
    if args.n == 1:
        user_msg = prompts[0]
    elif all(p == prompts[0] for p in prompts):
        sys_msg = (
            f"{sys_msg}\n\nAll {args.n * args.n} cells share exactly this "
            f"common prompt — apply it to every cell:\n\n{prompts[0]}"
        )
        user_msg = f"Generate all {args.n * args.n} cells."
    else:
        common = lcps(prompts)
        cell_prompts = [p[len(common):] for p in prompts] if common else prompts
        if common:
            sys_msg = (
                f"{sys_msg}\n\nEvery cell's prompt begins with this shared "
                f"preamble, stated once here so it need not be repeated "
                f"per cell — apply it to every cell:\n\n{common.strip()}"
            )
        user_msg = '\n\n'.join(
            f'=== CELL {cell_label(args.n, r, c)} ===\n{p}'
            for (r, c), p in zip(cells, cell_prompts)
        )

    print('--- system ---', file=sys.stderr)
    print(sys_msg, file=sys.stderr)
    print('', file=sys.stderr)
    print('--- user ---', file=sys.stderr)
    print(user_msg, file=sys.stderr)
    print('', file=sys.stderr)

    img, u = generate_image(client, sys_msg, user_msg)
    if args.d != img.width or args.d != img.height:
        img = img.resize((args.d, args.d), Image.LANCZOS)
    img.save(args.o, format='PNG')

    if u:
        print(f'usus: input={u[0]} (text={u[1]} image={u[2]}) '
              f'output={u[3]} total={u[4]}', file=sys.stderr)

    print(f'wrote {args.o} ({args.d}x{args.d}) n={args.n} '
          f'cells={args.n*args.n} modus={args.modus} rudis={args.rudis} '
          f'extra={extra}',
          file=sys.stderr)


if __name__ == '__main__':
    main()
