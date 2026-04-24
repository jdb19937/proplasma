#include "artista.h"
#include "communia.h"

#define N_OF(a) ((int)(sizeof(a) / sizeof((a)[0])))

static const char *elige(const char *const *s, int n) {
    return s[alea_ambitus((uint32_t)n)];
}

/* ---- claves ontologicae ---- */

enum { ART_DALIUS, ART_KLIMTIUS, ART_MONDRIANUS, ART_VERMERUS,
    ART_ESCHERUS, ART_KANDINSKIUS, ART_MAGRITTIUS, ART_POLLOCKIUS,
    ART_PICASSONUS, ART_VANGOGHUS, ART_WARHOLUS, ART_SCHIELEUS,
    ART_BACONIUS, ART_HOPPERUS, ART_HOKUSAIUS, ART_MUNCHIUS,
    ART_LICHTENSTEINIUS, ART_MODIGLIANIUS, ART_REMBRANDTUS,
    ART_HOCKNEIUS, ART_FREUDUS, ART_BASQUIATUS, ART_SEURATUS,
    ART_RIVEREUS,
    ART_VELASPINUS, ART_CRISPULUS, ART_NIMBULUS, ART_ECHOKUS,
    ART_FULGURITUS, ART_TESSELARIUS, ART_OBSCURUS, ART_FILUMENTUS,
    ART_CHRONOFUGUS, ART_SOMNIATOR, ART_VACUARIUS, ART_MORTUARIUS,
    ART_ALGORITHMICUS, ART_HOLOGRAPHUS, ART_CRYPTOLALUS, ART_INTERSTITIUS,
    ART_N };
static const char *const artifices_claves[ART_N] = {
    "dalius", "klimtius", "mondrianus", "vermerus",
    "escherus", "kandinskius", "magrittius", "pollockius",
    "picassonus", "vangoghus", "warholus", "schieleus",
    "baconius", "hopperus", "hokusaius", "munchius",
    "lichtensteinius", "modiglianius", "rembrandtus", "hockneius",
    "freudus", "basquiatus", "seuratus", "rivereus",
    "velaspinus", "crispulus", "nimbulus", "echokus",
    "fulguritus", "tesselarius", "obscurus", "filumentus",
    "chronofugus", "somniator", "vacuarius", "mortuarius",
    "algorithmicus", "holographus", "cryptolalus", "interstitius"
};

enum { MED_OLEUM, MED_TEMPERA, MED_ACRYLICUM, MED_GOUACHE,
    MED_ATRAMENTUM, MED_FRESCA, MED_COLLAGE, MED_MUSIVUM, MED_N };
static const char *const media_claves[MED_N] = {
    "oleum", "tempera", "acrylicum", "gouache",
    "atramentum", "fresca", "collage", "musivum"
};
/* Multipla nomina pro quaque clavi, ut descriptiones variae fiant. */
typedef struct {
    const char *const *opts;
    int n;
} PhraseSet;

static const char *const media_oleum[] = {
    "oil paint on a fine-weave linen canvas, 60 by 45 cm, glue-sized and twice-primed with lead white",
    "oil paint on a medium-weave linen canvas, sized with rabbit-skin glue and primed in a warm ivory ground",
    "oil paint on a prepared poplar panel, laid over a polished chalk gesso ground",
    "oil paint on a copper plate about A4 in size, the bare metal visible at its unpainted edges"
};
static const char *const media_tempera[] = {
    "egg tempera on a poplar panel, laid over a thin chalk gesso ground",
    "egg tempera on linen pasted to a pine panel, gessoed smooth with a rabbit-skin size",
    "egg tempera on cradled oak, sized and gessoed three times and finally polished"
};
static const char *const media_acrylicum[] = {
    "acrylic paint on primed cotton duck, the edges of the stretcher just visible under the paint",
    "acrylic on a gessoed hardboard panel, its edges taped clean and the paint applied flat",
    "acrylic on a stretched linen canvas 80 cm square, primed in a cool white"
};
static const char *const media_gouache[] = {
    "gouache on heavy cold-pressed watercolour paper, the tooth of the paper catching at every stroke",
    "gouache on a smooth illustration board, laid in flat opaque coats",
    "gouache over a graphite underdrawing on heavy hot-pressed paper, the underdrawing still faintly visible"
};
static const char *const media_atramentum[] = {
    "black carbon ink and brush-washed dilutions on laid, cream-coloured paper",
    "iron-gall ink on vellum, its lines still faintly bluish-black against the warm skin",
    "sumi ink on absorbent rice paper, the grain of the paper visible as the ink is drunk in"
};
static const char *const media_fresca[] = {
    "true fresco into fresh lime plaster, the colours set while the surface was still damp",
    "fresco secco over a dry plaster wall, the pigments bound with a casein medium",
    "buon fresco on a day-section of fresh intonaco, the giornata seams still visible as hairline joins"
};
static const char *const media_collage[] = {
    "torn magazine paper and printed fragments pasted over a painted ground, the tears left ragged",
    "cut and pasted coloured papers, each edge cleanly scissored, glued over a matte painted ground",
    "collaged newspaper clippings, bus tickets, and textile scraps glued over an oil-painted base"
};
static const char *const media_musivum[] = {
    "glass, stone, and gold-backed tesserae, each about 8 mm square, bedded in white setting plaster",
    "mosaic of marble and smalti, with gold-leaf tesserae reserved for the halo and ornament",
    "glass tesserae of varying sizes, the smallest 4 mm and the largest 15 mm, set in a buttery limewash bed"
};
static const PhraseSet media_sets[MED_N] = {
    [MED_OLEUM]      = { media_oleum,      N_OF(media_oleum) },
    [MED_TEMPERA]    = { media_tempera,    N_OF(media_tempera) },
    [MED_ACRYLICUM]  = { media_acrylicum,  N_OF(media_acrylicum) },
    [MED_GOUACHE]    = { media_gouache,    N_OF(media_gouache) },
    [MED_ATRAMENTUM] = { media_atramentum, N_OF(media_atramentum) },
    [MED_FRESCA]     = { media_fresca,     N_OF(media_fresca) },
    [MED_COLLAGE]    = { media_collage,    N_OF(media_collage) },
    [MED_MUSIVUM]    = { media_musivum,    N_OF(media_musivum) }
};

enum { PAL_CALIDA, PAL_FRIGIDA, PAL_SATURATA, PAL_MUTA,
    PAL_MONOCHROMA, PAL_PRIMARIA, PAL_TERREA, PAL_N };
static const char *const palettae_claves[PAL_N] = {
    "calida", "frigida", "saturata", "muta",
    "monochroma", "primaria", "terrea"
};

enum { HAB_SERENUS, HAB_TURBULENTUS, HAB_MELANCHOLICUS, HAB_IUBILANS,
    HAB_SOLEMNIS, HAB_TENSUS, HAB_N };
static const char *const habitus_claves[HAB_N] = {
    "serenus", "turbulentus", "melancholicus", "iubilans", "solemnis", "tensus"
};
static const char *const habitus_serenus[] = {
    "The overall affect is that of held stillness; the painted air behaves like dry, undisturbed glass.",
    "The overall affect is quiet and composed; nothing in the picture moves, and the stillness is companionable rather than oppressive.",
    "The overall affect is a patient calm; the subject breathes out slowly, and the picture breathes with them.",
    "The overall affect is settled and alert; the subject waits, unhurried, and the viewer settles into their waiting."
};
static const char *const habitus_turbulentus[] = {
    "The overall affect is turbulent: forms press outward at the edges, as if the picture were under a slow wind.",
    "The overall affect is restless; the composition strains against its own frame and refuses to sit quietly.",
    "The overall affect is unsettled; every line in the picture leans away from every other, as though the painting were being pulled apart slowly.",
    "The overall affect is charged; the air around the figure reads as if a storm had just passed or were about to arrive."
};
static const char *const habitus_melancholicus[] = {
    "The overall affect is a quiet blue melancholy; one long shadow eats the picture from its lower left.",
    "The overall affect is patient sadness; the subject does not grieve but remembers, and the picture keeps them company.",
    "The overall affect is wistful; the picture feels cool in a way not entirely explained by its palette.",
    "The overall affect is a soft, contained sorrow — nothing is pitied, but nothing is brightened either."
};
static const char *const habitus_iubilans[] = {
    "The overall affect is celebratory: the strongest chromas are put in the most exposed places and left to sing.",
    "The overall affect is openly joyful; the picture is pleased with itself, and its pleasure reads as generous rather than boastful.",
    "The overall affect is bright and expansive; every corner of the composition is lit and the figure inhabits that light fully.",
    "The overall affect is buoyant and warm; the picture reads as a good day made permanent."
};
static const char *const habitus_solemnis[] = {
    "The overall affect is ceremonial — everything holds position as though photographed at the moment of a prophecy.",
    "The overall affect is processional and weighty; the picture holds its subject with the dignity of a civic portrait.",
    "The overall affect is formal and composed; the figure does not acknowledge the viewer, and the viewer does not intrude on the figure.",
    "The overall affect is quiet gravity; the picture is ready to be hung where decisions are made."
};
static const char *const habitus_tensus[] = {
    "The overall affect is taut: nothing moves, and the quiet has the particular quality of a held breath.",
    "The overall affect is strung; every edge in the picture is under pressure, and the tension does not release.",
    "The overall affect is watchful and coiled; something is about to happen, and the picture refuses to say what.",
    "The overall affect is electric and still; the air around the figure reads as though lightly charged."
};
static const PhraseSet habitus_sets[HAB_N] = {
    [HAB_SERENUS]       = { habitus_serenus,       N_OF(habitus_serenus) },
    [HAB_TURBULENTUS]   = { habitus_turbulentus,   N_OF(habitus_turbulentus) },
    [HAB_MELANCHOLICUS] = { habitus_melancholicus, N_OF(habitus_melancholicus) },
    [HAB_IUBILANS]      = { habitus_iubilans,      N_OF(habitus_iubilans) },
    [HAB_SOLEMNIS]      = { habitus_solemnis,      N_OF(habitus_solemnis) },
    [HAB_TENSUS]        = { habitus_tensus,        N_OF(habitus_tensus) }
};

enum { FUN_PLANUM, FUN_ORNATUM, FUN_PAESAGIUM, FUN_ABSTRACTUM,
    FUN_TENEBROSUM, FUN_LUMINOSUM, FUN_N };
static const char *const fundi_claves[FUN_N] = {
    "planum", "ornatum", "paesagium", "abstractum", "tenebrosum", "luminosum"
};

/* ---- per artificem: phrases singulariter specificae ---- */

typedef struct {
    const int *media_praeferenda;
    int n_media;

    /* figurae: sententia integra, quomodo sessor pingitur */
    const char *const *figurae;
    int n_figurae;
    /* motiva: objecta specialissima, unum vel duo eligenda */
    const char *const *motiva;
    int n_motiva;

    /* palettae phrases specificae artifici, clavem PAL_* indexant */
    const char *palettae[PAL_N];
    /* fundi phrases specificae, clavem FUN_* indexant */
    const char *fundi[FUN_N];

    /* tres aspectus communes artistici: lumen, textura, compositio */
    const char *const *lumen;
    int n_lumen;
    const char *const *texturae;
    int n_texturae;
    const char *const *compositio;
    int n_compositio;

    /* sententia ultima de technica */
    const char *signatura;
} Stylus;

/* ============================================================
 * dalius — horologia liquescentia, planities deserta
 * ============================================================ */
static const int dalius_media[] = { MED_OLEUM, MED_TEMPERA };
static const char *const dalius_figurae[] = {
    "The subject's face is held together by a single forked wooden crutch jammed under the jaw from below; without it the features would slide off. The cheek on the left droops 6 cm lower than the cheek on the right, running down and pooling onto the collarbone like a slow, heavy honey.",
    "The forehead has come open along a hairline seam and three small mahogany drawers, each with a brass keyhole, slide outward by different amounts. The middle drawer is pulled out fully and contains neatly folded white linen; the upper drawer is ajar by about a centimetre; the lowest stays closed.",
    "The eyelids hang elongated, each about three times the normal length, folded over on themselves like soft brown leather. The iris on the left has detached slightly and floats a few millimetres forward of the eyeball, casting a tiny crescent of shadow.",
    "The jaw has softened into a viscous puddle spreading across the shoulder; a fly is preserved motionless in the thickest part of it. The lower lip extends outward and thins into a long drip that nearly touches the picture's lower edge.",
    "The subject's head is a smooth, polished solid, but one of the ears has unfurled into a second hand — five attenuated fingers in place of the helix — pointing back toward the temple.",
    "The skin over the whole face is glazed to a porcelain finish with no visible brushmark at any magnification. Beneath it, thin blue veins are painted as though they carried cold water rather than blood.",
    "The neck has been drawn out to twice its natural length, perfectly smooth and unlined, as though pulled from warm caramel; at its narrowest point it is no wider than two fingers before widening into the collar.",
    "The subject's hair has been replaced by a motionless vertical column of pale cream smoke that rises from the scalp to the top of the picture; no movement is implied anywhere within it.",
    "The tongue hangs out of the mouth attenuated to the length of a necktie; its tip rests softly against the shirt fabric, its surface painted with the same patient smoothness as the cheek.",
    "A thin clear drip has released from the tip of the nose and hangs 4 cm below it, refusing to fall, caught at the exact moment before separation.",
    "The subject's right eye has been replaced within the socket by a small functional clock face with Roman numerals, the hands set precisely to 10:10; the eyelashes of that side have been preserved exactly.",
    "Three small black flies have alighted on the cheek and brow; each has its own tiny cast shadow, each is frozen mid-landing as though embedded in varnish.",
    "The entire skull is painted as if made of translucent horn, so that a second, smaller skull is just visible inside the first, suspended at the level of the mouth.",
    "The subject's shoulders have elongated downward and outward by 15 cm on each side, tapering to narrow points that project well past the natural silhouette.",
    "The lower half of the face has slipped downward by about 2 cm relative to the upper half, leaving a horizontal seam at the bridge of the nose where the two halves imperfectly meet.",
    "The subject's face is perfectly intact and radiant — clear luminous skin, bright expressive eyes, full dark lips, a calm closed smile. The dream logic is confined to the objects around the figure: a drooping clock on the shoulder, a column of ants across the temple, a distant flaming giraffe on the horizon. The body itself remains beautiful and whole.",
    "The subject is painted as a striking beauty finished in high porcelain smoothness: flawless honey-warm skin, long dark lashes, a relaxed closed mouth, dark hair falling in a single patient wave. Only the surrounding elements — a melting pocket watch, a hovering key, a distant rhinoceros with an impossible shadow — carry the surreal charge; the face itself is healthy, composed, quietly glamorous.",
    "The face is perfectly modelled, unblemished, and confidently beautiful, its skin a warm rose and gold, its eyes clear and direct. Around it the landscape behaves impossibly — a long shadow cast by nothing, a horizon at the wrong height — but the subject reads as a real and desirable person, rendered in Dalí's glassy finish."
};
static const char *const dalius_motiva[] = {
    "a pocket watch, its case melted limp, drapes over the right shoulder with the hour hand hanging downward",
    "a column of about forty tiny black ants crosses the temple in a single obedient line from ear to brow",
    "a soft, unshelled egg rests balanced on the open palm, its membrane stretched but unbroken",
    "a small distant rhinoceros stands on the plain behind the subject and casts a shadow twice its own length",
    "a wooden Y-shaped crutch is wedged beneath the lower eyelid, holding it open like a tent pole under a soft canvas",
    "a single heavy brass key hangs from a fine thread around the neck, weightless, lifted out horizontally by an unfelt wind",
    "an eight-pointed ink-black starfish is pinned to the jacket over the heart, where a carnation should be",
    "a pyramid of six cast bronze spheres, each reflecting a different quadrant of the sky, is balanced on the shoulder",
    "a long loaf of bread lies across the crown of the head, precisely horizontal, casting no shadow whatsoever",
    "a small giraffe no larger than a finger stands burning on the horizon, its flame licking quietly upward with no smoke",
    "a live red-lacquer lobster rests on top of the head where a hat would be, claws tucked neatly forward",
    "an open pomegranate has cracked against the shoulder and a stream of small painted beads falls from it in a fine frozen arc",
    "a black bakelite telephone receiver hangs in place of an earring at the left ear, its cord curling downward out of the picture",
    "a tiny distant train made of bone crosses the plain behind the figure on a hairline track, smoke rising in a single straight column",
    "a single thin human leg, complete with polished shoe and grey sock, grows sideways from the collarbone like a branch",
    "a row of seven small blue drawers projects in graduated depths from the side of the torso, each with a brass keyhole",
    "a second, smaller melted pocket watch hangs over the edge of the lower lip like a tongue about to drip",
    "a long human arm reaches in from the left frame edge and gently steadies the back of the head from behind",
    "a soft wax candle grows from the top of the head, its wick unlit, the wax running down over the hairline in slow static rivulets",
    "a single painted bee hovers motionless 2 cm in front of the nose, casting a sharp small shadow on the forehead",
    "a capybara the size of a small dog rests calmly on the left shoulder, its damp fur glazed to a porcelain smoothness, its eyes half-closed"
};
static const char *const dalius_lumen[] = {
    "A single, low sun throws every shadow 4 to 6 times longer than the object that casts it, all shadows raked hard to the right.",
    "The light is desert noon but the shadows behave as if it were late afternoon — an impossibility the picture refuses to resolve.",
    "A flat, sourceless glow illuminates every surface equally; nothing casts a shadow except the small objects on the body, which cast enormous ones.",
    "Shadows lie on the ground as thin hard-edged bars of blue-black, darker at their ends than at their middles, as though light had pooled against them.",
    "The sun is nowhere visible but its angle is felt at the back of the neck: every cast shadow points in the same direction, long and exact.",
    "Small objects — ants, flies, keys — cast shadows larger than themselves; large objects cast shadows that have been cropped short as if cut with a knife.",
    "The sky is a single unbroken pale gradient and the ground takes all of its luminance; every modelled form glows faintly on its underside from the lit floor."
};
static const char *const dalius_texturae[] = {
    "Every square centimetre is polished to enamel; the surface under raking light shows no brushmark, only the weave of the canvas faintly through the paint.",
    "Thin oil glazes have been laid in many layers, each dried fully before the next, so that the skin has a translucent, almost edible depth.",
    "The paint has been worked so smooth that a fingernail drawn across it would feel only the ground beneath.",
    "The surface is so mirror-smooth that under raking light it reflects the room as though slightly warped plate glass.",
    "The paint is laid in transparent glazes a day apart; the cumulative depth reads like a varnish poured over a miniature ivory.",
    "No brushmark survives anywhere; the painter's hand is hidden entirely behind a photographic finish applied with sable hairs.",
    "Every highlight is placed with the exactness of a pinpoint, each no wider than a millimetre, each painted as its own single opaque dot."
};
static const char *const dalius_compositio[] = {
    "The subject occupies the exact vertical centre of the picture; the horizon behind passes through the mouth at a strict horizontal.",
    "The figure is set slightly left of centre, with the open plain extending unusually far to the right, giving every object a great deal of empty space to fall into.",
    "Everything is arranged on three parallel horizontal zones: ground, horizon, sky, each meeting the next with no transition.",
    "The horizon meets the picture at exactly two-thirds of the frame's height, a deliberate Renaissance proportion; the sky above is unfashionably empty.",
    "A single long cast shadow occupies the right half of the composition entirely, so that the subject shares the picture equally with their own shadow.",
    "All major elements lie strictly on horizontal or vertical axes; no diagonal is permitted except in the raking shadow of one object.",
    "The subject is pushed to the lower-left quadrant; the upper-right two-thirds of the picture is empty pale sky, crossed only by a single distant object."
};
static const Stylus stylus_dalius = {
    dalius_media, N_OF(dalius_media),
    dalius_figurae, N_OF(dalius_figurae),
    dalius_motiva, N_OF(dalius_motiva),
    {
        [PAL_CALIDA]    = "The colour is burnt ochre, dried-blood red, and bleached saffron, against a pale salmon sky.",
        [PAL_FRIGIDA]   = "The palette is pale Mediterranean blue, dove grey, and the exact grey-green of a dry olive leaf.",
        [PAL_SATURATA]  =
            "Acid cadmium yellow meets deep cobalt, with no middle tones in between; the contrast is almost aggressive.",
        [PAL_MUTA]      =
            "Dusty parchment and faded sand dominate; colour has been beaten back until it almost leaves the canvas.",
        [PAL_MONOCHROMA] = "The picture is entirely in graded warm sepia, from bone white highlight to bitumen shadow.",
        [PAL_PRIMARIA]  =
            "Pure red, yellow, and blue are set flat and untouched against a white ground, like three cards laid down.",
        [PAL_TERREA]    =
            "Raw umber, burnt sienna, and yellow ochre cover everything; it looks mixed from the soil of the Empordà."
    },
    {
        [FUN_PLANUM]     = "Behind the figure stretches an empty Catalan plain, razor-horizon, nothing on it for a kilometre.",
        [FUN_ORNATUM]    =
            "Behind the figure, a dry lakebed is scattered with small ceremonial objects — a clockface, a bent spoon, a bone.",
        [FUN_PAESAGIUM]  = "Behind the figure, eroded sandstone cliffs recede into a windless distance, lit from the side.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the ground fades into nothing; only a single long, cast shadow tells you a ground exists at all.",
        [FUN_TENEBROSUM] = "Behind the figure, a dusk-blue plain lies under a last-light sky the colour of a bruise.",
        [FUN_LUMINOSUM]  = "Behind the figure, a flat desert noon burns every cast shadow into a hard, ink-black bar."
    },
    dalius_lumen, N_OF(dalius_lumen),
    dalius_texturae, N_OF(dalius_texturae),
    dalius_compositio, N_OF(dalius_compositio),
    "The surface is finished to a mirror polish; no gesture of the brush is admitted anywhere on the picture."
};

/* ============================================================
 * klimtius — ornatus auri, musivum planum
 * ============================================================ */
static const int klimtius_media[] = { MED_OLEUM, MED_MUSIVUM };
static const char *const klimtius_figurae[] = {
    "Only the face, the neck, and the hands are modelled in realist flesh; everything else of the body flattens into a tall, vertical slab of gold-and-black ornament, as if the subject had stepped halfway into a decorated wall.",
    "The head is set against a large circular halo of beaten gold leaf, 34 cm across, crackled at its rim. The face, by contrast, is painted in small, patient strokes of soft olive-rose flesh tone.",
    "The garment covering the body is a continuous field of pattern: gold squares roughly 12 mm on a side, alternating with smaller black-and-silver spirals and occasional single almond-shaped eyes. No fold or weight of cloth is shown.",
    "The neck is encircled by a wide, beaten-gold collar 4 cm tall, embossed with repeating stylised sunflowers. Below it, the body dissolves completely into pattern within two centimetres.",
    "The face floats in the upper third of the picture, serene, eyes lowered, cheeks a soft flushed pink; the remaining two-thirds beneath is a tall ornamental slab of gold that carries the subject's shape only as a bounded silhouette.",
    "The entire body except for the hands and face is treated as a sheet of mosaic; a band of small silver fish scales covers the chest, a band of black triangles covers the waist, a band of amber dots covers the hem.",
    "The hair is rendered as a mass of tightly coiled gold spirals, each no larger than a thumbnail, pinned at the temples with small cloisonné stars.",
    "The shoulders are exaggeratedly wide and perfectly square, each corner marked with a beaten-gold rosette 5 cm across; the collarbone is not visible beneath the ornament.",
    "The subject's mouth is small and closed, painted in a single tight curve of carmine; the eyes are long almonds outlined in a thin black line without shading.",
    "The hands are modelled in the same patient flesh tones as the face but are held folded together at the waist; the long fingers disappear into ornamented cuffs that swallow them past the second knuckle."
};
static const char *const klimtius_motiva[] = {
    "a narrow vertical frieze of small gold teardrops runs down the left side of the garment, ten teardrops visible",
    "a dozen rectangular eyes, each about 6 mm wide, stare outward from the patterned ground at irregular positions",
    "a cluster of coiled black-and-silver spirals crowds the shoulder like a pelt of tiny shields",
    "a single applied square of true gold leaf, 3 cm on a side, has been laid at the centre of the chest; its edges catch light in physical ridges",
    "a stylised bouquet of five enamelled flowers, each a different jewel colour, lies in the lap",
    "a thin, ragged horizontal band of silver leaf crosses the garment at waist height, like a river seen from far above",
    "a triangle of small turquoise enamel dots, twenty in number, is distributed across the right shoulder",
    "a repeated motif of small black right-facing triangles runs in a tight column down the centre of the garment, fifty triangles end to end",
    "a band of alternating silver-and-gold checkers about 3 cm tall crosses the chest like a decorative sash",
    "a single enamelled beetle, iridescent green and blue, is set at the throat as a brooch",
    "thin golden lines radiate outward from the edges of the head in a sunburst pattern, filling the top half of the background",
    "a meander border in black-and-gold runs along the picture's lower edge for its full width",
    "a cluster of small mother-of-pearl discs, twelve of them, is inlaid across the shoulder where it meets the neck",
    "a field of tiny stylised black trees, no taller than a centimetre, fills a vertical strip down the right side of the garment"
};
static const char *const klimtius_lumen[] = {
    "The figure is lit by a frontal, even, indoor light; no cast shadow is allowed to fall across the ornamental field.",
    "Light enters only to strike the raised gold leaf, which scatters it in hard, physical flares across the picture surface.",
    "No directional light is admitted anywhere; the flesh glows faintly from within as if lit by candles held just behind the picture.",
    "The picture's illumination is carried entirely by the gold — where the gold is, the picture is bright; where it is withheld, the picture falls dark.",
    "Light falls softly on the face from above and disappears completely below the neck, where all illumination is replaced by ornament."
};
static const char *const klimtius_texturae[] = {
    "Real gold leaf is laid directly onto the panel in many small squares; under raking light its edges stand up in tiny physical ridges.",
    "The flesh passages are stroked on in tight, patient hatches; the ornamental passages are laid on flat and then incised with a stylus to mark the pattern lines.",
    "Mother-of-pearl inlays and small semi-precious stones are set physically into the paint layer; they reflect real light, not painted light.",
    "Areas of the ornament carry a low relief — about one millimetre — built up in gesso before gilding, so the pattern can be read by touch as well as sight.",
    "The surface is a collision of techniques: smooth oil for flesh, patient stylus-incised gold for ornament, small raised enamel studs for jewels."
};
static const char *const klimtius_compositio[] = {
    "The head is centred slightly high in the frame; the patterned body fills the entire lower two-thirds, top to edge.",
    "The figure is pushed to the right third of the picture, the gold ornamental field extending leftward to the frame edge without interruption.",
    "The face and hands occupy only about fifteen percent of the picture's total surface; all remaining area is given to the ornamental field.",
    "The figure is frontally placed, its bilateral symmetry exact except for the patterning, which is asymmetric in a studied way from side to side.",
    "The silhouette of the figure is perfectly contained within a tall rectangle; outside that rectangle is only continuous gold ornament."
};
static const Stylus stylus_klimtius = {
    klimtius_media, N_OF(klimtius_media),
    klimtius_figurae, N_OF(klimtius_figurae),
    klimtius_motiva, N_OF(klimtius_motiva),
    {
        [PAL_CALIDA]    = "The colour is beaten gold and soft olive-rose, with accents of warm madder at the lips and cheeks.",
        [PAL_FRIGIDA]   =
            "The ornament is worked in silver leaf, slate blue, and cold mint green, set against very pale flesh.",
        [PAL_SATURATA]  = "Emerald, ruby, and sapphire enamels are set into the gold field at jewellery intensity.",
        [PAL_MUTA]      = "The gold is dulled to an aged brass and the pattern colours are smoke, dust-rose, and lichen grey.",
        [PAL_MONOCHROMA] =
            "The whole picture is worked in graded gold and black alone, with only the flesh left in a single warm ivory note.",
        [PAL_PRIMARIA]  =
            "The pattern squares alternate pure red, yellow, and blue against the gold field in strict repetition.",
        [PAL_TERREA]    =
            "The gold is laid over an olive-brown bolus that shows through as warm earth where the leaf is worn thin."
    },
    {
        [FUN_PLANUM]     = "Behind the figure there is only a flat field of worked gold, unbroken from frame to frame.",
        [FUN_ORNATUM]    =
            "The entire ground behind the figure is a dense ornamental wall of spirals, rosettes, and small eye shapes, worked in gold and black.",
        [FUN_PAESAGIUM]  =
            "Far behind the ornamental body, a suggestion of a small alpine meadow appears through a doorway-shaped opening in the gold.",
        [FUN_ABSTRACTUM] =
            "The ground is a drift of disconnected gold rectangles on black, reading as pattern rather than as a place.",
        [FUN_TENEBROSUM] =
            "The gold is laid over a near-black ground that shows in the interstices, so the picture glows from darkness.",
        [FUN_LUMINOSUM]  = "The gold is laid over a white ground and extended brightly to every edge of the panel."
    },
    klimtius_lumen, N_OF(klimtius_lumen),
    klimtius_texturae, N_OF(klimtius_texturae),
    klimtius_compositio, N_OF(klimtius_compositio),
    "Gold leaf is applied in physical sheets; the pattern is incised into it with a stylus, so the surface carries real relief of less than a millimetre."
};

/* ============================================================
 * mondrianus — reticulum orthogonale
 * ============================================================ */
