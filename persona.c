#include "persona.h"
#include "communia.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* Generator numerorum fortuitorum: xorshift64*, ex semine determinatus. */
static uint64_t alea_status;

static void alea_seminare(uint64_t s) {
    if (s == 0)
        s = 0x9E3779B97F4A7C15ULL;
    alea_status = s;
}

static uint64_t alea_sequens(void) {
    uint64_t x = alea_status;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    alea_status = x;
    return x * 0x2545F4914F6CDD1DULL;
}

static uint32_t alea_ambitus(uint32_t n) { return (uint32_t)(alea_sequens() % n); }
static double   alea_unitas(void) { return (alea_sequens() >> 11) * (1.0 / 9007199254740992.0); }
static int      alea_fors(double p) { return alea_unitas() < p; }

/* Electio ponderata: summa ponderum non necesse est una esse. */
static int alea_ponderata(const double *pondera, int n) {
    double summa = 0;
    for (int i = 0; i < n; i++)
        summa += pondera[i];
    double r   = alea_unitas() * summa;
    double acc = 0;
    for (int i = 0; i < n; i++) {
        acc += pondera[i];
        if (r < acc)
            return i;
    }
    return n - 1;
}

/* Elige unum aequaliter ex serie. */
static const char *elige_unum(const char *const *series, int n) { return series[alea_ambitus(n)]; }

/* Articulus Anglicus: "a" vel "an". */
static const char *articulus(const char *s) {
    char c = s[0];
    if (c >= 'A' && c <= 'Z')
        c = c - 'A' + 'a';
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? "an" : "a";
}

/* Errorem in capaci vocantis deponere. */
static void pone_errorem(char *capax, size_t longitudo, const char *fmt, ...) {
    if (!capax || longitudo == 0)
        return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(capax, longitudo, fmt, ap);
    va_end(ap);
}

/* ---- tabulae ---- */

/* Colores comae cute notati: 'L' clara, 'M' media, 'D' obscura;
 * catena omnes cutes permissas enumerat. */
typedef struct {
    const char *textus;
    const char *cutes;
} ColorComae;
static const ColorComae colores_comae_iuvenum[] = {
    {"jet black", "LMD"}, {"pitch black", "LMD"}, {"raven black", "LMD"},
    {"coal black", "LMD"}, {"inky black", "LMD"},
    {"dark brown", "LMD"}, {"deep brown", "LMD"}, {"espresso brown", "LMD"},
    {"chocolate brown", "LMD"}, {"chestnut brown", "LM"},
    {"walnut brown", "LM"}, {"medium brown", "LM"}, {"mousy brown", "LM"},
    {"ash brown", "LM"}, {"light brown", "LM"},
    {"sandy brown", "L"}, {"mahogany brown", "LM"},
    {"dirty blonde", "L"}, {"dark blonde", "L"}, {"honey blonde", "L"},
    {"golden blonde", "L"}, {"wheat blonde", "L"}, {"sun-bleached blonde", "L"},
    {"platinum blonde", "L"}, {"flaxen blonde", "L"}, {"pale blonde", "L"},
    {"strawberry blonde", "L"},
    {"auburn", "LM"}, {"dark auburn", "LM"},
    {"copper red", "L"}, {"coppery red", "L"}, {"ginger", "L"},
    {"fiery red", "L"}, {"burnt orange", "L"}, {"rust red", "L"}, {"titian red", "L"}
};
static const char *const colores_comae_canescentes[] = {
    "salt-and-pepper", "pepper-and-salt", "mostly gray with dark streaks",
    "dark with scattered gray", "graying at the temples", "silver-gray", "pewter gray",
    "ash brown flecked with gray", "pepper gray", "steel-streaked", "half-silvered"
};
static const char *const colores_comae_senum[] = {
    "pure white", "snow white", "chalk white", "silver", "silvery", "iron gray",
    "slate gray", "pale gray", "thinning gray", "wispy white", "bone white"
};

/* Lineamentum sexu ('u' utrique, 'm', 'f') qualitateque
 * ('u' deformis, 'n' medium, 'p' pulchrum) discretum. */
typedef struct {
    const char *textus;
    char sexus;
    char qualitas;
} Lineamentum;

static const Lineamentum colores_oculorum[] = {
    {"deep brown", 'u', 'n'}, {"dark brown", 'u', 'n'}, {"coffee brown", 'u', 'n'},
    {"chocolate brown", 'u', 'n'}, {"near-black", 'u', 'n'}, {"walnut brown", 'u', 'n'},
    {"rich brown", 'u', 'n'}, {"warm brown", 'u', 'n'}, {"russet brown", 'u', 'n'},
    {"tawny brown", 'u', 'n'},
    {"warm amber", 'u', 'n'}, {"golden amber", 'u', 'n'}, {"honey-colored", 'u', 'n'},
    {"honey amber", 'u', 'n'}, {"topaz", 'u', 'n'},
    {"hazel", 'u', 'n'}, {"golden hazel", 'u', 'n'}, {"green-flecked hazel", 'u', 'n'},
    {"light hazel", 'u', 'n'},
    {"olive green", 'u', 'n'}, {"moss green", 'u', 'n'}, {"forest green", 'u', 'n'},
    {"sea green", 'u', 'n'}, {"emerald green", 'u', 'n'}, {"jade green", 'u', 'n'},
    {"mossy green", 'u', 'n'}, {"pale green", 'u', 'n'}, {"celadon green", 'u', 'n'},
    {"gray-green", 'u', 'n'},
    {"slate blue", 'u', 'n'}, {"steel blue", 'u', 'n'}, {"pale blue", 'u', 'n'},
    {"icy blue", 'u', 'n'}, {"cornflower blue", 'u', 'n'}, {"deep blue", 'u', 'n'},
    {"sky blue", 'u', 'n'}, {"navy blue", 'u', 'n'}, {"sapphire blue", 'u', 'n'},
    {"robin's-egg blue", 'u', 'n'}, {"turquoise", 'u', 'n'}, {"aquamarine", 'u', 'n'},
    {"blue-gray", 'u', 'n'},
    {"stormy gray", 'u', 'n'}, {"steel gray", 'u', 'n'}, {"pale gray", 'u', 'n'},
    {"silver-gray", 'u', 'n'}, {"slate gray", 'u', 'n'}, {"dove gray", 'u', 'n'},
    {"smoky gray", 'u', 'n'},
    {"green-flecked brown", 'u', 'n'}, {"amber-flecked brown", 'u', 'n'},
    {"violet-blue", 'u', 'p'},
    {"heterochromatic (one blue, one brown)", 'u', 'n'},
    {"small and dull", 'u', 'u'}, {"small and deep-set", 'u', 'u'},
    {"watery pale", 'u', 'u'}, {"bloodshot brown", 'u', 'u'},
    {"dull gray", 'u', 'u'}, {"close-set and dark", 'u', 'u'},
    {"deep-set and shadowed", 'u', 'u'}, {"tired-looking brown", 'u', 'u'},
    {"piercing and pale", 'u', 'p'}, {"warm and brown", 'u', 'n'},
    {"wide-set brown", 'u', 'n'}, {"narrow almond-shaped brown", 'u', 'n'},
    {"almond-shaped black", 'u', 'n'},
    {"large and expressive dark", 'u', 'p'}, {"luminous brown", 'u', 'p'},
    {"bright green", 'u', 'p'}, {"sparkling blue", 'u', 'p'},
    {"captivating hazel", 'u', 'p'},
    {"thickly lashed brown", 'f', 'p'}, {"thickly lashed green", 'f', 'p'},
    {"bright and clear blue", 'u', 'p'}, {"strikingly pale blue", 'u', 'p'},
    {"jewel-like emerald", 'u', 'p'}, {"wide and expressive", 'u', 'p'},
    {"doe-like brown", 'f', 'p'}, {"almond-shaped green", 'u', 'p'},
    {"almond-shaped hazel", 'u', 'p'}, {"elegantly almond-shaped dark", 'u', 'p'},
    {"strikingly bright", 'u', 'p'}, {"luminous pale gray", 'u', 'p'}
};

/* Colores cutis categoria lucis notati. */
typedef struct {
    const char *textus;
    char categoria;
} ColorCutis;
static const ColorCutis colores_cutis[] = {
    {"very pale", 'L'}, {"porcelain pale", 'L'}, {"alabaster", 'L'},
    {"ghostly pale", 'L'}, {"fair", 'L'}, {"light", 'L'}, {"light with freckles", 'L'},
    {"cream-pale", 'L'}, {"ivory", 'L'}, {"light olive", 'L'},
    {"warm olive", 'M'}, {"sallow olive", 'M'}, {"sun-warmed", 'M'},
    {"golden tan", 'M'}, {"tan", 'M'}, {"sun-tanned", 'M'}, {"deep tan", 'M'},
    {"bronzed", 'M'}, {"warm beige", 'M'}, {"medium brown", 'M'}, {"warm brown", 'M'},
    {"rich brown", 'D'}, {"russet", 'D'}, {"umber", 'D'},
    {"dark brown", 'D'}, {"deep brown", 'D'}, {"mahogany", 'D'},
    {"ebony", 'D'}, {"deep ebony", 'D'}, {"near-black", 'D'}
};