static const int mondrianus_media[] = { MED_OLEUM };
static const char *const mondrianus_figurae[] = {
    "A recognizable frontal portrait of a person remains clearly visible — this is unmistakably a human head and shoulders, not an abstract painting — but the features have been stylized into flat rectangles of primary colour separated by thick black horizontal and vertical lines. The eyes sit as two small blue squares where the eyes are; the lips sit as a short red horizontal bar where the mouth is; the nose sits as a single vertical strip where the nose is. The person is immediately readable.",
    "The subject is painted as a simplified portrait of a real person: the skin is a single flat field of creamy off-white, the hair a solid black rectangle capping the top of the head, the eyes two small blue squares, the lips a single red horizontal bar. The overall silhouette of the head, shoulders, and neck is unmistakably human.",
    "A human head and shoulders, frontal and symmetrical, are fully legible — this is clearly a portrait of a specific person, not an abstract composition — but every curve in the body has been straightened into horizontals and verticals. The round of the face has become an octagonal silhouette; the curve of the jaw has become a stepped black line; the arcs of the eyebrows have each become a single small horizontal bar.",
    "The face, still plainly a human face and still facing the viewer, is divided by four heavy black lines into enclosed flat fields: the eye-fields are two solid rectangles of cobalt blue, the mouth-field is one rectangle of cadmium red, the rest of the face is a pale cream flesh-tone. The hair appears as a single flat black field above the forehead.",
    "A clear portrait of a person is preserved — head, neck, shoulders, collar all legible — but the entire figure has been subdivided by a black-line grid. Each resulting cell carries a single unmodulated colour: the cells of the face are warm flesh tones, the cells of the hair are black, the cell at the mouth is red, the cells at the eyes are blue. The viewer reads a person first and a grid second.",
    "The whole portrait is visibly of a single human being and is laid out frontally and symmetrically; every edge of face, hair, collar, and garment has been re-drawn as a straight horizontal or vertical black line, and every surface between the lines has been filled with one flat unmixed colour from a narrow primary palette.",
    "The head is still a head, its silhouette clearly readable as a portrait: the eyes, nose, mouth, and ears are all present in their correct positions. But each of these features has been reduced to a single flat rectangle filled with one primary colour, and the boundaries of the features have been re-drawn as black lines intersecting at strict right angles.",
    "An unambiguous frontal portrait: a roughly circular head is enclosed within an orthogonal grid, the internal features (eyes, nose, mouth) translated into coloured rectangles at the correct anatomical positions. The grid does not abstract the portrait away — it sits on top of it like a scaffold — and the viewer sees first a person, then the orthogonal framework.",
    "The subject's face remains recognizable as the face of a real person, painted frontally, both shoulders square to the viewer. The facial planes — forehead, cheeks, jaw — have each been given a single flat colour bounded by black line. The red of the lips and the blue of the eyes are the picture's strongest chromatic notes, and the hair is a solid unmixed black field.",
    "The picture is first and foremost a portrait: a clear human face looks out of it, head and shoulders filling the upper two-thirds of the frame. Over and around this portrait the painter has laid a strict orthogonal grid in heavy black line, and filled selected resulting cells with pure red, pure yellow, or pure blue. The grid decorates and stylizes the portrait but never erases it."
};
static const char *const mondrianus_motiva[] = {
    "a small square of pure cadmium red, 6 cm on a side, sits exactly where the left eye would be",
    "a narrow yellow bar, 4 cm by 14 cm, runs vertically along the centre of the former neck",
    "one cobalt blue rectangle, 12 cm by 8 cm, anchors the lower-right corner of the field",
    "the single thickest black line in the picture crosses horizontally at shoulder height and is 12 mm wide",
    "two black lines meet at a perfect right angle at the chin; neither line extends past the intersection by more than a millimetre",
    "all black lines run either floor-true horizontal or wall-true vertical; no diagonal appears in the picture at any scale",
    "a tiny red square, 3 cm on a side, sits isolated in the upper-left corner of the picture, touched by no line",
    "a broad yellow rectangle, 10 cm by 18 cm, dominates the lower-right quadrant of the picture",
    "a single small blue square, 5 cm on a side, sits exactly at the picture's geometric centre",
    "the black lines never touch the picture's outer edge; each stops 4 cm short, leaving a narrow white margin around the whole composition",
    "a very thin black line (2 mm) crosses the picture vertically just off-centre, dividing it into two slightly unequal halves",
    "a single grey rectangle — the only grey in the picture — sits in the middle-left, dimensioned 8 cm by 8 cm",
    "every black line terminates exactly at another black line or at the picture's outer frame; no line dead-ends in open colour"
};
static const char *const mondrianus_lumen[] = {
    "No light source is implied; every coloured field is flat and shadeless, lit by an abstract, directionless illumination.",
    "The white fields read as pure light; the coloured fields read as pure colour; neither casts or receives a shadow.",
    "The picture is lit as though by a technical diagram: uniform brightness across every field, with no tonal modulation anywhere.",
    "Colour itself carries all the weight of illumination; the red, yellow, and blue are calibrated to read at identical apparent brightness.",
    "No highlight, no shadow, no gradient; the picture admits only flat fields and their hard black edges."
};
static const char *const mondrianus_texturae[] = {
    "The black lines are laid in with a flat brush against tape; their edges are mechanical and perfectly hard. The coloured fields are opaque, flat, unshaded oil, applied in two or three stacked coats.",
    "The white fields show a faint, carefully regular brush-grain; the coloured fields are worked smooth and matte.",
    "Each colour field has been repainted three or four times to flatten out every brushmark; under raking light, only the faintest trace of weave remains.",
    "The black of the lines is an unusually deep, slightly matte black — built up from layered thinned oil rather than direct mass-tone from the tube.",
    "The picture's only physical texture is at the line-edges, where the tape pulled away a fraction of the field paint, leaving a clean mechanical step."
};
static const char *const mondrianus_compositio[] = {
    "The lines partition the picture asymmetrically: the largest field is the upper-right white, about a third of the canvas; the smallest is a red square of about 5 cm at the lower-left.",
    "The grid is deliberately unbalanced — no two fields are the same size, and no field's dimensions repeat elsewhere in the picture.",
    "The composition's visual weight is anchored in the lower-right corner by a large blue rectangle; the remainder of the picture tilts slightly upward and leftward against this weight.",
    "The picture reads as a single worked-out rectangle of proportions roughly 3:4, containing exactly seven fields: four white, one red, one yellow, one blue.",
    "Black lines of four different thicknesses (2 mm, 4 mm, 8 mm, 12 mm) are deployed in a strict hierarchy — thicker lines carry larger spatial decisions."
};
static const Stylus stylus_mondrianus = {
    mondrianus_media, N_OF(mondrianus_media),
    mondrianus_figurae, N_OF(mondrianus_figurae),
    mondrianus_motiva, N_OF(mondrianus_motiva),
    {
        [PAL_CALIDA]    =
            "Red and yellow do all the colour work; blue is withheld entirely. The rest of the picture is white and black.",
        [PAL_FRIGIDA]   =
            "Blue does all the colour work; red and yellow are withheld. The rest of the picture is white and black.",
        [PAL_SATURATA]  =
            "The coloured fields are pure, uncut primaries at maximum saturation: signal red, canary yellow, cobalt blue.",
        [PAL_MUTA]      = "The primaries are softened to brick red, mustard, and slate blue against a warm off-white.",
        [PAL_MONOCHROMA] =
            "All colour is suppressed; the picture is composed only of black lines on white, with one field in grey.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue are set pure against black lines and white fields — no other colour appears anywhere in the picture.",
        [PAL_TERREA]    =
            "The primaries are replaced by Venetian red, yellow ochre, and Prussian blue, giving the picture a warmer, older key."
    },
    {
        [FUN_PLANUM]     =
            "There is no background separate from the figure; the grid extends to all four frame edges as a single continuous partition.",
        [FUN_ORNATUM]    =
            "Additional black lines subdivide the white fields into a finer inner grid, giving the picture an almost architectural density.",
        [FUN_PAESAGIUM]  = "No landscape is present; the grid is absolute and admits no depth cue at all.",
        [FUN_ABSTRACTUM] =
            "The grid itself is the whole world of the picture; there is no figure-ground split beyond the lines.",
        [FUN_TENEBROSUM] = "The white fields are darkened to a warm graphite grey; the grid reads against a low, heavy light.",
        [FUN_LUMINOSUM]  = "The white fields are clean, cold, and bright; the grid reads as a diagram lit by a laboratory."
    },
    mondrianus_lumen, N_OF(mondrianus_lumen),
    mondrianus_texturae, N_OF(mondrianus_texturae),
    mondrianus_compositio, N_OF(mondrianus_compositio),
    "The black lines are taped and painted with a flat brush to yield mechanical, perfectly sharp edges; the coloured fields are opaque, flat, and without modulation."
};

/* ============================================================
 * vermerus — aula quieta, lumen unius fenestrae
 * ============================================================ */
static const int vermerus_media[] = { MED_OLEUM, MED_TEMPERA };
static const char *const vermerus_figurae[] = {
    "The subject faces the viewer directly, mouth just parted as though about to speak. The right eye catches a single pinpoint white highlight; the left eye is fractionally dimmer.",
    "The face is lit from a high window out of frame at the upper left. The lit side of the forehead is a warm lead-white; the shaded side of the right cheek falls into a cool half-shadow the colour of skimmed milk.",
    "The skin carries small, painted dots of reflected highlight: one on the tip of the nose, one on the wet lower lip, one on the droplet of pearl at the ear.",
    "The head is covered by a simple close-fitting linen coif, its edge finely stitched and falling just over the ears; no turban, no elaborate wrap.",
    "The lips are painted in two dozen small patient strokes; no edge around the mouth is drawn, only suggested by the dark red of the mouth's own shadow.",
    "The subject's gaze is direct but unchallenging, held at the viewer's own height; the pupils are painted in slightly different shades of brown, the left darker than the right.",
    "The skin is painted in translucent layers over a warm ground; the cheek reads not as pigment but as light passing through flesh.",
    "The eyebrows are hardly drawn — each suggested by three or four fine tapered strokes, no more — yet they carry the full weight of the face's expression.",
    "A single soft strand of dark hair has escaped from beneath the head-cloth and lies across the forehead, painted in one single patient stroke 2 cm long.",
    "The subject faces forward with both shoulders square to the viewer; the window light strikes the left cheek and passes across the bridge of the nose into the quieter, cooler half-tones of the right cheek."
};
static const char *const vermerus_motiva[] = {
    "a small silver thimble is worn on the tip of the index finger, catching a single pinpoint of window light at its rounded end",
    "a plain white linen collar opens at the throat in folds so precisely painted that no brushmark is visible",
    "a brass basin sits just out of frame at the lower right; its reflected light warms the underside of the jaw by about a Kelvin",
    "a length of heavy blue-grey wool falls across the near shoulder, its shadow side glazed over with a cool green earth",
    "a small carved ivory hair comb is tucked into the hair at the side of the head, its teeth catching the window light in fine parallel lines",
    "a narrow silver chain holds a plain dull-green enamel pendant at the throat, the pendant no wider than a fingernail",
    "a single sheet of folded paper, held lightly in the fingers, reflects a cool glow back up into the chin",
    "an open folded note lies on a table at the lower edge of the frame, one corner touched by the subject's fingertip, its inked surface too softly blurred to be read",
    "a wooden lute rests unseen in the subject's lap; only the tips of two pegs at the upper end catch the light",
    "a small, glazed blue-and-white Delft ceramic pot stands on a dark tabletop at the right; its lid is ajar by about a finger's width",
    "a single brass pushpin is set into the plastered wall above the subject's shoulder, holding nothing, its shadow a neat elongated ellipse",
    "a heavy woven tapestry, partially rolled back, hangs at the picture's left edge, its folds rendered in soft patient brushstrokes",
    "a scattering of black dots across the white collar — six of them, evenly spaced — is the only patterning in the garment"
};
static const char *const vermerus_lumen[] = {
    "Light enters from a high window to the upper left at about a 40° angle. The subject's left side is warmly lit; the right side is in a cool, quiet half-shadow. No secondary light source is permitted.",
    "A single cool, northern window light falls diagonally across the picture. Every highlight is a discrete, small, round pinpoint of a slightly warmer white than its surround.",
    "The light source is out of the picture to the left and slightly above the subject's head; the shadows it casts on the far wall are long, gentle, and nearly vertical.",
    "The illumination is soft but absolutely consistent — the same cool cloudy-north light falls equally on every surface in the room, with no second light ever admitted.",
    "The shadows are painted not as absences of light but as quiet, warm-brown translucent glazes; light is felt still to pass through them."
};
static const char *const vermerus_texturae[] = {
    "The paint is built up in many thin oil glazes; highlights are added last as tiny impasto points of lead white, standing 0.5 mm above the surface.",
    "The darks are worked as thin, transparent glazes over a warm ground, so that the ground glows faintly through; the lights are dense, opaque, and stippled.",
    "The painter has used a small round brush throughout; no mark is longer than about 6 mm, and most are far shorter.",
    "The final layer of highlights is stippled in tiny impasto dots of lead white; the wet lip, the pearl, the eyes each receive exactly one such dot.",
    "The surface is so patiently worked that there is no single visible brushstroke anywhere — only an accumulated field of small, careful marks."
};
static const char *const vermerus_compositio[] = {
    "The figure fills about two-thirds of the picture's height; a band of plain plastered wall runs above the head for about 15 cm.",
    "The subject is set slightly left of centre; the space at the right shoulder is left deliberately empty, occupied only by the cool plaster wall.",
    "The picture's focal point is the single lit eye; around it the composition is arranged in concentric rings of descending brightness, outward to a dim warm edge.",
    "A single strong diagonal runs from the upper-left window (implied, out of frame) down through the pearl earring and into the dark fold of the shawl at the lower right.",
    "The figure is silent in a deliberately empty room; more than half the picture is given to wall, floor, and air rather than to person."
};
static const Stylus stylus_vermerus = {
    vermerus_media, N_OF(vermerus_media),
    vermerus_figurae, N_OF(vermerus_figurae),
    vermerus_motiva, N_OF(vermerus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm lead white, pale ochre flesh, a muted madder at the lips, and a lemon-yellow cloth accent.",
        [PAL_FRIGIDA]   =
            "The palette is dominated by natural ultramarine blue and cool lead white, with only small passages of muted flesh warmth.",
        [PAL_SATURATA]  =
            "A deep, pure ultramarine turban meets a saturated lead-tin yellow cloth at the shoulder; the flesh is kept neutral between them.",
        [PAL_MUTA]      =
            "The whole picture is kept in quiet halftones: bone white, soft taupe, a dusky rose, and a dulled blue.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone, from bone white highlight to a deep, translucent dark brown shadow.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue are admitted, each desaturated slightly so the picture reads warmly rather than harshly.",
        [PAL_TERREA]    =
            "The palette is raw umber, yellow ochre, bone black, lead white, and a very small touch of natural ultramarine at the cloth."
    },
    {
        [FUN_PLANUM]     =
            "Behind the subject, a plain plastered wall in cool white catches the window light as a soft gradient from upper left to lower right.",
        [FUN_ORNATUM]    =
            "A tooled leather map or a still-life of brass instruments hangs on the wall behind the subject, only partially visible at one edge.",
        [FUN_PAESAGIUM]  =
            "Through a doorway to the left, a narrow view of a red-brick Delft street is visible under a pale, overcast sky.",
        [FUN_ABSTRACTUM] =
            "Behind the subject is only the undifferentiated cool wall, with no object, map, or window allowed to break it.",
        [FUN_TENEBROSUM] =
            "The wall behind the subject is a deep, warm black, so that only the lit side of the face glows out of it.",
        [FUN_LUMINOSUM]  =
            "The wall behind the subject is a high, clean white lit by a second, indirect window, and the figure is almost backlit against it."
    },
    vermerus_lumen, N_OF(vermerus_lumen),
    vermerus_texturae, N_OF(vermerus_texturae),
    vermerus_compositio, N_OF(vermerus_compositio),
    "The surface is built up in thin transparent glazes over a warm ground; small impasto highlights are stippled last, standing above the surface in tiny physical points."
};

/* ============================================================
 * escherus — tessellatio, recursio impossibilis
 * ============================================================ */
static const int escherus_media[] = { MED_ATRAMENTUM };
static const char *const escherus_figurae[] = {
    "The subject's silhouette breaks at the edges into tessellating black birds that fly outward from the shoulders; as they move away from the body they interlock with white fish facing the opposite direction, with no empty space between them.",
    "The head is reflected in a convex silvered sphere held in the palm of the right hand; the entire surrounding room curves around the reflection, and at the exact centre of the sphere the reflected eye looks straight back at the viewer.",
    "The features of the face are built from interlocking lizards: each cheek is a single lizard; each scale on the cheek is itself a smaller lizard; each of the smaller lizards is, at a yet smaller scale, made of the same lizards.",
    "The picture is divided along a diagonal; the upper half is the subject drawn in black line on white, and the lower half is the negative — white line on black — and the two halves tessellate seamlessly into each other along the diagonal."
};
static const char *const escherus_motiva[] = {
    "behind the shoulder, a stone staircase climbs upward, turns right, climbs again, turns right, climbs again, and arrives at its own starting step",
    "a hand emerges from the sleeve holding a pen that is drawing the other hand; the other hand in turn holds a pen that is drawing the first",
    "a narrow stone waterway runs in a closed loop that rises visibly over the top of the shoulder and returns underneath, with water flowing perpetually downward the whole way",
    "two doorways recede into the background at angles that cannot coexist in a single three-dimensional space",
    "a flock of about twenty small black birds peels off the upper-right corner of the subject's coat and flies outward, becoming smaller and whiter as they recede until they are indistinguishable from the white ground",
    "a lizard climbs out of a flat drawing of a lizard lying on the desk beside the subject, and three steps further on re-enters another flat drawing at the desk's far edge"
};
static const char *const escherus_lumen[] = {
    "The light is not physical light; it is the absence or presence of ink. Black areas are pure black; white areas are pure white; the only halftones are achieved by hatching.",
    "A diffuse, diagrammatic illumination is implied, with no shadows cast in any direction. All form is built from line, not from modelling."
};
static const char *const escherus_texturae[] = {
    "The entire picture is pen-and-ink crosshatch on paper; every halftone is built from parallel strokes at calculated spacing, and no grey tone is achieved by dilution.",
    "The line weight is uniform throughout — a fine, even 0.3 mm — so the picture reads as a single continuous mathematical object rather than as a painting."
};
static const char *const escherus_compositio[] = {
    "The figure occupies the centre of the picture; tessellating motifs radiate outward from it with strict 60° rotational symmetry.",
    "The picture is composed of three interlocking planes that cannot share a single three-dimensional space: the subject's chest, a receding floor, and a tilted ceiling all meet at the throat in a geometrically impossible intersection."
};
static const Stylus stylus_escherus = {
    escherus_media, N_OF(escherus_media),
    escherus_figurae, N_OF(escherus_figurae),
    escherus_motiva, N_OF(escherus_motiva),
    {
        [PAL_CALIDA]    = "The picture is black ink on warm cream laid paper; only the paper tone supplies any warmth.",
        [PAL_FRIGIDA]   = "The picture is black ink on cold pale-grey paper, with no warm element admitted anywhere.",
        [PAL_SATURATA]  =
            "A single area — the reflecting sphere — is worked in saturated colour, while the rest of the picture remains black and white.",
        [PAL_MUTA]      =
            "The ink is diluted in two passes to achieve a soft mid-grey; the picture reads as a quiet graphite drawing rather than a hard line work.",
        [PAL_MONOCHROMA] = "Black ink on white paper; no other colour is admitted anywhere in the picture at any point.",
        [PAL_PRIMARIA]  =
            "Three flat primary fields — red, yellow, blue — are inserted behind the otherwise black-and-white tessellation, visible only through small open gaps in the pattern.",
        [PAL_TERREA]    = "Sepia ink replaces the black, producing a warm brown line on yellowed paper."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure, the white of the paper is allowed to remain uninterrupted to all four frame edges.",
        [FUN_ORNATUM]    =
            "The ground behind the figure is filled from edge to edge with a single tessellating motif — interlocking birds and fish — with no empty space permitted anywhere.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a small Italian hill town is rendered in perspective, but its stairs, balconies, and roofs form a closed loop that a walker could circle forever.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the space itself is impossible: a staircase, a corridor, and a ceiling all meet at a single point that denies three-dimensional consistency.",
        [FUN_TENEBROSUM] =
            "The ground behind the figure is solid black ink; the tessellating motifs are picked out as white reversals cut into the black.",
        [FUN_LUMINOSUM]  =
            "The ground behind the figure is bright white paper, and the tessellating motifs begin only at the very edges of the frame."
    },
    escherus_lumen, N_OF(escherus_lumen),
    escherus_texturae, N_OF(escherus_texturae),
    escherus_compositio, N_OF(escherus_compositio),
    "The entire picture is pen-and-ink line on paper; halftones are achieved exclusively by hatching, and every tessellation interlocks with no empty space between the figures."
};

/* ============================================================
 * kandinskius — figurae geometricae, chromaticae, musicae
 * ============================================================ */
static const int kandinskius_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const kandinskius_figurae[] = {
    "The subject survives only as a loose constellation of coloured geometry: a red disc for the head, a yellow triangle for the torso, two black arcs for the shoulders, and a single sharp blue line for the spine.",
    "The figure has dissolved into a bundle of floating shapes — seven circles of different sizes and colours, three triangles, and a scatter of short black lines — arranged in the approximate territory a head and shoulders would occupy.",
    "A single large red circle, 18 cm across, marks the head. Around it, four concentric black rings of decreasing width radiate outward to about 30 cm, and then break into short tangent lines.",
    "The face is a cluster of six overlapping translucent plates, each a different pure colour; where two plates overlap, a third colour — the optical mix — is painted flat, not blended."
};
static const char *const kandinskius_motiva[] = {
    "a fragment of musical staff five lines wide floats diagonally across the chest, carrying three black quarter-notes at different pitches",
    "a sharp yellow equilateral triangle, 14 cm on a side, pierces the composition downward from the upper edge like a falling blade",
    "a pair of crossed short black lines tethers two floating discs together, the whole assembly hanging as though in zero gravity",
    "a small red-and-green checkerboard, eight squares by eight, is balanced on what would have been the shoulder",
    "a single free black line enters from the upper-left corner, bends twice, and terminates in a dot at the centre of the head",
    "seven short parallel black lines of graded length fan outward from the mouth like a shout made visible",
    "a single large transparent blue disc overlaps the head halfway, the overlap area painted in the mixed violet rather than blended"
};
static const char *const kandinskius_lumen[] = {
    "No light source is represented; each shape is a flat, even, uninflected area of colour, lit by an abstract and directionless illumination.",
    "The picture admits no modelling and no cast shadow; depth is implied only by overlap of shapes and by saturation of colour."
};
static const char *const kandinskius_texturae[] = {
    "The shapes are laid in flat, clean-edged oil; the paint admits no brush grain and no modulation within any single coloured area.",
    "The coloured areas are painted in two opaque coats with crisp, taped edges; only the thinnest black lines retain the mark of the bristle."
};
static const char *const kandinskius_compositio[] = {
    "The major shapes are organised around a single invisible diagonal running from lower-left to upper-right; every form either rests on this diagonal or is tangent to it.",
    "The composition is centrifugal: a dense knot of shapes at the centre throws off smaller satellite forms outward toward each corner of the frame."
};
static const Stylus stylus_kandinskius = {
    kandinskius_media, N_OF(kandinskius_media),
    kandinskius_figurae, N_OF(kandinskius_figurae),
    kandinskius_motiva, N_OF(kandinskius_motiva),
    {
        [PAL_CALIDA]    =
            "The colour is dominated by cadmium red and chrome yellow; blue appears only as a small, sharp accent near the lower edge.",
        [PAL_FRIGIDA]   =
            "The colour is dominated by cobalt and viridian; red appears only as a single small disc somewhere near the centre.",
        [PAL_SATURATA]  =
            "Every shape is filled with pure, unmixed pigment at maximum saturation, set against a flat white ground.",
        [PAL_MUTA]      =
            "The colour is softened to rose-beige, sage, and pale lilac; the forms are geometric but their palette is domestic.",
        [PAL_MONOCHROMA] =
            "The picture is worked in black, white, and a single graded warm grey; all shapes retain their geometry but their colour is withheld.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue fill every coloured shape; no secondary or tertiary colour is admitted anywhere.",
        [PAL_TERREA]    =
            "The shapes are filled with burnt sienna, yellow ochre, and terre verte; the geometry is preserved but the palette has been walked back into the earth."
    },
    {
        [FUN_PLANUM]     = "Behind the shapes there is only a single flat white ground; nothing further is added.",
        [FUN_ORNATUM]    =
            "The ground behind the shapes is itself a wash of fainter coloured geometry — pale circles and translucent rectangles in washed pastels.",
        [FUN_PAESAGIUM]  =
            "Far behind the geometry, a narrow strip of saturated landscape — cobalt hills, yellow fields — is visible at the lower edge of the picture.",
        [FUN_ABSTRACTUM] =
            "The ground is itself a second layer of floating shapes, identical in construction to the figure, so that figure and ground cannot be separated.",
        [FUN_TENEBROSUM] =
            "The shapes are set against a deep, warm black that absorbs their edges and makes the colours read as lit signs.",
        [FUN_LUMINOSUM]  = "The shapes float on a bright, cold white, their coloured areas hovering as if lit from behind."
    },
    kandinskius_lumen, N_OF(kandinskius_lumen),
    kandinskius_texturae, N_OF(kandinskius_texturae),
    kandinskius_compositio, N_OF(kandinskius_compositio),
    "The shapes are laid in with flat, uninflected colour and hard, taped edges; the thinnest black lines are drawn in last, freehand, in a single decisive stroke each."
};

/* ============================================================
 * magrittius — vultus obtectus, substitutio cotidiana
 * ============================================================ */
static const int magrittius_media[] = { MED_OLEUM };
static const char *const magrittius_figurae[] = {
    "The entire face is covered by a smooth pale grey river stone, oval, 22 cm across, that fills the space between collar and hairline; it floats about 3 cm in front of where the face would be, held there by nothing.",
    "The whole head has been replaced by a single still flame, about 25 cm tall, burning silently upright from the collar; it gives off no heat and no smoke, and its colour matches the flesh of the neck exactly.",
    "The face is covered by a folded white linen handkerchief held in place by no visible hand, its upper edge just meeting the hairline, its lower edge falling just to the collar.",
    "The head is the shape of a head but its surface is painted as a clear sky over a low meadow; an identical sky-over-meadow fills the space outside the window behind the figure.",
    "The face has been replaced by the silhouette of a small domestic bird — a robin or a thrush — perched in profile at head-height, the same size as the head would have been, the shoulders continuing normally beneath.",
    "The head has been replaced by a polished wooden artist's mannequin head, blank-featured, the grain of the wood visible across the cheek; the neck and collar continue into flesh and fabric as though nothing were amiss.",
    "The whole head is shown in full, but in place of features there is only a flat painted panel — a rectangle 20 cm by 25 cm — hung at face-height, onto which a small separate picture of a night sky has been painted."
};
static const char *const magrittius_motiva[] = {
    "a grey, evenly-clouded sky identical to the sky outside the window fills the interior of the subject's body",
    "the sleeve of the jacket opens at the wrist onto a dusk forest of bare trees, from which the hand emerges as if from a doorway",
    "a painted inscription in looping cursive runs along the lower edge of the picture, contradicting what is shown above it",
    "a single smooth white egg is balanced on the top of the collar where the neck should emerge, the egg exactly the width of the neck",
    "a broken pane of glass floats horizontally across the chest; painted on each shard is a fragment of the sky behind it",
    "a small rectangular window, 10 cm by 15 cm, has been cut into the forehead; through it a clear blue daytime sky is visible",
    "the subject's cast shadow falls on the wall behind as an entirely different silhouette — a coat on a stand, or a narrow tree",
    "a single wrought-iron door key hangs in mid-air at the level of the throat, where a pendant would be, held by no visible thread",
    "a small open doorway, only 8 cm tall, is cut into the surface of the chest; the floor beyond is tiled in black and white",
    "a flock of small dark birds rises from the collar into the air above the shoulder, in a single rising column",
    "a thin, carefully-painted shelf runs behind the shoulder, and on it rests a single object — a wineglass, a stone, a feather — that casts no shadow"
};
static const char *const magrittius_lumen[] = {
    "The light is an even, overcast, sourceless daylight; every object is lit identically, with only the smallest, softest cast shadows beneath.",
    "A flat, shadowless theatrical light illuminates every object as though each were the only object in the picture."
};
static const char *const magrittius_texturae[] = {
    "The paint is flat, plain, and invisible in its making — as though painted by a capable commercial hand; no bravura stroke is allowed anywhere on the picture.",
    "The surface is matte, evenly worked, and carries no visible brushmark; the picture has the affect of a printed plate rather than of a hand-made painting."
};
static const char *const magrittius_compositio[] = {
    "The subject is centred with quiet precision; the substituting object at the face is placed exactly where the face would be and at exactly its scale.",
    "The composition is frontal, symmetrical, and classically centred — the surreal event is delivered without theatrical framing."
};
static const Stylus stylus_magrittius = {
    magrittius_media, N_OF(magrittius_media),
    magrittius_figurae, N_OF(magrittius_figurae),
    magrittius_motiva, N_OF(magrittius_motiva),
    {
        [PAL_CALIDA]    =
            "The colour is muted — soft warm grey sky, black jacket, white collar, with only the substituting object carrying any warm chromatic accent.",
        [PAL_FRIGIDA]   =
            "The entire picture is keyed cool: slate sky, black wool jacket, pale blue-white collar, and a single cool-toned substitute at the face.",
        [PAL_SATURATA]  =
            "The substituting object at the face is worked at full, unexpected saturation against a restrained grey-and-black background.",
        [PAL_MUTA]      =
            "Every surface is pulled toward grey; even the substituting object at the face has been walked back into the same quiet register.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded grey alone, from ivory at the brightest highlight to bone-black at the jacket.",
        [PAL_PRIMARIA]  =
            "The substituting object at the face is painted in a single pure primary colour — red, yellow, or blue — against an otherwise grey-and-black picture.",
        [PAL_TERREA]    =
            "The palette is earth brown, ivory, and sandstone; the substituting object at the face is a single weathered ordinary thing in the same earthy register."
    },
    {
        [FUN_PLANUM]     =
            "Behind the subject is a plain wall in a single uninflected mid-grey; no architectural detail is permitted to break it.",
        [FUN_ORNATUM]    =
            "Behind the subject, a wooden-framed domestic interior is fully depicted: picture rails, wallpaper in a small repeating leaf motif, a lit sconce at the left.",
        [FUN_PAESAGIUM]  =
            "Behind the subject, a Belgian landscape of low fields and a single dirt road recedes under the same overcast grey sky that fills the subject's body.",
        [FUN_ABSTRACTUM] =
            "Behind the subject, the wall has been replaced by an identical view of the sky; the picture is clearly indoors and clearly not.",
        [FUN_TENEBROSUM] =
            "The room behind the subject is dark brown, nearly unlit; only the substituting object at the face is brought forward by illumination.",
        [FUN_LUMINOSUM]  =
            "The wall behind the subject is a bright, overcast daylight grey, uniform to every edge of the frame."
    },
    magrittius_lumen, N_OF(magrittius_lumen),
    magrittius_texturae, N_OF(magrittius_texturae),
    magrittius_compositio, N_OF(magrittius_compositio),
    "The paint is laid on flat and plain, with invisible brushwork and a matte finish; no gesture of the painter's hand is permitted to draw attention to itself."
};

/* ============================================================
 * pollockius — filamenta guttarum, figura sub velis
 * ============================================================ */