static const Lineamentum formae_vultus[] = {
    {"oval", 'u', 'n'}, {"long oval", 'u', 'n'}, {"narrow oval", 'u', 'n'},
    {"egg-shaped", 'u', 'n'}, {"round", 'u', 'n'}, {"full-round", 'u', 'n'},
    {"full-cheeked", 'u', 'n'}, {"moon-faced", 'u', 'u'},
    {"cherubic", 'f', 'n'}, {"square-jawed", 'u', 'n'}, {"square-cut", 'u', 'n'},
    {"broad-jawed", 'm', 'n'}, {"strong-jawed", 'm', 'n'},
    {"blocky and square", 'm', 'u'}, {"heart-shaped", 'u', 'n'},
    {"inverted-triangle", 'u', 'n'}, {"tapering", 'u', 'n'},
    {"long and angular", 'u', 'n'}, {"lean and angular", 'u', 'n'},
    {"sharply angular", 'u', 'n'}, {"long and narrow", 'u', 'n'},
    {"narrow and long", 'u', 'n'}, {"broad and flat-cheeked", 'u', 'n'},
    {"wide and high-cheeked", 'u', 'n'}, {"high-cheekboned", 'u', 'p'},
    {"prominent-cheekboned", 'u', 'p'}, {"narrow and pointed-chinned", 'u', 'n'},
    {"narrow and tapered", 'u', 'n'}, {"diamond-shaped", 'u', 'n'},
    {"gaunt and hollow-cheeked", 'u', 'u'}, {"sunken-cheeked", 'u', 'u'},
    {"soft and rounded", 'u', 'n'}, {"softly rounded", 'u', 'n'},
    {"plump and round", 'u', 'u'}, {"chiseled", 'u', 'p'},
    {"sculpted", 'u', 'p'}, {"sharply chiseled", 'm', 'p'},
    {"oblong", 'u', 'n'}, {"pear-shaped", 'u', 'u'},
    {"wide-browed and narrow-chinned", 'u', 'n'}, {"heavy-browed", 'm', 'u'},
    {"heavy-jawed", 'm', 'u'}, {"boyish and round", 'u', 'n'},
    {"delicate and oval", 'f', 'p'}, {"fine-boned", 'u', 'p'},
    {"broad-browed", 'u', 'n'}, {"lopsided and asymmetrical", 'u', 'u'},
    {"coarse-featured", 'u', 'u'}, {"blotchy and uneven", 'u', 'u'},
    {"pudgy and round", 'u', 'u'}, {"pock-marked", 'u', 'u'},
    {"strikingly symmetrical", 'u', 'p'}, {"finely sculpted", 'u', 'p'},
    {"elegantly shaped", 'u', 'p'}, {"graceful", 'f', 'p'},
    {"beautifully proportioned", 'u', 'p'}, {"classically sculpted", 'u', 'p'},
    {"model-like", 'u', 'p'}, {"high-cheekboned and elegant", 'u', 'p'},
    {"sharply defined and balanced", 'u', 'p'}, {"softly sculpted", 'u', 'p'},
    {"porcelain-smooth and oval", 'f', 'p'}, {"swan-necked and oval", 'f', 'p'}
};

static const Lineamentum formae_nasi[] = {
    {"straight", 'u', 'n'}, {"straight and even", 'u', 'n'},
    {"straight and narrow", 'u', 'n'}, {"perfectly straight", 'u', 'p'},
    {"slightly aquiline", 'u', 'n'}, {"aquiline", 'u', 'n'},
    {"strongly aquiline", 'u', 'n'}, {"hooked", 'u', 'u'},
    {"sharply hooked", 'u', 'u'}, {"eagle-like", 'u', 'u'},
    {"roman", 'u', 'n'}, {"small and upturned", 'u', 'n'},
    {"small and buttoned", 'f', 'n'}, {"button-like", 'f', 'n'},
    {"pert", 'u', 'n'}, {"pert and upturned", 'u', 'n'},
    {"slightly upturned", 'u', 'n'}, {"broad", 'u', 'n'}, {"wide", 'u', 'n'},
    {"flat and broad", 'u', 'u'}, {"broad-based", 'u', 'n'},
    {"wide-nostriled", 'u', 'u'}, {"narrow", 'u', 'n'},
    {"thin and narrow", 'u', 'n'}, {"slim", 'u', 'n'},
    {"pinched", 'u', 'u'}, {"slightly bumped", 'u', 'u'},
    {"hump-bridged", 'u', 'u'}, {"refined and tapered", 'u', 'p'},
    {"refined", 'u', 'p'}, {"delicate", 'f', 'p'}, {"delicately shaped", 'f', 'p'},
    {"long and slender", 'u', 'n'}, {"long and narrow", 'u', 'n'},
    {"long and thin", 'u', 'n'}, {"short and snub", 'u', 'n'},
    {"snub", 'u', 'n'}, {"short and broad", 'u', 'u'},
    {"bulbous-tipped", 'u', 'u'}, {"round-tipped", 'u', 'u'},
    {"ski-jump", 'u', 'n'}, {"slightly crooked", 'u', 'u'},
    {"off-center", 'u', 'u'}, {"prominent", 'u', 'n'},
    {"prominent-bridged", 'u', 'n'}, {"flattened", 'u', 'u'},
    {"flared-nostriled", 'u', 'u'}, {"Greek-straight", 'u', 'n'},
    {"gently curved", 'u', 'n'}, {"drooping-tipped", 'u', 'u'},
    {"elegantly shaped", 'u', 'p'}, {"perfectly proportioned", 'u', 'p'},
    {"finely shaped", 'u', 'p'}, {"classically sculpted", 'u', 'p'},
    {"beautifully straight", 'u', 'p'}, {"gracefully tapered", 'u', 'p'},
    {"lumpy", 'u', 'u'}, {"crooked and scarred", 'u', 'u'},
    {"heavy and thick", 'u', 'u'}, {"misshapen", 'u', 'u'}
};

static const Lineamentum formae_labrorum[] = {
    {"full", 'u', 'n'}, {"plump", 'f', 'n'}, {"generously full", 'f', 'n'},
    {"thin", 'u', 'n'}, {"narrow", 'u', 'n'}, {"thin and pursed", 'u', 'u'},
    {"narrow upper and fuller lower", 'u', 'n'}, {"cupid's-bow", 'f', 'p'},
    {"bow-shaped", 'f', 'p'}, {"wide", 'u', 'n'}, {"broad", 'u', 'n'},
    {"small and delicate", 'f', 'n'}, {"small and tight", 'u', 'u'},
    {"evenly shaped", 'u', 'n'}, {"even", 'u', 'n'},
    {"soft and pillowy", 'f', 'p'}, {"firm and pressed", 'm', 'n'},
    {"chapped and cracked", 'u', 'u'}, {"thin and mean-looking", 'u', 'u'},
    {"too-thin", 'u', 'u'}, {"downturned", 'u', 'u'},
    {"full and shapely", 'f', 'p'}, {"sensual", 'f', 'p'},
    {"well-defined", 'u', 'p'}, {"beautifully shaped", 'u', 'p'},
    {"perfectly shaped", 'u', 'p'}, {"softly curved", 'u', 'p'},
    {"lush", 'f', 'p'}, {"elegantly bow-shaped", 'f', 'p'},
    {"heart-shaped and full", 'f', 'p'}, {"sculpted and full", 'u', 'p'}
};

static const char *const habitus_tenues[] = {
    "slight", "slender", "thin", "spare", "wiry", "lanky", "lean", "willowy",
    "narrow", "narrow-shouldered", "reedy", "gaunt", "rail-thin", "lean and narrow-shouldered"
};
static const char *const habitus_medii[] = {
    "average", "of average build", "medium-framed", "athletic", "trim", "fit",
    "solidly built", "sturdy", "well-proportioned", "compact", "moderately built"
};
static const char *const habitus_graves[] = {
    "broad", "broad-shouldered", "heavyset", "stocky", "thickset", "burly",
    "stout", "portly", "beefy", "round-shouldered", "barrel-chested",
    "broad and heavyset", "big-boned", "wide-framed"
};

/* Capillaturae sexu longitudineque divisae, ut formulis "worn in <X>"
 * vel "styled as <X>" congruant. */
static const char *const capillaturae_virorum_breves[] = {
    "a close-cropped buzz cut", "a shaved military cut", "a tidy side-parted cut",
    "a neatly combed-back style", "a slick side-part", "a short textured crop",
    "a short messy cut", "a clean fade", "a skin fade", "a high-and-tight cut",
    "a slightly tousled short cut", "a short curly cut close to the scalp",
    "a short crew cut", "a close-cropped style with shaved sides",
    "a short undercut with longer hair on top", "a side-shaved cut with a swept-over top",
    "a short classic pompadour", "a slicked-back short cut with a sharp part",
    "a short quiff swept up in front", "a short faux-hawk",
    "a short wet-look slicked-back cut", "a short Caesar cut with a straight fringe",
    "a short Ivy League cut", "a short French crop with a textured fringe",
    "a short afro, close to the head", "a short high-top fade",
    "short box braids close to the scalp", "short twisted coils",
    "short dreadlocks", "short cornrows running straight back",
    "a chopped punk cut with uneven lengths", "a short mohawk laid flat over the scalp"
};
static const char *const capillaturae_virorum_mediae[] = {
    "a medium-length style swept to one side", "a shoulder-length wavy cut",
    "a shaggy medium cut falling over the ears", "a curly medium-length style",
    "an ear-length wavy cut", "a loose medium cut parted in the middle",
    "a thick medium cut combed back", "a tousled medium-length wavy style",
    "a medium shag with layered ends", "a medium mullet",
    "a medium undercut with long hair flowing on top",
    "a curtained medium cut with a center part",
    "an ear-length bob cut", "a medium-length slicked-back style",
    "medium-length dreadlocks", "medium-length twists",
    "a surfer's medium wavy cut"
};
static const char *const capillaturae_virorum_longae[] = {
    "a long low ponytail", "long loose waves past the shoulders",
    "long straight hair parted in the middle",
    "long unkempt hair past the shoulders", "long curls to the collarbone",
    "long dreadlocks falling past the shoulders",
    "long braids gathered at the back", "a long man-bun at the nape",
    "long layered hair with natural waves", "long sleek hair parted to one side"
};
static const char *const capillaturae_feminarum_breves[] = {
    "a sharp pixie cut", "a soft pixie cut", "a chin-length bob", "a blunt chin-length bob",
    "a cropped undercut", "a short tousled cut", "a sleek bob parted to one side",
    "a choppy short cut", "a short cropped curly cut", "a cropped shag cut",
    "an asymmetric bob, longer on one side", "a chin-length bob with blunt bangs",
    "a jaw-length bob with curtain bangs", "a short shag with micro-bangs",
    "a textured pixie with a long side fringe", "a short afro, close to the head",
    "short box braids close to the scalp", "short cornrows running straight back",
    "a faux-hawk with shaved sides", "a short finger-waved cut",
    "a jaw-length blunt cut with a middle part", "a chin-length bob with a deep side part",
    "a crop with a fringe cut straight across the brow"
};
static const char *const capillaturae_feminarum_mediae[] = {
    "a shoulder-length wavy cut", "a straight medium cut with blunt ends",
    "loose medium-length curls", "a layered shoulder-length style",
    "a collarbone-length cut with soft layers", "a medium-length wavy style",
    "a medium-length low ponytail", "a shoulder-length shag",
    "shoulder-length hair with curtain bangs", "a shoulder-length lob with beachy waves",
    "a shoulder-length cut with blunt micro-bangs",
    "a crimped shoulder-length cut", "a finger-waved medium cut",
    "medium-length hair in loose barrel curls",
    "medium-length hair with a middle part and flipped-out ends",
    "a shoulder-length cut with a deep side part", "medium-length twists",
    "a medium-length hime cut with straight sidelocks"
};
static const char *const capillaturae_feminarum_longae[] = {
    "long straight hair past the shoulders", "a long cascade down the back",
    "long loose waves", "long flowing waves", "long spiraling curls", "long tight ringlets",
    "a thick braid draped over one shoulder", "two loose braids",
    "a long fishtail braid draped forward", "a long French braid laid down one shoulder",
    "long box braids", "long dreadlocks falling past the shoulders",
    "a long hime cut with blunt sidelocks and long back",
    "long hair with blunt bangs", "long hair with curtain bangs framing the face",
    "a long layered cut with face-framing pieces",
    "long mermaid waves", "long hair with a crown of small braids",
    "long hair with soft bohemian waves", "a long sleek cut with a sharp middle part"
};

static const char *const barbae[] = {
    "a full thick beard", "a full bushy beard", "a short neatly trimmed beard",
    "a close-cropped beard", "heavy stubble", "a few days' stubble", "light stubble",
    "a goatee", "a neat goatee", "a thin mustache", "a thick mustache", "a mustache only",
    "a long untamed beard streaked with gray", "a long flowing beard", "chin whiskers only",
    "a wiry graying beard", "a carefully shaped beard"
};


/* Vultus ad neutrum inclinat, imaginis inquadraturae aptus. */
static const char *const expressiones[] = {
    "a warm, easy expression with the faintest hint of a smile",
    "a relaxed and friendly look, mouth softly closed",
    "a composed expression with a quiet confidence",
    "a direct gaze with open, welcoming eyes",
    "a calm, self-assured expression, lips just touched by a smile",
    "an engaged, attentive look without grinning",
    "a soft, amiable expression — present but not performing",
    "a settled, poised expression, warm around the eyes",
    "a steady, confident gaze with a trace of humor at the mouth",
    "a friendly neutral expression, eyes bright and alert",
    "a grounded, approachable look",
    "an unforced, pleasant expression with a hint of a smile at one corner of the mouth",
    "a quietly confident expression, eyes engaged with the camera",
    "a warm and present expression, neither smiling broadly nor serious",
    "an open, natural look — gently smiling with the eyes"
};

/* Vestimentum notatum 'u' (utrique), 'm' (virile), 'f' (muliebre). */
typedef struct {
    const char *textus;
    char sexus;
} Vestimentum;