static const int pollockius_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const pollockius_figurae[] = {
    "The subject is buried under dense skeins of flung paint. Only the faintest hint of a shoulder remains, visible as a thicker ridge of dark enamel at the lower-left third of the picture; the head is inferred, not drawn.",
    "A head-shaped void of bare canvas — about 20 cm across, roughly oval — is all that remains at the centre of the picture; everything around it is a mesh of dripped black, aluminium, and dried-blood red.",
    "The figure is inferred only: a denser knot of black-and-silver tracks occupies the upper third where a head and shoulders would be, the density thinning outward to a quieter field at the picture's edges.",
    "No outline exists anywhere. The viewer reconstructs the subject entirely from negative evidence — from where the skeins of paint thin out and where the raw canvas shows through."
};
static const char *const pollockius_motiva[] = {
    "aluminium enamel runs in cold, metallic threads across the underpaint, crossing the picture in several long unbroken arcs",
    "a single cigarette end is pressed permanently into the paint surface near the lower-right edge, its filter still visible",
    "pools of black enamel have dried on the surface with the ridged, wrinkled skin of a slow pour",
    "flecks of sand, crushed glass, and paint-tin scrapings sit embedded in the thickest passages of dripped oil",
    "a single handprint in white oil, palm only, is pressed into the upper-left corner",
    "a length of hemp rope, about 30 cm long, has been laid across the picture and painted over; its ridge is still visible beneath the skeins",
    "three parallel arcs of signal-red enamel cross the picture from upper-left to lower-right like the signature of a single gesture"
};
static const char *const pollockius_lumen[] = {
    "No light source is implied; the picture reads flat under any illumination, with depth generated only by the physical layering of paint.",
    "The picture is lit only by the actual light in the room; its own surface is too flat and too dense to carry an illusion of light."
};
static const char *const pollockius_texturae[] = {
    "The paint stands off the canvas surface in places by up to 8 mm; the skeins are physical, looped rope-like deposits of enamel that have dried in mid-air.",
    "Some passages are puddled and flat; others are layered to a dense crust; the texture of the picture is the picture, and a raking light changes it completely."
};
static const char *const pollockius_compositio[] = {
    "The picture has no centre of gravity; the skeins of paint cover the entire surface with approximately equal density from edge to edge.",
    "The density of paint is slightly higher at the upper third and thins toward the lower corners, implying a figure without ever describing one."
};
static const Stylus stylus_pollockius = {
    pollockius_media, N_OF(pollockius_media),
    pollockius_figurae, N_OF(pollockius_figurae),
    pollockius_motiva, N_OF(pollockius_motiva),
    {
        [PAL_CALIDA]    = "The skeins are burnt orange, signal red, and aluminium silver on a bare cotton ground.",
        [PAL_FRIGIDA]   = "The skeins are cobalt, viridian, and lead white on a cold unbleached linen ground.",
        [PAL_SATURATA]  =
            "The skeins are pure red, pure yellow, and pure blue laid over one another at full saturation; the canvas ground is pulled almost out of sight.",
        [PAL_MUTA]      =
            "The skeins are mixed greys, olive, and a single soft ivory; the picture reads as a quiet tangle rather than as a storm.",
        [PAL_MONOCHROMA] =
            "The skeins are only black and white enamel on raw canvas; no other colour is admitted anywhere in the picture.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue enamel cover the canvas in separate skeins that never quite overlap — where they would, the canvas has been scraped back to raw.",
        [PAL_TERREA]    =
            "The skeins are raw umber, burnt sienna, and yellow ochre; the painting has the colour of earth being thrown over a body."
    },
    {
        [FUN_PLANUM]     =
            "The ground is bare, unsized cotton canvas, visible in small gaps throughout; nothing else lies behind the figure.",
        [FUN_ORNATUM]    =
            "Behind the figure, a second layer of finer skeins is laid in pale colours beneath the dominant ones, visible only at the gaps in the overlay.",
        [FUN_PAESAGIUM]  = "There is no landscape; the canvas itself, raw and unprimed, carries the entire notion of ground.",
        [FUN_ABSTRACTUM] = "The ground is completely abstract; figure and background are both only paint and canvas.",
        [FUN_TENEBROSUM] =
            "The canvas has been soaked with a dark stain before the skeins were thrown; the picture reads out of near-black rather than out of white.",
        [FUN_LUMINOSUM]  =
            "The canvas is bright raw cotton, left mostly bare; the skeins read as dark tangle on an almost glaring ground."
    },
    pollockius_lumen, N_OF(pollockius_lumen),
    pollockius_texturae, N_OF(pollockius_texturae),
    pollockius_compositio, N_OF(pollockius_compositio),
    "The canvas is laid flat on the floor, unsized and unstretched; the paint is poured, flung, and trailed from above with sticks and hardened brushes; no brush is ever drawn across the ground."
};

/* ============================================================
 * picassonus — cubismus analyticus, plana fracta
 * ============================================================ */
static const int picassonus_media[] = { MED_OLEUM, MED_GOUACHE };
static const char *const picassonus_figurae[] = {
    "The face is simultaneously a frontal view and a left profile, both painted onto the same flat plane with no perspective between them. The frontal eye sits where both eyes would normally sit; the profile eye emerges separately above the far ear.",
    "The head is a construction of flat angular planes of grey, ochre, and umber; each plane is bounded by straight black lines 3 to 5 mm thick, and no plane is modelled with curvature.",
    "The face has been broken along several vertical axes and the fragments shifted up, down, and sideways by a centimetre or two each, so that a horizontal seam runs across the forehead and the two halves of the mouth do not align.",
    "Where a nose would be, there is a single long rectangular plane shaded from pale grey at the top to deep umber at the bottom; where eyes would be, two almond-shaped planes of different sizes sit at different heights.",
    "The back of the head appears on the left side of the face, painted as though seen from behind, with a dark twist of hair; the front of the face remains on the right. Both views share the same plane.",
    "The shoulders are two flat trapezoids of different widths, meeting at a central vertical column that stands in for the neck and chest.",
    "The eyes are painted as though seen from three different angles at once: one full-front and round, one in profile and almond, one closed and horizontal.",
    "The face is a single heavy almond shape, outlined in a dark line 4 mm thick; inside, features are indicated by five or six intersecting straight lines rather than by any modelled form."
};
static const char *const picassonus_motiva[] = {
    "a single pasted fragment of torn newspaper is glued flat into the chest area, its surface scrubbed with a thin grey wash so any print is illegible",
    "a semi-circle of warm yellow slices in from the right edge, suggesting a sun or a plate with no perspective",
    "a cluster of three stencilled black glyph-shapes, belonging to no alphabet the viewer can name, floats free across the forehead",
    "a half-moon of pure black occupies what would have been the left eye socket",
    "a flattened mandolin shape, reduced to its silhouette, is tucked against the chest beneath the chin",
    "a painted pipe hangs from the lower lip at an impossible angle; its bowl points back at the face",
    "the ear has been detached from the side of the head and reattached 6 cm lower, upside down",
    "an angular black Z-shape represents the hair, rising from the top of the head as if a single lightning bolt",
    "a fragment of corrugated cardboard is collaged into the chest area, its ridges still visible under a thin grey wash",
    "two angular painted stencil-shapes in red float free above the right shoulder, their forms suggesting letters of some unnamed alphabet but resolving into none",
    "a small gridded piece of fishing net is glued over one cheek and painted flat over, so the plane beneath shows through the mesh",
    "a cluster of three painted black nails points inward toward the throat from three different directions",
    "a single bent copper wire is painted in perfect flat silhouette running from the top of the head to the lower edge of the picture"
};
static const char *const picassonus_lumen[] = {
    "No single light source is implied; each plane is shaded as though independently lit, and the lights of adjacent planes often contradict each other.",
    "Light and shadow are painted as flat, graded grey areas, not as smooth transitions; each plane has a light half and a dark half divided by a hard line.",
    "The face is lit from the front, but every plane also carries a small dark shadow along one of its edges regardless of where the light would fall."
};
static const char *const picassonus_texturae[] = {
    "The paint is applied flat and matte in large, deliberate strokes; the grain of the brush is visible within each plane but the plane itself is bounded by a hard outlined edge.",
    "Some planes have been scumbled with dry paint over a lighter ground, giving a pitted surface; others are painted smooth and slick.",
    "Collaged fragments of printed paper are glued into some of the planes; the printed patterns show through the thin paint laid over them."
};
static const char *const picassonus_compositio[] = {
    "The figure is organised around a strict central vertical axis, but features either side of it are asymmetric, scaled differently, and shifted vertically against each other.",
    "The picture's plane is divided by a single diagonal line from upper-left to lower-right; above this line the figure is painted from one viewpoint, below this line from another.",
    "No part of the composition recedes in depth; the entire picture reads as a single flat surface of faceted planes, fitted together like a broken mirror reassembled."
};
static const Stylus stylus_picassonus = {
    picassonus_media, N_OF(picassonus_media),
    picassonus_figurae, N_OF(picassonus_figurae),
    picassonus_motiva, N_OF(picassonus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, raw umber, terracotta, and a single sharp vermilion accent, all painted flat against off-white.",
        [PAL_FRIGIDA]   =
            "The palette is lead white, cool grey, slate blue, and a single dull Prussian blue; no warm pigment is admitted.",
        [PAL_SATURATA]  =
            "Saturated fields of pure red, yellow, and blue are set adjacent to one another without mixing, each bounded by a heavy black line.",
        [PAL_MUTA]      =
            "The entire picture is worked in a narrow grey-brown middle range — ivory, mushroom, putty, stone — with only one small accent of pure colour.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded grey alone, from bone white highlight to lamp-black shadow; no colour is admitted.",
        [PAL_PRIMARIA]  =
            "Only pure red, yellow, and blue are used; the planes of the face are filled with these three colours and a black-outlined white.",
        [PAL_TERREA]    =
            "Earth pigments alone — raw umber, burnt sienna, yellow ochre, and an unmixed warm black — do all the colour work."
    },
    {
        [FUN_PLANUM]     = "The background behind the figure is a single flat mid-grey, unmarked, with no illusion of depth.",
        [FUN_ORNATUM]    =
            "The background is a field of small pasted fragments — labels, ticket stubs, printed text — overlaid with thin washes of grey paint.",
        [FUN_PAESAGIUM]  =
            "A flattened landscape, shown from above, runs along the lower edge of the picture: small geometric houses and a river rendered as a single bent ribbon of blue.",
        [FUN_ABSTRACTUM] =
            "The background consists of further faceted planes, identical in construction to the face, so that figure and ground interpenetrate without separation.",
        [FUN_TENEBROSUM] =
            "The background is a deep, warm black; the planes of the figure emerge from it only where they are lightest.",
        [FUN_LUMINOSUM]  =
            "The background is a flat field of high white, pushed to the point where it out-values even the brightest plane of the face."
    },
    picassonus_lumen, N_OF(picassonus_lumen),
    picassonus_texturae, N_OF(picassonus_texturae),
    picassonus_compositio, N_OF(picassonus_compositio),
    "The entire work is painted flat on the picture plane; perspective, modelling, and foreshortening are each refused in favour of simultaneous multi-viewpoint construction."
};

/* ============================================================
 * vangoghus — impasto crassum, spirae flammantes
 * ============================================================ */
static const int vangoghus_media[] = { MED_OLEUM };
static const char *const vangoghus_figurae[] = {
    "The face is built from thick, separate strokes of unmixed oil paint, each stroke 2 to 4 cm long and standing up to 6 mm above the canvas. The strokes spiral outward from the eyes in concentric whorls.",
    "The skin is rendered in parallel short strokes of cadmium orange, chrome yellow, and unmixed viridian; the green is visible in the shadows of the jaw and under the cheekbones without being blended.",
    "The hair is a mass of curling impasto brushstrokes in burnt umber and sulphur yellow, each stroke twisting like a small flame; the hairs are individually sculpted, not painted flat.",
    "The beard is constructed of hundreds of short parallel strokes in ochre, rust, and cold white, laid down in rows so thick that their ridges catch the light in physical ridges.",
    "The eyes are heavily outlined in cobalt blue and stare directly at the viewer; the irises are painted with short comma-shaped strokes that radiate from the pupil.",
    "The entire face is built of strokes so thick and distinct that the contour of the head is only readable at a distance; close up, the face dissolves into its individual brushmarks.",
    "The neck and throat are painted in vertical strokes of raw sienna and pale olive, each about 3 cm long; the strokes do not meet but are laid in parallel rows with visible canvas weave between them."
};
static const char *const vangoghus_motiva[] = {
    "the collar of the jacket is turned up and painted in thick, flat strokes of dark Prussian blue; its edge is ridged with impasto",
    "a large yellow garden flower rests against the collar, its petals rendered in curling strokes of chrome and ochre; it is not a sunflower and not pinned, only leaning",
    "a neckerchief of coarse blue cotton is knotted loosely at the throat, painted in short rows of parallel strokes",
    "tall narrow dark plants rise in the distance behind the shoulder, each painted as a twisting column of short curling strokes of deep green",
    "a scattering of small swirling discs of paint floats in the dark passages of the background, each a different size, each painted in a curl of white and chrome yellow",
    "a soft flat wool cap rests on the head at a gentle angle, its body painted in parallel strokes of dull ochre, its brim catching the window in a single pale line",
    "the far ear is half-hidden by a curling stroke of hair; the near ear is painted plainly and without incident",
    "a quill pen and a folded sheet of paper lie partly visible at the lower edge of the picture, the paper's lines rendered as long curling black strokes",
    "a single lit candle rises behind the shoulder, its flame painted in a knot of yellow and vermilion impasto",
    "a rough wooden chair-back is visible behind the figure, its spindles painted as six short vertical strokes of warm brown",
    "a row of three short impasto strokes in acid yellow crosses the forehead just below the hairline",
    "a single thick dab of cadmium orange sits at the centre of the lower lip",
    "a simple earthenware jug, painted in warm ochre with a darker outline, stands at the lower-left edge",
    "a knotted kerchief of rough linen is tied loosely at the throat, its folds painted in short vertical strokes of two blues",
    "a plain wooden wall crosses behind the shoulder in rough vertical strokes of ultramarine and umber"
};
static const char *const vangoghus_lumen[] = {
    "The light is carried entirely by the colour of the paint — each stroke's value is set by its hue, not by modelling. Yellow and orange are the picture's highlights; blue and green are its shadows.",
    "A hot, southern noon light is implied, but no cast shadows are drawn; the picture is uniformly lit and every feature glows from within its own paint.",
    "Light and shadow are painted as contrasting unmixed pigments laid side by side; from a distance the eye mixes them into form, but up close every stroke is its own hue at full saturation."
};
static const char *const vangoghus_texturae[] = {
    "The paint stands physically off the canvas in ridges up to 6 mm high; under raking light the picture casts its own small shadows from every stroke.",
    "Each brushstroke is visible as a distinct, sculpted object; the painter's gesture is preserved as a physical record on the picture's surface.",
    "The canvas has been loaded to the point that the weave is invisible under the paint; only at the extreme edges can the raw fabric be seen."
};
static const char *const vangoghus_compositio[] = {
    "The figure is centred; behind the head, spiralling strokes radiate outward to the frame edge, forming a kind of halo of moving paint.",
    "The head occupies a ring of high-energy short strokes; the collar and chest below fall into quieter, longer strokes that run vertically downward.",
    "The entire picture is unified by a single tempo of stroke — short, confident, slightly curling — repeated across every surface with only the colour changing between regions."
};
static const Stylus stylus_vangoghus = {
    vangoghus_media, N_OF(vangoghus_media),
    vangoghus_figurae, N_OF(vangoghus_figurae),
    vangoghus_motiva, N_OF(vangoghus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is chrome yellow, cadmium orange, and vermilion, with a single cobalt accent at the eyes and collar.",
        [PAL_FRIGIDA]   =
            "The palette is dominated by cobalt and ultramarine, with small areas of unmixed viridian and only a single passage of pale flesh warmth.",
        [PAL_SATURATA]  =
            "Every stroke is laid down at pigment-jar saturation; no colour has been toned with white or grey, and no two adjacent strokes share a hue.",
        [PAL_MUTA]      =
            "The colour is pulled down toward sage, dust-yellow, and a cold ivory; the paint is still thick but the chroma has been walked back.",
        [PAL_MONOCHROMA] =
            "The picture is worked entirely in graded ultramarine and white, with a single sulphur-yellow accent at the pupils.",
        [PAL_PRIMARIA]  =
            "Pure red, yellow, and blue are used for almost every passage; the secondary colours appear only where two primaries physically overlap in the wet paint.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, yellow ochre, and terre verte, with only a single cobalt accent for the eyes."
    },
    {
        [FUN_PLANUM]     =
            "The background is a single flat-but-brushy field of Prussian blue, worked in short horizontal strokes edge to edge.",
        [FUN_ORNATUM]    =
            "Behind the figure, a wallpaper of small impasto yellow flowers on a cobalt ground covers the entire plane.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a field of wheat in impasto yellow strokes stretches to a horizon crossed by a single line of dark cypresses.",
        [FUN_ABSTRACTUM] =
            "The entire background is a whirling field of concentric spiral strokes in blue, green, and white, radiating outward from the head.",
        [FUN_TENEBROSUM] =
            "The background is a deep warm black worked in heavy horizontal strokes; the figure glows against it in hot orange and yellow.",
        [FUN_LUMINOSUM]  =
            "The background is a high cobalt-and-white field shot through with short parallel lines; the picture reads as though lit from behind."
    },
    vangoghus_lumen, N_OF(vangoghus_lumen),
    vangoghus_texturae, N_OF(vangoghus_texturae),
    vangoghus_compositio, N_OF(vangoghus_compositio),
    "The paint is laid on straight from the tube in thick impasto strokes; no stroke is blended into another, and the physical relief of the paint is integral to the image."
};

/* ============================================================
 * warholus — ars popularis, serigraphia plana
 * ============================================================ */
static const int warholus_media[] = { MED_ACRYLICUM };
static const char *const warholus_figurae[] = {
    "The face is reduced to three flat tones: a single hot pink for the lit areas of skin, a single lime green for the mid-tones, and pure black for the shadow edges. No gradient is admitted anywhere.",
    "The head is printed in flat black onto a brightly coloured acrylic ground; the printing registration is slightly off, so the black outline is displaced by 3 mm from the colour beneath.",
    "The skin is a single unmodulated flat field of fuchsia; the lips are a single unmodulated field of acid yellow; the eyes are simple black ovals with no iris detail.",
    "The entire figure is rendered in the language of a silkscreen print: areas of colour pure and flat, boundaries defined by a black key line that does not quite line up with the colour beneath.",
    "The hair is a single flat field of one saturated colour — canary yellow, electric orange, or chartreuse — with the individual locks drawn in as simple black lines over it.",
    "The face is split vertically down the centre; the left half is printed in one colour scheme (pink skin, yellow hair), the right half in another (green skin, orange hair)."
};
static const char *const warholus_motiva[] = {
    "a large areole of flat hot pink, 30 cm across, sits behind the head like a pop-art halo",
    "the lips are printed in unmixed cadmium red at a saturation level that reads as commercial rather than handmade",
    "the eyeshadow is a single slab of aquamarine flat acrylic, painted straight across both eyelids from one temple to the other",
    "the shirt is a field of repeated printed flowers — pink, yellow, orange — each flower identical, each rotated 90° from the next",
    "the image is overprinted with a slightly misregistered yellow screen, so that every edge is doubled with a thin yellow ghost",
    "a tall, generic stylised product bottle — unnamed, unlabelled — stands at the shoulder in flat black-on-white with no shading",
    "a band of eight identical small dots in saturated chrome yellow runs across the forehead in a straight horizontal line",
    "the entire image has been printed onto a single flat field of hot orange, leaving a narrow margin of the orange visible around every edge of the head"
};
static const char *const warholus_lumen[] = {
    "No light source is implied; every colour is laid flat at constant value, and no modelling appears anywhere on the face or body.",
    "The illusion of light is produced only by the placement of high-value colours (yellow, white) next to low-value ones (black, purple); no gradient is used.",
    "The picture is lit as a printed page is lit — evenly, commercially, with no atmosphere."
};
static const char *const warholus_texturae[] = {
    "The surface reads as silkscreened: flat acrylic colour laid over a canvas, with a separate black screen printed on top. The two layers do not quite align.",
    "The colour is deposited in a single thin flat coat; the weave of the canvas is visible through the paint, which has a slight matte quality.",
    "The black line of the figure is distributed unevenly — thick in places, thinned to almost nothing in others — as if a screen had clogged and cleared during the print run."
};
static const char *const warholus_compositio[] = {
    "The figure is centred frontally and is rendered at the scale of a commercial advertisement, not a painting; no painterly asymmetry intervenes.",
    "The composition is printed as though for reproduction: all major colours are set out in large flat areas with no internal detail, and the key-line black defines every edge.",
    "The picture sits just off square; the head is bisected by the vertical mid-line and centred within a single bright field of flat colour."
};
static const Stylus stylus_warholus = {
    warholus_media, N_OF(warholus_media),
    warholus_figurae, N_OF(warholus_figurae),
    warholus_motiva, N_OF(warholus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is hot pink, tangerine, and canary yellow against a warm orange ground; every colour is unmixed and unshaded.",
        [PAL_FRIGIDA]   =
            "The palette is aquamarine, teal, and pale lavender against a sharp ice blue; no warm pigment is admitted.",
        [PAL_SATURATA]  =
            "Every colour is set to maximum saturation — fuchsia, lime, electric orange, chrome yellow — and laid flat in adjacent unmodulated fields.",
        [PAL_MUTA]      =
            "The saturation is pulled back to sherbet tones — melon, pistachio, dusty lilac, cream — still flat, still printed, but no longer aggressive.",
        [PAL_MONOCHROMA] =
            "The entire image is printed as a single black screen over a flat white canvas; only the line carries any information.",
        [PAL_PRIMARIA]  =
            "Pure red, yellow, and blue are set as three separate flat fields filling the face, with black used only for the key-line edges.",
        [PAL_TERREA]    =
            "The palette is rust, mustard, avocado, and burnt cream — a seventies print-advertisement key, all colours flat and all unmixed."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of one saturated colour, unmarked, extending to every frame edge.",
        [FUN_ORNATUM]    =
            "Behind the figure, a repeated printed pattern — identical flowers, dollar signs, or cans — tiles the entire plane.",
        [FUN_PAESAGIUM]  =
            "No landscape is represented; a printed backdrop (a city skyline, a studio curtain) stands in for it in flat silhouetted colour.",
        [FUN_ABSTRACTUM] = "Behind the figure, further misregistered colour fields overlap one another; no depth is implied.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a single flat black screen; the figure's bright colours read as neon against it.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a single flat field of printer's white, illuminated with commercial photographic evenness."
    },
    warholus_lumen, N_OF(warholus_lumen),
    warholus_texturae, N_OF(warholus_texturae),
    warholus_compositio, N_OF(warholus_compositio),
    "The image is constructed by flat-screened colour fields overlaid with a black key line; registration is deliberately imperfect, giving every edge a ghost of another colour beneath."
};

/* ============================================================
 * schieleus — figura gracilis, contour acer
 * ============================================================ */
static const int schieleus_media[] = { MED_OLEUM, MED_GOUACHE };
static const char *const schieleus_figurae[] = {
    "The face is painted in a raw, emaciated register: jaundiced yellows and chalky whites laid over a hollowed-out cheek. A single hard black contour line, 2 mm thick and drawn in one unbroken gesture, defines the outside of the head.",
    "The skin is modelled in patchy washes of green, ochre, and bruised violet; the flesh reads as though it were bruised or unwell. The knuckles and collarbones are drawn in hard brown line.",
    "The hair is rendered as a spiky, ragged halo of dark strokes pulled outward from the scalp in all directions; no lock is smoothed or combed.",
    "The eyes are oversized, ringed in dark purplish shadow, and stare directly out of the picture with an intensity that does not quite resolve into an emotion.",
    "The fingers are unnaturally long and thin, splayed against the upper chest, each finger outlined in a single hard contour with the nail picked out in dry white.",
    "The mouth is a small, hard, pinched line; the teeth are not shown. The edge of the jaw is defined by a single decisive black stroke that does not forgive itself.",
    "The skin is painted flat in patches that do not quite meet; small areas of unpainted paper (or raw canvas) are left visible between the patches, reading as negative space.",
    "The subject is painted with the hard confident Schiele contour but in a healthy register: warm peach and gold flesh, a steady engaged gaze, a relaxed full mouth. The decisive black contour line remains, and the surface still shows expanses of bare paper around the figure, but the skin reads vital, unblemished, and attractive.",
    "The figure is lean but strong and handsomely rendered: the face is painted in warm alive flesh tones bounded by a single unbroken black line, the eyes alert, the mouth softly closed, the jaw clean. The graphic economy of Schiele — hard contour, open ground, patchy flesh — is preserved, but the body beneath is obviously healthy.",
    "A lively, attractive subject rendered in Schiele's language of hard line and open ground: bright clear eyes, a warm flush at the cheek, a confident direct gaze. The contour remains a single confident black stroke; the ground remains largely bare; but the flesh is plainly that of a fit young person rather than an invalid."
};
static const char *const schieleus_motiva[] = {
    "a length of rough brown drapery is pulled tight around the upper body, its folds rendered in broken, angular strokes",
    "the collar of the shirt is unbuttoned and falls open asymmetrically, one side curling outward and one pressed flat",
    "a single strand of dark hair falls across the forehead in a hard diagonal stroke",
    "the knuckles of both hands are exaggerated in size, each knuckle drawn as a small walnut-shaped lump",
    "dry white paint has been scraped through the flesh tones with the wooden end of the brush, exposing hard vertical lines of warm ground colour underneath",
    "a single area of unpainted paper is left exposed at the side of the throat, forming a sharp triangular void",
    "the ribbon at the collar is a raw red stripe, the only concentrated colour in the picture",
    "the nails of the fingers are each given a single white highlight in dry paint, flared at the tip"
};
static const char *const schieleus_lumen[] = {
    "The light is harsh and raking from the upper left, but it does not behave like studio light: shadows are painted as opaque coloured patches rather than as cast forms.",
    "No atmosphere is present; every feature is defined by line and by patch rather than by any illusion of transparent air.",
    "The light seems to be tubercular: it falls on the skin without warming it, revealing every hollow of the cheek and temple."
};
static const char *const schieleus_texturae[] = {
    "The paint is applied thinly, in scraped dry patches; the grain of the paper or canvas is visible through most passages, and the contour line sits on top of everything as the final mark.",
    "In some passages, the wooden end of the brush has been dragged through the wet paint to expose the ground; these scraped lines read as a second, ruined contour.",
    "The surface is deliberately undercoated: whole areas are left as raw paper or thinly stained canvas, and the painted passages float as patches on an empty ground."
};
static const char *const schieleus_compositio[] = {
    "The figure is set against an almost blank ground; large areas of the picture are deliberately empty, and the figure's hard contour reads all the more sharply against this emptiness.",
    "The head and shoulders are contained within a tight, angular silhouette that almost touches three of the four frame edges; the figure feels cramped in its own space.",
    "The composition is asymmetrical: the figure is centred vertically but pushed toward one side of the picture, the other side left as a deliberately empty expanse of bare ground."
};
static const Stylus stylus_schieleus = {
    schieleus_media, N_OF(schieleus_media),
    schieleus_figurae, N_OF(schieleus_figurae),
    schieleus_motiva, N_OF(schieleus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is raw ochre, bruised orange, and a dry burnt sienna; the skin runs to a jaundiced warmth.",
        [PAL_FRIGIDA]   =
            "The palette is grey-green, slate, and chalky white, with only a single stripe of cold red at the lips or collar.",
        [PAL_SATURATA]  =
            "A single saturated passage — a red scarf or ribbon — punctuates an otherwise undernourished palette of ochre, grey, and ivory.",
        [PAL_MUTA]      =
            "The colour is pulled almost entirely out of the picture: grey paper, pale ochre flesh, a single thin red line.",
        [PAL_MONOCHROMA] =
            "The picture is worked in sepia ink wash and black line on cream paper; no colour is admitted anywhere.",
        [PAL_PRIMARIA]  =
            "Primary colours appear only at single small hotspots — a red collar, a yellow button, a blue nail — against an otherwise desaturated sheet.",
        [PAL_TERREA]    =
            "The palette is raw umber, yellow ochre, and a sickly olive green; the whole picture reads as though unearthed rather than painted."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure, the paper or canvas is left almost completely bare, with only a few thin stains of colour bleeding outward from the silhouette.",
        [FUN_ORNATUM]    =
            "Behind the figure, a scatter of rough calligraphic marks — dates, initials, short angular lines — is distributed sparsely across the ground.",
        [FUN_PAESAGIUM]  =
            "A suggestion of a steep, angular Austrian village roofscape is indicated behind the shoulder in a few hard, dry lines.",
        [FUN_ABSTRACTUM] =
            "The ground is raw paper; around the figure, a few irregular patches of washed colour float without clear relation to one another.",
        [FUN_TENEBROSUM] =
            "The ground is a warm blackish wash that gathers around the figure like a close-fitting atmosphere; the figure is barely separated from it.",
        [FUN_LUMINOSUM]  =
            "The ground is a high, chalky, almost glaring white; the figure's contour reads all the more sharply against it."
    },
    schieleus_lumen, N_OF(schieleus_lumen),
    schieleus_texturae, N_OF(schieleus_texturae),
    schieleus_compositio, N_OF(schieleus_compositio),
    "The picture is constructed as line over wash: a thin, stained ground, small patches of opaque colour, and finally a single confident contour line drawn over the top, never corrected."
};

/* ============================================================
 * baconius — carnis imago, cavea vitrea
 * ============================================================ */
static const int baconius_media[] = { MED_OLEUM };
static const char *const baconius_figurae[] = {
    "The face has been dragged sideways by about 4 cm as though a wet rag had been pulled across it; the features are smeared into arcs of wet pigment, but the eyes remain intact and fixed on the viewer.",
    "The mouth is open in a soundless scream: the lips pulled back, the teeth visible as a row of painted bone-white marks, the interior of the mouth a deep crimson void. The rest of the face is less finished, painted in loose blurred strokes.",
    "The head is rendered in thick, half-abraded oil; a dense grey smear occupies where the nose would be, and both cheeks appear as though slashed by a palette knife and then smeared back together.",
    "The skin is the colour of raw meat — bruised pinks, liver browns, and streaks of bone-white — applied in short impasto strokes that do not quite resolve into a face.",
    "One side of the face is sharply painted in photographic realism; the other is reduced to a blur of dragged paint, as though caught in motion. The transition is a single vertical smear.",
    "The entire head is painted as though glimpsed through a pane of smeared glass: features present but displaced, the contour interrupted by visible strokes that do not belong to the face.",
    "The face is painted in Bacon's characteristic dragged and wet-into-wet oil, but the subject beneath reads as handsome and composed: strong clean features, warm full flesh, a steady mouth, clear engaged eyes. The smearing is confined to a single area — a soft drag across one temple — while the rest of the face holds together in dense, warm, confidently-modelled paint.",
    "The subject sits calmly and is painted in a warm, healthy register: a ruddy cheek, a steady bright eye, a full untroubled mouth. The Bacon-style thin glass cage of ochre line still contains the head, and the surrounding room is still a flat unmodulated colour, but the face itself is a confident, attractive likeness — nothing has dissolved.",
    "A handsome subject rendered in Bacon's muscular oil: the flesh is thickly and confidently worked, the paint warm and alive, the eyes sharp and direct. The cage of thin ochre line around the figure and the flat saturated background colour remain, but the figure within is plainly whole, vital, and self-possessed."
};
static const char *const baconius_motiva[] = {
    "the figure is contained within a thin transparent cubic framework of pale ochre lines, 60 cm on a side — a glass cage floating in the picture plane",
    "a single dead-white canvas arrow is painted on the background, pointing at the mouth from upper-right",
    "a pale grey carpet extends from the lower edge of the picture into the middle distance, rendered in flat unvarnished paint",
    "the figure sits on a cheap wooden stool whose splayed legs are visible at the lower edge, each painted in a single crude stroke",
    "a small hypodermic syringe hangs in mid-air beside the face, its needle painted in hard dry white",
    "a mound of pink-grey flesh, unrecognisable but clearly organic, rests on the shoulder where a bird would sit",
    "the lower half of the picture is occupied by a single flat plane of unpainted canvas, deliberately left dry against the worked passages above",
    "a rectangle of reflective black glass 30 cm wide hangs in the space above the head, reflecting nothing at all"
};
static const char *const baconius_lumen[] = {
    "Artificial light — a harsh overhead bulb — hammers the figure from above; cast shadows are hard, dark, and unflattering.",
    "The light is clinical, fluorescent, and colourless; every feature is lit from directly above, producing sharp shadows under the eyes, nose, and chin.",
    "The illumination is that of an operating theatre: uniform, intense, and without atmosphere; there is nowhere in the picture for a form to hide."
};
static const char *const baconius_texturae[] = {
    "The face is worked in a wet-in-wet mix of oil, directly dragged and wiped; the paint has the drag of a finger pulled through butter.",
    "The background is painted in large flat areas of matte unvarnished oil — paint allowed to dry without gloss, giving a dry, papery surface.",
    "Some passages of raw canvas are deliberately left unprimed and unpainted; against the worked passages they read as voids rather than as background."
};
static const char *const baconius_compositio[] = {
    "The figure is centrally placed within a plain, flat-coloured room that extends unbroken to all four edges of the frame.",
    "The figure is enclosed within a thin line drawing of a cube — a space-frame — that defines a volume around the head and shoulders independent of the surrounding room.",
    "The background is divided into two or three large flat rectangles of unmodulated colour, against which the worked figure reads as an interruption."
};
static const Stylus stylus_baconius = {
    baconius_media, N_OF(baconius_media),
    baconius_figurae, N_OF(baconius_figurae),
    baconius_motiva, N_OF(baconius_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is raw-meat pink, liver red, and bone-white against a warm orange-brown ground; the colours are those of a butcher's window.",
        [PAL_FRIGIDA]   =
            "The palette is pale surgical green, slate grey, and cold violet, against a single flat field of clinical blue.",
        [PAL_SATURATA]  =
            "A saturated vermilion interior of the mouth collides with a saturated cobalt background; the flesh is held between them in bruised desaturated pinks.",
        [PAL_MUTA]      =
            "The colour is pulled toward grey, putty, and a dusty rose; even the meat tones are held low in chroma.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded cold grey alone, except for a single passage of saturated blood red at the mouth.",
        [PAL_PRIMARIA]  =
            "The large flat background fields are in pure primary colours; the figure is held entirely in dirtied flesh tones against them.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, and bone black, with a single cold bone-white highlight at the wet lip."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of unmodulated, matte oil colour, extending to all four edges without inflection.",
        [FUN_ORNATUM]    =
            "Behind the figure, a subtle pattern of small evenly-spaced dots (about 4 mm apart) covers the entire plane in a slightly darker shade of the ground.",
        [FUN_PAESAGIUM]  =
            "Through a small painted doorway visible at the far right, a compressed view of an anonymous city street can be seen; the street is empty.",
        [FUN_ABSTRACTUM] =
            "The background is divided into three rectangles of different unmodulated colours — a band of each, like a flag stood on end.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a flat, deep, slightly warmed black; the figure emerges from it only at the wet lip and the whites of the eyes.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a flat, cold, almost violent orange; the figure reads against it as a darker, disintegrating form."
    },
    baconius_lumen, N_OF(baconius_lumen),
    baconius_texturae, N_OF(baconius_texturae),
    baconius_compositio, N_OF(baconius_compositio),
    "The paint is applied both as crisp geometric colour fields and as smeared, dragged flesh; the two are kept in deliberate opposition, and neither is allowed to intrude on the other."
};