static const Vestimentum vestes_formales[] = {
    {"a charcoal wool suit with a crisp white shirt", 'u'},
    {"a navy blazer over a collared shirt", 'u'},
    {"a dark turtleneck under a tailored jacket", 'u'},
    {"a simple black cardigan over a button-down", 'u'},
    {"a gray pinstripe jacket and open-collar shirt", 'u'},
    {"a tweed sport coat over a pale shirt", 'u'},
    {"a crisp white blouse beneath a dark blazer", 'f'},
    {"a silk scarf knotted over a fitted jacket", 'f'},
    {"a plum velvet jacket over a cream blouse", 'f'},
    {"a wool vest over a pressed shirt", 'u'},
    {"a three-piece brown suit", 'm'},
    {"a black tuxedo with a bow tie", 'm'},
    {"a burgundy waistcoat over a white shirt", 'm'},
    {"a beige trench coat over a dark sweater", 'u'},
    {"a fitted black dress with a thin gold chain", 'f'},
    {"a navy cocktail dress", 'f'},
    {"a cream silk blouse buttoned to the throat", 'f'},
    {"a collared jacket with epaulets", 'u'},
    {"a tailored blazer over a black camisole", 'f'},
    {"an embroidered shawl over a simple dress", 'f'},
    {"a high-necked lace blouse", 'f'},
    {"a satin evening gown", 'f'},
    {"a pressed dress shirt with a loosened tie", 'm'},
    {"a dinner jacket in midnight blue", 'm'},
    {"a long sheath dress in emerald green", 'f'}
};
static const Vestimentum vestes_cotidianae[] = {
    {"a faded denim jacket over a plain t-shirt", 'u'},
    {"a gray crewneck sweater", 'u'},
    {"a soft flannel shirt in muted reds", 'u'},
    {"a worn-in henley, sleeves pushed back", 'u'},
    {"a cream linen blouse", 'f'},
    {"a chunky oatmeal-colored knit sweater", 'u'},
    {"a loose chambray shirt", 'u'},
    {"a faded band t-shirt under an open overshirt", 'u'},
    {"a forest-green cable-knit sweater", 'u'},
    {"a simple cotton tunic", 'u'},
    {"a corduroy shirt in warm brown", 'u'},
    {"a thin wool cardigan over a tank top", 'u'},
    {"a striped sailor-cut shirt", 'u'},
    {"a turtleneck in deep burgundy", 'u'},
    {"a plain black t-shirt", 'u'},
    {"a plain white t-shirt", 'u'},
    {"a cropped sweatshirt", 'f'},
    {"a tie-dyed tee", 'u'},
    {"an oversized plaid shirt", 'u'},
    {"a sleeveless tank top", 'u'},
    {"a denim shirt buttoned halfway", 'u'},
    {"a mustard-yellow sweater", 'u'},
    {"a rust-colored henley", 'u'},
    {"a faded floral summer dress", 'f'},
    {"a cotton sundress", 'f'},
    {"a lace-collared blouse", 'f'},
    {"a Peter Pan collared top", 'f'},
    {"a paisley-print shirt", 'u'},
    {"a knit poncho in earthy tones", 'u'},
    {"a worn leather jacket over a tee", 'u'},
    {"a baggy wool sweater", 'u'},
    {"a simple cardigan in forest green", 'u'},
    {"a silk camisole with thin straps", 'f'},
    {"a button-up shirt with the sleeves rolled to the elbow", 'u'},
    {"a wrap top in deep teal", 'f'},
    {"a pale blue Oxford shirt", 'u'},
    {"a simple gray pullover", 'u'},
    {"a faded green t-shirt", 'u'},
    {"a navy striped long-sleeved tee", 'u'},
    {"a heather-purple v-neck tee", 'u'},
    {"a short-sleeved button-up in pale yellow", 'u'},
    {"a thin zippered track jacket", 'u'},
    {"a gray raglan sweatshirt with navy sleeves", 'u'},
    {"a threadbare concert tee", 'u'},
    {"a cream fisherman's-style knit sweater", 'u'},
    {"a soft pink tee", 'u'},
    {"a dark green polo shirt", 'u'},
    {"a burgundy sweatshirt", 'u'},
    {"a thin cotton henley in stone gray", 'u'},
    {"an unbuttoned flannel over a white undershirt", 'u'},
    {"a boxy oatmeal-colored cardigan", 'u'},
    {"a denim vest over a plain tee", 'u'},
    {"a checkered shirt tucked loosely at the waist", 'u'},
    {"a mock-neck cotton top", 'u'},
    {"a faded olive-green jacket", 'u'},
    {"a light cotton kimono-style jacket, open", 'u'},
    {"a tan windbreaker", 'u'},
    {"a quilted vest over a long-sleeved shirt", 'u'},
    {"a gingham button-up shirt", 'u'},
    {"a navy fleece pullover", 'u'},
    {"a plain ribbed turtleneck in cream", 'u'},
    {"a thin crewneck in sky blue", 'u'},
    {"a striped rugby shirt", 'u'},
    {"a soft cotton sweatshirt with a faded graphic", 'u'},
    {"a cropped denim jacket over a t-shirt", 'u'},
    {"a linen shirt rumpled and untucked", 'u'},
    {"a patterned button-down in muted blues", 'u'},
    {"a cotton sweater with elbow patches", 'u'},
    {"a faded bomber jacket zipped halfway", 'u'},
    {"a wrap-front blouse in dusty rose", 'f'},
    {"an off-the-shoulder knit top", 'f'},
    {"a scoop-neck tee in heather gray", 'u'},
    {"a crocheted vest over a white tank", 'f'},
    {"a boat-neck striped top", 'f'},
    {"a peasant blouse with loose sleeves", 'f'},
    {"a sundress with thin straps and a floral print", 'f'},
    {"a plaid pinafore over a cream blouse", 'f'},
    {"a lightweight kaftan", 'f'},
    {"a ribbed tank top layered under an open shirt", 'u'},
    {"a varsity jacket with wool sleeves", 'u'},
    {"a chunky turtleneck in charcoal", 'u'},
    {"a long-sleeved crewneck in forest green", 'u'},
    {"a soft lavender cardigan", 'u'},
    {"a muted teal thermal shirt", 'u'},
    {"a rust-orange crewneck sweater", 'u'},
    {"a plain navy sweatshirt", 'u'},
    {"a pale peach cotton blouse", 'f'},
    {"a black ribbed bodysuit under an open shirt", 'f'},
    {"a slouchy dolman-sleeve top", 'f'},
    {"a soft gray cashmere sweater", 'u'},
    {"a weather-beaten barn coat over a flannel", 'u'},
    {"a simple crochet top", 'f'},
    /* tuniculae unius coloris */
    {"a plain red t-shirt", 'u'}, {"a plain navy t-shirt", 'u'},
    {"a plain forest-green t-shirt", 'u'}, {"a plain charcoal t-shirt", 'u'},
    {"a plain olive t-shirt", 'u'}, {"a plain burgundy t-shirt", 'u'},
    {"a plain mustard-yellow t-shirt", 'u'}, {"a plain teal t-shirt", 'u'},
    {"a plain burnt-orange t-shirt", 'u'}, {"a plain cream t-shirt", 'u'},
    {"a plain sky-blue t-shirt", 'u'}, {"a plain dusty-pink t-shirt", 'u'},
    {"a plain maroon t-shirt", 'u'}, {"a plain sage-green t-shirt", 'u'},
    {"a faded vintage t-shirt", 'u'}, {"a pocket t-shirt in heather gray", 'u'},
    /* tunicae plicatiles ("flannels") */
    {"a red and black buffalo-plaid flannel shirt", 'u'},
    {"a green and navy plaid flannel shirt", 'u'},
    {"a faded blue plaid flannel shirt", 'u'},
    {"a brown and cream plaid flannel shirt", 'u'},
    {"a worn flannel shirt in autumn reds and oranges", 'u'},
    {"a heavy flannel shirt over a white tee", 'u'},
    {"a plaid flannel shirt with the sleeves rolled up", 'u'},
    {"a soft flannel shirt in forest greens", 'u'},
    {"a gray and burgundy plaid flannel", 'u'},
    /* lanea et sudatoria */
    {"a crewneck sweater in cobalt blue", 'u'},
    {"a crewneck sweater in dusty rose", 'u'},
    {"a crewneck sweater in hunter green", 'u'},
    {"a crewneck sweater in cranberry red", 'u'},
    {"a crewneck sweater in camel tan", 'u'},
    {"a crewneck sweater in pale yellow", 'u'},
    {"a cable-knit sweater in ivory", 'u'},
    {"a cable-knit sweater in navy", 'u'},
    {"a cable-knit sweater in charcoal", 'u'},
    {"a college sweatshirt in faded maroon", 'u'},
    {"a college sweatshirt in navy and gold", 'u'},
    {"a vintage sweatshirt in sun-faded red", 'u'},
    {"a pullover sweater in mustard yellow", 'u'},
    {"a chunky cardigan in oatmeal", 'u'},
    {"a chunky cardigan in rust", 'u'},
    /* fibulatae et collares */
    {"a pale blue Oxford shirt", 'u'},
    {"a white Oxford shirt", 'u'},
    {"a pink Oxford shirt", 'u'},
    {"a chambray shirt in washed blue", 'u'},
    {"a faded denim button-up", 'u'},
    {"a red gingham button-up", 'u'},
    {"a blue gingham button-up", 'u'},
    {"a navy henley", 'u'},
    {"a forest-green henley", 'u'},
    {"a cream henley", 'u'},
    {"a maroon henley", 'u'},
    {"a navy polo shirt", 'u'},
    {"a white polo shirt", 'u'},
    {"a red polo shirt", 'u'},
    {"a pale yellow polo shirt", 'u'},
    /* collum altum, tunicae sine manicis, paenulae */
    {"a black turtleneck", 'u'},
    {"a cream turtleneck", 'u'},
    {"a forest-green turtleneck", 'u'},
    {"a white tank top", 'u'},
    {"a black tank top", 'u'},
    {"a gray tank top", 'u'},
    {"a classic blue denim jacket", 'u'},
    {"a faded black denim jacket", 'u'},
    {"a brown leather jacket", 'u'},
    {"a green canvas field jacket", 'u'},
    {"a navy windbreaker", 'u'},
    {"a khaki chore coat", 'u'},
    /* vestes muliebres */
    {"a white eyelet blouse", 'f'},
    {"a floral print blouse", 'f'},
    {"a ruffled blouse in soft pink", 'f'},
    {"a blouse in dusty lavender", 'f'},
    {"a crop top in burgundy", 'f'},
    {"a scoop-neck tee in navy", 'f'},
    /* plures tunicae muliebres */
    {"a silk camisole in champagne", 'f'},
    {"a silk camisole in black", 'f'},
    {"a satin blouse in blush pink", 'f'},
    {"a chiffon blouse in pale blue", 'f'},
    {"a peasant blouse with embroidered neckline", 'f'},
    {"a tie-neck blouse in cream", 'f'},
    {"a bell-sleeved top in rust orange", 'f'},
    {"a puff-sleeved blouse in white", 'f'},
    {"a wrap blouse in forest green", 'f'},
    {"a wrap top in plum", 'f'},
    {"a smocked top in sky blue", 'f'},
    {"a ribbed knit top in dusty rose", 'f'},
    {"a square-neck top in sage green", 'f'},
    {"a scoop-neck top in lilac", 'f'},
    {"a V-neck blouse in mustard", 'f'},
    {"a halter-neck top in coral", 'f'},
    {"a cami top in ivory", 'f'},
    {"a tank top in rose pink", 'f'},
    {"a boho peasant top in cream", 'f'},
    {"a lace-trimmed blouse in white", 'f'},
    {"a polka-dot blouse in navy and white", 'f'},
    {"a floral sundress in yellow and white", 'f'},
    {"a floral sundress in blue", 'f'},
    {"a gingham sundress in pink and white", 'f'},
    {"a midi dress in sage green", 'f'},
    {"a wrap dress in navy with white dots", 'f'},
    {"a shirt dress in khaki", 'f'},
    {"a denim dress with buttons down the front", 'f'},
    {"a little black dress", 'f'},
    {"a knit sweater dress in camel", 'f'},
    {"a fit-and-flare dress in teal", 'f'},
    {"a corduroy pinafore over a white tee", 'f'},
    {"an overall dress in denim", 'f'},
    {"a kimono-sleeve top in navy", 'f'},
    {"a crochet top over a camisole", 'f'},
    {"an embroidered peasant blouse in white", 'f'},
    {"a lace-collared dress in navy", 'f'},
    {"a sweater in blush pink", 'f'},
    {"a mohair sweater in powder blue", 'f'},
    {"an angora sweater in cream", 'f'},
    {"a fuzzy cardigan in pale pink", 'f'},
    {"a cropped cardigan in butter yellow", 'f'},
    {"a long cardigan in heather gray", 'f'},
    {"a striped boatneck top in navy and white", 'f'},
    {"a mock-neck blouse in ivory", 'f'},
    {"a flannel shirtdress in red plaid", 'f'}
};
static const Vestimentum vestes_insolitae[] = {
    {"a heavy knit Aran jumper", 'u'},
    {"a wool duffel coat with toggle buttons", 'u'},
    {"a brocade vest over a ruffled shirt", 'u'},
    {"a kimono-style robe in indigo", 'u'},
    {"a poncho woven in red and black", 'u'},
    {"a dashiki in bright green and gold", 'u'},
    {"a linen kurta", 'm'},
    {"a sherwani in deep maroon", 'm'},
    {"a cheongsam in black silk", 'f'},
    {"a thick fur-lined parka with the hood down", 'u'},
    {"a long black robe with wide sleeves", 'u'},
    {"a traditional embroidered vest over a white shirt", 'u'},
    {"a sari draped over one shoulder", 'f'},
    {"a flamenco-cut blouse with ruffles", 'f'},
    {"a salwar kameez in pale blue", 'f'},
    {"a kimono in cherry blossom pattern", 'f'},
    {"a yukata in dark blue", 'u'},
    {"a hanbok jeogori in pink and white", 'f'},
    {"an áo dài in sky blue", 'f'},
    {"a cheongsam in red with gold embroidery", 'f'},
    {"a tang suit jacket in black silk", 'u'},
    {"a silk kurta with gold trim", 'm'},
    {"a sherwani in ivory with embroidery", 'm'},
    {"a dupatta draped over the shoulders", 'f'},
    {"a nehru jacket in charcoal", 'm'},
    {"an agbada in cream and gold", 'm'},
    {"a boubou in royal blue", 'u'},
    {"a kente-cloth stole over a plain shirt", 'u'},
    {"a thobe in white", 'm'},
    {"a djellaba in earth tones", 'u'},
    {"a kaftan with gold embroidery", 'u'},
    {"a caftan in turquoise", 'f'},
    {"a huipil with floral embroidery", 'f'},
    {"a guayabera shirt in white", 'm'},
    {"a Western shirt with pearl snaps", 'u'},
    {"a cowboy shirt with an embroidered yoke", 'u'},
    {"a bolo tie over a pressed shirt", 'm'},
    {"a charro jacket with silver buttons", 'm'},
    {"a serape draped over the shoulders", 'u'},
    {"a Peruvian poncho in earthy tones", 'u'},
    {"a gaucho-style poncho", 'u'},
    {"a Nordic lopapeysa with a patterned yoke", 'u'},
    {"an Icelandic knit sweater with a geometric yoke", 'u'},
    {"a fair-isle patterned sweater", 'u'},
    {"a vyshyvanka with red cross-stitch", 'u'},
    {"a kosovorotka shirt with embroidered collar", 'm'},
    {"a Tibetan chuba in deep red", 'u'},
    {"a batik shirt in indigo and white", 'u'},
    {"an ikat-print top", 'u'},
    {"a Hawaiian aloha shirt in a tropical print", 'u'},
    {"a Hawaiian muumuu in a floral print", 'f'},
    {"a tea-length dress in a 1950s cut", 'f'},
    {"a pinstripe zoot-style jacket", 'm'},
    {"a velvet smoking jacket in burgundy", 'm'},
    {"a brocade jacket in forest green", 'u'},
    {"a silk robe with a sash", 'u'},
    {"a Chinese-style padded jacket", 'u'},
    {"a Mongolian deel in deep blue", 'u'},
    {"a shearling-lined denim jacket", 'u'},
    {"a sequined top in silver", 'f'},
    {"a beaded bolero jacket over a plain top", 'f'},
    {"an embroidered Mexican blouse", 'f'},
    {"a gele head-wrap paired with a plain blouse", 'f'},
    {"a turban of patterned silk", 'u'},
    {"a crocheted granny-square vest", 'u'},
    {"a tie-dye caftan", 'u'},
    {"a batik-print wrap top", 'f'},
    {"a Breton fisherman's cap over a striped shirt", 'u'},
    {"a Russian sarafan with embroidered bodice", 'f'},
    {"a Scottish tartan sash over a white blouse", 'f'},
    {"a Balinese embroidered kebaya", 'f'},
    {"a Filipino barong tagalog in sheer piña fabric", 'm'},
    {"a kilt-style sporran strap crossing the chest over a collarless shirt", 'm'},
    {"a Bavarian dirndl bodice laced up the front", 'f'},
    {"a lederhosen-style embroidered shirt", 'm'},
    {"a Basque red beret with a black shirt", 'u'},
    {"a Moroccan kaftan with intricate beadwork", 'f'},
    {"a Nigerian iro and buba", 'f'},
    {"a Rajasthani turban in saffron", 'm'},
    {"a Sikh dastar in deep blue", 'm'},
    {"a keffiyeh draped over the shoulders", 'u'},
    {"a prayer shawl with fringed edges", 'u'},
    {"a tallit over a white shirt", 'm'}
};
static const Vestimentum vestes_nudae[] = {
    {"nothing — the bare shoulders and upper chest are visible", 'u'},
    {"no clothing, the bare shoulders exposed", 'u'},
    {"a bath towel wrapped loosely across the chest", 'u'},
    {"a bedsheet draped around the shoulders", 'u'},
    {"only a thin chain at the neck, the upper chest bare", 'u'},
    {"bare-shouldered, the torso unclothed", 'u'},
    {"no shirt, bare collarbones and upper chest visible", 'u'}
};