/* ============================================================
 * hopperus — sol oblique, silentium Americanum
 * ============================================================ */
static const int hopperus_media[] = { MED_OLEUM };
static const char *const hopperus_figurae[] = {
    "The face is simply modelled in warm flesh tones, but the light falling across it is hard, late-afternoon, and comes in at a steep diagonal from the upper left. The side of the face in shadow is a deep cool umber; the lit side is a pale warm cream.",
    "The eyes look slightly off to one side, not quite meeting the viewer; the expression is unreadable. The mouth is closed and held evenly.",
    "The figure is painted with restraint: flat, opaque colour, no impasto, no decorative brushwork. The edges are soft but the light is hard.",
    "The skin is rendered in four or five tones only — highlight, mid-light, mid-shadow, deep shadow, reflected light — each as a single flat passage separated by a clean boundary.",
    "The hair is a single simple mass of warm brown, its top catching a hard horizontal edge of afternoon sun; the underneath is in deep cool shadow."
};
static const char *const hopperus_motiva[] = {
    "a rectangular patch of hot afternoon sunlight falls across the shoulder and the left side of the neck, its edges geometrically hard",
    "an open window behind the figure admits a vertical bar of hard yellow light that falls diagonally across the chest",
    "a white porcelain coffee cup sits on a counter at the lower-right edge of the picture, its handle turned away from the figure",
    "the collar of the shirt is sharply pressed; its corners catch small points of direct sunlight",
    "a telephone sits on a green-painted table just behind the shoulder; its receiver is at rest",
    "a single red-painted brick is visible in a section of exposed wall behind the figure",
    "the window frame behind the shoulder is painted in slightly peeling white, each imperfection carefully rendered",
    "a small newspaper lies folded on the sill just beyond the shoulder, its print too small to read",
    "a neon sign visible through the window spells a single generic word in sunburnt red"
};
static const char *const hopperus_lumen[] = {
    "The light is late-afternoon sunlight at a low angle, coming through a window out of frame at the upper left; it falls as a hard, flat-edged rectangle across one side of the figure and part of the wall behind.",
    "The illumination is purely directional: where the sun falls, the colour is warm and saturated; where it does not fall, the colour is cool, desaturated, and slightly darker than the lit side by two full values.",
    "A single second hot source — a lamp, a neon sign — may appear, but its effect is localised and does not soften the overall hard diagonal shadow across the figure."
};
static const char *const hopperus_texturae[] = {
    "The paint is applied flat, opaque, and matte; there are no visible bravura strokes, and the boundaries between lit and shadowed areas are clean and hard.",
    "The brushwork is deliberately simple: broad passages of a single colour, separated by hard edges, worked up quickly and left without revision.",
    "The paint has the flat quality of a film still or a stage backdrop; it admits no painterly texture that would draw attention from the stillness of the scene."
};
static const char *const hopperus_compositio[] = {
    "The figure is set in a plain interior; most of the picture is given to empty wall, empty floor, and the single hard rectangle of sunlight crossing it.",
    "A single strong diagonal of shadow crosses the picture from upper-left to lower-right, dividing it into a lit zone and a shaded zone; the figure sits partly in each.",
    "Horizontal and vertical architectural elements — a windowframe, a picture rail, a counter edge — dominate the composition and lock the figure into a strict grid of space."
};
static const Stylus stylus_hopperus = {
    hopperus_media, N_OF(hopperus_media),
    hopperus_figurae, N_OF(hopperus_figurae),
    hopperus_motiva, N_OF(hopperus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm cream, burnt orange, and yellow ochre, with a single cool slate accent at the shaded wall.",
        [PAL_FRIGIDA]   =
            "The palette is cool grey, slate blue, and desaturated olive; the warm passages are reserved only for the small rectangle of direct sunlight.",
        [PAL_SATURATA]  =
            "A single rectangle of saturated chrome-orange afternoon sun falls across an otherwise desaturated field of grey and putty.",
        [PAL_MUTA]      =
            "The palette is entirely pulled toward grey, putty, and cream; even the sunlit passages are held just below saturation.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm grey alone, from bone white in direct sun to warm umber in the deepest corners of the room.",
        [PAL_PRIMARIA]  =
            "The architecture is painted in pure saturated primaries — a red brick wall, a yellow window frame, a blue doorway — while the figure remains in restrained flesh tones.",
        [PAL_TERREA]    =
            "The palette is raw sienna, burnt umber, and ivory black, with a single slate-blue accent at the window or distant wall."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a plain interior wall in a flat warm cream, crossed only by a single hard diagonal shadow.",
        [FUN_ORNATUM]    =
            "Behind the figure is a modest interior: a framed picture on the wall, a partly-visible doorway, a hanging electric lamp, each painted with the same restraint.",
        [FUN_PAESAGIUM]  =
            "Through a window behind the shoulder, a fragment of small-town street is visible: a clapboard house, a bare tree, a patch of sky.",
        [FUN_ABSTRACTUM] =
            "Behind the figure is simply a flat arrangement of three large rectangles — wall, window, shadow — that read as pure geometry first and as a room second.",
        [FUN_TENEBROSUM] =
            "The room behind the figure is nearly dark; only a narrow hot rectangle of afternoon sun falls across the far wall.",
        [FUN_LUMINOSUM]  =
            "The room behind the figure is flooded with direct afternoon sun; the whole wall glows a warm cream and the figure catches every edge of it."
    },
    hopperus_lumen, N_OF(hopperus_lumen),
    hopperus_texturae, N_OF(hopperus_texturae),
    hopperus_compositio, N_OF(hopperus_compositio),
    "The paint is matte, opaque, and simply applied; all effect is produced by the light itself — specifically by its sharp, directional, afternoon character — rather than by any painterly flourish."
};

/* ============================================================
 * hokusaius — xylographia Iaponica, linea firma
 * ============================================================ */
static const int hokusaius_media[] = { MED_GOUACHE, MED_ATRAMENTUM };
static const char *const hokusaius_figurae[] = {
    "The face is drawn in a single confident unbroken black line 1 mm thick, then filled with flat fields of unmodulated colour; no modelling, no shading, no gradient is used anywhere.",
    "The eyes are drawn as narrow almond shapes with a single stroke for each upper lid; the iris is a simple flat circle of black, the pupil not further indicated.",
    "The hair is a single mass of solid, deep, unmixed Japanese black ink, its outline drawn in confident curves; individual hairs are suggested by a few discrete negative-space lines left in white.",
    "The skin is a flat field of unmodulated pale ochre; the cheek has a single subtle block of slightly warmer colour printed over the base where a blush would be.",
    "The mouth is drawn as two confident lines — upper and lower — with the interior a simple flat pale red; no teeth, no modelling.",
    "The figure is entirely a matter of bounded flat colour; there is no three-dimensional illusion, and the edges of the forms are the drawing.",
    "The clothing falls in long, broad, flat sweeps of pattern and colour; folds are represented by a few curving black lines rather than by shading."
};
static const char *const hokusaius_motiva[] = {
    "the sleeves of the kimono are printed with a repeating wave motif in deep Prussian blue and white, each wave drawn with a curling calligraphic black line",
    "a single cherry blossom branch enters the picture from the upper right, each blossom five-petalled and printed in flat pale pink",
    "the obi at the waist is a broad horizontal band of printed pattern — tortoiseshell hexagons, or stylised fans — in two colours only",
    "a small cartouche in the upper corner contains a few columns of calligraphic black script on a pale yellow ground",
    "a crane stands in the lower-left corner, its long black-and-white legs drawn in two confident single strokes",
    "the hair is pinned with three lacquered hairpins, each drawn as a single long stroke with a small black disc at its end",
    "a parasol made of oiled paper rests partly visible behind the shoulder; its spokes are drawn as converging black lines",
    "a small printed seal in red ink is placed in the lower-right corner of the picture, containing two stylised characters"
};
static const char *const hokusaius_lumen[] = {
    "No light source is implied; every colour field is flat and shadeless, and all form is carried by the black line alone.",
    "The illumination is purely notional: a flat, even light that produces no highlights or cast shadows anywhere in the picture.",
    "Areas that would be in shadow are rendered not with darker colour but with more densely spaced black lines printed over the base colour."
};
static const char *const hokusaius_texturae[] = {
    "The surface is that of a woodblock print: thin, matte, water-soluble pigment laid flat, with the grain of the block very faintly visible as horizontal striations through the colour fields.",
    "The black line has been printed from a keyblock: its quality is confident but it carries small interruptions where the block has worn — tiny gaps, tiny hesitations — never corrected.",
    "The colour fields are printed from separate blocks, each in a single flat colour; their registration is near-perfect but a thin sliver of white paper is sometimes visible at the boundary between two colours."
};
static const char *const hokusaius_compositio[] = {
    "The figure is centred and contained within the frame; the composition is flat, symmetrical, and admits no illusionistic depth.",
    "The composition is decorative in its rhythm: pattern answers pattern, curved line answers curved line, and each area of the picture carries roughly equal visual weight.",
    "A single decorative cartouche in a corner of the picture carries calligraphic text; it is not separate from the image but is laid on the same plane as the figure."
};
static const Stylus stylus_hokusaius = {
    hokusaius_media, N_OF(hokusaius_media),
    hokusaius_figurae, N_OF(hokusaius_figurae),
    hokusaius_motiva, N_OF(hokusaius_motiva),
    {
        [PAL_CALIDA]    = "The palette is pale ochre, red madder, and warm cream, with a single accent of sulphur yellow.",
        [PAL_FRIGIDA]   =
            "The palette is dominated by deep Prussian blue, pale celadon, and black, against a warm off-white ground.",
        [PAL_SATURATA]  =
            "The colour fields are printed at high saturation — coral, vermilion, indigo, sap green — each absolutely flat and bounded by black line.",
        [PAL_MUTA]      =
            "The palette is soft mineral tones — celadon, persimmon, oyster — each at half saturation, the overall register quiet and decorative.",
        [PAL_MONOCHROMA] =
            "The picture is printed in black line on cream paper, with no colour added at all; only the keyblock is used.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue are used as colour fields, each flat and unmixed, bounded by the black keyline.",
        [PAL_TERREA]    =
            "The palette is yellow ochre, red iron oxide, and charcoal black, against a natural paper-cream ground."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of unmodulated pale colour, extending to all four edges of the print.",
        [FUN_ORNATUM]    =
            "Behind the figure, a decorative pattern — stylised clouds, or a diapered field of small fans — covers the entire plane.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a flat landscape is drawn in receding bands: a field in one colour, a river in another, a distant mountain in a third, each bounded by black line.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, a stylised abstract pattern of wave-forms, mountain silhouettes, or geometric cloud shapes fills the ground.",
        [FUN_TENEBROSUM] =
            "The ground is a single flat deep Prussian blue, against which the figure's pale flesh and bright clothing read as floating.",
        [FUN_LUMINOSUM]  =
            "The ground is simply the cream of the paper, allowed to breathe around the figure without further printing."
    },
    hokusaius_lumen, N_OF(hokusaius_lumen),
    hokusaius_texturae, N_OF(hokusaius_texturae),
    hokusaius_compositio, N_OF(hokusaius_compositio),
    "The image is produced by woodblock printing: a single black keyline is printed first, and each flat colour field is printed from its own separate block over it; registration is careful but not machine-perfect."
};

/* ============================================================
 * munchius — clamor, caelum sanguineum
 * ============================================================ */
static const int munchius_media[] = { MED_OLEUM, MED_TEMPERA };
static const char *const munchius_figurae[] = {
    "The face is elongated into a soft ovoid, drawn out by wavering contour lines that continue past the silhouette of the head and into the sky behind as echoing parallel curves.",
    "The skin is a sickly greenish-yellow, worked in long curving strokes that follow the contour of the face; the cheekbones are not modelled but suggested by two parallel curved lines of warmer flesh tone.",
    "The mouth is closed and held in a single slightly uneven horizontal line; the lips are painted in wavering strokes of a dull red, just darker than the flesh.",
    "The eyes are wide and hollow, ringed in bruised violet; the pupils are two small black dots set in irises of a sickly pale yellow-green.",
    "The hands are held at the lower edge of the picture, crossed quietly at the waist; the fingers are drawn in long curving strokes that merge at the wrists into the folds of the clothing.",
    "The entire head is outlined by parallel wavering lines that radiate outward into the sky and landscape behind it, so that the subject's contour appears to continue visibly into the air around them.",
    "The brow is painted in two long curving strokes of deep umber that converge over the nose, pulling the whole face into a quiet frown.",
    "The jawline is indicated by a single wavering contour that does not close; it drifts past the chin and continues as a curve down into the collar.",
    "The subject is painted with Munch's wavering parallel strokes and radiating outward contours but rendered as a healthy and attractive figure: warm gold-and-peach flesh, bright alert eyes, a calm closed mouth. The curving radiating lines of the background still pull outward from the head, but the figure's colour is vivid and its expression untroubled.",
    "The head and shoulders are painted with Munch's characteristic curving long strokes, but the flesh is rendered in warm healthy tones of rose and ochre, the eyes clear, the lips a natural dusty rose, the posture upright and self-possessed. The atmospheric sky behind continues to wear its long wavering bands of warm colour.",
    "A striking, quietly confident subject painted in long wavering strokes: the colour is full, the face composed and attractive, the eyes clear and meeting the viewer. The radiating curving contours of the background carry the Munch atmosphere, but the figure itself is plainly a healthy and good-looking person."
};
static const char *const munchius_motiva[] = {
    "the sky behind the figure is painted in thick horizontal bands of blood red, ochre, and burnt orange, each band wavering and continuous from one edge of the picture to the other",
    "the clothing is a heavy black mass, its folds rendered in long curving strokes that echo the wavering contour of the head",
    "a small brooch of pale green paint is pinned at the throat, the only cool accent in the picture",
    "a single dark vertical tree stands in the middle distance behind the figure, painted as a wavering column of near-black",
    "a quiet stretch of cold sea is visible over the far shoulder, painted in parallel horizontal strokes of deep blue-green",
    "a distant dirt path runs across the middle distance behind the shoulder, painted as a single pale curving band",
    "a pale wooden fencepost stands alone in the middle distance, its top catching a single bright stroke of ochre",
    "a single great albatross, wings outspread about a metre and a half, hangs motionless in the darkening sky above the subject's shoulder"
};
static const char *const munchius_lumen[] = {
    "The light is dusk: the sun is out of frame but its last light floods the sky behind the figure with bands of red and orange; the figure itself is partly in shadow.",
    "The light is sickly and atmospheric rather than directional; it seems to emanate from the sky itself, not from any single source, and stains every surface it touches.",
    "There is no cast shadow in the ordinary sense; light and dark are carried by colour temperature — warm sky, cold flesh — rather than by modelled form."
};
static const char *const munchius_texturae[] = {
    "The paint is applied in long, wavering, parallel strokes 3 to 8 cm long; each stroke is a visible gesture, and the whole surface seems to move in slow waves.",
    "The paint is thinned heavily in places so the canvas weave shows through as a second, underlying texture; in other places it is impastoed but never sculpturally thick.",
    "The picture's surface appears worked by a single tempo of hand: long, slow, curving strokes, everywhere, with no passage treated in a different register."
};
static const char *const munchius_compositio[] = {
    "The figure is centred and the sky behind it takes up the upper two-thirds of the picture; the landscape and any secondary figures are confined to a narrow band beneath.",
    "A strong diagonal — a bridge rail, a shoreline — runs across the lower portion of the picture and recedes sharply into the distance behind the figure's shoulder.",
    "Wavering contour lines radiate outward from the figure's head in concentric echoes, so that the figure and its surroundings are tied into a single undulating composition."
};
static const Stylus stylus_munchius = {
    munchius_media, N_OF(munchius_media),
    munchius_figurae, N_OF(munchius_figurae),
    munchius_motiva, N_OF(munchius_motiva),
    {
        [PAL_CALIDA]    =
            "The sky is painted in bands of blood red, cadmium orange, and burnt ochre; the figure stands against it in sickly yellow-green flesh and black wool.",
        [PAL_FRIGIDA]   =
            "The sky is painted in cold bands of Prussian blue, slate, and greenish-grey; the figure's flesh is a pale cold olive against it.",
        [PAL_SATURATA]  =
            "Every band of the sky is laid in at full, unmixed saturation; the figure's flesh is kept desaturated so the sky reads the more aggressively.",
        [PAL_MUTA]      =
            "The palette is pulled to dusk tones — mushroom, grey-violet, pale olive, cold ochre — and the urgency of the picture is carried by gesture rather than colour.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded blue-grey alone, with one single passage of dull red at the mouth or sky.",
        [PAL_PRIMARIA]  =
            "The sky is painted in bands of red, yellow, and blue only; the figure's flesh is painted in a single flat green that is nearly their optical mix.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, yellow ochre, and terre verte; the sky bands are muted into the same earthy register as the figure."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of wavering horizontal strokes, all in one colour band; no landscape or object intrudes.",
        [FUN_ORNATUM]    =
            "Behind the figure, parallel wavering contours radiate outward in echoing rings from the head, filling the entire upper plane.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a cold northern coast recedes into the distance: a low dark shore, a stretch of slate-blue sea, a single dark tree standing on its own in the middle distance.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the sky has dissolved into pure wavering horizontal stripes of colour, with no horizon visible at all.",
        [FUN_TENEBROSUM] =
            "The ground is a deep, heavy near-black, worked in long horizontal strokes; only the figure's face and the sky's lowest band are lit.",
        [FUN_LUMINOSUM]  =
            "The sky behind the figure is a hot, saturated bright orange that fills the upper two-thirds of the picture and casts a warm stain over the figure itself."
    },
    munchius_lumen, N_OF(munchius_lumen),
    munchius_texturae, N_OF(munchius_texturae),
    munchius_compositio, N_OF(munchius_compositio),
    "The paint is applied in long wavering parallel strokes everywhere — face, sky, clothing, landscape — so that a single visual tempo unifies the entire surface."
};

/* ============================================================
 * lichtensteinius — pictura popularis, puncta Benday
 * ============================================================ */
static const int lichtensteinius_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const lichtensteinius_figurae[] = {
    "The face is drawn in the style of a 1960s comic-book panel: thick black outlines 2 to 3 mm wide define every contour, the skin is filled with a regular field of small red dots printed on white, and the hair is a single flat unmixed yellow.",
    "The subject is painted as though a single romance-comic frame has been enlarged into a painting: large tearful eyes with heavy black lashes, parted lips in flat unmixed red, hair in a solid bright field of one primary colour.",
    "The skin is a regular printed field of round red dots, each about 1 mm across, spaced 2 mm centre to centre. A single unbroken black outline 3 mm thick defines the silhouette of the face and every internal feature.",
    "Hair is a single flat uninflected area of pure yellow, over which a few thick confident black wavy lines are drawn to indicate locks; nothing is modelled or shaded.",
    "The cheeks carry a second, denser layer of red dots over the skin dots — giving a printed blush — while the whites of the eyes are perfectly unprinted flat white fields, catching a single sharp rhomboid highlight.",
    "Teeth are a single flat field of pure white, the lips a single flat pure red, a single thin black line separating upper lip from lower. No gradient or modelling is admitted anywhere."
};
static const char *const lichtensteinius_motiva[] = {
    "a speech balloon floats to one side of the head, empty of text but drawn with the characteristic jagged tail pointing at the mouth",
    "a sharp yellow starburst-shape explodes from the upper-right corner of the picture, its rays of varying length reaching a third of the way across",
    "a single graphic tear in the shape of a comma hangs from the lower lash of the right eye, outlined in black and filled in flat blue",
    "a stylised black telephone handset is held up to one ear, its coiled cord curling out of the frame in a flat black spiral",
    "a field of tightly-packed blue dots tiles the upper portion of the background, each dot identical and spaced 2 mm centre to centre",
    "a hard-edged starburst silhouette — the angular outline of a comic-book onomatopoeia with no letters inside — is painted in flat black across the upper edge",
    "the whole image carries a slight cyan misregistration, so that every edge shows a 1 mm ghost of cyan slightly offset",
    "a row of three thin white exclamation-marks runs above the head, each drawn in hard flat white line"
};
static const char *const lichtensteinius_lumen[] = {
    "No light source is represented; the picture is lit as a commercial print page is lit — uniformly, mechanically, without atmosphere.",
    "The illusion of form is produced by dot density alone: tightly packed dots read as shadow, widely spaced dots read as highlight, but nothing is blended.",
    "Every shadow on the face is drawn as a separate flat area bounded by black line and filled with a slightly darker dot-pattern."
};
static const char *const lichtensteinius_texturae[] = {
    "The dots are painted individually in flat unmixed acrylic, each about 1 mm across, printed in unmodulated primary colour onto a flat white ground.",
    "The black outlines are 2 to 4 mm thick and painted with a mechanical, steady hand, as if printed rather than brushed.",
    "The surface is matte and mechanical; no brushmark is visible anywhere, and the whole picture reads as though enlarged directly from a newsprint comic."
};
static const char *const lichtensteinius_compositio[] = {
    "The figure is centred and frontal; the composition is constructed from flat fields of colour and pattern separated by thick mechanical black outlines, as in a comic panel.",
    "The picture is arranged as a single enlarged comic-book frame, with the figure filling most of the picture and a narrow fringe of background showing behind.",
    "The composition is absolutely flat — no depth is implied — and all spatial relationships are indicated by overlap and by dot density rather than by perspective."
};
static const Stylus stylus_lichtensteinius = {
    lichtensteinius_media, N_OF(lichtensteinius_media),
    lichtensteinius_figurae, N_OF(lichtensteinius_figurae),
    lichtensteinius_motiva, N_OF(lichtensteinius_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is hot red dots on white skin, canary-yellow hair, and warm cream — no cool colour is admitted.",
        [PAL_FRIGIDA]   =
            "The palette is pure cobalt blue dots on white, aqua, and flat black outlines; warm notes appear only as small red accents at the lips.",
        [PAL_SATURATA]  =
            "Every colour is laid flat at maximum saturation — signal red, canary yellow, pure cobalt — separated by thick black line, never blended.",
        [PAL_MUTA]      =
            "The saturation is pulled back to soft printing inks — salmon, butter yellow, cornflower — but the flat, dotted, outlined construction remains.",
        [PAL_MONOCHROMA] =
            "The entire picture is printed in black ink on a white ground; all halftones are carried exclusively by varying densities of black dots.",
        [PAL_PRIMARIA]  =
            "Only pure red, yellow, and blue are admitted as colour; the black outlines and white ground complete the palette.",
        [PAL_TERREA]    =
            "The bright pops are replaced by earth halftones — sienna, ochre, and olive dots on cream — though the mechanical dot-and-line construction is unchanged."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of one pure primary colour, unmarked, extending to every frame edge.",
        [FUN_ORNATUM]    =
            "Behind the figure, a field of dense red dots tiles the entire plane; each dot identical in size and position to every other.",
        [FUN_PAESAGIUM] =
            "A stylised landscape is indicated behind the figure in flat fields: a green patch for grass, a flat yellow field for sky, a triangular grey peak, each bounded by black line.",
        [FUN_ABSTRACTUM] =
            "The background is a set of overlapping rays, starbursts, and dot-fields in three primary colours, arranged as for a comic-book panel.",
        [FUN_TENEBROSUM] = "Behind the figure is solid flat black, against which the dotted face reads as sharply lit.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a flat field of pure white, as if on newsprint, extending to every edge without inflection."
    },
    lichtensteinius_lumen, N_OF(lichtensteinius_lumen),
    lichtensteinius_texturae, N_OF(lichtensteinius_texturae),
    lichtensteinius_compositio, N_OF(lichtensteinius_compositio),
    "The image is constructed as a single enlarged comic-book panel: dots printed in primary colours bounded by thick mechanical black outlines, with no painterly gesture permitted anywhere."
};

/* ============================================================
 * modiglianius — vultus oblongus, collum gracile
 * ============================================================ */
static const int modiglianius_media[] = { MED_OLEUM };
static const char *const modiglianius_figurae[] = {
    "The face is stretched into a long soft ovoid, narrower than life; the cheeks taper smoothly to a small rounded chin. The eyes are slim almond shapes, set slightly too close to the nose, and each is painted as a single unbroken flat field of pale blue with no visible pupil.",
    "The neck is noticeably long and slender, almost twice the natural proportion, and is painted in a single smooth curve between the jaw and the shoulders. The whole figure reads as upright, quiet, and elegantly elongated.",
    "The features are simplified and quiet: the mouth is a small rosebud of dusty red, the nose a single long line tipped with a soft shadow, the eyebrows two thin patient arcs. The face carries no tension.",
    "The skin is worked in warm ochres, rose, and olive, built up in patient thin brushstrokes that follow the length of the face; the overall register is confident, muted, classical.",
    "The entire head and neck are enclosed in a single smooth long curving silhouette, broken only at the shoulders where the garment begins; nothing jagged or broken is permitted in the contour."
};
static const char *const modiglianius_motiva[] = {
    "the hair is gathered in a single smooth dark mass pulled back from the forehead, catching one warm highlight along its centre",
    "a thin strand of pearls lies once around the long neck, each pearl no larger than a grain of barley",
    "a simple linen collar opens at the throat in two long clean curves",
    "a single warm rose-coloured flower, half-hidden in the hair, catches the only saturated colour in the picture",
    "the shoulders are wrapped loosely in a dark shawl whose folds are painted in single long simple strokes",
    "a plain wooden chair-back is partially visible behind the far shoulder, painted as two warm brown verticals and a horizontal at shoulder height",
    "the subject's hands, if visible, are long and narrow, the fingers painted as smooth tapered shapes with minimal jointing shown"
};
static const char *const modiglianius_lumen[] = {
    "The light is soft, uniform, and almost atmospheric; the face is modelled gently with warm half-tones, and no hard cast shadow is admitted anywhere.",
    "A quiet studio light falls evenly across the figure; the warm side of the face is an ochre-rose, the cool side a pale green-grey, and the two meet in a soft blended transition."
};
static const char *const modiglianius_texturae[] = {
    "The paint is applied in patient, parallel brushstrokes that follow the length of the face and neck; the surface is smooth but the grain of the brush remains faintly visible throughout.",
    "The darks are worked as thin transparent warm glazes over a warmer ground; the lights are more opaque and slightly built up, but never impasto."
};
static const char *const modiglianius_compositio[] = {
    "The figure is centred and upright; the elongated head and neck carry most of the composition's vertical weight, with the shoulders tapering gently outward beneath.",
    "A strong central vertical axis passes through the nose, mouth, and throat; the figure is frontally symmetrical along this axis and the background is simplified to support the elongation."
};
static const Stylus stylus_modiglianius = {
    modiglianius_media, N_OF(modiglianius_media),
    modiglianius_figurae, N_OF(modiglianius_figurae),
    modiglianius_motiva, N_OF(modiglianius_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, terracotta, and rose flesh against a warm umber ground; the whole picture glows quietly in the yellow-to-red range.",
        [PAL_FRIGIDA]   =
            "The palette is pale olive, grey-green, and cool ivory, with only a single muted rose accent at the lips.",
        [PAL_SATURATA]  =
            "A single deep ultramarine garment meets warm ochre skin at the neckline; the saturation of the two colours carries the whole picture.",
        [PAL_MUTA]      =
            "The entire picture is held in quiet halftones: ivory, taupe, dusky rose, and pale olive, each at half chroma.",
        [PAL_MONOCHROMA] =
            "The picture is worked entirely in graded warm sepia, from bone white at the cheek to dark umber at the neck and hair.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue are admitted; the flesh is rendered as a warm optical mix, the garment as a single saturated primary field.",
        [PAL_TERREA]    =
            "The palette is raw umber, yellow ochre, Venetian red, and terre verte; the whole picture has the register of worked earth."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single plain field of warm ochre or olive, unmodulated, with no object in it at all.",
        [FUN_ORNATUM]    =
            "Behind the figure, a patterned wall of small repeating motifs — diamonds, stars — is suggested in soft warm browns.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, through a small window or doorway, a simplified hill landscape is visible in warm ochres and olives.",
        [FUN_ABSTRACTUM] =
            "The background is a warm, shadowed, largely undefined space of overlapping brushstrokes; no specific object is rendered.",
        [FUN_TENEBROSUM] =
            "The background is a deep, warm dark brown; the figure emerges from it only at the lit side of the face and the highlights of the neck.",
        [FUN_LUMINOSUM]  = "The background is a pale ivory-gold; the elongated figure reads as a darker silhouette against it."
    },
    modiglianius_lumen, N_OF(modiglianius_lumen),
    modiglianius_texturae, N_OF(modiglianius_texturae),
    modiglianius_compositio, N_OF(modiglianius_compositio),
    "The paint is applied in patient, parallel strokes; the figure's proportions are deliberately elongated, but every element — face, neck, shoulders — is painted with a quiet, classical confidence."
};

/* ============================================================
 * rembrandtus — tenebrae et lumen aureum
 * ============================================================ */
static const int rembrandtus_media[] = { MED_OLEUM };
static const char *const rembrandtus_figurae[] = {
    "The face emerges from a deep warm brown shadow; one side of the face is lit by a single warm source at the upper left, the other side falls away into near-black. The transition between lit and shadowed areas is slow and atmospheric.",
    "The skin is worked in many thin glazes of warm flesh tones — ochre, madder, and raw umber — over a toned brown ground that glows faintly through the darks. The eyes catch a single small highlight each.",
    "The face is modelled with Baroque patience: the forehead and nose carry the strongest warm light, the cheeks carry a quieter ochre, and the shadow side of the face is a rich translucent umber through which the ground still glows.",
    "The subject wears a heavy dark garment — wool or velvet — that reads as near-black but is painted in deep varied tones of warm umber, Prussian blue, and lamp black; the lit edge of the collar catches the only hard highlight in the picture.",
    "The eyes are engaged directly with the viewer: the left eye sits in the lit half of the face and carries a small, decisive white highlight; the right eye sits in the shadow and glows only faintly, its iris a translucent brown.",
    "The hair is a dark mass against an even darker background, painted in loose confident strokes of umber over black; a few long lit strands catch the side-light in warm gold."
};
static const char *const rembrandtus_motiva[] = {
    "a gold chain rests on the chest in three slow, dragged loops; each link is modelled with a single warm highlight of lead white",
    "a soft, dark velvet cap sits low on the head, its shadow-side indistinguishable from the background, its lit side catching a single warm-gold glint",
    "a worn leather-bound book is held loosely at the waist, its spine just catching the lit side of the picture in dull warm ochre",
    "the collar of the shirt is a wide band of worked white linen, its folds rendered in many thin wet strokes, catching the single warm light at its upper edge",
    "a heavy gold medallion hangs from a dark ribbon around the neck, reflecting the warm light at its curved upper surface in a single thick impasto highlight",
    "a small patch of fur trim at the shoulder is suggested in many short golden strokes laid over a shadowed undertone",
    "the subject's hands, resting quietly in the lower edge of the picture, are modelled with the same patient warm glazes as the face — each knuckle receiving one small highlight"
};
static const char *const rembrandtus_lumen[] = {
    "A single warm light source from the upper left illuminates one side of the face and the near shoulder; everything else in the picture falls into deep atmospheric shadow.",
    "The illumination is golden and warm: the shadows are not black but a dark translucent brown through which the toned ground still glows.",
    "The light is selective — it strikes only the forehead, the bridge of the nose, the near cheek, and one small area of collar; the rest of the picture is left in quiet darkness.",
    "The eyes catch one small, decisive white highlight each; apart from these highlights, the face itself carries only soft warm transitions between light and shadow."
};
static const char *const rembrandtus_texturae[] = {
    "The darks are worked as many thin transparent glazes over a warm brown ground that glows faintly through them; the lights are more opaque, and the brightest highlights are laid on as soft impasto.",
    "The brush is confident and varied: broad dragged strokes in the hair and garment, patient small strokes in the lit flesh, and a few near-gestural marks at the lace or fur trim.",
    "The surface has real physical variation — raised impasto at the brightest highlights, smooth translucent glaze in the shadows — and its texture is part of the illusion of light itself."
};
static const char *const rembrandtus_compositio[] = {
    "The head is centred in the upper two-thirds of the picture; a dark diagonal of shadow runs across the lower third, connecting the shoulder to the picture's opposite corner.",
    "The figure emerges from the darkness slightly to one side of centre; most of the picture is given to atmospheric shadow, and only a compact area — the face and near shoulder — is fully lit."
};
static const Stylus stylus_rembrandtus = {
    rembrandtus_media, N_OF(rembrandtus_media),
    rembrandtus_figurae, N_OF(rembrandtus_figurae),
    rembrandtus_motiva, N_OF(rembrandtus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, madder red, and raw umber, with small impasto lead-white highlights; the whole picture glows golden.",
        [PAL_FRIGIDA]   =
            "The palette is cool umber and bone black, with a single cool highlight of lead white; the warm notes are confined to the pupils of the eyes.",
        [PAL_SATURATA]  =
            "A deep saturated madder red dominates the garment; the skin is kept quieter, and the contrast of saturated cloth and restrained flesh carries the picture.",
        [PAL_MUTA]      =
            "The palette is pulled toward warm grey-brown throughout: everything is a variation of umber, ochre, and bone, held at low chroma.",
        [PAL_MONOCHROMA] =
            "The picture is painted in graded warm brown alone, from bone white highlight to deep translucent bitumen shadow.",
        [PAL_PRIMARIA]  =
            "Only warm red, yellow, and a single deep blue are admitted; the whole picture is held in earthy variations of these three colours.",
        [PAL_TERREA]    =
            "Raw umber, burnt sienna, Venetian red, and yellow ochre do almost all the colour work; a single small touch of natural ultramarine appears at the eyes."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single dark, warm, nearly-black field painted in slow varied brown strokes; no architectural detail is admitted.",
        [FUN_ORNATUM]    =
            "Behind the figure, a suggestion of patterned tapestry or tooled leather is just visible in the shadow, rendered in deep warm glazes.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, through an arched opening at the far left, a narrow view of an atmospheric landscape recedes into golden distance.",
        [FUN_ABSTRACTUM] =
            "The background is undifferentiated atmospheric shadow; no plane, object, or horizon is specifically indicated.",
        [FUN_TENEBROSUM] =
            "The background is a deep warm near-black; the figure emerges from it only where the single warm light source strikes.",
        [FUN_LUMINOSUM]  =
            "The background is warmer than usual — a glowing dim gold — so the figure reads as a darker silhouette against it."
    },
    rembrandtus_lumen, N_OF(rembrandtus_lumen),
    rembrandtus_texturae, N_OF(rembrandtus_texturae),
    rembrandtus_compositio, N_OF(rembrandtus_compositio),
    "The paint is built up in many thin transparent glazes over a toned brown ground; the brightest highlights are finally laid on in thick, confident impasto, standing physically off the surface."
};

/* ============================================================
 * hockneius — lumen Californicum, planities chromatica
 * ============================================================ */
static const int hockneius_media[] = { MED_ACRYLICUM };
static const char *const hockneius_figurae[] = {
    "The face is painted in flat, clean fields of warm modern colour: a single confident pale flesh tone for the lit side, a slightly cooler flesh tone for the shaded side, and a clean hard edge between them. No atmospheric transitions are admitted.",
    "The skin is rendered in bright, flattering, almost cosmetic tones — peach, warm rose, and a single cool highlight of almost white — each laid as a flat area with a clean boundary. The face looks well-rested, confident, and modern.",
    "The hair is a single flat field of one saturated modern colour: sun-bleached blond, soft grey, or deep chocolate, with a few confident darker lines drawn over it to indicate the fall of the locks.",
    "The eyes are drawn as two confident almond shapes in cobalt or viridian, the irises flat and unmixed, the pupils single round black dots; the whites of the eyes are a clean, bright lead white.",
    "The face is painted with Californian optimism: a relaxed closed smile, a single cheekbone highlight, bright direct eyes, nothing shadowed or heavy anywhere."
};
static const char *const hockneius_motiva[] = {
    "a pair of round tortoiseshell spectacles sits on the nose, their frames drawn in a confident single-stroke line of warm brown",
    "the shirt is a single flat field of one saturated modern colour — lemon yellow, pool blue, or candy pink — with the collar clean and sharp",
    "a single white slat of a venetian blind is visible behind the shoulder, painted as a single flat horizontal bar",
    "a potted cactus sits on a low shelf at the lower-right edge of the picture, each needle drawn as a single thin dark stroke",
    "the subject wears a narrow striped tie in three flat saturated colours, its stripes running at a slight modern diagonal",
    "a patterned square scarf is wrapped loosely at the throat, its print rendered in flat areas of three pure colours",
    "a single saturated pool-blue rectangle, 10 cm by 30 cm, represents a distant swimming pool in the background — rendered without perspective"
};
static const char *const hockneius_lumen[] = {
    "The light is hard, clean, and Californian: a high clear sun illuminates the face evenly, producing only minimal soft shadows under the chin and nose. No atmospheric complexity is admitted.",
    "The illumination is even, flat, and optimistic; no hard cast shadow falls anywhere on the face, and the transition between lit and shaded areas is made entirely through colour temperature rather than value."
};
static const char *const hockneius_texturae[] = {
    "The paint is flat, opaque acrylic, laid in clean even coats; no brushmark is admitted in the colour fields, and the picture reads with the clarity of a printed poster.",
    "The surface is matte, clean, and modern; line-work is drawn over the flat fields in confident single strokes, never corrected."
};
static const char *const hockneius_compositio[] = {
    "The figure is centred and frontal within a bright, cleanly-organised composition; the background is divided into two or three large flat fields of modern colour.",
    "The composition is graphic and flat; the figure reads first as a confident silhouette filled with flat colour, and only then as a modelled face."
};
static const Stylus stylus_hockneius = {
    hockneius_media, N_OF(hockneius_media),
    hockneius_figurae, N_OF(hockneius_figurae),
    hockneius_motiva, N_OF(hockneius_motiva),
    {
        [PAL_CALIDA]    = "The palette is warm peach flesh, sunny yellow, and bright terracotta against a clean cream ground.",
        [PAL_FRIGIDA]   =
            "The palette is pool blue, viridian, and cool lavender, against a clean white ground; warm notes are limited to the flesh.",
        [PAL_SATURATA]  =
            "Every field is a saturated modern colour — pool blue, signal yellow, hot pink, lime — set adjacent, all flat and unmodulated.",
        [PAL_MUTA]      =
            "The saturation is pulled back to pale ice-cream tones — mint, peach, pale lilac — each still laid flat and hard-edged.",
        [PAL_MONOCHROMA] =
            "The picture is worked in flat fields of one graded warm grey, with a single saturated accent at the shirt or scarf.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue are laid as flat saturated fields; the skin is a clean warm optical mix between them.",
        [PAL_TERREA]    =
            "The palette is warm terracotta, burnt sienna, and sand, against an olive-grey ground; the colours are flat but the key is warm and earthy."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of one saturated modern colour, clean and unmarked, extending to every frame edge.",
        [FUN_ORNATUM]    =
            "Behind the figure, a clean flat pattern of modern geometric shapes — circles, bars, zigzags — in three primary colours tiles the entire plane.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a simplified California garden is visible: a slab of pool blue, a green lawn, a single stylised palm tree, each a flat field of saturated colour.",
        [FUN_ABSTRACTUM] =
            "The background is three large flat rectangles of saturated colour, abutting one another without transition.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a single deep teal-black; the figure's clean bright fields read all the more sharply against it.",
        [FUN_LUMINOSUM]  = "Behind the figure is a single bright clean lemon-yellow or sky blue, flooded edge to edge."
    },
    hockneius_lumen, N_OF(hockneius_lumen),
    hockneius_texturae, N_OF(hockneius_texturae),
    hockneius_compositio, N_OF(hockneius_compositio),
    "The paint is flat, clean acrylic in confidently-chosen saturated colours; line-work is added last as single decisive strokes, and no atmospheric modelling is permitted."
};

/* ============================================================
 * freudus — carnis veritas, impasto
 * ============================================================ */
static const int freudus_media[] = { MED_OLEUM };
static const char *const freudus_figurae[] = {
    "The face is modelled in thick, honest oil paint; every imperfection of the skin — a small broken vessel at the cheek, a pore near the nose, a hair stray at the temple — is recorded with unflinching patient realism. The paint itself reads as flesh.",
    "The skin is built up in many varied fleshy tones: warm pink at the cheekbones, cool grey-green under the eye, ochre at the forehead, a subtle violet-blue under the jaw. The transitions are painted as physical shifts of hue, not as smooth gradients.",
    "The face is painted in heavy, thoughtful impasto — the paint stands 2 to 3 mm off the canvas in places — and the brushwork follows the direction of the underlying flesh: across the cheekbone, along the jaw, around the eye socket.",
    "The eyes are painted with patient attention: the whites are slightly warmer than one would expect, the iris carries three or four different hues, the lower lid is modelled with a single warm highlight.",
    "The mouth is full and softly modelled; the transitions between lip and surrounding skin are painted as small physical ridges of paint, not as drawn lines."
};
static const char *const freudus_motiva[] = {
    "a length of heavy linen cloth is visible at the shoulder, its fibres picked out individually in short varied strokes of warm and cool white",
    "the hair is rendered with extraordinary patience: each lock modelled in thick paint, each root hinted at with a short dark stroke, no area generalised",
    "a single carved wooden bedpost is visible behind the shoulder, its grain rendered in patient dry strokes of warm brown",
    "a plain leather belt is visible at the waist, its edge catching the room's soft overhead light in a single long highlight",
    "the hands are modelled with the same attention as the face, every finger individually painted, every knuckle carrying its own small highlight and shadow",
    "the skin over the collarbone is translucent enough that a single faint blue vein is visible, painted as a soft curving thin line"
};
static const char *const freudus_lumen[] = {
    "The light is a single overhead studio source — soft, even, and slightly cool — that falls on every part of the figure uniformly; shadows are atmospheric rather than cast.",
    "The illumination is patient and unmoving, as though the painter has had the figure sit for many hours under the same light; the shadows and highlights are not dramatic but carefully observed."
};
static const char *const freudus_texturae[] = {
    "The paint is thick, varied, and deliberate; it stands physically off the canvas in many places, and its own relief contributes to the illusion of flesh.",
    "The surface is visibly worked: each stroke is confident and individual, and no area is smoothed out. The painter's patience, not their gesture, is what shows."
};
static const char *const freudus_compositio[] = {
    "The figure is centred and frontal; the composition is held still, and the picture feels as though it has been studied for a long time.",
    "The background is a single close, enclosing space — a plain wall, a corner of a room — that pushes the figure forward into the viewer's space."
};
static const Stylus stylus_freudus = {
    freudus_media, N_OF(freudus_media),
    freudus_figurae, N_OF(freudus_figurae),
    freudus_motiva, N_OF(freudus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, madder, rose, and a quiet burnt sienna; the flesh is a varied honest warmth.",
        [PAL_FRIGIDA]   =
            "The palette is cool olive, slate, grey-violet, and ivory; the flesh is painted in muted cold greens and blues.",
        [PAL_SATURATA]  =
            "The flesh is painted at unexpected full saturation: bright warm rose at the cheek, strong ochre at the forehead, clear umber in the shadow.",
        [PAL_MUTA]      =
            "The saturation is pulled down to muted earthy tones; the paint remains thick but the chroma is domestic rather than vivid.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone; the impasto and the honest modelling remain, but colour is withheld.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue are admitted as colour; the flesh is painted as their optical mix, never directly blended.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, yellow ochre, and terre verte, with small lead-white impasto highlights."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a plain studio wall in a single quiet warm grey, worked in patient matte strokes.",
        [FUN_ORNATUM]    =
            "Behind the figure, a corner of a working studio is visible: an unmade cot, a paint-spattered floor, a stack of canvases.",
        [FUN_PAESAGIUM]  =
            "Through a small window visible at the upper right, a modest view of a London courtyard garden is suggested in patient small strokes.",
        [FUN_ABSTRACTUM] =
            "The background is a single close, undifferentiated shadow; only a faint suggestion of wall or floor is admitted.",
        [FUN_TENEBROSUM] =
            "The background is a deep close warm brown; the figure is brought forward out of it by the light on the face alone.",
        [FUN_LUMINOSUM]  =
            "The background is a high, soft white; the figure is pressed forward from this light in full physical paint."
    },
    freudus_lumen, N_OF(freudus_lumen),
    freudus_texturae, N_OF(freudus_texturae),
    freudus_compositio, N_OF(freudus_compositio),
    "The paint is thick, honest, and patient; the surface of the picture is itself the texture of the flesh, and no area of the figure is generalised or simplified."
};

/* ============================================================
 * basquiatus — lineae urbanae, corona
 * ============================================================ */
static const int basquiatus_media[] = { MED_ACRYLICUM, MED_OLEUM };
static const char *const basquiatus_figurae[] = {
    "The face is drawn with the rough confidence of a subway line: a few thick black strokes define the silhouette, the eyes are two wide black-and-white discs, the teeth are visible as a row of hard white rectangles. The face reads as raw, urgent, alive.",
    "The head is rendered as a skull-like form over flat flesh: the structure of bone beneath is visible through hatched lines at the temples and the jaw, but the eyes, nose, and mouth are painted whole and fierce on top.",
    "The subject's face is painted in a scribbled field of many marks — short strokes, scratchings, reversals, annotations — yet the underlying portrait is unmistakable: a real person looking directly out of the picture.",
    "Across the face are painted short scrawled marks — arrows, scratched-out rectangles, illegible tally-strokes — done in oil stick over the wet paint, as though the picture were being annotated by its maker.",
    "The eyes are large, frontal, and filled with a single flat colour; the pupils are hard black dots; the whites have been stained with a thin oil-stick yellow scrubbed across them."
};
static const char *const basquiatus_motiva[] = {
    "a three-pointed black crown with small ticks along its rim is painted above the head in thick black oil stick, standing 5 cm proud of the picture's top edge",
    "a single hard angular glyph belonging to no alphabet, sometimes crossed out, is scrawled across the forehead in confident oil-stick line",
    "a stylised skeleton arm is visible through the flesh of the upper chest, each rib drawn as a single hard white stroke",
    "a copyright symbol (© or ℗) has been painted small near the shoulder, as though marking the figure as a product",
    "a scatter of annotations — tally marks, short diagrammatic fragments, small crossed-out shapes — is distributed across the background in oil stick",
    "a single decisive oil-stick gesture crosses the lower edge of the picture, its shape a loose abstract scribble that reads as mark rather than writing",
    "a single dark arrow, 15 cm long, points inward at the crown from the upper-right edge, drawn with a paint-loaded brush"
};
static const char *const basquiatus_lumen[] = {
    "No light source is represented; the picture is lit as graffiti is lit — by the colour of the paint and the contrast of line against ground, without atmospheric modelling.",
    "The illumination is provided by colour alone: bright saturated fields read as lit, dark scrubbed passages read as shadow, but nothing is modelled."
};
static const char *const basquiatus_texturae[] = {
    "The surface is worked in loose, energetic acrylic laid over a raw or painted ground; oil-stick annotations are drawn over the paint in confident dry strokes.",
    "Several layers are visible: a first wash of colour, a painted figure on top, and a layer of scrawled text and marks laid on last as though correcting the image itself."
};
static const char *const basquiatus_compositio[] = {
    "The figure fills most of the composition frontally, head and shoulders centred; marks, labels, and small diagrams fill the air around the head without crowding it out.",
    "The composition is loose and hectic but the figure at its centre is calm and direct; the annotations radiate outward from the head without ever obscuring the face."
};
static const Stylus stylus_basquiatus = {
    basquiatus_media, N_OF(basquiatus_media),
    basquiatus_figurae, N_OF(basquiatus_figurae),
    basquiatus_motiva, N_OF(basquiatus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is raw cadmium red, signal orange, and sulphur yellow, against a hot coffee-stained brown ground.",
        [PAL_FRIGIDA]   =
            "The palette is cool cobalt, slate, and viridian, against a dirty white ground; warm notes are limited to the flesh of the face.",
        [PAL_SATURATA]  =
            "Every passage is at full saturation — cadmium red, signal yellow, pure cobalt, cool green — against a black-and-white scribbled ground.",
        [PAL_MUTA]      =
            "The saturation is pulled back to dirty neutrals — mushroom, rust, olive, cream — while the black oil-stick marks remain hard and saturated.",
        [PAL_MONOCHROMA] = "The picture is worked in black oil stick on a cream or dirty white ground; no colour is admitted.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue are used as flat saturated fields; black oil stick is laid over them for every line and annotation.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, yellow ochre, and ivory; the marks are laid in black oil stick over warm stained ground."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single scrubbed field of one raw colour, laid on in broad confident brushstrokes that leave the underlying canvas partly visible.",
        [FUN_ORNATUM]    =
            "Behind the figure, a scatter of painted fragments — single letters, tally marks, small diagrams, crowns — fills the space without repetition.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a rough urban skyline of rectangular silhouettes is indicated in a few confident dark strokes along the horizon.",
        [FUN_ABSTRACTUM] =
            "The background is a field of layered marks, lines, and labels laid on top of a rough painted ground; no coherent space is implied.",
        [FUN_TENEBROSUM] =
            "The background is a deep scribbled near-black, against which the figure's face and annotations glow in warm colour.",
        [FUN_LUMINOSUM]  =
            "The background is a dirty flat white, against which every oil-stick mark and every saturated colour-field stands out sharply."
    },
    basquiatus_lumen, N_OF(basquiatus_lumen),
    basquiatus_texturae, N_OF(basquiatus_texturae),
    basquiatus_compositio, N_OF(basquiatus_compositio),
    "The image is built in layers: a rough painted ground, a confidently drawn figure, and an upper layer of oil-stick marks, labels, and annotations laid on top without correction."
};

/* ============================================================
 * seuratus — puncta pigmenti, lux quieta
 * ============================================================ */
static const int seuratus_media[] = { MED_OLEUM };
static const char *const seuratus_figurae[] = {
    "The entire face is built from thousands of tiny separate dots of unmixed pigment, each about 1 mm across. No line is drawn anywhere; every edge is produced by the density and hue of the dots, not by a contour.",
    "The skin is a field of interlocking dots: warm ochre dots, cool violet dots, dots of pale green and rose, all laid adjacent without ever blending. From a distance the face reads as a soft warm flesh; up close it dissolves into pure coloured specks.",
    "The face is quietly composed and symmetrical; it carries no strong expression. The mouth is a slightly darker cluster of red and violet dots, the eyes a darker cluster of blue and umber dots, the cheekbone a faint warmer cluster.",
    "The hair is a denser field of dots in darker hues — chestnut, umber, and a cool violet — separated from the face by no line, only by the change of hue density.",
    "The lips, the nostrils, the eyebrows are indicated not as drawn marks but as subtle local concentrations of darker or warmer dots, readable only at a distance."
};
static const char *const seuratus_motiva[] = {
    "a straw boater sits neatly on the head, its brim defined not by a line but by the change of dot density — warm yellow dots giving way to white dots to cool grey dots in the shadow beneath",
    "a plain dark jacket with a high collar is built from dense dots of ultramarine, violet, and a faint green; from a distance it reads as black",
    "a tall blade of grass rises at the lower-left edge, composed of fifty tiny green and warm yellow dots",
    "a small dark parasol is visible partially furled behind the shoulder, built from a tight cluster of warm grey and violet dots",
    "a cluster of small white dots against a slightly denser violet field suggests a single distant lit lamp post in the background",
    "a butterfly rests briefly on the shoulder, composed of about eighty dots in yellow, orange, and black",
    "a simple striped scarf is suggested by alternating bands of warmer and cooler dots across the chest"
};
static const char *const seuratus_lumen[] = {
    "The light is still, afternoon, and atmospheric; it is conveyed entirely by the hue and density of the dots — warmer dots reading as lit, cooler dots reading as shadow.",
    "No cast shadow is drawn; the transition from sun to shadow is a slow migration in the hue of the dots, from warm orange-yellow to cool blue-violet."
};
static const char *const seuratus_texturae[] = {
    "The entire surface is stippled: tens of thousands of small round dots of unmixed pigment, each no larger than 1 mm, laid with patient regularity.",
    "No area of the picture is allowed to be continuous; every passage, even the darkest shadow, is built from tiny separate dots of two or three hues laid adjacent."
};
static const char *const seuratus_compositio[] = {
    "The figure is centred and still; the composition is stable and geometric, and the picture reads as much as a patient optical experiment as it does as a portrait.",
    "The composition is held in strict equilibrium: the head at the picture's geometric centre, the shoulders balanced left and right, the background's dot-density uniform around the figure."
};
static const Stylus stylus_seuratus = {
    seuratus_media, N_OF(seuratus_media),
    seuratus_figurae, N_OF(seuratus_figurae),
    seuratus_motiva, N_OF(seuratus_motiva),
    {
        [PAL_CALIDA]    =
            "The dots are primarily warm — chrome yellow, vermilion, warm ochre, soft madder — with violet and green used only in the shadow passages.",
        [PAL_FRIGIDA]   =
            "The dots are primarily cool — cobalt, viridian, grey-violet — with only a small field of warm ochre dots in the flesh.",
        [PAL_SATURATA]  =
            "The dots are laid at full pigment saturation; the optical mix from a distance reads as richly coloured but the individual dots are unmixed.",
        [PAL_MUTA]      =
            "The dot palette is pulled to soft, atmospheric tones — mushroom, dove, cream, pale lilac — and the picture reads as a quiet dusty field.",
        [PAL_MONOCHROMA] =
            "The entire picture is built from dots of black and white alone on a cream ground; halftones are produced by dot density.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue dots are admitted; every perceived hue is produced as an optical mix between pairs of these primaries.",
        [PAL_TERREA]    =
            "The dot palette is raw umber, burnt sienna, yellow ochre, and terre verte; the picture reads warm and earthy at viewing distance."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure, the ground is a single uniform field of dots of one dominant cool hue, extending to every edge.",
        [FUN_ORNATUM]    =
            "Behind the figure, a field of dot-built small flowers and grass blades tiles the plane in quiet regular rhythm.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a Sunday park of the Île de la Grande Jatte is implied — grass in warm and cool greens, a strip of river blue, figures in distant dot-silhouettes.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the dots continue as an almost uniform warm grey field, producing an atmospheric rather than representational space.",
        [FUN_TENEBROSUM] =
            "The background dots are clustered into a deep cool violet-black; the figure's warmer dots glow against it.",
        [FUN_LUMINOSUM]  =
            "The background dots are clustered into a bright warm cream; the figure reads as a soft darker silhouette against it."
    },
    seuratus_lumen, N_OF(seuratus_lumen),
    seuratus_texturae, N_OF(seuratus_texturae),
    seuratus_compositio, N_OF(seuratus_compositio),
    "The entire picture is composed of small round dots of unmixed pigment, each about 1 mm across, laid adjacent without ever blending; from a distance the eye mixes them into form."
};

/* ============================================================
 * rivereus — pictura muralis, figura fortis
 * ============================================================ */
static const int rivereus_media[] = { MED_FRESCA, MED_OLEUM };
static const char *const rivereus_figurae[] = {
    "The face is painted with the solid, monumental simplicity of a mural: large planes of warm flesh tone, each bounded by a confident soft contour, no excess detail. The subject reads as dignified, grounded, and physically present.",
    "The head is rendered with a simple but unmistakable weight: the cheekbones are broad, the nose full, the mouth strong and closed. Every feature is modelled in two or three tones — no more — each transition soft but definite.",
    "The skin is worked in warm earth tones — burnt sienna, ochre, Venetian red — with a single cool shadow tone across the far cheek. The overall effect is that of sunlit worked stone.",
    "The hair is a single large mass of deep blue-black, bounded by a soft confident outline and shaped in broad generous curves.",
    "The eyes are large, dark, and direct; each iris is a warm umber with a single small highlight, and the lower lid catches a faint warm reflected light."
};
static const char *const rivereus_motiva[] = {
    "a white cotton shirt with an open soft collar is painted in broad flat strokes of warm white with a few shadow planes in cool lavender",
    "a single large calla lily is held in one hand at the lower edge of the picture, its flower a warm confident curve of unmixed white",
    "a thick braid of dark hair falls over one shoulder, painted in long continuous strokes of deep blue-black",
    "a red embroidered ribbon is worked at the collar, its saturated colour the one strong accent in the picture",
    "a woven straw hat, broad-brimmed, is tilted gently on the head, its weave indicated in parallel rows of short warm strokes",
    "a patterned rebozo shawl is wrapped over the shoulders, its geometric pattern — small diamonds and zigzags — painted flat in two or three earthy colours",
    "a small jade bead hangs from a dark cord at the throat, catching the single cool highlight in the picture"
};
static const char *const rivereus_lumen[] = {
    "The light is warm, high, and steady, as though the figure were lit by a midday sun passing through an open courtyard; shadows are soft and short.",
    "The illumination is even and generous; every surface receives light, and the shadows are cool and transparent rather than deep or dramatic."
};
static const char *const rivereus_texturae[] = {
    "The paint is matte and opaque, applied flat and confidently in broad strokes; the surface reads as a section of a larger mural, as though the painter were used to working on walls.",
    "The picture carries the slightly granular quality of fresco — a soft tooth to the paint — even when it is worked in oil; the handling is simple and public, not private or detailed."
};
static const char *const rivereus_compositio[] = {
    "The figure is centred and monumental, painted large within the frame; the background is simplified into broad flat areas that do not compete with the figure.",
    "The composition is frontal, symmetrical, and stable; the figure carries the full weight of the picture, and the background exists only to support it."
};
static const Stylus stylus_rivereus = {
    rivereus_media, N_OF(rivereus_media),
    rivereus_figurae, N_OF(rivereus_figurae),
    rivereus_motiva, N_OF(rivereus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, burnt sienna, Venetian red, and sulphur yellow, against a sun-warmed earth-pink ground.",
        [PAL_FRIGIDA]   =
            "The palette is cool stone grey, pale turquoise, and jade green, against a muted cool stone ground; the flesh is kept restrained.",
        [PAL_SATURATA]  =
            "A saturated red embroidered garment or flower meets warm ochre skin; the saturation of the single strong accent carries the whole picture.",
        [PAL_MUTA]      =
            "The palette is quiet earth tones — sand, clay, putty, ivory — and the picture reads with a dignified, sunlit restraint.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm earth tones alone, from cream to deep sienna, giving the register of a fresco seen in raking light.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue are used as flat saturated fields in the garment, accessories, and background; the flesh is kept in quiet optical mixes.",
        [PAL_TERREA]    =
            "The palette is entirely earth pigments — raw umber, yellow ochre, burnt sienna, terre verte — with small accents of carbon black and lead white."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field of warm stone-pink, painted in quiet matte brushstrokes that do not draw attention.",
        [FUN_ORNATUM]    =
            "Behind the figure, a low wall patterned with stylised pre-Columbian motifs — stepped crosses, serpent scales, small sun shapes — rises to shoulder height.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a stylised Mexican landscape recedes into the distance: a band of corn field, a terraced hill, a distant volcano, each a flat area of confident earth colour.",
        [FUN_ABSTRACTUM] =
            "The background is a broad flat division of two or three warm earth fields, abutting one another as large simple bands.",
        [FUN_TENEBROSUM] =
            "The background is a deep warm umber that surrounds the figure like the interior of a shaded courtyard; only the figure's face and shoulders catch the day.",
        [FUN_LUMINOSUM]  =
            "The background is a bright warm buff, the colour of sunlit plaster; the figure reads as a rich warm silhouette against it."
    },
    rivereus_lumen, N_OF(rivereus_lumen),
    rivereus_texturae, N_OF(rivereus_texturae),
    rivereus_compositio, N_OF(rivereus_compositio),
    "The paint is matte and opaque; every surface is handled in broad confident public strokes, and the figure is given the solidity and dignity of a section of a mural wall."
};

/* ============================================================
 * velaspinus — pictor veli diagonalis (fictio)
 * ============================================================ */