/* Eligit vestem sexu congruentem aut utrique communem. */
static const char *elige_vestem(const Vestimentum *series, int n, char sexus_c) {
    int indices[256];
    int k = 0;
    for (int i = 0; i < n && k < 256; i++) {
        if (series[i].sexus == 'u' || series[i].sexus == sexus_c)
            indices[k++] = i;
    }
    return series[indices[alea_ambitus(k)]].textus;
}

/* Eligit lineamentum sexu et qualitate pulchritudinis aptum. */
static const char *elige_lineamentum(const Lineamentum *series, int n, char sexus_c, int pulchritudo) {
    const char *permissa;
    switch (pulchritudo) {
    case 0:
    case 1:
        permissa = "un";
        break;
    case 2:
        permissa = "n";
        break;
    default:
        permissa = "np";
        break;
    }
    int indices[256], k = 0;
    for (int i = 0; i < n && k < 256; i++) {
        if ((series[i].sexus == 'u' || series[i].sexus == sexus_c) && strchr(permissa, series[i].qualitas))
            indices[k++] = i;
    }
    if (k == 0) {
        for (int i = 0; i < n && k < 256; i++) {
            if (series[i].sexus == 'u' || series[i].sexus == sexus_c)
                indices[k++] = i;
        }
    }
    return series[indices[alea_ambitus(k)]].textus;
}

static const char *elige_colorem_comae_iuvenem(char cutis_categoria) {
    int n = sizeof colores_comae_iuvenum / sizeof *colores_comae_iuvenum;
    int indices[64], k = 0;
    for (int i = 0; i < n && k < 64; i++) {
        if (strchr(colores_comae_iuvenum[i].cutes, cutis_categoria))
            indices[k++] = i;
    }
    return colores_comae_iuvenum[indices[alea_ambitus(k)]].textus;
}

/* ---- generatio ---- */

typedef enum {
    AETAS_PUER,       /* infans / puer */
    AETAS_ADULESCENS, /* adulescens */
    AETAS_IUVENIS,    /* iuvenis */
    AETAS_ADULTUS,    /* adultus */
    AETAS_MATURUS,    /* maturus */
    AETAS_SENEX       /* senex */
} Aetas;

typedef enum { SEXUS_MAS, SEXUS_FEMINA } Sexus;