static const int velaspinus_media[] = { MED_OLEUM, MED_TEMPERA };
static const char *const velaspinus_figurae[] = {
    "The face is painted clearly and fully, but a single translucent veil of pale cream silk runs diagonally across the entire picture from upper-left to lower-right, so the features are slightly softened and cooled where the veil passes and sharper and warmer where it does not.",
    "The subject is rendered in patient realist oil, and then a thin gauze veil has been painted over the entire surface in semi-transparent lead white; the weave of the gauze is visible as a faint square mesh over every feature.",
    "The head and shoulders are fully and confidently painted, but the right half of the picture — from the corner of the mouth outward — is covered by a thin painted layer of pearl-grey translucency that lowers the saturation and softens every edge beneath it.",
    "The features are sharp and real where the veil does not fall, and identical but muted behind the veil; the painter has worked every detail twice, once at full clarity and once at a quarter opacity, so the subject reads as both present and remembered.",
    "A single thin diagonal fold of the veil runs directly across the lit eye, producing one small area where the painted veil physically ridges up 1 mm from the surface — the only impasto in the picture."
};
static const char *const velaspinus_motiva[] = {
    "the veil's lower corner has gathered into a loose knot at the picture's lower-left edge, painted in three confident folds",
    "a single silver pin passes through the veil at the shoulder, its head catching the light in a small bright bead",
    "a row of four tiny stitched marks runs along the upper edge of the veil, each an X in pale thread",
    "where the veil crosses the mouth, the subject's breath has fogged it in a faint soft circle about 6 cm across",
    "the veil catches a diagonal highlight along its entire length, a soft pale pearl stripe running upper-left to lower-right",
    "one corner of the veil has been rolled back by a breath of wind and a small patch of face beneath is revealed sharply",
    "a small stamped ornament in the shape of a spidery curlicue is visible along the veil's lower hem, in black thread",
    "a second narrow veil, barely visible, runs perpendicular to the first; the two veils intersect at the throat in a woven cross",
    "a small dragonfly has alighted on the veil and is painted in precise miniature at the outer fold",
    "a row of six tiny silver sequins is stitched along the upper edge of the veil, each catching its own pinpoint highlight",
    "a small tear in the veil above the right temple has been mended with bright gold thread, the repair left visible"
};
static const char *const velaspinus_lumen[] = {
    "The light falls from the upper left onto the veil first and the face second; the veil therefore carries most of the picture's brightness, and the face reads as quieter behind it.",
    "A single soft overhead light catches the veil's weave in pinpoint highlights, scattering across the surface like a dew-field.",
    "Shadows behind the veil are softened into warm pearl; shadows outside the veil keep their own warm cold edge."
};
static const char *const velaspinus_texturae[] = {
    "The flesh beneath the veil is worked in patient oil glazes; the veil itself is painted last, in a single thin translucent layer of lead white and a trace of raw umber, over the dry portrait.",
    "The veil's weave is scored into the wet paint with the point of a fine brush handle, giving a physical square mesh that catches the light slightly."
};
static const char *const velaspinus_compositio[] = {
    "The diagonal of the veil divides the picture into two triangles — upper-right bright and veiled, lower-left darker and unveiled; the face is centred at the join.",
    "The composition is frontal and centred; the veil is the only asymmetric element, running its single slow diagonal across the still figure."
};
static const Stylus stylus_velaspinus = {
    velaspinus_media, N_OF(velaspinus_media),
    velaspinus_figurae, N_OF(velaspinus_figurae),
    velaspinus_motiva, N_OF(velaspinus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm cream flesh, pale honey, and a quiet rose, with the veil in a warm pearl that catches every highlight.",
        [PAL_FRIGIDA]   =
            "The palette is cool pearl, slate grey, and pale ice-blue; the veil is the coldest note in the picture and the face is warmed only at the lips.",
        [PAL_SATURATA]  =
            "Beneath the veil the saturation is full and deep; through the veil it is halved; the contrast between the two halves is the picture's saturation story.",
        [PAL_MUTA]      =
            "The whole picture is kept in a narrow band of soft pearl, taupe, and dove, the veil barely distinguishable from the flesh beneath.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm pearl alone, with the veil indicated only by a subtle shift in value.",
        [PAL_PRIMARIA]  =
            "The veil is a translucent cream; beneath it, flat fields of pure red, yellow, and blue have been painted as the underlying garments, visible through the veil as desaturated primary shapes.",
        [PAL_TERREA]    =
            "The palette is raw umber, yellow ochre, and a soft warm cream for the veil; the picture reads as though painted on aged linen."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure and the veil is a single flat field of warm pearl, lit as softly as the veil itself.",
        [FUN_ORNATUM]    =
            "Behind the figure, a patterned damask wall is visible — small repeating vine-motifs — further softened by the veil where the veil crosses it.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, through a window visible at one edge, a far pale landscape can be made out — softened still further by the veil.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the ground fades into a soft gradient of pearl, with no object or horizon indicated.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a deep warm near-black; the veil, where it crosses this ground, reads as a luminous diagonal stripe of grey.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a flat high pearl-white; the veil is almost invisible against it and the face reads as quietly backlit."
    },
    velaspinus_lumen, N_OF(velaspinus_lumen),
    velaspinus_texturae, N_OF(velaspinus_texturae),
    velaspinus_compositio, N_OF(velaspinus_compositio),
    "The portrait is painted in confident oil realism beneath; a thin translucent diagonal veil is laid as the final layer over the dry picture, covering roughly half the figure with a quiet pearl softness."
};

/* ============================================================
 * crispulus — pictor chartae adustae (fictio)
 * ============================================================ */
static const int crispulus_media[] = { MED_TEMPERA, MED_OLEUM };
static const char *const crispulus_figurae[] = {
    "The face is painted as though rendered on a sheet of cream paper that has been lightly scorched: a warm umber halo surrounds each eye, each nostril, and the corners of the mouth, as if heat had gathered at those points and browned the paper.",
    "The skin is worked in pale ivory tones streaked with patches of warm scorch-brown; the edges of the cheeks curl faintly as though the paper beneath were beginning to warp from dry heat.",
    "A faint smoke-stain rises from the lower edge of the picture and fades upward over the collarbone, the only dark passage in an otherwise cream-coloured face.",
    "The whole head carries a thin warm brown wash as though varnished with smoke; beneath this wash the original sharp drawing of the features is still visible.",
    "Small irregular brown spots, each 2-4 mm across, are scattered across the forehead and cheek, suggesting the small charred points where embers briefly touched the surface."
};
static const char *const crispulus_motiva[] = {
    "the upper-right corner of the picture has curled inward by about 2 cm, its edge blackened and ragged",
    "a narrow strip of the collar is charred black at its outermost edge, the black giving way to brown and then to cream toward the throat",
    "a single visible burn-hole, 8 mm across, sits just above the left eyebrow, its edges dark and curled",
    "a small inked mark at the lower right is half burned away; only a charred fragment of the original gesture survives",
    "a thin line of dark umber runs horizontally across the chest, where a seam in the paper has been weakened by heat",
    "the hair carries streaks of silver-grey ash at its crown, as though fine dust had settled there",
    "a faint blueish smoke-ring stains the background just behind the right shoulder, soft at its centre and darker at its rim"
};
static const char *const crispulus_lumen[] = {
    "The light is warm and dry; the picture's illumination seems to come from the heat that has scorched the paper rather than from any spatial source.",
    "No cast shadow is drawn; the picture's tonal variation comes from the uneven scorching of the ground, not from any modelling of the face."
};
static const char *const crispulus_texturae[] = {
    "The surface reads as warped paper: faint irregular ridges run across the picture, and the paint in the scorched passages sits slightly darker and drier than in the clean passages.",
    "The scorch-marks are painted with a brown glaze that pools at the edges of each mark, giving each spot a darker rim — as a real burn would."
};
static const char *const crispulus_compositio[] = {
    "The figure is centred and frontal; the scorching is distributed asymmetrically across the surface, concentrated most heavily at one corner and fading outward.",
    "The composition is held still and classical, but the entire picture is read through the filter of heat-damage; the face survives at the centre, the margins are the least protected."
};
static const Stylus stylus_crispulus = {
    crispulus_media, N_OF(crispulus_media),
    crispulus_figurae, N_OF(crispulus_figurae),
    crispulus_motiva, N_OF(crispulus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is cream, pale ivory, and warm scorch-brown; the picture glows in the range from paper to embers.",
        [PAL_FRIGIDA]   =
            "The picture is worked in cool ash-grey and pale blue-smoke over a cream ground; the scorch is present but has cooled to a silver register.",
        [PAL_SATURATA]  =
            "A single saturated ember-orange stripe runs across one corner of the picture where the scorch has almost caught fire; the rest remains quiet cream.",
        [PAL_MUTA]      =
            "The whole picture is held in soft warm neutrals — cream, oatmeal, dust-brown — with only the faintest scorch-marks admitted.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm brown alone, from pale cream at the cleanest areas to near-black at the deepest burns.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue appear only as three small saturated motifs painted on the scorched ground; the rest of the palette is ash and cream.",
        [PAL_TERREA]    =
            "The palette is entirely earth browns — raw umber, burnt sienna, yellow ochre, warm cream — with no bright colour admitted."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is an unmarked field of cream paper; the scorching fades outward from the figure to clean paper at the edges.",
        [FUN_ORNATUM]    =
            "Behind the figure, a pattern of stencilled dark lines and small rosettes is visible, partly obscured by the same scorching that marks the figure.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a small far landscape drawn in pale brown ink is visible through the smoke-stain, its features softened by heat-damage.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the paper ground carries uneven brown staining in soft drifting shapes, like slow fire seen from above.",
        [FUN_TENEBROSUM] =
            "Behind the figure, the ground has been scorched almost to black, and the figure emerges from the smoked dark as a slightly paler silhouette.",
        [FUN_LUMINOSUM]  =
            "Behind the figure, the cream paper remains nearly untouched, bright and clean; only the figure itself carries the warm scorched halation."
    },
    crispulus_lumen, N_OF(crispulus_lumen),
    crispulus_texturae, N_OF(crispulus_texturae),
    crispulus_compositio, N_OF(crispulus_compositio),
    "The image is painted on a warm cream ground and then treated as though lightly burned: a layer of warm brown scorch-halation, small darker burn-spots, and a few charred curling edges are painted last, over the otherwise clean portrait."
};

/* ============================================================
 * nimbulus — pictor tempestatis domesticae (fictio)
 * ============================================================ */
static const int nimbulus_media[] = { MED_OLEUM, MED_GOUACHE };
static const char *const nimbulus_figurae[] = {
    "The subject is painted as a realist portrait, but a small personal weather system hovers in the immediate space around the head and shoulders: a low soft grey cloud rests at the crown of the head, and a fine drizzle falls in pale grey strokes across the forehead.",
    "The subject's hair is rimed with fine silver frost, each individual frost-crystal rendered as a tiny pale white dot; their breath is visible in a soft white plume in the air in front of the mouth.",
    "A small bright fragment of rainbow arches from the right shoulder upward and out of the frame, its bands of colour thin but saturated; beneath it, small pale droplets catch the light on the collarbone.",
    "The subject's face is entirely dry and lit, but along the shoulders and upper chest a film of small water-droplets has collected, rendered each as a tiny curved highlight.",
    "A faint personal mist gathers about the subject's head, so the outline of the hair is softened but the face remains clear; the mist is painted in very thin white glazes laid over the finished face."
};
static const char *const nimbulus_motiva[] = {
    "a small dark cloud, about the size of an open book, hovers 20 cm above the crown of the head, a single thin thread of grey rain falling from it",
    "three small fine white snowflakes, each six-pointed, are caught in flight just in front of the cheek",
    "a thin horizontal band of fog crosses the picture at shoulder height, partly obscuring the upper chest",
    "a single soft golden sunbeam pierces a small gap in the personal cloud and catches the left eye, lighting it sharply",
    "a narrow ribbon of steam rises from a teacup held just out of frame at the lower edge, curling upward past the jaw",
    "the subject's breath has fogged a small circle on the picture surface about 8 cm in front of the mouth, softening the image where it is",
    "a single tiny lightning-bolt, 4 cm long, flickers between two fingers of the hand held at the lower edge"
};
static const char *const nimbulus_lumen[] = {
    "The light is complex and localised: a soft grey rain-light falls on most of the figure, while a small sunbeam from the personal weather's gap lights one eye or cheek at a sharper, warmer angle.",
    "Each weather element — cloud, mist, rainbow, snow — has its own small local illumination, and the face is lit by the net sum of these rather than by any single external source."
};
static const char *const nimbulus_texturae[] = {
    "The face and clothing are painted in smooth patient realism; the weather elements are painted in thinner, wetter glazes and very soft washes laid over the dry figure.",
    "The rain and snow are touched in last, as small white and grey impasto marks that stand 0.5 mm off the surface, so they catch the real room's light."
};
static const char *const nimbulus_compositio[] = {
    "The figure is centred and the personal weather radiates outward from the head and shoulders, its phenomena all contained within a loose circle about 60 cm across.",
    "The picture is split vertically by the figure; the weather belongs to the figure, not to the rest of the picture, and fades out just beyond the shoulders."
};
static const Stylus stylus_nimbulus = {
    nimbulus_media, N_OF(nimbulus_media),
    nimbulus_figurae, N_OF(nimbulus_figurae),
    nimbulus_motiva, N_OF(nimbulus_motiva),
    {
        [PAL_CALIDA]    =
            "The weather is golden: warm drizzle like amber, a small honey-coloured cloud, and sunbeams through it in warm chrome yellow.",
        [PAL_FRIGIDA]   =
            "The weather is cool and wintry: grey cloud, silver frost, blue-white mist, and fine white snow; the flesh beneath is cool and slightly chilled.",
        [PAL_SATURATA]  =
            "The personal rainbow is at full saturation — a thin compact arc of red, yellow, green, and violet — contrasting with the quieter flesh beneath.",
        [PAL_MUTA]      =
            "The weather is pulled to soft grey tones — dove cloud, pearl mist, silver rain — and barely separates from the quiet flesh.",
        [PAL_MONOCHROMA] =
            "The entire picture is worked in graded cool grey; the weather is visible only by a slight difference in value between the air above the head and the flesh.",
        [PAL_PRIMARIA]  =
            "The weather uses only red, yellow, and blue: a yellow sunbeam, a blue cloud, a few small red raindrops; the flesh remains a quiet warm mix.",
        [PAL_TERREA]    =
            "The weather takes on earth colours — a brown dusty cloud, an ochre drizzle, a faint rose fog — as though the subject stood in a windswept field."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat neutral wall, unmarked; the personal weather is the only non-flat element in the picture.",
        [FUN_ORNATUM]    =
            "Behind the figure, an ordinary domestic interior is indicated: a picture frame on the wall, a bookcase at the edge; each dry and untouched by the figure's personal weather.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a calm sunlit landscape extends into the distance — contradicting the figure's personal storm, which remains localised to their head and shoulders.",
        [FUN_ABSTRACTUM] =
            "The background is a soft neutral gradient of atmospheric grey, without specific objects; the figure's weather is the only spatial event in the picture.",
        [FUN_TENEBROSUM] =
            "The room behind the figure is dark, but the figure's personal weather carries its own faint light, so the figure is visible as if self-illuminated.",
        [FUN_LUMINOSUM]  =
            "The room behind the figure is brightly lit; the personal weather reads as a soft anomaly against the otherwise cheerful ground."
    },
    nimbulus_lumen, N_OF(nimbulus_lumen),
    nimbulus_texturae, N_OF(nimbulus_texturae),
    nimbulus_compositio, N_OF(nimbulus_compositio),
    "The figure is rendered in patient realist oil; a small personal weather system — cloud, rain, frost, mist, or rainbow — is painted last as thin soft glazes layered over the dry figure."
};

/* ============================================================
 * echokus — pictor geminationis (fictio)
 * ============================================================ */
static const int echokus_media[] = { MED_OLEUM };
static const char *const echokus_figurae[] = {
    "The subject is painted twice on the same canvas: once fully opaque and sharp at its proper position, and again displaced 6 cm to the right at about one-third opacity, so the face has a translucent twin standing beside it. Both heads fill the upper two-thirds of the frame.",
    "The subject is painted as a single sharp figure, but their head carries a ghosted echo: a translucent second outline of the same head, displaced upward by 3 cm and drawn in dilute paint, as though a moment earlier or later of the same sitting had been recorded over the main one.",
    "Two versions of the subject occupy the same picture plane: the main version is present in full colour and firm contour; behind and slightly offset to the left, a second paler version of the same face is visible through the first, as though in mild double-exposure.",
    "The subject's head is sharp; their left shoulder is doubled by a translucent ghost shoulder that extends outward 8 cm beyond the real one, as if the figure had just moved.",
    "The picture contains two superimposed paintings of the subject — one in full colour, one translucent — offset so the two mouths are 2 cm apart. Both mouths are individually legible; they are not blurred into one."
};
static const char *const echokus_motiva[] = {
    "the ghosted double's eyes are closed where the primary figure's eyes are open, suggesting two different moments of the same pose",
    "the translucent second figure holds a small mirror at chest height; the primary figure does not",
    "the two heads' outlines interlock at the temples, producing a small area where both contours are equally visible",
    "the ghost version has lifted one hand to the cheek; the primary figure's hands are at rest",
    "a thin line of pale paint connects the corner of the primary figure's mouth to the corner of the ghost's, as though the two were whispering to each other",
    "the ghost's collar is cleaner than the primary figure's; one has just put the coat on, the other has worn it for hours",
    "the ghost figure casts a second, fainter shadow on the wall behind, exactly parallel to the primary shadow"
};
static const char *const echokus_lumen[] = {
    "A single light source lights the primary figure fully; the ghost figure receives the same light but at reduced intensity throughout, producing matching but muted shadows.",
    "The primary and ghost figures both cast shadows on the wall behind, parallel but offset, as though two lamps had lit the same person at two slightly different times."
};
static const char *const echokus_texturae[] = {
    "The primary figure is painted with full opaque oil paint; the ghost figure is painted in thinned glazes over dry ground, about one third as thick, so the weave of the canvas shows through the ghost.",
    "Where the primary and the ghost overlap, the opaque paint of the primary covers the ghost entirely; where they do not overlap, the ghost reads as a faint transparency."
};
static const char *const echokus_compositio[] = {
    "The primary figure is centred; the ghost is offset along a single consistent direction (say 6 cm right and 2 cm down), so the composition reads as a slow horizontal drift.",
    "Both figures share the same vertical axis for head, shoulders, and chest; the offset is slight and is produced only by small horizontal and vertical displacements of the ghost."
};
static const Stylus stylus_echokus = {
    echokus_media, N_OF(echokus_media),
    echokus_figurae, N_OF(echokus_figurae),
    echokus_motiva, N_OF(echokus_motiva),
    {
        [PAL_CALIDA]    =
            "Both primary and ghost are painted in warm ochre and rose flesh; the ghost is the same palette at reduced value and chroma.",
        [PAL_FRIGIDA]   =
            "Both figures are cool: pale blue-grey flesh and silvered hair; the ghost is paler still, approaching the colour of the background wall.",
        [PAL_SATURATA]  =
            "The primary figure is at full saturation; the ghost is at exactly one-third saturation, so the difference between them is carried by chroma rather than by hue.",
        [PAL_MUTA]      =
            "Both primary and ghost are kept in a narrow range of soft halftones; the distinction between them is so quiet it is almost subliminal.",
        [PAL_MONOCHROMA] =
            "The entire picture is worked in graded warm grey; primary and ghost differ only by value and by hard versus soft contour.",
        [PAL_PRIMARIA]  =
            "The primary figure is painted in saturated primary colour areas; the ghost is painted in the same areas at half opacity over a white ground.",
        [PAL_TERREA]    =
            "Both figures are worked in raw umber, burnt sienna, and yellow ochre; the ghost is thinner, letting the warm ground beneath show through."
    },
    {
        [FUN_PLANUM]     =
            "Behind both figures is a single flat quiet ground against which both primary and ghost read cleanly.",
        [FUN_ORNATUM]    =
            "Behind both figures is a patterned wall — paisley, damask, or small stars — visible clearly through the ghost and only faintly through the primary.",
        [FUN_PAESAGIUM]  =
            "Behind both figures, a view through a window shows a calm landscape; it is unchanged between primary and ghost, as though the figures moved but the world did not.",
        [FUN_ABSTRACTUM] =
            "The background is a soft atmospheric field with no specific object; the displacement of the ghost is the picture's only spatial signal.",
        [FUN_TENEBROSUM] =
            "The background is deep warm dark; the primary figure emerges from it strongly, the ghost only faintly, as two successive moments of illumination.",
        [FUN_LUMINOSUM]  =
            "The background is clean bright white; both figures read as silhouettes against it, one crisp and one faint."
    },
    echokus_lumen, N_OF(echokus_lumen),
    echokus_texturae, N_OF(echokus_texturae),
    echokus_compositio, N_OF(echokus_compositio),
    "The subject is painted twice on the same canvas — once as a fully opaque realist portrait, and once offset and in dilute glazes — so the picture is a double-exposure of two moments of the same sitting."
};

/* ============================================================
 * fulguritus — pictor corporum vitreorum (fictio)
 * ============================================================ */
static const int fulguritus_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const fulguritus_figurae[] = {
    "The subject's skin is translucent, rendered as though cast from warm fused glass; internal veins of blue-white light are visible through the flesh, branching from the throat upward into the face and outward along the arms.",
    "The head and shoulders appear cast in a single pour of amber glass; within the head, a soft glowing network of fine blue lines radiates outward from behind the eyes to the edges of the skull.",
    "The face is translucent: the light source behind the figure shows through the cheeks and the edge of the jaw, so those areas glow a warm orange from within while the eyes and lips remain opaque.",
    "The subject reads as a figure made of clear cold glass with a single bright lightning-form frozen inside the chest, its branches visible through the sternum and clavicles.",
    "The skin is a honey-coloured glass; tiny bubbles (each 1-2 mm across) are suspended inside the substance of the face, visible as small pale highlights that do not align with the light source."
};
static const char *const fulguritus_motiva[] = {
    "a single bright lightning-branch is frozen inside the chest, its main axis about 20 cm long and its branches terminating at the collar and the shoulders",
    "the hair is visible as a mass of fused cold glass, each strand catching light as a separate tiny refraction",
    "a small chipped area at the corner of the jaw shows fresh clear glass beneath the darker external surface",
    "the eyes are opaque where the rest of the face is translucent, rendered as small dense almonds of dark resin",
    "a thin crack runs from the temple down to the collarbone, its line filled with a thin pale blue light",
    "a single air bubble, 4 mm across, is frozen exactly at the bridge of the nose",
    "the mouth is sealed shut and painted opaque; the rest of the face is glass"
};
static const char *const fulguritus_lumen[] = {
    "The figure is lit both externally — from a single raking source at the upper left — and internally, from the lightning-form in the chest and the light-veins in the head; the two lights do not always agree.",
    "The picture's highlights come from inside the figure; the external light provides only the contour and the edges, while the internal glow gives the face its warmth."
};
static const char *const fulguritus_texturae[] = {
    "The paint is applied in many thin glazes to achieve the optical depth of glass; no single layer is opaque, and the cumulative surface reads as translucent substance rather than as pigment.",
    "The internal lightning-veins are painted last with a brush loaded in pale cold blue, drawn over the dried translucent passages as single decisive strokes."
};
static const char *const fulguritus_compositio[] = {
    "The figure is centred and the internal lightning-form is aligned along the central vertical axis of the chest; the picture's spatial logic is built around this internal axis.",
    "The composition is symmetric; the figure is placed in a deep dark space and lit from both within and without, so the head reads as a glowing object floating in a dark room."
};
static const Stylus stylus_fulguritus = {
    fulguritus_media, N_OF(fulguritus_media),
    fulguritus_figurae, N_OF(fulguritus_figurae),
    fulguritus_motiva, N_OF(fulguritus_motiva),
    {
        [PAL_CALIDA]    =
            "The glass is warm amber; the internal light is gold; the eyes and mouth are deep resin-brown; the picture glows in a honey register.",
        [PAL_FRIGIDA]   =
            "The glass is cold pale blue; the internal light is almost white; the background is a deep cold navy; the figure looks as though lit from ice.",
        [PAL_SATURATA]  =
            "The internal lightning is pure electric violet; the glass body is a saturated amber; the contrast reads as pulled from a neon sign.",
        [PAL_MUTA]      =
            "Both glass and internal light are pulled to pale tones — dusty peach, faint celadon, soft lilac — and the effect is quiet rather than dramatic.",
        [PAL_MONOCHROMA] =
            "The entire picture is worked in graded blue-white, from palest ice at the lightning to deepest marine at the shadow of the jaw.",
        [PAL_PRIMARIA]  =
            "The internal lightning branches into three separate colours — pure red, yellow, and blue — each radiating from its own point inside the chest.",
        [PAL_TERREA]    =
            "The glass reads as earthen amber and smoked brown; the internal light is muted gold; the whole picture has the register of worked resin or amber."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single deep flat dark; the glass body is the only bright object in the picture.",
        [FUN_ORNATUM]    =
            "Behind the figure, a pattern of small painted stars or tiny light-points covers the dark ground, as though the figure stood in a night sky.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a dark storm-landscape is visible in the far distance, with small bright branches of external lightning echoing the internal ones.",
        [FUN_ABSTRACTUM] =
            "The background is a field of slow cool gradients; the figure's internal glow is the picture's only hard light.",
        [FUN_TENEBROSUM] = "The background is pure black; the figure reads as a single luminous object floating in nothing.",
        [FUN_LUMINOSUM]  =
            "The background is a bright cool white; the glass body reads as a faint refractive silhouette against it, with the internal lightning only barely visible."
    },
    fulguritus_lumen, N_OF(fulguritus_lumen),
    fulguritus_texturae, N_OF(fulguritus_texturae),
    fulguritus_compositio, N_OF(fulguritus_compositio),
    "The figure is built up in many thin transparent glazes to read as glass; a single internal lightning-form is painted last in pale cold blue, drawn as decisive single strokes through the translucent flesh."
};

/* ============================================================
 * tesselarius — pictor testarum confractarum (fictio)
 * ============================================================ */
static const int tesselarius_media[] = { MED_OLEUM, MED_COLLAGE };
static const char *const tesselarius_figurae[] = {
    "The portrait is constructed from dozens of small rectangular painted tiles, each 2 to 4 cm on a side, fitted together like slightly misaligned pottery shards. Each tile carries a painted fragment of a feature — a part of an eye, a corner of a lip, a stretch of cheek — and the joints between tiles are hairline dark lines.",
    "The head and shoulders are built from about sixty tiles of varying sizes and rectangular proportions. Each tile is individually painted with a fragment of the larger portrait, and the tiles do not quite align at their edges, leaving the picture legible as a person but visibly reassembled.",
    "The whole picture is divided into a loose irregular grid of painted tiles; each tile is finished to a polished smooth surface, and each is separated from its neighbours by a thin dark grout-line 1 mm wide.",
    "The portrait is complete and recognisable, but obvious fault-lines run through it horizontally and diagonally; the fault-lines divide the picture into roughly thirty large painted plates, each a fragment of the continuous portrait.",
    "Some tiles are slightly rotated relative to their neighbours by a degree or two, so the features they carry are slightly off-axis within the larger figure; the face therefore reads as alive and reassembled rather than mechanical."
};
static const char *const tesselarius_motiva[] = {
    "three small tiles are missing from the lower-right corner of the chest, exposing a dark backing beneath and leaving three neat rectangular voids",
    "one tile at the temple carries a fragment of an entirely different picture — a tiny section of sky, a corner of a distant landscape — where the face-fragment should have been",
    "the tile carrying the left eye is slightly larger than the others (about 5 cm across) and is visibly of a different vintage — its paint slightly darker, its grout slightly browner",
    "a single long rectangular tile runs horizontally across the mouth, splicing the upper and lower lips into discontinuous halves",
    "the grout between tiles is dark umber in most of the face but a pale cool blue at the throat, marking the picture as made from two different batches of tiles",
    "one tile has been repaired with visible gold-coloured filler at its cracked edge, in a thin bright line",
    "the tile at the crown of the head bears a small painted number (e.g. '14') in the lower corner, as though from a numbered set"
};
static const char *const tesselarius_lumen[] = {
    "The light within each tile is consistent with the overall light direction of the picture, but the edge of each tile catches a hairline of highlight at its boundary, giving the whole picture a faint crosshatch of light at tile-joints.",
    "Each tile is individually glazed and sealed; under raking light the tile-edges catch a row of tiny highlights that reveal the construction."
};
static const char *const tesselarius_texturae[] = {
    "Each tile is painted in full oil realism and then sealed to a glossy finish; between tiles, dark grout-line mortar 1 mm wide separates one painted plate from the next.",
    "Some tiles are flat and polished; others are slightly raised from the picture plane by 2-3 mm, giving the surface physical relief at the boundaries between plates."
};
static const char *const tesselarius_compositio[] = {
    "The face is centred and reads whole from a distance; up close the composition is a patchwork, and the viewer's eye moves between reading the portrait and reading the grid of tiles.",
    "The grid of tiles is irregular — no two tiles are the same size — and this irregularity is itself a compositional device, clustering more small tiles at the face and fewer larger ones at the shoulders."
};
static const Stylus stylus_tesselarius = {
    tesselarius_media, N_OF(tesselarius_media),
    tesselarius_figurae, N_OF(tesselarius_figurae),
    tesselarius_motiva, N_OF(tesselarius_motiva),
    {
        [PAL_CALIDA]    =
            "The tiles carry warm ochre, terracotta, and rose tones; the grout is a warm dark brown; the whole picture reads as fired clay reassembled.",
        [PAL_FRIGIDA]   =
            "The tiles carry cool grey, pale blue, and stone-green tones; the grout is a cool dark slate; the picture reads as porcelain, not earthenware.",
        [PAL_SATURATA]  =
            "The tiles are painted at full saturation in their individual fragments; the grout between them is dark, so the picture reads as stained-glass in its colour force.",
        [PAL_MUTA]      =
            "The tiles are painted in soft quiet tones; the grout between them is almost invisible; the picture reads as subtly segmented rather than as openly fragmented.",
        [PAL_MONOCHROMA] =
            "All tiles are painted in graded warm sepia; the grout is a single fixed dark brown, consistent across the picture.",
        [PAL_PRIMARIA]  =
            "Tiles cycle through red, yellow, blue, and white in a strict but irregular order; each tile is a flat field of one primary colour carrying its fragment of portrait.",
        [PAL_TERREA]    =
            "The tiles are entirely earth-coloured — umber, sienna, ochre, cream — as though the portrait were made from fragments of ancient plaster."
    },
    {
        [FUN_PLANUM]     =
            "Behind the tiled figure is a single flat neutral field extending to all frame edges; the tiles of the figure end at a clean silhouette.",
        [FUN_ORNATUM]    =
            "The tiles continue beyond the figure into the background, where they carry small painted motifs — stars, lines, small plants — rather than portrait-fragments.",
        [FUN_PAESAGIUM]  =
            "The tiles continue beyond the figure into a tiled landscape — a field of tiles carrying fragments of hill, sky, and road behind the shoulder.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the tiles continue as abstract fragments of colour with no underlying image; the grid of tiles itself becomes the background.",
        [FUN_TENEBROSUM] =
            "Behind the figure, the tiles are much darker — deep warm near-black — and only a faint change in hue distinguishes them from pure ground.",
        [FUN_LUMINOSUM]  =
            "Behind the figure, the tiles are bright ivory and catch the room-light cleanly; the figure reads as a slightly darker patch of grid."
    },
    tesselarius_lumen, N_OF(tesselarius_lumen),
    tesselarius_texturae, N_OF(tesselarius_texturae),
    tesselarius_compositio, N_OF(tesselarius_compositio),
    "The entire portrait is assembled from many small rectangular painted tiles, each bearing a fragment of the larger image, fitted together with thin dark grout lines and occasionally slightly misaligned."
};

/* ============================================================
 * obscurus — pictor luminis intus positi (fictio)
 * ============================================================ */
static const int obscurus_media[] = { MED_OLEUM };
static const char *const obscurus_figurae[] = {
    "The subject emerges from deep warm darkness; the only light in the picture comes from a single small source that is inside the body — a glow from within the mouth, visible past slightly parted lips, lighting the underside of the chin and nose from beneath.",
    "The figure is painted in shadow; only the face is visible, lit from below and within by a warm light that seems to emerge from the open palm held at chest height, which the subject gazes at.",
    "The subject's chest glows faintly through the coat, as though a lantern had been placed inside the ribcage; the light rises upward and lights the underside of the jaw and the hollows of the throat, but the eyes remain in shadow.",
    "No external light source is admitted. A single warm gold light issues from the centre of the subject's forehead — not a lamp, simply a soft glow — and casts the surrounding face upward and outward into soft warmth.",
    "A small bright sphere is held in the subject's cupped hand at waist height; its light climbs the body from below, rendering the shadow-side of the face visible only as a rim of cool reflected colour."
};
static const char *const obscurus_motiva[] = {
    "a small candle flame is visible inside the slightly parted mouth, its tip just catching at the upper lip",
    "the palm of one hand held at chest height carries a single glowing ember, the only bright point in the picture",
    "a thin luminous thread runs from the throat upward to the chin, lighting its immediate surround in warm gold",
    "the subject's eyes reflect the internal light back as two small bright specks, though no exterior source exists",
    "a soft glow lines the inside edge of one nostril, as if a tiny fire were burning within",
    "a cluster of small warm sparks has collected at the hollow of the throat, each a 1-2 mm impasto dot of pale gold",
    "the knuckles of one hand glow faintly where the skin is thinnest, as though the light were leaking outward between the bones"
};
static const char *const obscurus_lumen[] = {
    "The only light in the picture is the internal source; it illuminates the face from below and within, producing an inverted lighting — highlights under the chin, shadows on the forehead — that reads as quietly unnatural.",
    "The internal light is warm and small; its reach is limited, so the outer edges of the face fall back into deep warm black within 10 to 15 cm of the source."
};
static const char *const obscurus_texturae[] = {
    "The darks are worked in many thin transparent glazes over a toned brown ground; the tiny internal light source and its lit passages are laid last as soft warm impasto.",
    "No bright external highlights are permitted; all luminous passages are warm and restricted, and the picture's surface is dark and still except at the single internal source."
};
static const char *const obscurus_compositio[] = {
    "The picture is centred vertically; the internal light source occupies the geometric centre, and the face above it is drawn upward into the light.",
    "Most of the picture is given to warm darkness; the lit portion is compact and carefully placed, occupying perhaps a quarter of the total area."
};
static const Stylus stylus_obscurus = {
    obscurus_media, N_OF(obscurus_media),
    obscurus_figurae, N_OF(obscurus_figurae),
    obscurus_motiva, N_OF(obscurus_motiva),
    {
        [PAL_CALIDA]    =
            "The internal light is warm amber-gold; the darkness around it is a deep warm brown-black; nothing cool is admitted.",
        [PAL_FRIGIDA]   =
            "The internal light is cold pale blue; the darkness around it is a deep cool navy; the figure reads as though lit by a moon swallowed.",
        [PAL_SATURATA]  =
            "The internal light is pure saturated signal-red or orange; its colour dominates the face entirely and bleeds outward into the surrounding dark.",
        [PAL_MUTA]      =
            "The internal light is a pale ivory; the surrounding dark is a warm ashen brown; the effect is quiet and almost ceremonial.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone; the internal light is the lightest value, the surrounding dark the deepest, with no colour elsewhere.",
        [PAL_PRIMARIA]  =
            "The internal light is one pure primary colour — red, yellow, or blue — and the surrounding dark is its complement at very low value.",
        [PAL_TERREA]    =
            "The internal light is a warm ochre-gold; the surrounding darkness is raw umber and burnt sienna; the picture reads as worked earth lit from within."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single unmodulated deep warm dark, indistinguishable from the ground at the picture's edges.",
        [FUN_ORNATUM]    =
            "Behind the figure, in the outer dark, a few tiny distant pale motifs — small painted stars or candles — are just barely visible as further points of internal light.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a far dark landscape is indicated: a low horizon, a single dark tree, a distant hill, all painted at very low value.",
        [FUN_ABSTRACTUM] = "The background is pure warm black; no object, no horizon, no edge is indicated anywhere.",
        [FUN_TENEBROSUM] =
            "The background is the deepest passage in the picture; it absorbs all but the internal light, and the figure emerges from it only where that light reaches.",
        [FUN_LUMINOSUM]  =
            "The background is a single lit distant glow at the far horizon, lower than the figure; it provides only the faintest cool rim behind the shoulders."
    },
    obscurus_lumen, N_OF(obscurus_lumen),
    obscurus_texturae, N_OF(obscurus_texturae),
    obscurus_compositio, N_OF(obscurus_compositio),
    "The picture is built from deep translucent glazes over a toned warm brown ground; the single internal light source — inside the mouth, the chest, or the palm — is painted last in warm impasto, and everything else remains in warm darkness."
};

/* ============================================================
 * filumentus — pictor filorum parallelorum (fictio)
 * ============================================================ */
static const int filumentus_media[] = { MED_OLEUM, MED_GOUACHE };
static const char *const filumentus_figurae[] = {
    "The entire portrait is built from fine parallel painted threads, each line about 1 mm thick, laid on the canvas in long unbroken strokes. The face reads as an embroidered tapestry of coloured lines: warm tones at the cheek, cool tones under the eye, each hue a single continuous thread running for 10 to 20 cm.",
    "The face is rendered as a weave: vertical threads of flesh-warm colour are crossed by a much fewer number of horizontal threads in cool tones, and the intersections form the modelling of the features. No area is blended.",
    "The subject's head is constructed from long radial threads that fan outward from a point at the centre of the forehead; each thread changes hue as it moves outward, so the overall face reads as a radial tapestry of graded colour.",
    "The hair is a dense bundle of parallel threads — hundreds of them — each a slightly different shade from charcoal to warm umber, each laid in a single long stroke running from the crown to the shoulder.",
    "Every feature is indicated by a change in the hue of the threads rather than by any outline: the eye is a cluster of very short cool threads, the lip a cluster of warm red threads, each thread remaining parallel to its neighbours."
};
static const char *const filumentus_motiva[] = {
    "one small area of the weave at the shoulder has unravelled slightly, and three or four long threads hang loose, painted in bright coloured lines that extend past the silhouette",
    "a single bright gold thread runs horizontally across the entire picture at eye level, as though a single warp of precious metal had been added to the weave",
    "the collar carries a running band of alternating warm and cool threads, producing a striped border around the throat",
    "a knotted fringe of short threads hangs along the lower edge of the picture, each fringe-thread a different colour",
    "a small patch where the weave has been repaired with slightly different-coloured thread is visible at the temple, its boundary faintly rectangular",
    "the threads of one eyebrow have been laid in a different direction from those of the surrounding face, so the eyebrow reads as a small island of perpendicular weave",
    "a long loose thread of saturated red drifts down across the cheek and neck, unattached to the surrounding weave"
};
static const char *const filumentus_lumen[] = {
    "The light is implied only by the hue of the threads — warmer hues read as lit, cooler hues read as shadow, and the two kinds of thread alternate to produce the illusion of form.",
    "No cast shadow is admitted; all light and shadow are produced by the density and hue of the parallel threads, and the picture reads as flat woven colour."
};
static const char *const filumentus_texturae[] = {
    "Each painted thread is laid as a single long confident stroke, 1 to 2 mm thick, and no stroke is ever crossed or painted over; the surface is composed entirely of discrete parallel lines.",
    "The threads have a slight physical relief of about 0.5 mm, so under raking light the picture reveals itself as a directional weave and casts small shadows from each line."
};
static const char *const filumentus_compositio[] = {
    "All threads run in a single dominant direction across the picture — usually vertical — with only small areas of perpendicular thread for the eyes, lips, and other features.",
    "The composition is woven rather than drawn: the figure's silhouette is the edge of the weave, not a drawn contour, and no line crosses from figure into background."
};
static const Stylus stylus_filumentus = {
    filumentus_media, N_OF(filumentus_media),
    filumentus_figurae, N_OF(filumentus_figurae),
    filumentus_motiva, N_OF(filumentus_motiva),
    {
        [PAL_CALIDA]    = "The threads are warm — ochre, sienna, coral, gold — and the picture glows in a fire register.",
        [PAL_FRIGIDA]   =
            "The threads are cool — slate, viridian, pale cobalt, silver — and the picture reads as though woven from winter sky.",
        [PAL_SATURATA]  =
            "Every thread is at full saturation; adjacent threads contrast sharply in hue, so the weave reads as chromatic and almost loud at close distance.",
        [PAL_MUTA]      =
            "The threads are kept in a narrow band of soft halftones — mushroom, cream, pale rose, dust-blue — and the weave reads as quiet and atmospheric.",
        [PAL_MONOCHROMA] =
            "All threads are in graded warm sepia alone; the modelling of the face is produced by density and value of the threads, not by hue.",
        [PAL_PRIMARIA]  =
            "Only red, yellow, and blue threads are admitted; the apparent colours of flesh and hair are produced by the interleaving of these three primaries.",
        [PAL_TERREA]    =
            "The threads are raw umber, burnt sienna, yellow ochre, and terre verte — the palette of an ancient worn tapestry."
    },
    {
        [FUN_PLANUM]     =
            "The threads of the background run in the same direction as those of the figure, but all in a single muted hue; no specific object is indicated.",
        [FUN_ORNATUM]    =
            "The background threads weave a geometric pattern — diamonds, stars, small flowers — in two or three contrasting hues behind the figure.",
        [FUN_PAESAGIUM]  =
            "The background threads change hue in horizontal bands to suggest a landscape: a band of greens for grass, a band of blues for sky, each still woven as parallel threads.",
        [FUN_ABSTRACTUM] =
            "The background is an uninflected field of threads in a single mid-grey tone; no distinction between figure-weave and ground-weave is admitted except by small hue shifts.",
        [FUN_TENEBROSUM] =
            "The background threads are deep warm dark, and the figure's threads emerge from them only by slight value shifts; the weave reads as a single dark cloth.",
        [FUN_LUMINOSUM]  =
            "The background threads are pale bright cream; the figure's threads read as a slightly denser, more varied passage of weave within a luminous whole."
    },
    filumentus_lumen, N_OF(filumentus_lumen),
    filumentus_texturae, N_OF(filumentus_texturae),
    filumentus_compositio, N_OF(filumentus_compositio),
    "The entire picture is constructed from fine parallel painted threads, each laid as a single long unbroken stroke; no blending, no crossing, no painterly gesture is admitted anywhere."
};

/* ============================================================
 * chronofugus — pictor ex futuro respiciens (fictio)
 * ============================================================ */
static const int chronofugus_media[] = { MED_OLEUM, MED_TEMPERA };
static const char *const chronofugus_figurae[] = {
    "The subject is painted with the clinical anthropological distance of someone rendering a figure from five centuries away. The portrait is competent and careful, but small anachronisms are confidently placed: a button that does not yet exist, a collar-stitch a century too early, an eye-colour the wrong shade by one gene.",
    "The head and shoulders are rendered in patient academic realism, but every decorative detail is subtly wrong in the way an archaeologist might misreconstruct: the hair is parted on the incorrect side, a piece of jewellery belongs to an adjacent century, the posture is a decade anachronistic.",
    "The face is painted with the quiet reverence of a historical reconstruction. It reads as a specific person, but one the painter has never met — only heard described across a long distance of time.",
    "The subject is present with full fidelity, but the painting's conventions belong to a time that has not yet arrived: a pigment that does not exist, a framing convention for a culture centuries hence, a medium described in a footnote but not seen.",
    "The portrait is laid on with the careful correctness of a museum catalogue illustration; the subject is being documented, not celebrated, by a hand that belongs to a far descendant civilisation."
};
static const char *const chronofugus_motiva[] = {
    "a small square label is pinned beside the shoulder, carrying four lines of meticulous archival text in an unfamiliar alphabet",
    "a narrow metallic instrument of unclear present-day purpose hangs from a cord around the neck, its function specific but not yet invented",
    "the collar carries a small woven badge bearing a symbol that does not yet exist as a symbol",
    "a tiny gridded rule is visible at the edge of the picture, marked off in units neither metric nor imperial",
    "the background contains a single piece of furniture whose design has not yet been produced but will be in three hundred years",
    "a small crack across the painting's surface has been carefully retouched by a later conservator; the retouching is visible and dated in pencil at the corner"
};
static const char *const chronofugus_lumen[] = {
    "The light is soft, even, and archival: a museum-like illumination that respects the subject without shadowing the face dramatically.",
    "The illumination is indirect and cool, as though the picture were lit by the fluorescents of a future gallery rather than by a contemporary sun."
};
static const char *const chronofugus_texturae[] = {
    "The paint is carefully applied in many thin patient layers; the surface has been slightly aged in a way that feels deliberate, as though the painting already is what it will later become.",
    "The handling is absolutely correct but the correctness belongs to a later century's idea of how a portrait of this period should look."
};
static const char *const chronofugus_compositio[] = {
    "The figure is centred frontally in the classical portrait manner; the composition follows an ancient convention with one small anachronistic deviation — a half-centimetre asymmetry that is deliberate.",
    "The portrait is composed with the formality of a civic commission, stable and balanced, but one compositional detail (a horizon height, a framing margin) does not belong to any known period."
};
static const Stylus stylus_chronofugus = {
    chronofugus_media, N_OF(chronofugus_media),
    chronofugus_figurae, N_OF(chronofugus_figurae),
    chronofugus_motiva, N_OF(chronofugus_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm ochre, muted madder, and lead-white, with every hue aged slightly toward the warm end — as though already in an archive.",
        [PAL_FRIGIDA]   = "The palette is cool grey, slate blue, and pale olive, held as though under museum glass.",
        [PAL_SATURATA]  =
            "A single saturated passage — a ribbon, a badge — reads as period-accurate; everything else is held in a quieter archival register.",
        [PAL_MUTA]      =
            "The whole picture is held in quiet museum tones — taupe, dust, cream, stone — every colour pulled down as though seen through a century of varnish.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone, with the formality and distance of a posthumous daguerreotype.",
        [PAL_PRIMARIA]  =
            "The three primary colours appear only as small symbolic accents in archival detail — a red ribbon, a yellow emblem, a blue thread — each period-appropriate but placed slightly wrongly.",
        [PAL_TERREA]    =
            "The palette is raw umber, burnt sienna, and yellow ochre, aged toward the olive end; the picture reads as fresco copied from a damaged original."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single plain flat field painted in the quiet register of a museum backdrop, with no specific object.",
        [FUN_ORNATUM]    =
            "Behind the figure, period-appropriate ornamental elements are present — a pilaster, a drapery, a carved inscription — but at least one detail is from the wrong century.",
        [FUN_PAESAGIUM]  =
            "Through a window visible at one edge, a landscape is shown that does not match any known present: a distant structure whose engineering is not yet invented, beneath a recognisable sky.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, a soft atmospheric field with no specific objects, as though the picture had been mounted against an unmarked archival paper.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a dignified near-black, the conventional backing for an official portrait two centuries ago and two centuries hence.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a high clean archival grey lit from above, as though the picture were already hanging in its future gallery."
    },
    chronofugus_lumen, N_OF(chronofugus_lumen),
    chronofugus_texturae, N_OF(chronofugus_texturae),
    chronofugus_compositio, N_OF(chronofugus_compositio),
    "The portrait is painted with the careful correctness of a historical reconstruction — specific and reverent, but with small confident anachronisms placed as though the painter were separated from the subject by centuries."
};

/* ============================================================
 * somniator — pictor somniorum (fictio)
 * ============================================================ */
static const int somniator_media[] = { MED_OLEUM, MED_GOUACHE };
static const char *const somniator_figurae[] = {
    "The subject is painted as if the painter had only ever seen them in dreams. The features are confidently rendered but slightly inconsistent across the picture: the left half of the face is younger than the right, the smile drifts between eye and mouth, and the hair changes length by 2 cm across the shoulders.",
    "The portrait is rendered with full commitment and no hesitation, but the specifics do not quite hold: both eyes are of slightly different colours, the mouth does not match the jaw beneath it, and the left ear is a centimetre higher than the right.",
    "Every feature is painted with the clarity of waking life, but the overall construction refuses to settle: the face reads as a specific person, but if the viewer looks twice, the specific person is different.",
    "The subject's face is softly doubled in a way that does not correspond to any physical motion: two noses at a 3 mm offset, two slight smiles at different intensities, one head that is two heads averaging toward a single impression.",
    "The features are painted with the over-sharpness of dream memory: the eyes are more present than the nose, the mouth more present than the cheeks, and parts of the face that seemed important at the moment of dreaming have been finished while others remain summary."
};
static const char *const somniator_motiva[] = {
    "a small object — a seashell, a spool of thread, a key — is held loosely in the hand, its specific identity changing as the viewer looks at it",
    "behind the shoulder, a doorway opens onto a room that cannot coexist with the room the figure is standing in",
    "a small embroidered sigil is stitched into the collar in thread, its shape suggesting writing from no language ever learned",
    "the subject wears a small flower pinned at the throat; the species is not a real species but is painted with complete botanical specificity",
    "a thin gold chain hangs from the ear, and at its end is an object which appears to be an object but fails to resolve into any particular one",
    "the hands are painted with unusual care, in contrast to the rest of the figure; the hands are specific and memorable in a way the face is not"
};
static const char *const somniator_lumen[] = {
    "The light is inconsistent from area to area: the left side of the face is lit from the upper left, the right side from the upper right, but the contradiction is gentle and the face remains legible.",
    "The illumination belongs to an unreal interior: too soft to be a room, too local to be outdoors, too warm to be either."
};
static const char *const somniator_texturae[] = {
    "The paint is applied in confident patient strokes in some areas and in softer half-finished passages in others; the finished passages are exactly those which the dreamer remembered most clearly.",
    "Small areas are sharp and overworked; surrounding areas are impressionistic and generalized, creating a field of varied finish that mirrors the uneven attention of dream memory."
};
static const char *const somniator_compositio[] = {
    "The figure is centred but its outline is slightly inconsistent: the right edge of the silhouette is drawn twice, 1-2 cm apart, as the dreamer's memory revised itself mid-painting.",
    "The composition holds the figure in place, but small areas of the picture are finished to a different specification than others, as though the painter had worked from several dreams of the same person."
};
static const Stylus stylus_somniator = {
    somniator_media, N_OF(somniator_media),
    somniator_figurae, N_OF(somniator_figurae),
    somniator_motiva, N_OF(somniator_motiva),
    {
        [PAL_CALIDA]    =
            "The palette is warm honey and dusky rose, specific but slightly wrong; the hues have the impossible saturation of remembered light.",
        [PAL_FRIGIDA]   =
            "The palette is cool pearl, twilight blue, and a faint silver; it reads as the palette of a room one has never quite visited.",
        [PAL_SATURATA]  =
            "A single saturated colour — a red ribbon, a green leaf — is more vivid than any colour in waking life; everything else is slightly underdescribed.",
        [PAL_MUTA]      =
            "The whole picture is kept in soft, almost silent halftones, with the luminosity of a dream that has just ended.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone, as though the dream had been remembered the morning after through a sepia filter.",
        [PAL_PRIMARIA]  =
            "Red, yellow, and blue appear as small specific symbols — a cup, a leaf, a bird — each improbably saturated in a picture otherwise held in quieter tones.",
        [PAL_TERREA]    =
            "The palette is raw umber, yellow ochre, and a soft green-grey, with the slightly unreal warmth of light remembered rather than seen."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single plain field whose colour is specific but whose identity is unclear — wall? curtain? sky?",
        [FUN_ORNATUM]    =
            "Behind the figure, decorative elements are visible — small painted stars, a line of foliage, a fragment of pattern — each specific but not matching any real wallpaper or mural.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a landscape appears that could not exist: a hill of a specific but impossible geometry, a distant door in the sky, a tree that is also a building.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the space has the soft drift of an unfinished dream: no horizon, no object, no edge; only gently-shifting tone.",
        [FUN_TENEBROSUM] =
            "The background is a warm dark that seems to pulse faintly, as though remembered rather than observed; the figure emerges from it at a single soft warm rim.",
        [FUN_LUMINOSUM]  =
            "The background is a high luminous cream, too bright for any real light, softly flooding the entire picture from all directions."
    },
    somniator_lumen, N_OF(somniator_lumen),
    somniator_texturae, N_OF(somniator_texturae),
    somniator_compositio, N_OF(somniator_compositio),
    "The figure is painted with the full conviction of a dreamed memory: confidently rendered, specifically wrong in several places at once, and never corrected."
};

/* ============================================================
 * vacuarius — pictor absentiae (fictio)
 * ============================================================ */
static const int vacuarius_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const vacuarius_figurae[] = {
    "The subject is not painted at all. Instead, the picture is a single person-shaped absence: the background — wall, drapery, distant landscape — has moved aside, displaced and bent around the empty space where the subject stands. A specific individual is perfectly legible by inference alone.",
    "Where the figure would be, there is an area of unpainted or softly-toned negative space. Every object and surface behind the figure is continuous up to the edge of the absence and resumes on the other side, but the displacement is consistent with a specific head and shoulders.",
    "The painter has rendered everything except the subject: the chair behind them, the curtain beside them, the jewellery they would have worn, the cast shadow they would have produced — all are present, and the subject is a hole through which these things are now visible.",
    "The figure is present only as a soft aura of difference: the background paint is slightly thinner, slightly lighter, slightly cooler where the figure was. A specific face is readable in the aura.",
    "The absence is silhouetted sharply against a fully-worked background. No features are drawn within the silhouette, but the silhouette's every contour is as specific as a line portrait would be."
};
static const char *const vacuarius_motiva[] = {
    "a pair of earrings hangs in the empty air where the ears would have been, each catching a single small highlight",
    "a hat sits on empty space where the crown of the head would have been, fully rendered but unsupported",
    "a small object — a flower, a book — is held by empty air at chest height, in the position a hand would have held it",
    "the cast shadow of the figure falls on the floor behind, fully rendered in every contour, even though the figure itself is not",
    "a single strand of jewellery hangs from nothing around the absent neck, its links and pendant fully realised",
    "a spoken-breath mist hangs in the air in front of the empty mouth, painted in thin warm-white glazes"
};
static const char *const vacuarius_lumen[] = {
    "The light is consistent with a normal room, fully cast onto every present object; the absence receives no light because there is nothing there to catch it.",
    "The illumination produces exactly the shadows a present figure would produce, only without any figure; the shadows are the evidence of the absence."
};
static const char *const vacuarius_texturae[] = {
    "The background and objects are painted in confident opaque oil; the absence itself is either raw canvas or the faintest tone-wash, deliberately unworked.",
    "The boundary between painted and absent passages is sharp and clean — no fade, no soft transition — because the absence is total, not gradual."
};
static const char *const vacuarius_compositio[] = {
    "The composition is built around a specific person-shaped void; the rest of the picture is arranged to make the void legible, as though the background were leaning away from what is not there.",
    "The absent figure occupies the upper two-thirds of the frame; every painted element is arranged to respect the silhouette of the person who is not present."
};
static const Stylus stylus_vacuarius = {
    vacuarius_media, N_OF(vacuarius_media),
    vacuarius_figurae, N_OF(vacuarius_figurae),
    vacuarius_motiva, N_OF(vacuarius_motiva),
    {
        [PAL_CALIDA]    =
            "The surrounding picture is warm — ochre, madder, cream — and the absence inside it is kept as raw warm canvas.",
        [PAL_FRIGIDA]   =
            "The surrounding picture is cool — slate, silver, pale blue — and the absence is kept as a paler cool area, barely distinguishable from the ground.",
        [PAL_SATURATA]  =
            "The surrounding picture is at full saturation; the absence, by contrast, reads as a soft neutral void at the picture's centre.",
        [PAL_MUTA]      =
            "The whole picture is held in soft halftones; the absence is only very subtly different from the surrounding tone, and almost requires the viewer's attention to find.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm grey alone; the absence is the lightest passage in the picture, reading as quiet highlight rather than as shape.",
        [PAL_PRIMARIA]  =
            "The surrounding picture uses flat red, yellow, and blue; the absence is pure white — the unpainted ground showing through.",
        [PAL_TERREA]    =
            "The surrounding picture is raw umber and burnt sienna over warm ground; the absence is the exposed warm ground itself."
    },
    {
        [FUN_PLANUM]     =
            "Behind the absence is a single plain painted wall, continuous to all edges and present on both sides of the silhouette.",
        [FUN_ORNATUM]    =
            "Behind the absence, a richly-painted domestic interior is fully visible: framed pictures, patterned wallpaper, a carved chair-back, each accurate except where displaced by the figure that is not there.",
        [FUN_PAESAGIUM]  =
            "Behind the absence, a fully-painted landscape continues uninterrupted up to the silhouette and resumes on the other side.",
        [FUN_ABSTRACTUM] =
            "Behind the absence, the background is a field of flowing tone with no specific object; the absence reads as a specific silhouette within this undefined space.",
        [FUN_TENEBROSUM] =
            "The background is deep and fully painted; the absence reads as a slightly paler person-shaped void within the otherwise continuous darkness.",
        [FUN_LUMINOSUM]  =
            "The background is a bright fully-painted field; the absence reads as a darker person-shaped void where the light has not been allowed to pass."
    },
    vacuarius_lumen, N_OF(vacuarius_lumen),
    vacuarius_texturae, N_OF(vacuarius_texturae),
    vacuarius_compositio, N_OF(vacuarius_compositio),
    "The picture is painted in its entirety except for a single specific person-shaped area, which is left as negative space; a specific individual is legible by implication alone."
};

/* ============================================================
 * mortuarius — pictor memoriae (fictio)
 * ============================================================ */
static const int mortuarius_media[] = { MED_OLEUM };
static const char *const mortuarius_figurae[] = {
    "The subject is alive and well, but the portrait is painted with the conventions of a memorial: subdued colours, a dignified pose, quiet composition, and a soft stillness that belongs to the memory of a person rather than to their present life.",
    "The face is rendered with the quiet respect of a posthumous commission — every feature painted carefully, no smile permitted, the gaze level and composed. The subject is vital and in good health, but the painting treats them as though already enshrined.",
    "The portrait has the formality of a bereavement photograph: centred, still, flat-lit, with a single pale flower held near the throat and a thin horizontal decorative rule painted quietly along the lower edge.",
    "The subject is painted in a register of mild melancholy not necessarily their own: the eyes are soft and distant, the mouth composed, the skin slightly cooler than life. Nothing is animated.",
    "Every decorative choice — the quiet palette, the enclosed format, the soft shadowing, the muted backdrop — belongs to the vocabulary of memorial portraiture; yet the subject is plainly alive when sat."
};
static const char *const mortuarius_motiva[] = {
    "a single white lily or pale rose is pinned near the throat, its petals painted with particular care",
    "a thin black mourning-ribbon runs around the inner edge of the frame, painted as though part of the picture itself",
    "a single thin ruled line in faint black runs along the lower edge of the picture, centred, the quiet horizontal convention of a memorial portrait",
    "a faint soft vignette darkens the outer corners of the picture, drawing the figure into a quiet centre",
    "a small oval locket hangs at the throat, closed, its chain rendered as a thin delicate line",
    "a single small candle is painted at the lower edge of the frame, its flame steady, indicating only a moment's pause"
};
static const char *const mortuarius_lumen[] = {
    "The light is quiet, indirect, and slightly cool — the light of a lit memorial rather than of a natural room.",
    "The illumination falls softly and evenly, with no hard shadow; nothing dramatic is permitted to disturb the stillness of the picture."
};
static const char *const mortuarius_texturae[] = {
    "The paint is applied in many patient thin layers; the surface is smooth and quiet, with no impasto and no gestural stroke admitted anywhere.",
    "The handling is careful and restrained throughout; the picture has the polished quiet of a picture meant to be kept for a long time."
};
static const char *const mortuarius_compositio[] = {
    "The figure is centred with unusual precision; the composition is frontal, symmetric, and formally enclosed, as memorial compositions traditionally are.",
    "A soft oval vignette draws the face to the centre and darkens the corners; the picture feels already set into its final frame."
};
static const Stylus stylus_mortuarius = {
    mortuarius_media, N_OF(mortuarius_media),
    mortuarius_figurae, N_OF(mortuarius_figurae),
    mortuarius_motiva, N_OF(mortuarius_motiva),
    {
        [PAL_CALIDA]    = "The palette is warm ivory, pale rose, and a muted ochre, all held in a quiet restrained register.",
        [PAL_FRIGIDA]   =
            "The palette is cool bone, slate, pale lavender, and a quiet silver; the flesh is just barely warmer than the wall behind.",
        [PAL_SATURATA]  =
            "A single small saturated element — a red flower, a deep cobalt ribbon — sits at the throat in an otherwise restrained picture.",
        [PAL_MUTA]      =
            "The whole picture is pulled far toward grey: bone, putty, pearl, ash; the memorial register is absolute.",
        [PAL_MONOCHROMA] =
            "The picture is worked in graded warm sepia alone, like an old memorial photograph carefully reproduced in paint.",
        [PAL_PRIMARIA]  =
            "The only saturated colours are the small memorial details — a red ribbon, a yellow candle-flame, a blue mourning-locket; the figure itself remains quiet.",
        [PAL_TERREA]    =
            "The palette is raw umber, ochre, and bone white, in the slightly aged register of a memorial kept for decades."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a quiet plain wall in warm cream or cool dove grey, faintly vignetted into the corners.",
        [FUN_ORNATUM]    =
            "Behind the figure, a subdued floral pattern — small lilies or stylised laurel — is just visible on the wall.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, through a narrow opening, a dignified landscape is visible: a low calm field, a distant cypress, a pale horizon.",
        [FUN_ABSTRACTUM] =
            "Behind the figure is a soft atmospheric vignette, deeper at the corners and quieter at the centre; no specific object is admitted.",
        [FUN_TENEBROSUM] =
            "Behind the figure is a quiet warm black, with the figure emerging only at the single warm light falling on the face.",
        [FUN_LUMINOSUM]  =
            "Behind the figure is a soft dove-grey flood of indirect light, even and quiet, with no drama admitted."
    },
    mortuarius_lumen, N_OF(mortuarius_lumen),
    mortuarius_texturae, N_OF(mortuarius_texturae),
    mortuarius_compositio, N_OF(mortuarius_compositio),
    "The portrait is executed in the quiet conventions of memorial painting — restrained palette, still composition, subdued light — even though the subject is plainly alive and well."
};

/* ============================================================
 * algorithmicus — pictor regularum mechanicarum (fictio)
 * ============================================================ */