char *persona_generare(
    uint64_t semen,
    const PersonaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    PersonaOptiones vacuae = {0};
    if (!optiones)
        optiones = &vacuae;

    alea_seminare(semen);

    const char *arg_sexus       = optiones->sexus;
    const char *arg_aetas       = optiones->aetas;
    const char *arg_pulchritudo = optiones->pulchritudo;
    const char *arg_vestitus    = optiones->vestitus;
    const char *arg_cutis       = optiones->cutis;

    /* Aetas — verisimilis inclinatio ad adultos, nisi mutatur. */
    double pondera_aetatum[] = { 0.07, 0.10, 0.22, 0.28, 0.20, 0.13 };
    Aetas aetas;
    int aetas_mutata_anni = -1;
    if (arg_aetas) {
        char *finis = NULL;
        long n      = strtol(arg_aetas, &finis, 10);
        if (!finis || *finis != 0 || n < 1 || n > 120) {
            pone_errorem(error_locus, error_longitudo, "aetas vitiosa: %s (numerus integer exspectatur)", arg_aetas);
            return NULL;
        }
        aetas_mutata_anni = (int)n;
        if      (n <= 12)
            aetas = AETAS_PUER;
        else if (n <= 17)
            aetas = AETAS_ADULESCENS;
        else if (n <= 27)
            aetas = AETAS_IUVENIS;
        else if (n <= 39)
            aetas = AETAS_ADULTUS;
        else if (n <= 59)
            aetas = AETAS_MATURUS;
        else
            aetas = AETAS_SENEX;
    } else {
        aetas = (Aetas)alea_ponderata(pondera_aetatum, 6);
    }
    int aetas_anni;
    switch (aetas) {
    case AETAS_PUER:
        aetas_anni = 5  + alea_ambitus(8);
        break;
    case AETAS_ADULESCENS:
        aetas_anni = 13 + alea_ambitus(5);
        break;
    case AETAS_IUVENIS:
        aetas_anni = 18 + alea_ambitus(10);
        break;
    case AETAS_ADULTUS:
        aetas_anni = 28 + alea_ambitus(12);
        break;
    case AETAS_MATURUS:
        aetas_anni = 40 + alea_ambitus(20);
        break;
    default:
        aetas_anni = 60 + alea_ambitus(30);
        break;
    }

    Sexus sexus;
    if (arg_sexus) {
        if      (!strcmp(arg_sexus, "m") || !strcmp(arg_sexus, "mas"))
            sexus = SEXUS_MAS;
        else if (!strcmp(arg_sexus, "f") || !strcmp(arg_sexus, "femina"))
            sexus = SEXUS_FEMINA;
        else {
            pone_errorem(error_locus, error_longitudo, "sexus vitiosus: %s (m|f|mas|femina)", arg_sexus);
            return NULL;
        }
    } else {
        sexus = alea_fors(0.5) ? SEXUS_MAS : SEXUS_FEMINA;
    }

    /* Cutis — duplex gradus: primum categoria ponderibus fixis, deinde aequaliter intra. */
    double pondera_cutium[] = { 0.55, 0.30, 0.15 };  /* L, M, D */
    char cutis_categoria;
    if (arg_cutis) {
        if      (!strcmp(arg_cutis, "clara"))
            cutis_categoria = 'L';
        else if (!strcmp(arg_cutis, "media"))
            cutis_categoria = 'M';
        else if (!strcmp(arg_cutis, "obscura"))
            cutis_categoria = 'D';
        else {
            pone_errorem(error_locus, error_longitudo, "cutis vitiosa: %s (clara|media|obscura)", arg_cutis);
            return NULL;
        }
    } else {
        cutis_categoria = "LMD"[alea_ponderata(pondera_cutium, 3)];
    }
    int numerus_cutium = sizeof colores_cutis / sizeof *colores_cutis;
    int congruentes[32], numerus_congruentium = 0;
    for (int i = 0; i < numerus_cutium; i++)
        if (colores_cutis[i].categoria == cutis_categoria)
            congruentes[numerus_congruentium++] = i;
    int indicium_cutis = congruentes[alea_ambitus(numerus_congruentium)];
    const char *cutis  = colores_cutis[indicium_cutis].textus;

    /* Color comae aetate regitur, cute filtratur pro pictura iuvenum. */
    const char *color_comae;
    if (aetas >= AETAS_SENEX) {
        color_comae = elige_unum(colores_comae_senum, sizeof colores_comae_senum / sizeof *colores_comae_senum);
    } else if (aetas == AETAS_MATURUS && alea_fors(0.6)) {
        color_comae =
            elige_unum(colores_comae_canescentes, sizeof colores_comae_canescentes / sizeof *colores_comae_canescentes);
    } else if (aetas == AETAS_ADULTUS && alea_fors(0.15)) {
        color_comae =
            elige_unum(colores_comae_canescentes, sizeof colores_comae_canescentes / sizeof *colores_comae_canescentes);
    } else {
        color_comae = elige_colorem_comae_iuvenem(cutis_categoria);
    }

    /* Longitudo comae — sexu coniuncta sed non coacta. */
    int longitudo_comae;  /* 0 brevis, 1 media, 2 longa */
    if (sexus == SEXUS_MAS) {
        double pondera[] = { 0.65, 0.28, 0.07 };
        longitudo_comae = alea_ponderata(pondera, 3);
    } else {
        double pondera[] = { 0.18, 0.37, 0.45 };
        longitudo_comae = alea_ponderata(pondera, 3);
    }
    const char *capillatura;
    if (sexus == SEXUS_MAS) {
        if (longitudo_comae == 0)
            capillatura =
                elige_unum(capillaturae_virorum_breves, sizeof capillaturae_virorum_breves / sizeof *capillaturae_virorum_breves);
        else if (longitudo_comae == 1)
            capillatura =
                elige_unum(capillaturae_virorum_mediae, sizeof capillaturae_virorum_mediae / sizeof *capillaturae_virorum_mediae);
        else
            capillatura =
                elige_unum(capillaturae_virorum_longae, sizeof capillaturae_virorum_longae / sizeof *capillaturae_virorum_longae);
    } else {
        if (longitudo_comae == 0)
            capillatura =
                elige_unum(capillaturae_feminarum_breves, sizeof capillaturae_feminarum_breves / sizeof *capillaturae_feminarum_breves);
        else if (longitudo_comae == 1)
            capillatura =
                elige_unum(capillaturae_feminarum_mediae, sizeof capillaturae_feminarum_mediae / sizeof *capillaturae_feminarum_mediae);
        else
            capillatura =
                elige_unum(capillaturae_feminarum_longae, sizeof capillaturae_feminarum_longae / sizeof *capillaturae_feminarum_longae);
    }

    /* Calvities viris senioribus possibilis. */
    int calvus = 0;
    if (sexus == SEXUS_MAS && aetas >= AETAS_MATURUS && alea_fors(aetas >= AETAS_SENEX ? 0.5 : 0.25))
        calvus = 1;

    /* Barba — solum in viris adultis, aetate frequentior. */
    const char *barba = NULL;
    if (sexus == SEXUS_MAS && aetas >= AETAS_IUVENIS) {
        double p = (aetas == AETAS_IUVENIS) ? 0.25 : (aetas == AETAS_ADULTUS) ? 0.45 : 0.55;
        if (alea_fors(p))
            barba = elige_unum(barbae, sizeof barbae / sizeof *barbae);
    }

    /* Pulchritudo — plerique mediocres, extremi rariores; prius iacta ut
     * lineamenta filtrari possint. */
    double pondera_pulchritudinis[] = { 0.08, 0.22, 0.40, 0.22, 0.08 };
    int pulchritudo = alea_ponderata(pondera_pulchritudinis, 5);

    if (arg_pulchritudo) {
        char *finis2 = NULL;
        long n2      = strtol(arg_pulchritudo, &finis2, 10);
        if (!finis2 || *finis2 != 0 || n2 < 0 || n2 > 4) {
            pone_errorem(error_locus, error_longitudo, "pulchritudo vitiosa: %s (0-4)", arg_pulchritudo);
            return NULL;
        }
        pulchritudo = (int)n2;
    }

    char sexus_littera = (sexus == SEXUS_MAS) ? 'm' : 'f';
    const char *oculi =
        elige_lineamentum(colores_oculorum, sizeof colores_oculorum / sizeof *colores_oculorum, sexus_littera, pulchritudo);
    const char *vultus =
        elige_lineamentum(formae_vultus, sizeof formae_vultus / sizeof *formae_vultus, sexus_littera, pulchritudo);
    const char *nasus  = elige_lineamentum(formae_nasi, sizeof formae_nasi / sizeof *formae_nasi, sexus_littera, pulchritudo);
    const char *labra =
        elige_lineamentum(formae_labrorum, sizeof formae_labrorum / sizeof *formae_labrorum, sexus_littera, pulchritudo);

    /* Habitus — aetate leniter coniunctus; pulchritudo ad athleticum
     * vel gravem inclinat. */
    const char *habitus;
    double pondera_habitus_iuvenum[]  = { 0.35, 0.50, 0.15 };
    double pondera_habitus_adultorum[] = { 0.25, 0.50, 0.25 };
    double pondera_habitus_senum[]    = { 0.35, 0.35, 0.30 };
    int indicium_habitus;
    if (aetas <= AETAS_ADULESCENS)
        indicium_habitus = alea_ponderata(pondera_habitus_iuvenum, 3);
    else if (aetas >= AETAS_MATURUS)
        indicium_habitus = alea_ponderata(pondera_habitus_senum, 3);
    else
        indicium_habitus = alea_ponderata(pondera_habitus_adultorum, 3);
    if (pulchritudo >= 3)
        indicium_habitus = 1;  /* pulchri semper medii vel athletici */
    if (indicium_habitus == 0)
        habitus = elige_unum(habitus_tenues, sizeof habitus_tenues / sizeof *habitus_tenues);
    else if (indicium_habitus == 1)
        habitus = elige_unum(habitus_medii, sizeof habitus_medii / sizeof *habitus_medii);
    else
        habitus = elige_unum(habitus_graves, sizeof habitus_graves / sizeof *habitus_graves);

    const char *pulchritudo_phrasis;
    static const Vestimentum phrases_pulchr_0[] = {
        {"plain and unremarkable, with a face that could be called homely", 'u'},
        {"unattractive in a quiet, forgettable way", 'u'},
        {"homely, with features that do not flatter", 'u'},
        {"awkward-featured and a little odd-looking", 'u'},
        {"of rough, weathered looks", 'u'}
    };
    static const Vestimentum phrases_pulchr_1[] = {
        {"of modest, ordinary looks", 'u'},
        {"a touch below average in appearance", 'u'},
        {"plain but not unpleasant to look at", 'u'},
        {"unremarkable but pleasant enough", 'u'}
    };
    static const Vestimentum phrases_pulchr_2[] = {
        {"average and everyday in appearance", 'u'},
        {"of ordinary looks", 'u'},
        {"plainly average-looking", 'u'},
        {"unremarkable, with a face you might pass in the street and not recall", 'u'},
        {"neither handsome nor homely", 'm'},
        {"neither pretty nor plain", 'f'}
    };
    static const Vestimentum phrases_pulchr_3[] = {
        {"good-looking in an easy, approachable way", 'u'},
        {"pleasant-faced and attractive", 'u'},
        {"agreeable and nice to look at", 'u'},
        {"above-average in looks without being showy", 'u'},
        {"handsome in an understated way", 'm'},
        {"ruggedly handsome", 'm'},
        {"pretty in a quiet way", 'f'},
        {"lovely in an understated way", 'f'}
    };
    static const Vestimentum phrases_pulchr_4[] = {
        {"strikingly attractive, with features that draw the eye", 'u'},
        {"possessed of rare, striking beauty", 'u'},
        {"arrestingly handsome", 'm'},
        {"classically handsome", 'm'},
        {"strikingly handsome, with features that draw the eye", 'm'},
        {"unusually beautiful, with a face that stops conversation", 'f'},
        {"classically beautiful", 'f'},
        {"radiantly beautiful", 'f'}
    };
    switch (pulchritudo) {
    case 0:
        pulchritudo_phrasis =
            elige_vestem(phrases_pulchr_0, sizeof phrases_pulchr_0 / sizeof *phrases_pulchr_0, sexus_littera);
        break;
    case 1:
        pulchritudo_phrasis =
            elige_vestem(phrases_pulchr_1, sizeof phrases_pulchr_1 / sizeof *phrases_pulchr_1, sexus_littera);
        break;
    case 2:
        pulchritudo_phrasis =
            elige_vestem(phrases_pulchr_2, sizeof phrases_pulchr_2 / sizeof *phrases_pulchr_2, sexus_littera);
        break;
    case 3:
        pulchritudo_phrasis =
            elige_vestem(phrases_pulchr_3, sizeof phrases_pulchr_3 / sizeof *phrases_pulchr_3, sexus_littera);
        break;
    default:
        pulchritudo_phrasis =
            elige_vestem(phrases_pulchr_4, sizeof phrases_pulchr_4 / sizeof *phrases_pulchr_4, sexus_littera);
        break;
    }

    /* Notae — rariusculae, fortuite cumulatae. */
    char notae_cumulus[512];
    notae_cumulus[0]  = 0;
    int notae_numerus = 0;
    #define ADDE_NOTAM(s) do { \
        if (notae_numerus++ > 0) strncat(notae_cumulus, ", ", sizeof notae_cumulus - strlen(notae_cumulus) - 1); \
        strncat(notae_cumulus, (s), sizeof notae_cumulus - strlen(notae_cumulus) - 1); \
    } while (0)
    {
        static const char *const lentigines[] = {
            "a scattering of freckles across the nose and cheeks",
            "freckled cheeks and nose", "a dense pattern of freckles across the face",
            "light freckling on the nose", "sun-earned freckles across the bridge of the nose"
        };
        static const char *const naevi[] = {
            "a small mole above the lip", "a beauty mark on one cheek",
            "a small mole near the jaw", "a dark mole beside the eye"
        };
        static const char *const cicatrices[] = {
            "a faint old scar along one eyebrow", "a thin pale scar on the chin",
            "a small scar through one eyebrow", "an old scar faintly crossing the forehead"
        };
        static const char *const rugae_tenues[] = {
            "fine lines at the corners of the eyes", "faint crow's feet", "soft laugh lines around the eyes",
            "the first creases at the outer eyes"
        };
        static const char *const rugae_altae[] = {
            "deep creases at the brow and mouth", "deeply lined skin around the eyes and mouth",
            "weathered wrinkles across the face", "a face lined by decades"
        };
        if (alea_fors(0.18))
            ADDE_NOTAM(elige_unum(lentigines, sizeof lentigines / sizeof *lentigines));
        if (alea_fors(0.08))
            ADDE_NOTAM(elige_unum(naevi, sizeof naevi / sizeof *naevi));
        if (alea_fors(0.06))
            ADDE_NOTAM(elige_unum(cicatrices, sizeof cicatrices / sizeof *cicatrices));
        if (aetas >= AETAS_MATURUS && alea_fors(0.7))
            ADDE_NOTAM(elige_unum(rugae_tenues, sizeof rugae_tenues / sizeof *rugae_tenues));
        if (aetas >= AETAS_SENEX)
            ADDE_NOTAM(elige_unum(rugae_altae, sizeof rugae_altae / sizeof *rugae_altae));
    }

    /* Perspicilla. */
    double fors_perspicillorum = (aetas >= AETAS_MATURUS) ? 0.45 : (aetas >= AETAS_IUVENIS) ? 0.25 : 0.10;
    const char *perspicilla    = NULL;
    if (alea_fors(fors_perspicillorum)) {
        static const char *const spp[] = {
            "thin wire-framed glasses", "heavy black-framed glasses",
            "round tortoiseshell glasses", "rimless reading glasses perched low on the nose",
            "thick horn-rimmed glasses", "small oval-lensed glasses",
            "gold wire-rim glasses", "half-moon reading glasses", "tinted round glasses",
            "narrow rectangular glasses", "steel-framed glasses"
        };
        perspicilla = elige_unum(spp, sizeof spp / sizeof *spp);
    }

    /* Vestis ex quattuor vasis eligitur, sexu filtratur. */
    const char *vestis;
    int nudus_electus = 0;
    if (aetas >= AETAS_IUVENIS) {
        /* formalis, cotidiana, insolita, nuda */
        double pondera_vestium[] = { 0.20, 0.70, 0.05, 0.05 };
        int indicium_vestium = alea_ponderata(pondera_vestium, 4);
        if (indicium_vestium == 0)
            vestis = elige_vestem(vestes_formales,  sizeof vestes_formales  / sizeof *vestes_formales,  sexus_littera);
        else if (indicium_vestium == 1)
            vestis = elige_vestem(vestes_cotidianae, sizeof vestes_cotidianae / sizeof *vestes_cotidianae, sexus_littera);
        else if (indicium_vestium == 2)
            vestis = elige_vestem(vestes_insolitae, sizeof vestes_insolitae / sizeof *vestes_insolitae, sexus_littera);
        else {
            vestis        = elige_vestem(vestes_nudae, sizeof vestes_nudae / sizeof *vestes_nudae, sexus_littera);
            nudus_electus = 1;
        }
    } else {
        /* pueri et adulescentes: tantum cotidiana */
        vestis = elige_vestem(vestes_cotidianae, sizeof vestes_cotidianae / sizeof *vestes_cotidianae, sexus_littera);
    }

    const char *expressio = elige_unum(expressiones, sizeof expressiones / sizeof *expressiones);

    /* ---- mutationes applicare ---- */
    if (aetas_mutata_anni >= 0)
        aetas_anni = aetas_mutata_anni;
    if (arg_vestitus) {
        nudus_electus = 0;
        if (!strcmp(arg_vestitus, "formalis"))
            vestis = elige_vestem(vestes_formales, sizeof vestes_formales / sizeof *vestes_formales, sexus_littera);
        else if (!strcmp(arg_vestitus, "cotidianus"))
            vestis = elige_vestem(vestes_cotidianae, sizeof vestes_cotidianae / sizeof *vestes_cotidianae, sexus_littera);
        else if (!strcmp(arg_vestitus, "insolitus"))
            vestis = elige_vestem(vestes_insolitae, sizeof vestes_insolitae / sizeof *vestes_insolitae, sexus_littera);
        else if (!strcmp(arg_vestitus, "nudus")) {
            vestis        = elige_vestem(vestes_nudae, sizeof vestes_nudae / sizeof *vestes_nudae, sexus_littera);
            nudus_electus = 1;
        } else {
            pone_errorem(error_locus, error_longitudo, "vestitus vitiosus: %s (formalis|cotidianus|insolitus|nudus)", arg_vestitus);
            return NULL;
        }
    }

    /* ---- promptum in fluxum memoriae emittere ---- */

    char *capax = NULL;
    size_t capax_longitudo = 0;
    FILE *exitus = open_memstream(&capax, &capax_longitudo);
    if (!exitus) {
        pone_errorem(error_locus, error_longitudo, "open_memstream defecit");
        return NULL;
    }

    fprintf(
        exitus, "A front-facing portrait photograph of a single person. The "
        "entire head must be visible inside the frame with clear empty "
        "space above the top of the hair — under no circumstances should "
        "the top of the head, the hair, or the crown be clipped by the "
        "upper edge. Leave generous headroom. The ears and chin should "
        "also sit comfortably inside the frame, not at the edges. The "
        "subject looks straight into the lens in a relaxed, neutral "
        "pose. "
    );

    const char *sexus_nomen;
    if (sexus == SEXUS_MAS) {
        if (aetas == AETAS_PUER)
            sexus_nomen = "boy";
        else if (aetas == AETAS_ADULESCENS)
            sexus_nomen = "teenage boy";
        else
            sexus_nomen = "man";
    } else {
        if (aetas == AETAS_PUER)
            sexus_nomen = "girl";
        else if (aetas == AETAS_ADULESCENS)
            sexus_nomen = "teenage girl";
        else
            sexus_nomen = "woman";
    }

    fprintf(
        exitus, "The subject is a %s %d years old, %s with %s skin and %s %s face. ",
        sexus_nomen, aetas_anni, habitus, cutis, articulus(vultus), vultus
    );

    fprintf(
        exitus, "%s has %s eyes, %s %s nose, and %s lips, and is %s. ",
        (sexus == SEXUS_MAS) ? "He" : "She", oculi, articulus(nasus), nasus, labra, pulchritudo_phrasis
    );

    const char *Ille = (sexus == SEXUS_MAS) ? "He" : "She";
    const char *Eius = (sexus == SEXUS_MAS) ? "His" : "Her";

    if (calvus) {
        static const char *const templ_calvitatis[] = {
            "%s hair is %s and thinning on top, what remains cut short. ",
            "%s has lost much of %s %s hair, keeping what is left close-cropped. ",
            "On top %s hair is thin and receding, %s color. "
        };
        int i_calv = alea_ambitus(3);
        if (i_calv == 0)
            fprintf(exitus, templ_calvitatis[0], Eius, color_comae);
        else if (i_calv == 1)
            fprintf(exitus, templ_calvitatis[1], Ille, (sexus == SEXUS_MAS) ? "his" : "her", color_comae);
        else
            fprintf(exitus, templ_calvitatis[2], Eius, color_comae);
    } else {
        static const char *const templ_comae[] = {
            "%s hair is %s, worn in %s. ",
            "%s wears %s hair in %s. ",
            "%s has %s hair, styled as %s. "
        };
        int i_com = alea_ambitus(3);
        if (i_com == 0)
            fprintf(exitus, templ_comae[0], Eius, color_comae, capillatura);
        else if (i_com == 1)
            fprintf(exitus, templ_comae[1], Ille, color_comae, capillatura);
        else
            fprintf(exitus, templ_comae[2], Ille, color_comae, capillatura);
    }

    if (barba) {
        static const char *const templ_barbae[] = { "He wears %s. ", "He has %s. ", "His face carries %s. " };
        fprintf(exitus, templ_barbae[alea_ambitus(3)], barba);
    }
    if (perspicilla) {
        static const char *const templ_perspicillorum[] = { "%s wears %s. ", "%s has %s on. ", "On %s face sit %s. " };
        int i_per = alea_ambitus(3);
        if (i_per == 2)
            fprintf(exitus, templ_perspicillorum[2], (sexus == SEXUS_MAS) ? "his" : "her", perspicilla);
        else
            fprintf(exitus, templ_perspicillorum[i_per], Ille, perspicilla);
    }

    if (notae_cumulus[0]) {
        static const char *const templ_notarum[] = { "Notable details: %s. ", "Other features: %s. ", "Also visible: %s. " };
        fprintf(exitus, templ_notarum[alea_ambitus(3)], notae_cumulus);
    }

    if (nudus_electus) {
        fprintf(exitus, "The subject is shown wearing %s. ", vestis);
    } else {
        static const char *const templ_vestis[] = {
            "%s is wearing %s. ", "%s is dressed in %s. ", "%s wears %s. "
        };
        fprintf(exitus, templ_vestis[alea_ambitus(3)], Ille, vestis);
    }

    fprintf(exitus, "The expression is %s. ", expressio);

    /* Fundus — sermo photographicus, non-distractive: tabulae plures,
     * una pro categoria eligitur, deinde phrasis intra categoriam. */
    static const char *const fundus_planum[] = {
        "a seamless medium-gray studio backdrop",
        "a seamless soft-gray studio backdrop, very slightly darker toward the edges",
        "a seamless warm-gray studio backdrop",
        "a seamless cool neutral studio backdrop",
        "a seamless taupe studio backdrop",
        "a seamless charcoal-gray studio backdrop"
    };
    static const char *const fundus_candidum[] = {
        "a clean bright white seamless backdrop, evenly lit",
        "a crisp high-key white studio backdrop with no visible seam",
        "a pure white studio paper backdrop, softly lit"
    };
    static const char *const fundus_ater[] = {
        "a deep black seamless studio backdrop, matte and non-reflective",
        "a solid black studio backdrop with a slight vignette falling off from the figure",
        "an unlit black backdrop, the figure emerging cleanly from the dark"
    };
    static const char *const fundus_coloratum[] = {
        "a saturated cobalt-blue painted wall, matte finish",
        "a vivid emerald-green painted wall",
        "a bright scarlet-red painted wall",
        "a deep royal purple painted wall",
        "a bright marigold-yellow painted wall",
        "a hot coral-pink painted wall",
        "a saturated teal painted wall",
        "a rich magenta painted wall",
        "a bold ultramarine-blue painted wall",
        "a bright tangerine-orange painted wall",
        "a deep forest-green painted wall",
        "a vivid chartreuse painted wall",
        "a rich plum-violet painted wall",
        "a warm tomato-red painted wall",
        "a bright turquoise painted wall",
        "a saturated mustard-gold painted wall",
        "a deep crimson painted wall",
        "a bright fuchsia painted wall",
        "a vivid cerulean painted wall",
        "a bold lime-green painted wall",
        "a muted sage-green painted wall",
        "a dusty rose painted wall, matte finish",
        "a soft mustard-ochre painted wall",
        "a deep teal painted wall",
        "a warm terracotta painted wall",
        "a pale powder-blue painted wall",
        "a muted olive painted wall",
        "a deep burgundy painted wall",
        "a slate-blue painted wall",
        "a pale butter-yellow painted wall",
        "a muted lavender painted wall"
    };
    static const char *const fundus_textura[] = {
        "a softly wrinkled cream muslin backdrop",
        "a painted canvas backdrop with gentle mottling in warm grays",
        "a lightly textured painted canvas backdrop in muted blue-gray, in the old portrait-studio manner",
        "a hand-painted canvas backdrop with soft brown and umber mottling",
        "a faint sponged-texture backdrop in pale slate"
    };
    static const char *const fundus_ambitus[] = {
        "a softly out-of-focus interior behind the figure: warm lamplight and indistinct furniture",
        "an out-of-focus interior behind the figure: a pale window and the suggestion of a bookshelf",
        "a gently defocused domestic interior with muted color and no readable detail",
        "a softly blurred studio interior, the background lights rendered as faint round bokeh"
    };
    static const char *const fundus_exterior[] = {
        "soft out-of-focus foliage behind the figure, green and warm",
        "a blurred exterior of pale sky and indistinct buildings",
        "a softly defocused garden behind the figure, with gentle green highlights",
        "an out-of-focus street behind the figure, the lights rendered as faint bokeh"
    };

    const char *fundus_phrasis = NULL;
    const char *arg_fundus     = optiones->fundus;
    if (arg_fundus) {
        if      (!strcmp(arg_fundus, "planum"))
            fundus_phrasis = elige_unum(fundus_planum,    sizeof fundus_planum    / sizeof *fundus_planum);
        else if (!strcmp(arg_fundus, "candidum"))
            fundus_phrasis = elige_unum(fundus_candidum,  sizeof fundus_candidum  / sizeof *fundus_candidum);
        else if (!strcmp(arg_fundus, "ater"))
            fundus_phrasis = elige_unum(fundus_ater,      sizeof fundus_ater      / sizeof *fundus_ater);
        else if (!strcmp(arg_fundus, "coloratum"))
            fundus_phrasis = elige_unum(fundus_coloratum, sizeof fundus_coloratum / sizeof *fundus_coloratum);
        else if (!strcmp(arg_fundus, "textura"))
            fundus_phrasis = elige_unum(fundus_textura,   sizeof fundus_textura   / sizeof *fundus_textura);
        else if (!strcmp(arg_fundus, "ambitus"))
            fundus_phrasis = elige_unum(fundus_ambitus,   sizeof fundus_ambitus   / sizeof *fundus_ambitus);
        else if (!strcmp(arg_fundus, "exterior"))
            fundus_phrasis = elige_unum(fundus_exterior,  sizeof fundus_exterior  / sizeof *fundus_exterior);
        else {
            pone_errorem(
                error_locus, error_longitudo,
                "fundus vitiosus: %s (planum|candidum|ater|coloratum|textura|ambitus|exterior)",
                arg_fundus
            );
            fclose(exitus);
            free(capax);
            return NULL;
        }
    } else {
        /* Pondera naturalia pro photographia studii. */
        double pondera_fundorum[] = { 0.15, 0.06, 0.06, 0.45, 0.12, 0.10, 0.06 };
        int i_fnd = alea_ponderata(pondera_fundorum, 7);
        switch (i_fnd) {
        case 0:
            fundus_phrasis = elige_unum(fundus_planum,    sizeof fundus_planum    / sizeof *fundus_planum);
            break;
        case 1:
            fundus_phrasis = elige_unum(fundus_candidum,  sizeof fundus_candidum  / sizeof *fundus_candidum);
            break;
        case 2:
            fundus_phrasis = elige_unum(fundus_ater,      sizeof fundus_ater      / sizeof *fundus_ater);
            break;
        case 3:
            fundus_phrasis = elige_unum(fundus_coloratum, sizeof fundus_coloratum / sizeof *fundus_coloratum);
            break;
        case 4:
            fundus_phrasis = elige_unum(fundus_textura,   sizeof fundus_textura   / sizeof *fundus_textura);
            break;
        case 5:
            fundus_phrasis = elige_unum(fundus_ambitus,   sizeof fundus_ambitus   / sizeof *fundus_ambitus);
            break;
        default:
            fundus_phrasis = elige_unum(fundus_exterior,  sizeof fundus_exterior  / sizeof *fundus_exterior);
            break;
        }
    }
    fprintf(
        exitus, "The background is %s; it should be simple and not "
        "compete with the face.\n", fundus_phrasis
    );

    fclose(exitus);
    return capax;
}