static const int algorithmicus_media[] = { MED_ACRYLICUM, MED_OLEUM };
static const char *const algorithmicus_figurae[] = {
    "The entire picture is the output of a single consistent generative rule applied across the canvas: a recurrence, a branching automaton, or a fractal iteration. A human face emerges from the rule's pattern as an unintended but inevitable consequence, never explicitly drawn.",
    "The surface is covered by a strict repeating rule — a tiled cellular automaton, an iterated function — and the face of a specific person can be read in the clustered output where the rule's local density happens to resolve into features.",
    "Every mark on the canvas follows from the rule; there are no decisions made about the face, only about the rule. Yet the viewer sees an unambiguous portrait, its contours and features arising from where the rule happens to output darker or lighter cells.",
    "The picture is a field of small geometric units — circles, triangles, squares — arranged by a published algorithm; a face has emerged in the field where the density of units happens to form features.",
    "The painter has not drawn any feature of the face. They have only set a rule in motion across the canvas and allowed it to run; the face is a pareidolic accident that the rule, run on this particular seed, happens to produce."
};
static const char *const algorithmicus_motiva[] = {
    "a small legend at the lower edge of the picture describes the rule in a single line of mathematical notation",
    "a tiny coordinate system is painted at one corner, with an origin and unit marks, under which the whole picture is generated",
    "the rule's initial seed value is painted as a small integer in the upper-right corner, in unobtrusive numerals",
    "one region of the picture has been allowed to run for twice as many iterations as the rest; its pattern is visibly denser",
    "a small glitch is visible at one cell of the grid, where the rule failed momentarily — the imperfection is left uncorrected",
    "along one edge, a single row of cells has been annotated with the state each cell took at each iteration"
};
static const char *const algorithmicus_lumen[] = {
    "No illumination is represented; each cell of the rule is simply either on or off, dark or bright, according to the rule's output.",
    "The picture's tonal distribution arises entirely from cell density; there is no light source, no modelling, no shadow."
};
static const char *const algorithmicus_texturae[] = {
    "The paint is applied as flat uniform units, each unit bounded and separate; under close inspection every unit is identical in technique, and variation exists only in which units are present.",
    "The picture is executed as a machine might execute it: exactly, without flourish, each cell the same size and the same shape, the whole field covered completely."
};
static const char *const algorithmicus_compositio[] = {
    "The composition is a regular grid, or a regular lattice, or a fractal branching; the figure within it is emergent, not centred.",
    "The figure arises from the overall pattern at exactly the scale at which the human eye begins to pattern-match; smaller features disappear into the rule, larger ones dissolve it."
};
static const Stylus stylus_algorithmicus = {
    algorithmicus_media, N_OF(algorithmicus_media),
    algorithmicus_figurae, N_OF(algorithmicus_figurae),
    algorithmicus_motiva, N_OF(algorithmicus_motiva),
    {
        [PAL_CALIDA]    =
            "Each cell is either warm ochre or warm cream; the face emerges from the density of warm-valued cells.",
        [PAL_FRIGIDA]   =
            "Each cell is either cool slate or cool ivory; the face emerges from the density of cool-valued cells.",
        [PAL_SATURATA]  =
            "Cells cycle through pure red, yellow, and blue at maximum saturation; the face emerges from the distribution of the three primaries in the rule's output.",
        [PAL_MUTA]      =
            "Cells are held in a very narrow range of soft halftones; the pattern is still absolute but the chromatic variation is quiet.",
        [PAL_MONOCHROMA] =
            "Every cell is either pure black or pure white; the face emerges from their spatial distribution alone.",
        [PAL_PRIMARIA]  =
            "Cells are red, yellow, blue, or white, assigned strictly by the rule; the face emerges from the aggregate density of chromatic cells.",
        [PAL_TERREA]    =
            "Cells are raw umber, burnt sienna, and yellow ochre; the rule produces the face as a density variation among these three earths."
    },
    {
        [FUN_PLANUM]     =
            "The rule covers the entire picture plane with no distinction between figure and ground; the face emerges within the field.",
        [FUN_ORNATUM]    =
            "The same rule decorates the picture as a whole, densely; the decoration itself produces the face at the appropriate scale.",
        [FUN_PAESAGIUM]  =
            "The rule produces not only a face but, at smaller scale, a suggestion of a landscape behind it — a horizon, a hill — as additional pareidolic artefacts.",
        [FUN_ABSTRACTUM] =
            "The picture is pure rule-output with no distinction between figure and ground; the viewer's eye selects the face from the noise.",
        [FUN_TENEBROSUM] =
            "The cells are dark on a black ground; the face emerges as a slightly denser cluster of dark cells within the almost-uniform darkness.",
        [FUN_LUMINOSUM]  =
            "The cells are light on a white ground; the face emerges as a slightly denser cluster of light cells within the almost-uniform brightness."
    },
    algorithmicus_lumen, N_OF(algorithmicus_lumen),
    algorithmicus_texturae, N_OF(algorithmicus_texturae),
    algorithmicus_compositio, N_OF(algorithmicus_compositio),
    "The picture is the output of a single consistent generative rule applied across the canvas; the face of a specific person emerges as an emergent, unintended, but inevitable consequence of that rule."
};

/* ============================================================
 * holographus — pictor quattuor dimensionum (fictio)
 * ============================================================ */
static const int holographus_media[] = { MED_OLEUM, MED_ACRYLICUM };
static const char *const holographus_figurae[] = {
    "The subject is painted as if rotating through a fourth dimension: three or four simultaneous angles of the same face are visible as overlapping transparencies in the same picture plane. The frontal view is most opaque; profile views fade outward from it at 30% and 15% opacity.",
    "The head is shown as a continuous revolution through time: the nose traces a faint arc across the face, each position of the nose painted as a slightly less opaque echo of the last, so the figure reads as turning without moving.",
    "Every feature is present in multiple simultaneous positions: two full pairs of eyes (frontal and profile-left, overlapping), two complete mouths (frontal and slightly-turned), one nose that is three noses superimposed.",
    "The outline of the head carries four echoed silhouettes at 90° intervals, overlapping cleanly at the centre; the face reads as a single person seen from every direction at once.",
    "The subject is fully and sharply rendered at the primary angle, and more faintly rendered at each of several secondary angles; the composite is both a portrait and a rotation."
};
static const char *const holographus_motiva[] = {
    "a small axis-cross is painted in one corner, showing the four-dimensional orientation of the figure",
    "each angle of the figure carries a slightly different small detail (a different earring, a different collar fold); the viewer assembles them into a single person",
    "the shadow cast by the figure is itself a composite, with several overlapping silhouettes on the wall behind",
    "the subject's hair is rendered as many overlapping positions of itself, producing a soft-edged halo around the head",
    "a single earring in the primary view becomes a loop of four earrings when the viewer reads all the angles at once",
    "a small label at the lower edge lists the angles present: '0°, 30°, 60°, 90°'"
};
static const char *const holographus_lumen[] = {
    "Each angle of the figure is lit from a consistent direction, so the overlapping transparencies produce a composite that is itself coherent if the viewer picks out a single angle.",
    "The light direction rotates with the figure, so that each echoed angle carries its own internally-consistent modelling; the overall effect is of simultaneous illumination from every direction."
};
static const char *const holographus_texturae[] = {
    "The primary angle is painted in full opaque oil; each additional angle is painted in progressively thinner glazes over the dried primary, so the surface carries several layers of decreasing opacity.",
    "The layering is visible at the edges: the primary silhouette is sharp, then fades through a corona of transparencies into the background."
};
static const char *const holographus_compositio[] = {
    "All angles of the figure share the same vertical axis; the rotation is about this axis only, so the composite retains a clear central symmetry.",
    "The primary frontal view is centred and dominant; the additional angles spread outward from it in soft concentric echoes."
};
static const Stylus stylus_holographus = {
    holographus_media, N_OF(holographus_media),
    holographus_figurae, N_OF(holographus_figurae),
    holographus_motiva, N_OF(holographus_motiva),
    {
        [PAL_CALIDA]    =
            "Each angle is painted in warm flesh tones; overlapping passages carry the additive warmth of the superimposed layers.",
        [PAL_FRIGIDA]   =
            "Each angle is painted in cool flesh tones; overlapping passages become cooler still, toward a pale ice-blue at the centre of maximum overlap.",
        [PAL_SATURATA]  =
            "Each angle is painted in fully saturated colour at reduced opacity; the overlapping passages produce optical mixes of extraordinary richness.",
        [PAL_MUTA]      =
            "All angles are held in soft halftones; the composite reads as a quiet shimmer rather than a dramatic rotation.",
        [PAL_MONOCHROMA] =
            "All angles are painted in graded warm sepia; the composite is a single subtle shimmer of brown values.",
        [PAL_PRIMARIA]  =
            "Each angle is painted in a single primary colour — one angle red, one yellow, one blue — and the overlapping regions produce optical secondaries.",
        [PAL_TERREA]    =
            "All angles are painted in raw umber and ochre; the composite is a warm earthen shimmer with soft depth."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single flat field through which the overlapping angles of the figure read cleanly.",
        [FUN_ORNATUM]    =
            "Behind the figure is a subtly patterned wall, visible at different opacities through the overlapping transparent edges of the figure.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a calm landscape extends; it remains unchanged under every angle of the figure, so its consistency contrasts with the figure's rotation.",
        [FUN_ABSTRACTUM] =
            "The background is a soft field of rotating transparent shapes, echoing the figure's four-dimensional motion at the ground's own pace.",
        [FUN_TENEBROSUM] =
            "The background is a deep warm dark; the figure's overlapping angles emerge from it only where they coincide most densely, at the central frontal view.",
        [FUN_LUMINOSUM]  =
            "The background is a clean bright field; the figure's overlapping angles spread across it as a soft flowering silhouette."
    },
    holographus_lumen, N_OF(holographus_lumen),
    holographus_texturae, N_OF(holographus_texturae),
    holographus_compositio, N_OF(holographus_compositio),
    "The subject is painted at three or four simultaneous angles of rotation, each as a progressively less opaque transparency overlaid on the others, so the figure reads as a single person seen through four dimensions at once."
};

/* ============================================================
 * cryptolalus — pictor litterarum inventarum (fictio)
 * ============================================================ */
static const int cryptolalus_media[] = { MED_OLEUM, MED_ATRAMENTUM };
static const char *const cryptolalus_figurae[] = {
    "Every feature of the face is composed of dense clusters of small glyphs in an invented writing system. Each glyph is about 2 mm across, painted carefully in black or warm brown; from a distance the clustered glyphs resolve into eyes, nose, lips, and the contour of the head.",
    "The face is a passage of unreadable text: the cheeks are built from flowing curves of an unknown cursive, the eyes are each a single compact ideogram, the lips are a single line of closely-written syllables.",
    "The skin is a tightly-packed field of interlocking glyphs in varied sizes; the density of the writing produces the shading, and the direction of the strokes produces the modelling of bone and muscle beneath.",
    "Every stroke that makes up the portrait is also a letter in an invented script; a reader of the script would see both a face and a specific, untranslatable sentence.",
    "The glyphs are legibly a writing system, with a stable alphabet of about thirty characters, but they do not correspond to any known language; the face is constructed from what seems to be a long document written across the head."
};
static const char *const cryptolalus_motiva[] = {
    "a small cartouche in the lower-right corner contains the subject's name, rendered in the same invented script as the face",
    "a single character has been circled in red at the centre of the forehead, as though emphasised by a careful reader",
    "a thin interlinear commentary runs between the letters at the jawline, in even smaller glyphs",
    "the collar of the garment carries a single embroidered repeating glyph in gold thread, 4 mm tall",
    "a scattered group of larger glyphs hovers in the background, as if the text of the face had overflowed its bounds",
    "a single blot of ink sits at the corner of the mouth, as though the scribe's pen had paused there"
};
static const char *const cryptolalus_lumen[] = {
    "No light source is implied; the picture is a manuscript, and its shading comes from the density of written glyphs rather than from modelled form.",
    "The illumination is that of a lit reading-desk — even, diffuse, and appropriate for reading — rather than of a studio."
};
static const char *const cryptolalus_texturae[] = {
    "The surface is worked as a manuscript page: each glyph is individually pen-drawn with a confident stroke, and every accent and diacritic is separately rendered.",
    "The paper-tone of the ground is visible between glyphs, and the picture reads as much as a passage of writing as it does as a portrait."
};
static const char *const cryptolalus_compositio[] = {
    "The face is centred and frontal; the glyph-strokes that compose it flow in a consistent reading direction, so the picture carries both a written and a visual rhythm.",
    "The composition echoes the structure of a manuscript page: a written field fills the upper two-thirds, with a small cartouche and margin-notes confined to the lower strip."
};
static const Stylus stylus_cryptolalus = {
    cryptolalus_media, N_OF(cryptolalus_media),
    cryptolalus_figurae, N_OF(cryptolalus_figurae),
    cryptolalus_motiva, N_OF(cryptolalus_motiva),
    {
        [PAL_CALIDA]    =
            "The glyphs are written in warm brown ink on a cream vellum ground, with initials and major glyphs picked out in red.",
        [PAL_FRIGIDA]   =
            "The glyphs are written in cool grey and slate-blue on pale blue-grey paper; nothing warm is admitted.",
        [PAL_SATURATA]  =
            "Initial glyphs of each feature are worked in saturated red or gold; the surrounding minor glyphs are kept in black.",
        [PAL_MUTA]      =
            "All glyphs are in quiet sepia and brown on cream; the picture reads as a subtly monochromatic manuscript.",
        [PAL_MONOCHROMA] =
            "Black ink only on pale ground; the glyphs do all the work of the picture without any colour admitted.",
        [PAL_PRIMARIA]  =
            "Glyphs cycle through red, yellow, and blue in careful rotation; each feature is a dense cluster of the three primary inks.",
        [PAL_TERREA]    =
            "The glyphs are raw umber and iron-gall brown on a warm cream vellum; the whole picture has the register of an old manuscript."
    },
    {
        [FUN_PLANUM]     =
            "Behind the glyph-composed figure is a single unmarked expanse of vellum or paper, continuous to all edges.",
        [FUN_ORNATUM]    =
            "Behind the figure, a sparse scatter of further glyphs continues the document into the margins; no figurative element breaks the written plane.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a small hand-drawn landscape fills a rectangular inset, framed by glyph-text that identifies it.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the ground is a uniform field of very small, light-toned glyphs at a much smaller scale than those of the face.",
        [FUN_TENEBROSUM] =
            "The ground is dark paper with the glyphs picked out in pale ink; the face reads as a luminous text.",
        [FUN_LUMINOSUM]  =
            "The ground is a high bright vellum with the glyphs picked out in hard black; the face reads as a dense passage of writing."
    },
    cryptolalus_lumen, N_OF(cryptolalus_lumen),
    cryptolalus_texturae, N_OF(cryptolalus_texturae),
    cryptolalus_compositio, N_OF(cryptolalus_compositio),
    "The entire portrait is composed of small glyphs from a consistent but invented writing system; each glyph is pen-drawn individually, and the face emerges from their clustered density."
};

/* ============================================================
 * interstitius — pictor inter momenta (fictio)
 * ============================================================ */
static const int interstitius_media[] = { MED_OLEUM };
static const char *const interstitius_figurae[] = {
    "The subject is painted in the gap between two consecutive instants. Every feature is doubled at a 1 mm offset, as though the figure were captured in micro-tremor: the eyelid half-closed and half-open, both mouths slightly parted, each iris overlapping its own echo.",
    "Every contour in the picture is drawn twice at a 1-2 mm displacement, so the whole figure reads as shimmering in place without moving; the face is specific but its edges are in constant small vibration.",
    "The features themselves are sharp in their individual positions, but each position carries a tiny ghost of its neighbour-instant; the face is both here and a thousandth of a second later.",
    "The picture shows a single subject caught in the gap between breathing in and breathing out: the chest is both expanded and relaxed, the lips both parted and closed, the eyes both open and just-closing.",
    "Two full portraits of the subject at a 1 mm offset have been painted on top of each other, perfectly registered except for the small displacement; the composite reads as a vibrating human."
};
static const char *const interstitius_motiva[] = {
    "a pendant on a fine chain shows both its positions as it swings, each painted at one-third opacity, producing a faint arc across the collarbone",
    "a single strand of hair is in two places at once, each painted at half opacity, arcing about 5 mm apart across the temple",
    "a tear on the lower lid is in two positions at once: about to form, and newly formed",
    "a small fly passing through the picture is painted as eight overlapping instants of itself, arcing across the shoulder",
    "an insect's wing outside the frame has dropped a pollen-speck onto the shoulder; the pollen is in three positions at once — falling, landing, settled",
    "the breath from the mouth is visible as a thin mist painted in two successive positions at a 1 mm drift"
};
static const char *const interstitius_lumen[] = {
    "A single light source produces two overlapping modelling systems on the figure, offset by 1 mm, so every highlight is doubled and every shadow is doubled.",
    "The light itself is static, but the figure it falls on is caught mid-tremor, so each shadow edge carries its own micro-shimmer."
};
static const char *const interstitius_texturae[] = {
    "Every passage of the figure is painted twice, once at full opacity and once at 50%, at a consistent 1 mm offset; the layering is visible under close inspection as a slight doubling of edge.",
    "The paint is applied carefully and patiently, but every confident stroke is followed by a second, slightly offset, slightly lighter stroke — never by a single finished mark."
};
static const char *const interstitius_compositio[] = {
    "The composition is frontally centred; the doubling is applied uniformly across the picture in a consistent direction, so the figure reads as shimmering along one axis.",
    "The primary and secondary layers share all vertical and horizontal axes; the offset is consistent and produces a coherent micro-tremor rather than a visual confusion."
};
static const Stylus stylus_interstitius = {
    interstitius_media, N_OF(interstitius_media),
    interstitius_figurae, N_OF(interstitius_figurae),
    interstitius_motiva, N_OF(interstitius_motiva),
    {
        [PAL_CALIDA]    =
            "Both overlapping layers are warm ochre and rose; the composite reads as a gently trembling warm flesh.",
        [PAL_FRIGIDA]   = "Both layers are cool slate and pale blue; the shimmer is quiet and chilled.",
        [PAL_SATURATA]  =
            "The two layers differ slightly in hue (say, a warm orange primary and a slightly cooler orange shadow); the composite shimmers with chromatic micro-movement.",
        [PAL_MUTA]      =
            "Both layers are soft halftones; the doubling is barely perceptible, reading as a subtle liveliness rather than as shimmer.",
        [PAL_MONOCHROMA] = "The picture is worked entirely in graded warm grey; the shimmer is a purely tonal effect.",
        [PAL_PRIMARIA]  =
            "The primary layer is in red-yellow-blue; the secondary layer is in the same primaries shifted by one step, producing optical rainbow flickers at every edge.",
        [PAL_TERREA]    = "Both layers are raw umber and ochre; the shimmer reads as a warm trembling earth."
    },
    {
        [FUN_PLANUM]     =
            "Behind the figure is a single plain field, unmodulated; the shimmer is entirely within the figure and does not extend to the background.",
        [FUN_ORNATUM]    =
            "Behind the figure, a patterned wall is itself slightly shimmered at the same 1 mm offset, so the whole picture trembles consistently.",
        [FUN_PAESAGIUM]  =
            "Behind the figure, a distant landscape is painted in a single stable layer; only the figure and its immediate surround shimmer.",
        [FUN_ABSTRACTUM] =
            "Behind the figure, the entire ground is in subtle micro-displacement, so that no single edge in the picture is quite still.",
        [FUN_TENEBROSUM] =
            "The background is deep warm dark, still; the figure emerges from it with its shimmering doubled contours.",
        [FUN_LUMINOSUM]  =
            "The background is a clean high ivory, still; the figure reads as a small shimmering silhouette against it."
    },
    interstitius_lumen, N_OF(interstitius_lumen),
    interstitius_texturae, N_OF(interstitius_texturae),
    interstitius_compositio, N_OF(interstitius_compositio),
    "The subject is painted twice on the same canvas at a 1-2 mm consistent offset; the composite reads as a single person caught in the gap between two instants of micro-tremor."
};

static const Stylus *const styli[ART_N] = {
    &stylus_dalius, &stylus_klimtius, &stylus_mondrianus, &stylus_vermerus,
    &stylus_escherus, &stylus_kandinskius, &stylus_magrittius, &stylus_pollockius,
    &stylus_picassonus, &stylus_vangoghus, &stylus_warholus, &stylus_schieleus,
    &stylus_baconius, &stylus_hopperus, &stylus_hokusaius, &stylus_munchius,
    &stylus_lichtensteinius, &stylus_modiglianius, &stylus_rembrandtus,
    &stylus_hockneius, &stylus_freudus, &stylus_basquiatus, &stylus_seuratus,
    &stylus_rivereus,
    &stylus_velaspinus, &stylus_crispulus, &stylus_nimbulus, &stylus_echokus,
    &stylus_fulguritus, &stylus_tesselarius, &stylus_obscurus, &stylus_filumentus,
    &stylus_chronofugus, &stylus_somniator, &stylus_vacuarius, &stylus_mortuarius,
    &stylus_algorithmicus, &stylus_holographus, &stylus_cryptolalus,
    &stylus_interstitius
};

/* ---- claves ad indices vertere ---- */

static int quaere_indicem(const char *clavis, const char *const *tab, int n) {
    if (!clavis)
        return -1;
    for (int i = 0; i < n; i++)
        if (strcmp(clavis, tab[i]) == 0)
            return i;
    return -2; /* clavis ignota */
}

static int resolve_clavem(
    const char *clavis, const char *const *tab, int n,
    const char *nomen_campi, char *err, size_t errn
) {
    int i = quaere_indicem(clavis, tab, n);
    if (i == -1)
        return (int)alea_ambitus((uint32_t)n);
    if (i == -2) {
        pone_errorem(err, errn, "clavis ignota in campo %s: %s", nomen_campi, clavis);
        return -1;
    }
    return i;
}

/* ---- descriptionem componere ---- */

static int compone(
    Charta *out, const ArtistaOptiones *opt,
    char *err, size_t errn
) {
    int i_art = resolve_clavem(opt->artifex, artifices_claves, ART_N, "artifex", err, errn);
    if (i_art < 0)
        return 0;
    const Stylus *st = styli[i_art];

    int i_med;
    if (opt->medium) {
        i_med = quaere_indicem(opt->medium, media_claves, MED_N);
        if (i_med == -2) {
            pone_errorem(err, errn, "clavis ignota in campo medium: %s", opt->medium);
            return 0;
        }
    } else {
        i_med = st->media_praeferenda[alea_ambitus((uint32_t)st->n_media)];
    }

    int i_pal = resolve_clavem(opt->palaestra, palettae_claves, PAL_N, "palaestra", err, errn);
    if (i_pal < 0)
        return 0;
    int i_hab = resolve_clavem(opt->habitus, habitus_claves, HAB_N, "habitus", err, errn);
    if (i_hab < 0)
        return 0;
    int i_fun = resolve_clavem(opt->fundus, fundi_claves, FUN_N, "fundus", err, errn);
    if (i_fun < 0)
        return 0;

    /* Secundus transitus: electiones per semen factae orthogonales sunt;
     * hic paucas consonantias fortiores inferimus, sed solum ad campos
     * quos vocans non praebuit (ne usoris electio umquam superetur). */
    if (!opt->habitus) {
        if (i_pal == PAL_MONOCHROMA && i_hab == HAB_IUBILANS)
            i_hab = HAB_SOLEMNIS;
        if (i_pal == PAL_MUTA       && i_hab == HAB_IUBILANS)
            i_hab = HAB_SERENUS;
        if (i_pal == PAL_SATURATA   && i_hab == HAB_MELANCHOLICUS)
            i_hab = HAB_TURBULENTUS;
        if (i_fun == FUN_TENEBROSUM && i_hab == HAB_IUBILANS)
            i_hab = HAB_SOLEMNIS;
        if (
            i_fun == FUN_LUMINOSUM  && i_hab == HAB_MELANCHOLICUS
            && i_pal != PAL_MUTA && i_pal != PAL_MONOCHROMA
        ) i_hab = HAB_SERENUS;
    }
    if (!opt->fundus) {
        if (i_pal == PAL_MONOCHROMA && i_fun == FUN_LUMINOSUM)
            i_fun = FUN_PLANUM;
    }

    /* Per-artificem: quidam artifices nonnullos habitus/palestras/fundos
     * simpliciter non sustinent; eos movemus. Iterum, nonnisi si usor
     * non praebuit. */
    int hab_free = !opt->habitus;
    int pal_free = !opt->palaestra;
    int fun_free = !opt->fundus;
    switch (i_art) {
    case ART_MORTUARIUS:
        if (
            hab_free && (
                i_hab == HAB_IUBILANS || i_hab == HAB_TURBULENTUS
                || i_hab == HAB_TENSUS
            )
        ) i_hab = HAB_SERENUS;
        if (pal_free && i_pal == PAL_SATURATA)
            i_pal = PAL_MUTA;
        if (fun_free && i_fun == FUN_LUMINOSUM)
            i_fun = FUN_PLANUM;
        break;
    case ART_MONDRIANUS:
        if (hab_free && i_hab == HAB_TURBULENTUS)
            i_hab = HAB_SERENUS;
        if (hab_free && i_hab == HAB_MELANCHOLICUS)
            i_hab = HAB_SERENUS;
        break;
    case ART_VERMERUS:
        if (hab_free && (i_hab == HAB_TURBULENTUS || i_hab == HAB_IUBILANS))
            i_hab = HAB_SERENUS;
        break;
    case ART_SEURATUS:
        if (hab_free && i_hab == HAB_TURBULENTUS)
            i_hab = HAB_SERENUS;
        break;
    case ART_REMBRANDTUS:
        if (hab_free && i_hab == HAB_IUBILANS)
            i_hab = HAB_SOLEMNIS;
        if (pal_free && i_pal == PAL_PRIMARIA)
            i_pal = PAL_TERREA;
        if (fun_free && i_fun == FUN_LUMINOSUM)
            i_fun = FUN_TENEBROSUM;
        break;
    case ART_CHRONOFUGUS:
        if (hab_free && (i_hab == HAB_IUBILANS || i_hab == HAB_TURBULENTUS))
            i_hab = HAB_SOLEMNIS;
        if (pal_free && i_pal == PAL_SATURATA)
            i_pal = PAL_MUTA;
        break;
    case ART_VACUARIUS:
        if (hab_free && i_hab == HAB_IUBILANS)
            i_hab = HAB_SOLEMNIS;
        break;
    case ART_OBSCURUS:
        if (hab_free && (i_hab == HAB_IUBILANS || i_hab == HAB_TURBULENTUS))
            i_hab = HAB_SOLEMNIS;
        if (fun_free && i_fun == FUN_LUMINOSUM)
            i_fun = FUN_TENEBROSUM;
        break;
    case ART_HOKUSAIUS:
        if (hab_free && i_hab == HAB_TURBULENTUS)
            i_hab = HAB_SERENUS;
        break;
    case ART_POLLOCKIUS:
        if (hab_free && i_hab == HAB_SERENUS)
            i_hab = HAB_TURBULENTUS;
        break;
    case ART_BACONIUS:
        if (hab_free && i_hab == HAB_IUBILANS)
            i_hab = HAB_TENSUS;
        break;
    case ART_WARHOLUS:
        if (hab_free && i_hab == HAB_MELANCHOLICUS)
            i_hab = HAB_SERENUS;
        break;
    case ART_VELASPINUS:
        if (hab_free && i_hab == HAB_TURBULENTUS)
            i_hab = HAB_SERENUS;
        break;
    case ART_INTERSTITIUS:
        if (hab_free && i_hab == HAB_SERENUS)
            i_hab = HAB_TENSUS;
        break;
    default:
        break;
    }

    const char *figura    = elige(st->figurae,    st->n_figurae);
    const char *motivum_a = elige(st->motiva,     st->n_motiva);
    const char *motivum_b = NULL;
    if (st->n_motiva > 1 && alea_fors(0.66)) {
        for (int guard = 0; guard < 12; guard++) {
            const char *m = st->motiva[alea_ambitus((uint32_t)st->n_motiva)];
            if (m != motivum_a) {
                motivum_b = m;
                break;
            }
        }
    }
    const char *motivum_c = NULL;
    if (motivum_b && alea_fors(0.35)) {
        for (int guard = 0; guard < 12; guard++) {
            const char *m = st->motiva[alea_ambitus((uint32_t)st->n_motiva)];
            if (m != motivum_a && m != motivum_b) {
                motivum_c = m;
                break;
            }
        }
    }
    const char *lumen      = elige(st->lumen,      st->n_lumen);
    const char *textura    = elige(st->texturae,   st->n_texturae);
    const char *compositio = elige(st->compositio, st->n_compositio);

    if (!charta_adde(out, INQUADRAMENTUM))
        return 0;

    if (!charta_scribe(out, "%s ", figura))
        return 0;

    if (
        !charta_scribe(
            out,
            "The whole work is executed in %s. %s ",
            elige(media_sets[i_med].opts, media_sets[i_med].n),
            st->palettae[i_pal]
        )
    ) return 0;

    if (!charta_scribe(out, "%s ", st->fundi[i_fun]))
        return 0;

    if (motivum_c) {
        if (
            !charta_scribe(
                out,
                "Three specific elements are present on the picture surface: %s; %s; and %s. ",
                motivum_a, motivum_b, motivum_c
            )
        ) return 0;
    } else if (motivum_b) {
        if (
            !charta_scribe(
                out,
                "Two specific elements are present on the picture surface: %s; and %s. ",
                motivum_a, motivum_b
            )
        ) return 0;
    } else {
        if (
            !charta_scribe(
                out,
                "One specific element is present on the picture surface: %s. ",
                motivum_a
            )
        ) return 0;
    }

    if (!charta_scribe(out, "%s ", lumen))
        return 0;
    if (!charta_scribe(out, "%s ", compositio))
        return 0;
    if (!charta_scribe(out, "%s ", textura))
        return 0;
    if (
        !charta_scribe(
            out, "%s ",
            elige(habitus_sets[i_hab].opts, habitus_sets[i_hab].n)
        )
    ) return 0;
    if (!charta_scribe(out, "%s\n", st->signatura))
        return 0;
    return 1;
}

/* ---- rudis: parametros mero modo iterat ----
 *
 * Praecursor idem est ac in persona_generare_rudis, ut utraque
 * functio imagines comparabiles producat. Si hic mutatur, persona.c
 * quoque mutandus est. */
static const char *const rudis_praecursor =
    "Generate a portrait. The subject's head is centered in the frame "
    "and the subject is facing the viewer. ";

char *artista_generare_rudis(
    uint64_t semen,
    const ArtistaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    static const ArtistaOptiones vacua = {0};
    if (!optiones)
        optiones = &vacua;
    if (error_locus && error_longitudo)
        error_locus[0] = '\0';

    Charta out = {0};
    if (!charta_adde(&out, rudis_praecursor))
        goto defecit;
    if (
        !charta_adde(
            &out,
            "This is an artista: a painted portrait of a person, rendered "
            "in an invented artistic style of your own choosing. "
        )
    ) goto defecit;
    if (!charta_adde(&out, "Make a random portrait of someone."))
        goto defecit;
    (void)semen;

    static const struct {
        const char *key_latine;
        const char *key_anglice;
        const char *const *val_p;
    } campi[] = {
        { "artifex",   "style",      NULL },
        { "medium",    "medium",     NULL },
        { "palaestra", "palette",    NULL },
        { "habitus",   "mood",       NULL },
        { "fundus",    "background", NULL }
    };
    const char *valores[5] = {
        optiones->artifex, optiones->medium, optiones->palaestra,
        optiones->habitus, optiones->fundus
    };
    for (int i = 0; i < 5; i++) {
        if (!valores[i])
            continue;
        if (!charta_scribe(&out, " Also %s should be %s.", campi[i].key_anglice, valores[i]))
            goto defecit;
    }
    if (!charta_adde(&out, "\n"))
        goto defecit;
    return out.d;

defecit:
    free(out.d);
    pone_errorem(error_locus, error_longitudo, "memoria defecit");
    return NULL;
}

char *artista_generare(
    uint64_t semen,
    const ArtistaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    static const ArtistaOptiones vacua = {0};
    if (!optiones)
        optiones = &vacua;

    if (error_locus && error_longitudo)
        error_locus[0] = '\0';

    alea_seminare(semen);

    Charta out = {0};
    if (!compone(&out, optiones, error_locus, error_longitudo)) {
        free(out.d);
        if (error_locus && error_longitudo && !error_locus[0]) {
            pone_errorem(error_locus, error_longitudo, "memoria defecit");
        }
        return NULL;
    }
    return out.d;
}

void artista_usus(FILE *f) {
    usus_claves(
        f,
        "      --artifex X     ",
        "                      ",
        artifices_claves, ART_N
    );
    usus_claves(
        f,
        "      --medium X      ",
        "                      ",
        media_claves, MED_N
    );
    usus_claves(
        f,
        "      --palaestra X   ",
        "                      ",
        palettae_claves, PAL_N
    );
    usus_claves(
        f,
        "      --habitus X     ",
        "                      ",
        habitus_claves, HAB_N
    );
    usus_claves(
        f,
        "      --fundus X      ",
        "                      ",
        fundi_claves, FUN_N
    );
}