/* ---- rudis: parametros mero modo iterat ----
 *
 * Praecursor idem est ac in artista_generare_rudis, ut utraque functio
 * imagines comparabiles producat. Si hic mutatur, artista.c quoque
 * mutandus est. */
static const char *const rudis_praecursor =
    "Generate a portrait. The subject's head is centered in the frame "
    "and the subject is facing the viewer. ";

char *persona_generare_rudis(
    uint64_t semen,
    const PersonaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    static const PersonaOptiones vacua = {0};
    if (!optiones)
        optiones = &vacua;
    if (error_locus && error_longitudo)
        error_locus[0] = '\0';

    char *capax = NULL;
    size_t capax_longitudo = 0;
    FILE *exitus = open_memstream(&capax, &capax_longitudo);
    if (!exitus) {
        pone_errorem(error_locus, error_longitudo, "open_memstream defecit");
        return NULL;
    }

    fputs(rudis_praecursor, exitus);
    fputs(
        "This is a pictura: a photographic portrait of a realistic "
        "person of your own invention. ", exitus
    );
    fputs("Make a random portrait of someone.", exitus);
    (void)semen;

    static const char *const claves_anglice[] = {
        "sex", "age", "attractiveness", "clothing", "skin tone", "background"
    };
    const char *valores[6] = {
        optiones->sexus, optiones->aetas, optiones->pulchritudo,
        optiones->vestitus, optiones->cutis, optiones->fundus
    };
    for (int i = 0; i < 6; i++) {
        if (!valores[i])
            continue;
        fprintf(exitus, " Also %s should be %s.", claves_anglice[i], valores[i]);
    }
    fputc('\n', exitus);

    fclose(exitus);
    return capax;
}
