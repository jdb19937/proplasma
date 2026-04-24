#include "bestia.h"
#include "communia.h"

/* ---- claves ontologicae ---- */

enum { SPC_VULPES, SPC_CORVUS, SPC_BUBO, SPC_LUPUS, SPC_LEPUS,
    SPC_FELIS, SPC_AQUILA, SPC_CERVUS, SPC_SERPENS, SPC_SIMIA,
    SPC_URSUS, SPC_PISCIS, SPC_MUSTELA, SPC_TESTUDO, SPC_ARIES,
    SPC_TAURUS, SPC_ARANEA, SPC_EQUUS, SPC_CANIS, SPC_LEO,
    SPC_HIRCUS, SPC_DELPHINUS, SPC_VESPERTILIO, SPC_PAVO,
    SPC_HYDROCHOERUS, SPC_DIOMEDEA,
    SPC_ELEPHAS, SPC_CAMELUS, SPC_RHINOCEROS, SPC_TIGRIS, SPC_PARDUS,
    SPC_LYNX, SPC_HYAENA, SPC_APER, SPC_MELES, SPC_SCIURUS,
    SPC_ERINACEUS, SPC_GORILLA, SPC_CAMELOPARDALIS, SPC_CYGNUS,
    SPC_CICONIA, SPC_IBIS, SPC_PSITTACUS, SPC_GALLUS, SPC_FALCO,
    SPC_CROCODILUS, SPC_CHAMAELEON, SPC_RANA, SPC_CARCHARIAS,
    SPC_POLYPUS, SPC_APIS, SPC_PAPILIO, SPC_SCORPIO,
    SPC_CUNICULUS, SPC_MUS, SPC_PASSER, SPC_CASTOR,
    SPC_LUTRA, SPC_MANTIS, SPC_CICADA, SPC_SALMO,
    SPC_N };

static const char *const species_claves[SPC_N] = {
    "vulpes", "corvus", "bubo", "lupus", "lepus",
    "felis", "aquila", "cervus", "serpens", "simia",
    "ursus", "piscis", "mustela", "testudo", "aries",
    "taurus", "aranea", "equus", "canis", "leo",
    "hircus", "delphinus", "vespertilio", "pavo",
    "hydrochoerus", "diomedea",
    "elephas", "camelus", "rhinoceros", "tigris", "pardus",
    "lynx", "hyaena", "aper", "meles", "sciurus",
    "erinaceus", "gorilla", "camelopardalis", "cygnus",
    "ciconia", "ibis", "psittacus", "gallus", "falco",
    "crocodilus", "chamaeleon", "rana", "carcharias",
    "polypus", "apis", "papilio", "scorpio",
    "cuniculus", "mus", "passer", "castor",
    "lutra", "mantis", "cicada", "salmo"
};

enum { GRD_ADUMBRATIO, GRD_MIXTURA, GRD_THERIOCEPHALUS, GRD_BESTIA_IPSA, GRD_N };
static const char *const gradus_claves[GRD_N] = {
    "adumbratio", "mixtura", "theriocephalus", "bestia_ipsa"
};

enum { RAT_PHYSIOGNOMONICUS, RAT_TOTEMICUS, RAT_FABULARIS,
    RAT_MYTHICUS, RAT_LUSORIUS, RAT_N };
static const char *const ratio_claves[RAT_N] = {
    "physiognomonicus", "totemicus", "fabularis", "mythicus", "lusorius"
};

enum { GST_VIGIL, GST_DORMIENS, GST_VENANS, GST_FUGIENS,
    GST_SUPERBUS, GST_SOLEMNIS, GST_PAVIDUS, GST_QUIETUS,
    GST_IRATUS, GST_RIDENS, GST_MEDITANS, GST_SUPPLEX,
    GST_CURIOSUS, GST_LUDENS, GST_AMANS, GST_MIRANS, GST_N };
static const char *const gestus_claves[GST_N] = {
    "vigil", "dormiens", "venans", "fugiens",
    "superbus", "solemnis", "pavidus", "quietus",
    "iratus", "ridens", "meditans", "supplex",
    "curiosus", "ludens", "amans", "mirans"
};

enum { AMC_NULLUS, AMC_NEMES, AMC_COLLARE, AMC_LORICA,
    AMC_STOLA, AMC_PELTA, AMC_SERTUM, AMC_LATRUNCULUS,
    AMC_CORONA, AMC_VELUM, AMC_INFULA, AMC_TORQUIS,
    AMC_FOCALE, AMC_TAENIA, AMC_FLOS, AMC_GEMMA, AMC_N };
static const char *const amictus_claves[AMC_N] = {
    "nullus", "nemes", "collare", "lorica", "stola", "pelta", "sertum", "latrunculus",
    "corona", "velum", "infula", "torquis",
    "focale", "taenia", "flos", "gemma"
};

enum { FND_PLANUM, FND_TENEBROSUM, FND_LUMINOSUM, FND_AUREUM,
    FND_PAESAGIUM, FND_ORNATUM, FND_SILVA, FND_TEMPLUM,
    FND_COLORATUM, FND_AQUATICUM, FND_NOCTURNUM,
    FND_CREPUSCULUM, FND_N };
static const char *const fundus_claves[FND_N] = {
    "planum", "tenebrosum", "luminosum", "aureum",
    "paesagium", "ornatum", "silva", "templum", "coloratum",
    "aquaticum", "nocturnum", "crepusculum"
};

/* Pro gradu planum et coloratum, tabulae phrasium variantur; ceteri
 * gradus uno enuntiato contenti sunt. */
static const char *const fundus_planum_opts[] = {
    "a plain, unbroken field of cool slate gray, with no objects or texture",
    "a plain, unbroken field of warm ivory, with no objects or texture",
    "a plain, unbroken field of soft dove-gray, with no objects or texture",
    "a plain, unbroken field of muted taupe, with no objects or texture",
    "a plain, unbroken field of pale oatmeal, with no objects or texture",
    "a plain, unbroken field of cold bone-white, with no objects or texture",
    "a plain, unbroken field of dim ash-gray, with no objects or texture",
    "a plain, unbroken field of muted sage, with no objects or texture",
    "a plain, unbroken field of soft clay-pink, with no objects or texture"
};
static const char *const fundus_coloratum_opts[] = {
    "a saturated cobalt-blue ground, a single vivid flat color with no objects or texture",
    "a saturated vermilion-red ground, a single vivid flat color with no objects or texture",
    "a saturated emerald-green ground, a single vivid flat color with no objects or texture",
    "a saturated marigold-yellow ground, a single vivid flat color with no objects or texture",
    "a saturated royal-purple ground, a single vivid flat color with no objects or texture",
    "a saturated tangerine-orange ground, a single vivid flat color with no objects or texture",
    "a saturated fuchsia-pink ground, a single vivid flat color with no objects or texture",
    "a saturated turquoise ground, a single vivid flat color with no objects or texture",
    "a saturated crimson-red ground, a single vivid flat color with no objects or texture",
    "a saturated ultramarine-blue ground, a single vivid flat color with no objects or texture",
    "a saturated chartreuse ground, a single vivid flat color with no objects or texture",
    "a saturated magenta ground, a single vivid flat color with no objects or texture",
    "two flat fields of saturated color meeting at a hard vertical line: scarlet at the left, emerald at the right",
    "two flat fields of saturated color meeting at a hard vertical line: cobalt at the left, marigold at the right",
    "two flat fields of saturated color meeting at a hard horizontal line: saturated magenta above, saturated teal below",
    "a saturated field of alternating wide vertical stripes in vivid color — scarlet and cobalt, or marigold and emerald —",
    "a saturated acid-lime ground, a single vivid flat color with no objects or texture",
    "a saturated sapphire-blue ground, a single vivid flat color with no objects or texture",
    "a saturated coral ground, a single vivid flat color with no objects or texture",
    "a saturated indigo ground, a single vivid flat color with no objects or texture",
    "three flat horizontal bands of saturated color meeting at hard lines: scarlet above, ivory in the middle, cobalt below",
    "a saturated diagonal split of two flat color fields, emerald meeting royal-purple at a sharp oblique line",
    "a circular medallion of saturated marigold set against a flat field of deep ultramarine, both pure unmodulated color",
    "a flat field of strong vermilion ornamented only by a single white disc centered behind the head"
};
static const char *const fundus_scribenda[FND_N] = {
    NULL,  /* planum: tabula */
    "a deep, near-black ground in the manner of a Baroque portrait — only the figure emerges from the dark, with no visible setting",
    "a softly luminous pale background, evenly lit and almost white, so that the figure seems to float against clean light",
    "a flat gilded ground worked with a very fine stippled texture, as in a Byzantine icon — no depth, only golden light behind the head",
    "a distant suggestion of landscape: low hills, a thin horizon, and a pale sky, all softly out of focus",
    "an ornamental ground of repeating motifs in bold saturated color — bright scarlet tendrils on cobalt, or gold scales on deep emerald — worked in a flat tapestry manner",
    "a hint of woodland: tall dark trunks and dim green shadow, indistinct and recessive",
    "the inner wall of a temple cella: plain fitted stone with a single broad band of strongly saturated color — scarlet, ultramarine, or gold — running across at shoulder height",
    NULL,  /* coloratum: tabula */
    "a greenish submarine depth: shafts of slanting light falling through still water, with a few drifting motes and the ghost of kelp in the gloom",
    "a deep indigo night-sky scattered with small bright stars, a single slender crescent moon visible at one corner",
    "a soft twilight sky banded in violet and apricot, a thin dark horizon, and no other feature"
};

/* ---- species: data anatomica et culturalia ---- */

typedef struct {
    const char *anglice;       /* nomen Anglicum, e.g. "fox" */
    const char *pellis;        /* vestis cutanea */
    const char *caput;         /* forma capitis */
    const char *oculi;         /* oculi animalis */
    const char *nota;          /* nota insignis (dentes, cornua, rostrum) */
    const char *humanum;       /* phrasis adumbrationis: vultus humanus animali similis */
    const char *mythicum;      /* nomen mythicum theriocephali */
} SpeciesDatum;

static const SpeciesDatum species_data[SPC_N] = {
    [SPC_VULPES] = {
        "fox", "russet fur with a white throat and black-tipped ears",
        "a narrow tapering muzzle and tall upright ears",
        "bright amber eyes with vertically slit pupils",
        "a neat row of sharp white teeth just visible at the parted lips",
        "a narrow, sharp-featured face with a watchful alertness and a foxlike cast",
        "a fox-headed trickster spirit in the manner of Japanese Inari"
    },
    [SPC_CORVUS] = {
        "raven", "glossy black feathers with a faint iridescent sheen of blue and violet",
        "a sleek black-feathered head and a long straight beak",
        "pale, glassy eyes with a sidelong, evaluating stare",
        "a heavy black beak, slightly parted",
        "a long, sharp-nosed face with hooded eyes and a corvid watchfulness",
        "a raven-headed psychopomp recalling Odin's messengers"
    },
    [SPC_BUBO] = {
        "owl", "tawny and cream-barred feathers across the head and shoulders",
        "a broad disc-shaped feathered face and tufted horn-like ears",
        "enormous round orange-gold eyes set forward in the face",
        "a small hooked beak half-hidden in feathers",
        "a broad, round-cheeked face dominated by wide, unblinking eyes",
        "an owl-headed oracle recalling Athena's attendant"
    },
    [SPC_LUPUS] = {
        "wolf", "thick gray and charcoal fur mantling the neck and shoulders",
        "a broad muzzle and erect triangular ears",
        "yellow-gold eyes, steady and pale",
        "long canine teeth faintly showing",
        "a broad-browed, heavy-jawed face with pale, steady eyes",
        "a wolf-headed war-god in the manner of an Anatolian relief"
    },
    [SPC_LEPUS] = {
        "hare", "soft brown fur tipped with silver along the cheeks",
        "a gently rounded head and long upright ears",
        "large dark liquid eyes set to the sides of the face",
        "a cleft upper lip and small incisors just showing",
        "a soft, wide-eyed face with long upper lip and a startled gentleness",
        "a hare-headed moon-spirit drawn from East Asian folklore"
    },
    [SPC_FELIS] = {
        "cat", "short smoke-gray fur with faint tabby striping",
        "a rounded skull and small pointed ears",
        "green eyes with narrow vertical pupils",
        "a small pink nose and delicate whiskers",
        "a small-featured, heart-shaped face with feline, almond-slanted eyes",
        "the cat-headed goddess Bastet in processional pose"
    },
    [SPC_AQUILA] = {
        "eagle", "dark brown body plumage and a crown of pale head feathers",
        "a sleek feathered head and fierce brow ridge",
        "piercing yellow eyes under a pronounced bony brow",
        "a massive hooked yellow beak",
        "a sharp-browed, hook-nosed face with piercing pale eyes",
        "an eagle-headed herald in the manner of Mesopotamian Anzu"
    },
    [SPC_CERVUS] = {
        "stag", "short reddish-brown coat smoothing to buff at the throat",
        "a long slender head crowned by spreading antlers",
        "dark wet eyes with long lashes",
        "a dark velvet muzzle and a single white flash on the forehead",
        "a long, fine-boned face with dark liquid eyes and an antlered bearing",
        "an antlered forest-lord after Cernunnos"
    },
    [SPC_SERPENS] = {
        "serpent", "pale green scales with a faint diamond patterning",
        "a low smooth-scaled head and no ears",
        "lidless golden eyes with vertically slit pupils",
        "a thin forked tongue flickering between the lips",
        "a smooth-skinned, narrow-eyed face with an almost lidless reptilian gaze",
        "a serpent-headed oracle after the Naga of the south"
    },
    [SPC_SIMIA] = {
        "ape", "short dark bristly fur framing the face",
        "a heavy-browed, broad-jawed simian head",
        "deep-set brown eyes under a shelving brow",
        "a wide nostril-flared nose and slightly parted heavy lips",
        "a heavy-browed, deep-jawed face with a simian set to the features",
        "a monkey-headed sage after Sun Wukong of the Journey to the West"
    },
    [SPC_URSUS] = {
        "bear", "thick brown-black fur, heavy around the shoulders",
        "a broad rounded head and small rounded ears",
        "small dark eyes nearly lost in fur",
        "a heavy wet snout and the hint of a tooth at the lip",
        "a heavy, broad-browed face with small deep-set eyes and a bearish bulk",
        "a bear-headed ancestor after the northern shamanic tradition"
    },
    [SPC_PISCIS] = {
        "fish", "silvery scales fading to blue along the crown",
        "a smooth scaled head and flared gill-plates at the neck",
        "round lidless eyes set to the sides of the head",
        "a small puckered mouth slightly open",
        "a pallid, wide-eyed face with a strangely lipless mouth and cold fish-clean skin",
        "the fish-headed sage Oannes of Mesopotamian lore"
    },
    [SPC_MUSTELA] = {
        "weasel", "sleek honey-brown fur with a cream underside",
        "a narrow low-slung head and small rounded ears",
        "small glossy black eyes, quick and restless",
        "a pointed pink nose and needle-fine teeth",
        "a narrow, long-chinned face with quick restless eyes and a weaselly set",
        "a weasel-headed thief in a medieval bestiary"
    },
    [SPC_TESTUDO] = {
        "tortoise", "leathery grey-green skin patterned with fine scales",
        "a small wrinkled head on a long folded neck",
        "small dark eyes with heavy drooping lids",
        "a hard horn-beaked mouth, closed",
        "a deeply-lined, hooded-eyed face with a slow, ancient stillness",
        "a tortoise-headed sage of the long-lived eastern tradition"
    },
    [SPC_ARIES] = {
        "ram", "dense cream-white wool curling at the cheeks and forehead",
        "a long wool-framed head with heavy curling horns",
        "rectangular pupils set in pale gold eyes",
        "great spiralling horns framing the skull",
        "a long-faced, heavy-horned bearing with strange horizontal-pupiled eyes",
        "a ram-headed fertility-spirit of the Celtic iron age"
    },
    [SPC_TAURUS] = {
        "bull", "short black hide and a coarse forelock between the horns",
        "a massive broad head with short forward-curving horns",
        "small dark eyes under heavy ridges",
        "a damp broad nose and a bright brass ring through the septum",
        "a massive, bull-browed face with small dark eyes and a bovine heft",
        "the bull-headed Minotaur in a Cretan frieze"
    },
    [SPC_ARANEA] = {
        "spider", "fine black bristles covering the crown and cheeks",
        "a small round head with no clear ears",
        "eight small glossy black eyes clustered above the brow",
        "a pair of short curved chelicerae at the mouth",
        "a small, black-eyed, many-eyed face with an unsettling arachnid patience",
        "a spider-headed weaver after the Anansi of West African story"
    },
    [SPC_EQUUS] = {
        "horse", "short chestnut hair and a coarse black mane down the neck",
        "a long narrow head and tall flicking ears",
        "large dark liquid eyes set to the sides of the face",
        "soft velvet nostrils and a white blaze down the forehead",
        "a long, narrow, high-cheeked face with large dark side-set eyes",
        "a horse-headed bodhisattva after Hayagriva"
    },
    [SPC_CANIS] = {
        "dog", "short tan fur with a dark mask across the eyes",
        "a long muzzle and folded drop ears",
        "warm brown eyes with a steady, trusting gaze",
        "a black wet nose and a lolling pink tongue",
        "a broad-cheeked, soft-eyed face with a loyal, canine set",
        "a dog-headed Saint Christopher Cynocephalus from a Byzantine icon"
    },
    [SPC_LEO] = {
        "lion", "tawny golden hide ringed by a heavy russet mane",
        "a broad square-muzzled head inside a great dark mane",
        "pale gold eyes under a heavy brow",
        "long ivory canines and a wet black nose",
        "a broad, square-jawed face wreathed as if by a mane, with heavy-lidded gold eyes",
        "a lion-headed guardian at the gates of a Chinese imperial temple"
    },
    [SPC_HIRCUS] = {
        "goat", "shaggy dark-brown hair with a pale stripe down the face",
        "a long bony head with backward-curving horns and a wispy beard",
        "pale yellow eyes with horizontal rectangular pupils",
        "a short beard and two swept-back horns",
        "a long-boned, bearded face with disquieting horizontal-pupiled eyes",
        "the goat-headed sabbatic idol of medieval imagination"
    },
    [SPC_DELPHINUS] = {
        "dolphin", "smooth slate-grey skin paling to near white at the throat",
        "a smooth rounded head and a long beaked snout",
        "small dark eyes, bright and knowing",
        "a fixed half-smile at the parted lips",
        "a smooth-skinned, high-domed face with a strange fixed smile",
        "a dolphin-headed sea-spirit in the Hellenic manner"
    },
    [SPC_VESPERTILIO] = {
        "bat", "short velvet-dark fur on the face and crown",
        "a small round head and enormous membranous ears",
        "tiny black eyes, almost hidden",
        "a pug-nosed muzzle and small needle-fine teeth",
        "a small, flat-nosed face with enormous flaring ears and tiny black eyes",
        "a bat-headed night-daemon from the Mesoamerican codices"
    },
    [SPC_PAVO] = {
        "peacock", "an iridescent crest of blue-green feathers across the crown",
        "a small sleek-feathered head with a fan of crest-feathers",
        "small dark eyes ringed by bare blue skin",
        "a fan of eyed tail-feathers spreading behind the shoulders",
        "a narrow, long-necked bearing with a feathered crest and proud carriage",
        "a peacock-headed celestial after the Hindu Kartikeya's mount"
    },
    [SPC_HYDROCHOERUS] = {
        "capybara", "short coarse reddish-brown fur, damp-looking and smoothed down",
        "a broad, blunt-muzzled head with small rounded ears set high",
        "small calm dark eyes set high on the sides of the head",
        "a broad flat muzzle and the faint line of two large incisors",
        "a broad, blunt-featured, placid face with a remarkably composed and unhurried expression",
        "a capybara-headed river-spirit of the southern wetlands"
    },
    [SPC_DIOMEDEA] = {
        "albatross", "pure white body plumage with long slate-gray wings folded at the shoulders",
        "a sleek white-feathered head and a long hooked pale-yellow beak",
        "dark, far-seeing eyes ringed in fine black feathering",
        "an enormous pale beak tipped with a subtle hook",
        "a long-browed, far-eyed, windward-set face with a seafaring stillness",
        "an albatross-headed mariner's daemon in the manner of Coleridge's rime"
    },
    [SPC_ELEPHAS] = {
        "elephant", "thick gray wrinkled hide with sparse coarse bristles",
        "an enormous domed head with great fanning ears and a long trunk",
        "small warm brown eyes with long lashes, set low in the face",
        "two curved ivory tusks and a pendulous trunk",
        "a heavy, broad-browed face with small warm eyes and a patient, long-memoried air",
        "the elephant-headed Ganesha in his seated pose"
    },
    [SPC_CAMELUS] = {
        "camel", "short dusty-tawny fur matted at the crown",
        "a long lofty head with a drooping lower lip and slit nostrils",
        "heavy-lidded brown eyes under a double row of long lashes",
        "a single humped outline visible at the back of the neck",
        "a long-faced, heavy-lidded, drooping-lipped bearing with desert patience",
        "a camel-headed caravan-spirit of the Arabian trade-routes"
    },
    [SPC_RHINOCEROS] = {
        "rhinoceros", "thick folded gray hide, almost armored in appearance",
        "a great low-slung head with a single forward-curving horn",
        "small dull eyes deeply set in folds of skin",
        "a prominent keratin horn rising from the snout",
        "a heavy, horn-browed, small-eyed face with a blunt weight",
        "a rhinoceros-headed guardian after Dürer's wood-block beast"
    },
    [SPC_TIGRIS] = {
        "tiger", "orange fur banded with black tiger-stripes, white at the throat",
        "a broad round head framed by a short ruff of fur",
        "pale gold eyes with narrow vertical pupils",
        "long white whiskers and the hint of a canine tooth",
        "a broad-cheeked face with pale gold eyes and a barely-contained feline menace",
        "the tiger-headed mount of the goddess Durga"
    },
    [SPC_PARDUS] = {
        "leopard", "tawny-golden fur with neat black rosette markings",
        "a small round-cheeked head with short pricked ears",
        "cold pale green eyes with round pupils",
        "faint dark rosettes scattered along the cheek and neck",
        "a sleek-cheeked, cold-eyed face with a rosette-spotted complexion",
        "a leopard-headed spirit of the sacred groves of Dahomey"
    },
    [SPC_LYNX] = {
        "lynx", "thick silver-tipped gray fur with faint dark mottling",
        "a round broad-cheeked head with tufted black-tipped ears",
        "pale yellow eyes with vertically slit pupils",
        "long pointed ear-tufts and a wide muttonchop ruff at the jaw",
        "a round-cheeked, tuft-eared face with pale watchful eyes",
        "a lynx-headed watcher of the northern forests"
    },
    [SPC_HYAENA] = {
        "hyena", "coarse sandy-brown fur spotted and crested along the nape",
        "a heavy-jawed head with a bristly crest and rounded ears",
        "small gold eyes with a sidelong evaluating stare",
        "powerful jaws and a permanent half-smile of bared teeth",
        "a heavy-jawed, sidelong-eyed face with a low unsettling smile",
        "a hyena-headed trickster of the Ethiopian highland tales"
    },
    [SPC_APER] = {
        "boar", "thick coarse black-brown bristles and a stiff dorsal crest",
        "a long snouted head with small upright ears",
        "small dark eyes deeply set above the jowls",
        "upward-curving ivory tusks jutting from the lower jaw",
        "a heavy-snouted, small-eyed face with a tusked, low-browed ferocity",
        "a boar-headed war-god after the Vedic Varaha"
    },
    [SPC_MELES] = {
        "badger", "silvery-gray fur with a bold black-and-white striped face",
        "a low wedge-shaped head with small rounded ears",
        "small dark shoe-button eyes",
        "a black-and-white banded face unmistakable in any light",
        "a striped-faced, low-browed, close-set-eyed bearing with an earthen stubbornness",
        "a badger-headed ancestor from the sett-dwellers of British folklore"
    },
    [SPC_SCIURUS] = {
        "squirrel", "soft russet-red fur with a pale underbelly",
        "a small round-cheeked head with tall tufted ears",
        "large black liquid eyes, alert and round",
        "prominent front incisors just showing at the upper lip",
        "a round-cheeked, bright-eyed, tuft-eared face with a quick nervous alertness",
        "a squirrel-headed messenger after the Norse Ratatoskr"
    },
    [SPC_ERINACEUS] = {
        "hedgehog", "soft gray face-fur giving way to a cape of stiff brown spines at the shoulders",
        "a small pointed-snouted head with small rounded ears",
        "small dark bright eyes",
        "a small pink snout and a mantle of stiff spines behind the head",
        "a small, sharp-snouted face ringed by a prickly halo of spines",
        "a hedgehog-headed spirit of the hedgerows"
    },
    [SPC_GORILLA] = {
        "gorilla", "dense black fur streaked with silver down the back",
        "a massive sagittal-crested head with a heavy brow ridge",
        "deep brown eyes in shadowed sockets under a shelving brow",
        "a broad flat nose and a powerful jaw",
        "a massive-browed, heavy-jawed, sorrowful-eyed face with a patient strength",
        "a gorilla-headed elder of the deep forest"
    },
    [SPC_CAMELOPARDALIS] = {
        "giraffe", "pale cream hide dappled with large irregular tan spots",
        "a small high head with two short fur-covered ossicones",
        "large dark lashed eyes set high on the head",
        "two fur-covered ossicones and the beginnings of a very long neck",
        "a small-headed, long-necked, lash-eyed bearing with an aloof serenity",
        "a giraffe-headed guardian after the Ming admiral's tributary qilin"
    },
    [SPC_CYGNUS] = {
        "swan", "pure white plumage, softly feathered at the throat",
        "a small sleek white-feathered head and a long curving neck",
        "small dark eyes set against a bold orange-black beak",
        "an orange beak with a black knob at the base",
        "a long-necked, small-headed, orange-beaked bearing with a cool imperious grace",
        "a swan-headed Apollonian mask after the Hyperborean rite"
    },
    [SPC_CICONIA] = {
        "stork", "white body plumage with long black flight-feathers at the wing",
        "a small white-feathered head and an immensely long red beak",
        "pale eyes ringed in bare red skin",
        "a very long red beak and the bare red face-skin of the adult bird",
        "a long-beaked, red-faced bearing with a patient watchfulness at the reeds",
        "a stork-headed herald of births after the old European cradle-lore"
    },
    [SPC_IBIS] = {
        "ibis", "white body plumage with iridescent black trailing edges",
        "a bare black-skinned head and a long down-curved black beak",
        "small dark eyes set in unfeathered black face-skin",
        "a long curving scythe-shaped beak",
        "a bare-faced, long-curve-beaked bearing with a quiet scribal precision",
        "the ibis-headed Thoth at his tablet"
    },
    [SPC_PSITTACUS] = {
        "parrot", "brilliant green plumage with scarlet flashes at the wing",
        "a rounded green-feathered head and a strongly hooked beak",
        "round pale yellow eyes ringed by a patch of bare white skin",
        "a heavy curving upper beak and a bright tongue visible at the parted mandibles",
        "a sharp-beaked, bright-eyed, loud-feathered bearing with a witty bookish air",
        "a parrot-headed messenger of Kamadeva the love-god"
    },
    [SPC_GALLUS] = {
        "rooster", "glossy red-gold neck feathers cascading over the shoulders",
        "a small bold head crowned by a tall scarlet comb",
        "small amber eyes, quick and bright",
        "a scarlet comb above and scarlet wattles beneath the beak",
        "a comb-crowned, sharp-eyed, strutting bearing with a morning's arrogance",
        "a rooster-headed solar-herald after the Gallic dawn-cult"
    },
    [SPC_FALCO] = {
        "falcon", "slate-blue back feathers and a pale barred breast",
        "a sleek dark-hooded head with distinct black 'malar' stripes beneath the eyes",
        "enormous dark eyes ringed in bright yellow cere-skin",
        "a short hooked beak and a notched upper mandible",
        "a hooded-eyed, sharp-cheeked, dark-streaked face with a raptor's unsettling focus",
        "a falcon-headed herald from a Persian miniature"
    },
    [SPC_CROCODILUS] = {
        "crocodile", "plated olive-green scales with dark banding across the shoulders",
        "a long low armored head with ridged bony crests over the eyes",
        "small gold eyes with vertically slit pupils",
        "rows of conical teeth visible outside the closed jaw",
        "a low-slung, ridge-browed, slit-eyed face with an ancient reptilian stillness",
        "a crocodile-headed river-lord of the West African mangrove-cult"
    },
    [SPC_CHAMAELEON] = {
        "chameleon", "finely granulated skin shifting from pale green to turquoise over the shoulders",
        "a helmet-like casque-headed skull with turreted swivelling eye-mounts",
        "independently swivelling eyes set in conical turrets, half-closed",
        "a coiled prehensile tail just visible behind the shoulder",
        "a casque-headed, turret-eyed face with an otherworldly lateral gaze",
        "a chameleon-headed trickster of West African cosmogony"
    },
    [SPC_RANA] = {
        "frog", "smooth damp green skin with fine darker spotting",
        "a broad flat-topped head with bulging eyes set high and wide",
        "enormous gold-and-black eyes bulging above the skull",
        "a wide slit of a mouth and a soft pulsing throat-sac",
        "a wide-mouthed, bulge-eyed, smooth-skinned face with a damp amphibian calm",
        "a frog-headed rain-bringer from a Mesoamerican codex"
    },
    [SPC_CARCHARIAS] = {
        "shark", "smooth steel-gray skin fading to white below",
        "a low torpedo-shaped head with paired slit nostrils",
        "flat black eyes with no visible iris, unblinking",
        "rows of serrated triangular teeth in a half-open mouth",
        "a flat-eyed, steel-skinned, teeth-ranked face with a pelagic hunger",
        "a shark-headed sea-daemon of the Polynesian ancestor-cults"
    },
    [SPC_POLYPUS] = {
        "octopus", "smooth mottled red-brown skin flushing to cream across the mantle",
        "a domed bulbous head with no visible neck, tentacles beginning at the shoulders",
        "horizontally slit rectangular-pupiled eyes",
        "eight muscular tentacles fanning out from the collar in place of arms",
        "a domed, bulbous-browed, rectangular-eyed face with a terrifying invertebrate intelligence",
        "an octopus-headed seer of the Pacific abyssal traditions"
    },
    [SPC_APIS] = {
        "bee", "a coat of fine golden-yellow fur banded with velvet black",
        "a small rounded head with large compound eyes and feathery antennae",
        "enormous curving compound eyes occupying most of the face",
        "a slender curved proboscis and feathered antennae",
        "a compound-eyed, fuzz-faced, antennaed bearing with a busy industrious focus",
        "a bee-headed priestess of the old Aegean apiarian cults"
    },
    [SPC_PAPILIO] = {
        "butterfly", "a coat of iridescent scale-fur in deep blue and black",
        "a small fur-crowned head with long club-tipped antennae",
        "large dark compound eyes in a soft fuzz-ringed face",
        "a coiled proboscis and two tall club-tipped antennae",
        "a fuzz-faced, antennaed, compound-eyed bearing with a fragile patterned elegance",
        "a butterfly-headed soul-bearer after the Greek Psyche"
    },
    [SPC_SCORPIO] = {
        "scorpion", "plated amber-yellow chitin, glossy at the shoulders",
        "a low armored head plate with small sensory pedipalps beside the mouth",
        "several small bead-like black eyes clustered on the carapace",
        "a curling, sting-tipped tail arched above the shoulder",
        "a chitin-plated, many-eyed, sting-tailed bearing with a poised arid menace",
        "a scorpion-headed desert-watcher of the Saharan Tuareg tradition"
    },
    [SPC_CUNICULUS] = {
        "rabbit", "soft dove-gray fur, downy across the cheeks and throat",
        "a small rounded head with long upright ears lined in pale pink",
        "warm dark eyes set to the sides of the face, ringed by fine whiskers",
        "a twitching cleft upper lip and two small pale incisors",
        "a soft, round-cheeked face with long upright ears and a faintly trembling gentleness",
        "a rabbit-headed moon-hare of the Chinese lunar palace"
    },
    [SPC_MUS] = {
        "mouse", "short warm-brown fur paling to cream along the belly",
        "a tiny pointed-snouted head with large rounded ears",
        "small glittering black eyes like wet beads",
        "a pink twitching nose and delicate whiskers",
        "a small, sharp-featured face with enormous rounded ears and quick bright eyes",
        "a mouse-headed scribe of the temple granaries"
    },
    [SPC_PASSER] = {
        "sparrow", "mottled chestnut and dun plumage streaked with black",
        "a small round-crowned head with a short conical beak",
        "small bright black eyes, quick and observant",
        "a short pale beak and a chestnut cap over the crown",
        "a small, bright-eyed, sharp-beaked bearing with a plain streetwise quickness",
        "a sparrow-headed messenger of Aphrodite's chariot"
    },
    [SPC_CASTOR] = {
        "beaver", "dense water-slicked russet-brown fur",
        "a broad blunt head with small rounded ears set far back",
        "small dark eyes, calm and deep-set",
        "two bright orange incisors visible beneath the upper lip",
        "a broad-cheeked, blunt-muzzled face with orange-toothed industriousness",
        "a beaver-headed builder-spirit of the northern river-clans"
    },
    [SPC_LUTRA] = {
        "otter", "sleek water-dark brown fur, soft and whiskered at the cheeks",
        "a rounded head with small neat ears and a long whiskered muzzle",
        "bright dark eyes set forward in the face, playful and observant",
        "pale whiskers bristling around a black button nose",
        "a whiskered, round-cheeked face with bright playful eyes and a sinuous alertness",
        "an otter-headed water-spirit of the Scottish kelpie-lore"
    },
    [SPC_MANTIS] = {
        "praying mantis", "slender pale-green chitin plated across the shoulders",
        "a small triangular head on a long flexible neck",
        "two enormous bulbous compound eyes set at the points of the triangle",
        "a pair of folded raptorial forelimbs raised at the chest, as if in prayer",
        "a triangle-headed, huge-eyed bearing with the folded-handed patience of an ambush-predator",
        "a mantis-headed ascetic of the old Kalahari rock-paintings"
    },
    [SPC_CICADA] = {
        "cicada", "lacquered black-and-bronze chitin with faint golden veining",
        "a broad blunt head with two large rounded compound eyes far apart",
        "wide-set compound eyes with a hard jewel-like sheen",
        "two pairs of clear veined wings folded tent-wise behind the shoulders",
        "a wide-eyed, lacquer-faced, veined-winged bearing with a summer-noon stillness",
        "a cicada-headed chorister of the Greek pastoral lyric"
    },
    [SPC_SALMO] = {
        "salmon", "silvery scales flushed with rose along the shoulders and flank",
        "a long tapered head with a hooked lower jaw",
        "round coppery eyes, lidless and steady",
        "a slightly hooked kype at the lower jaw and fine banded scales",
        "a long-jawed, coppery-eyed, rose-flushed face with a river-running resolve",
        "a salmon-headed wisdom-keeper from the Irish otherworld-tales"
    }
};

/* ---- phrases variae ---- */

static const char *const gestus_phrases[GST_N] = {
    "watchful and alert, head lifted and turned very slightly toward a sound",
    "drowsy and half-lidded, the head slightly lowered as if on the edge of sleep",
    "poised and intent, as though about to spring on some unseen quarry",
    "tensed and backward-leaning, as though listening for pursuit",
    "proudly upright, chin lifted and shoulders squared",
    "solemn and still, the gaze held steady on the viewer",
    "timid and drawn-in, shoulders hunched a little and eyes wide",
    "perfectly quiet and composed, neither tense nor loose",
    "wrathful, brow drawn low and lips parted on the edge of a snarl",
    "openly laughing, head thrown slightly back and eyes creased with mirth",
    "deep in contemplation, eyes half-closed and the head tilted forward in thought",
    "imploring, the face turned slightly upward and the lips parted as if in supplication",
    "warmly curious, head tilted quizzically to one side and the ears pricked forward",
    "playful and delighted, the mouth softly open in a small happy grin and the eyes crinkled with mirth",
    "tender and affectionate, the head softly inclined and the eyes unmistakably fond",
    "wide-eyed with gentle wonder, the lips parted as though having just glimpsed something marvellous"
};

static const char *const amictus_nemes_opts[] = {
    "an Egyptian nemes headcloth striped in blue and gold, gathered at the shoulders",
    "a softly draped indigo-dyed cotton cowl pulled up close behind the head, in the manner of a Tuareg tagelmust",
    "a pale linen head-wrap wound loosely about the crown, in the manner of a Levantine keffiyeh",
    "a folded silk headcloth patterned in soft peach and ivory, in the manner of a Persian chador",
    "a heavy embroidered gele of russet and gold wound into tall pleats, in the West African manner",
    "a saffron silk headcloth falling in soft folds to the shoulders, in the manner of a monastic veil",
    "a thick felted-wool cap pulled low over the ears, in the manner of the northern steppe-riders",
    "a crisply folded Sikh dastar in sky-blue cotton, neatly pleated at the brow",
    "a white Japanese hachimaki tied across the brow with the knot over one ear",
    "a long trailing dupatta of pale-rose silk drawn lightly over the crown"
};

static const char *const amictus_phrases[AMC_N] = {
    "no ornament or garment beyond the plain ground of the portrait",
    "an Egyptian nemes headcloth striped in blue and gold, gathered at the shoulders",  /* nemes:
        tabula amictus_nemes_opts variationem praebet */
    "a heavy studded metal collar set with a single polished cabochon",
    "a segmented bronze lorica worked with scale and ring across the shoulders",
    "a draped white stola clasped at one shoulder with a bronze pin",
    "a small round shield (pelta) slung at the shoulder, rim visible above the arm",
    "a plaited sertum of laurel and small wildflowers about the brow",
    "a carved ivory chess-piece pendant on a slim chain — unmistakably a knight, its horse-head in sharp profile at the hollow of the throat",
    "a high open crown of worked gold, set with a single cabochon ruby at the brow",
    "a sheer dark veil falling from the crown over the shoulders, the face just visible through the cloth",
    "broad white woollen infulae — the sacred ritual fillets — bound at the brow and trailing to the shoulders",
    "a heavy twisted gold torc at the throat, its finials worked into small animal heads",
    "a soft hand-knitted woollen scarf in cream and oatmeal, wrapped loosely at the throat",
    "a small cheerful ribbon bow tied neatly just beneath the chin, in lemon-yellow or sky-blue",
    "an oversized fresh daisy tucked behind one ear, its white petals standing out against the fur or skin",
    "a simple strand of tiny river-pearls at the throat, clasped with a small silver heart"
};

/* ---- compositio ---- */

static int compone(
    Charta *out, const BestiaOptiones *o,
    char *error_locus, size_t error_longitudo
) {
    int i_spc, i_grd, i_rat, i_gst, i_amc, i_fnd;

    if (o->species) {
        i_spc = indicium_clavis(o->species, species_claves, SPC_N);
        if (i_spc < 0) { pone_errorem(
            error_locus, error_longitudo,
            "species vitiosa: %s", o->species
        );
            return 0;
        }
    } else
        i_spc = alea_ambitus(SPC_N);

    if (o->gradus) {
        i_grd = indicium_clavis(o->gradus, gradus_claves, GRD_N);
        if (i_grd < 0) { pone_errorem(
            error_locus, error_longitudo,
            "gradus vitiosus: %s", o->gradus
        );
            return 0;
        }
    } else
        i_grd = alea_ambitus(GRD_N);

    if (o->ratio) {
        i_rat = indicium_clavis(o->ratio, ratio_claves, RAT_N);
        if (i_rat < 0) { pone_errorem(
            error_locus, error_longitudo,
            "ratio vitiosa: %s", o->ratio
        );
            return 0;
        }
    } else {
        /* lusorius rara sit: sine argumento tantum ~1/16 casuum eligitur,
         * ne scaccorum tessellae inquadramentum dominentur. */
        if (alea_ambitus(16) == 0)
            i_rat = RAT_LUSORIUS;
        else
            i_rat = alea_ambitus(RAT_N - 1);
    }

    if (o->gestus) {
        i_gst = indicium_clavis(o->gestus, gestus_claves, GST_N);
        if (i_gst < 0) { pone_errorem(
            error_locus, error_longitudo,
            "gestus vitiosus: %s", o->gestus
        );
            return 0;
        }
    } else
        i_gst = alea_ambitus(GST_N);

    if (o->amictus) {
        i_amc = indicium_clavis(o->amictus, amictus_claves, AMC_N);
        if (i_amc < 0) { pone_errorem(
            error_locus, error_longitudo,
            "amictus vitiosus: %s", o->amictus
        );
            return 0;
        }
    } else {
        i_amc = alea_ambitus(AMC_N);
        /* latrunculus (pendens scacci) thematice tantum cum lusorio congruit;
         * alias amictus aliud eligitur. */
        if (i_amc == AMC_LATRUNCULUS && i_rat != RAT_LUSORIUS) {
            i_amc = alea_ambitus(AMC_N - 1);
            if (i_amc >= AMC_LATRUNCULUS)
                i_amc++;
        }
    }

    if (o->fundus) {
        i_fnd = indicium_clavis(o->fundus, fundus_claves, FND_N);
        if (i_fnd < 0) { pone_errorem(
            error_locus, error_longitudo,
            "fundus vitiosus: %s", o->fundus
        );
            return 0;
        }
    } else
        i_fnd = alea_ambitus(FND_N);

    const SpeciesDatum *s = &species_data[i_spc];
    const char *art = (
        s->anglice[0] == 'a' || s->anglice[0] == 'e' || s->anglice[0] == 'i' ||
        s->anglice[0] == 'o' || s->anglice[0] == 'u'
    ) ? "an" : "a";

    if (!charta_adde(out, INQUADRAMENTUM))
        return 0;

    /* Corpus effigiei secundum gradum — tres templata per casum, ex
     * semine unum eligitur. Argumenta per casum eadem manent. */
    static const char *const templ_adumbratio[4] = {
        "The subject is an entirely human being, neither costumed nor "
        "masked, but the face carries %1$s. The features are all human, "
        "yet the resemblance to %2$s %3$s is unmistakable. ",
        "This is a straight human portrait, no hybrid anatomy of any "
        "kind — yet anyone looking at the face would say at once: there "
        "is %2$s %3$s here. The bearing is %1$s. ",
        "A human face, nothing added, nothing taken away — but the "
        "resemblance is so strong that the viewer reads %2$s %3$s in "
        "the features: %1$s. ",
        "A fully human portrait in the physiognomic tradition: the "
        "anatomy is nothing but human, yet about this face hangs "
        "something unmistakably animal — %1$s. The spectator reads %2$s "
        "%3$s at once in the set of the features. "
    };
    static const char *const templ_mixtura[4] = {
        "The subject is a chimeric being: the head is still broadly "
        "human in overall shape, but the ears, eyes, and the surface of "
        "the skin have taken on the character of %1$s %2$s. In "
        "particular, the head bears %3$s, and the face shows %4$s. ",
        "A partial hybrid: broadly a human head in shape, but %3$s "
        "spreads across the skin and scalp, and %4$s look out where "
        "human eyes would be. The overall impression is of %1$s %2$s "
        "still in the process of becoming human, or the reverse. ",
        "The head is a blend — human in outline, animal in substance. "
        "The skin shows %3$s and the eyes are %4$s. The effect is of "
        "%1$s %2$s half-contained inside a human form. ",
        "A transitional creature: the skull is still broadly human, but "
        "the ears have pricked into those of %1$s %2$s, %3$s has crept "
        "in at the hairline and jaw, and where human eyes once were "
        "%4$s now look out. The face hovers between kinds. "
    };
    static const char *const templ_theriocephalus[4] = {
        "The subject has the head of %1$s %2$s set atop a fully human "
        "body. The head is rendered anatomically — %3$s, with %4$s, "
        "%5$s, and %6$s — while the shoulders, neck, and visible chest "
        "are those of an ordinary human adult. ",
        "A theriocephalic figure in the ancient manner: the body below "
        "the collarbone is human and unremarkable, but the head is that "
        "of %1$s %2$s, complete and anatomically correct — %3$s, %4$s, "
        "and %5$s, with %6$s. No mask: the head meets the human neck at "
        "the skin, with no seam or edge. ",
        "Human body, animal head: the shoulders and chest are those of "
        "an adult human, but where a human head should be there is "
        "instead %1$s %2$s's head — %3$s — with %4$s, %5$s, and %6$s. "
        "The join is smooth, no mask. ",
        "A classical theriocephalic composition drawn from the wide tradition "
        "of animal-headed figures — Egyptian, Hindu, Mesoamerican, Celtic, "
        "Byzantine — an ordinary adult human body supporting, at the neck, "
        "the anatomically exact head of %1$s %2$s — %3$s, %4$s, %5$s, and "
        "%6$s. There is no costume and no mask; fur or feather or scale "
        "meets human skin at the collarbone as though it had always been so. "
    };
    static const char *const templ_bestia_ipsa[4] = {
        "There is no human in this portrait: the subject is %1$s %2$s, "
        "depicted in all the conventions of a human formal portrait. "
        "The body is entirely that of the animal, shown from the chest "
        "up: %3$s, %4$s, %5$s, and %6$s. ",
        "The subject is purely animal: %1$s %2$s, no human anatomy at "
        "any point. The animal is shown in the pose and framing of a "
        "dignified human portrait — %3$s, %4$s, %5$s, and %6$s — but "
        "nothing has been anthropomorphized. ",
        "A straight animal portrait, only the framing borrowed from "
        "human convention. The subject is %1$s %2$s and nothing else: "
        "%3$s, with %4$s, %5$s, and %6$s. No clothes, no hands, no "
        "human features of any kind. ",
        "The sitter is simply %1$s %2$s, rendered as a dignified "
        "bust-length portrait. %3$s, %4$s, %5$s, and %6$s — all faithful "
        "to the living animal, with no trace of anthropomorphism in "
        "pose or expression. "
    };
    int v_grd = (int)alea_ambitus(4);
    switch (i_grd) {
    case GRD_ADUMBRATIO:
        if (
            !charta_scribe(
                out, templ_adumbratio[v_grd],
                s->humanum, art, s->anglice
            )
        ) return 0;
        break;
    case GRD_MIXTURA:
        if (
            !charta_scribe(
                out, templ_mixtura[v_grd],
                art, s->anglice, s->pellis, s->oculi
            )
        ) return 0;
        break;
    case GRD_THERIOCEPHALUS:
    case GRD_BESTIA_IPSA: {
            const char *const *t = (i_grd == GRD_THERIOCEPHALUS)
                ? templ_theriocephalus : templ_bestia_ipsa;
            if (
                !charta_scribe(
                    out, t[v_grd],
                    art, s->anglice, s->caput, s->pellis, s->oculi, s->nota
                )
            ) return 0;
            break;
        }
    }

    /* Framing sententia secundum rationem — idem modus: tres templata
     * per casum, ex semine unum. */
    static const char *const templ_physiognomonicus[4] = {
        "The picture is staged in the manner of Giambattista della "
        "Porta's physiognomic comparisons: the portrait is presented "
        "quite seriously, as a study of character through animal "
        "resemblance, with no comic exaggeration. ",
        "The staging is that of a sober sixteenth-century physiognomonic "
        "plate: the figure is observed as if for a learned treatise on "
        "how bestial resemblances disclose character — no caricature, "
        "no humor. ",
        "The framing is deliberately clinical, in the tradition of the "
        "old physiognomists: a straight portrait presented as a piece "
        "of natural-philosophical evidence about the temperament of "
        "its subject. ",
        "The frame is that of a quiet learned plate, after the old "
        "physiognomists who read the bestial in the human face: no "
        "caricature, no moralizing, only the patient documentation of "
        "a resemblance. "
    };
    static const char *const templ_totemicus[4] = {
        "Just behind the subject, half in shadow, a small living %s is "
        "also visible — perched at the shoulder or crouched against the "
        "chest — as a totemic companion that doubles the portrait's "
        "meaning. ",
        "At the subject's shoulder a small living %s stands in "
        "attendance, plainly visible but secondary to the human figure, "
        "functioning as the subject's totem. ",
        "Quietly doubling the subject, a single %s is shown close by — "
        "at the shoulder, on the chest, or just behind the head — as an "
        "attendant spirit-animal. ",
        "A small living %s appears in the frame as the subject's totem: "
        "perched on a gloved hand, curled in the crook of the arm, or "
        "looking out from behind the shoulder — clearly the subject's "
        "familiar rather than a separate sitter. "
    };
    static const char *const templ_fabularis[4] = {
        "The picture is staged in the manner of Grandville or Tenniel: "
        "the subject wears human clothing appropriate to a specific "
        "station or trade, and occupies the portrait with the easy "
        "self-possession of a fable's protagonist. ",
        "The framing is Aesopic and fabular: the figure wears human "
        "dress of a defined profession or class and behaves like a "
        "character in a moral tale, with the unforced composure of "
        "someone used to being painted. ",
        "An illustrator's fable-portrait: the subject is dressed as a "
        "particular human role — judge, scholar, soldier, shopkeeper, "
        "mother — and carries itself without any awkwardness about the "
        "costume, as if this were simply its ordinary life. ",
        "A Victorian fable-plate in the Grandville manner: the subject "
        "is fully clothed in the dress of a recognizable human trade or "
        "rank, and sits for its portrait with the solemn dignity of a "
        "frontispiece in a moral storybook. "
    };
    static const char *const templ_mythicus[4] = {
        "The picture is staged as a hieratic, cult image: the subject "
        "is treated as %s, with formal, frontal posture and a field of "
        "plain pigment behind, in the manner of ancient temple art. ",
        "The framing is that of a religious icon of %s: frontal, "
        "symmetrical, reverent, with none of the psychological "
        "looseness of a secular portrait. ",
        "A cult image of %s: the figure sits in strict frontal hieratic "
        "posture, as if painted on a temple wall rather than in a "
        "patron's studio. ",
        "The composition is a devotional panel of %s: strictly frontal, "
        "strictly centered, the hieratic stillness of a votive offering "
        "rather than a likeness from life. "
    };
    static const char *const templ_lusorius[4] = {
        "The picture is staged as a formal portrait of a board-game "
        "piece come to life: the %s is posed in the manner of a carved "
        "chess or draughts piece, with stiff heraldic bearing, and a "
        "polished black-and-white checkered floor or tile visible at "
        "the lower edge of the frame as a plain reminder of the game. "
        "The pose has the carved stillness of a Lewis chessman. ",
        "The framing borrows from the world of the chessboard: the %s "
        "stands as if it has just stepped off its square, with stiff "
        "heraldic carriage and a black-and-white checkered surface "
        "underfoot, rendered in the style of a sober illustrated chess "
        "treatise. ",
        "A game-piece portrait: the %s is treated as if it were a "
        "chessman or checkers king, posed with carved-wood stillness, "
        "a plain checkered ground underfoot, and the air of a figure "
        "that exists primarily to move on a board. ",
        "An illuminated manuscript's chess-diagram come to life: the "
        "%s stands in the exact posture of a turned-wood game-piece, "
        "with a checkered pavement of ivory and ebony running to the "
        "lower edge of the frame and the stiff heraldic bearing of "
        "something carved rather than born. "
    };
    int v_rat = (int)alea_ambitus(4);
    switch (i_rat) {
    case RAT_PHYSIOGNOMONICUS:
        if (!charta_adde(out, templ_physiognomonicus[v_rat]))
            return 0;
        break;
    case RAT_TOTEMICUS:
        if (!charta_scribe(out, templ_totemicus[v_rat], s->anglice))
            return 0;
        break;
    case RAT_FABULARIS:
        if (!charta_adde(out, templ_fabularis[v_rat]))
            return 0;
        break;
    case RAT_MYTHICUS:
        if (!charta_scribe(out, templ_mythicus[v_rat], s->mythicum))
            return 0;
        break;
    case RAT_LUSORIUS:
        if (!charta_scribe(out, templ_lusorius[v_rat], s->anglice))
            return 0;
        break;
    }

    if (!charta_scribe(out, "The bearing is %s. ", gestus_phrases[i_gst]))
        return 0;

    if (i_amc == AMC_NULLUS) {
        if (
            !charta_adde(
                out, "There is no ornament or garment at the "
                "shoulders: only the bare form of the subject. "
            )
        ) return 0;
    } else {
        const char *amc_phrasis = (i_amc == AMC_NEMES)
            ? amictus_nemes_opts[alea_ambitus(
                sizeof amictus_nemes_opts / sizeof *amictus_nemes_opts
            )]
            : amictus_phrases[i_amc];
        if (!charta_scribe(out, "At the shoulders is %s. ", amc_phrasis))
            return 0;
    }

    const char *fundus_phrasis;
    if (i_fnd == FND_PLANUM) {
        fundus_phrasis = fundus_planum_opts[
            alea_ambitus(sizeof fundus_planum_opts / sizeof *fundus_planum_opts)];
    } else if (i_fnd == FND_COLORATUM) {
        fundus_phrasis = fundus_coloratum_opts[
            alea_ambitus(sizeof fundus_coloratum_opts / sizeof *fundus_coloratum_opts)];
    } else {
        fundus_phrasis = fundus_scribenda[i_fnd];
    }
    if (!charta_scribe(out, "The background is %s.\n", fundus_phrasis))
        return 0;

    return 1;
}

char *bestia_generare(
    uint64_t semen,
    const BestiaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    static const BestiaOptiones vacua = {0};
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

/* ---- rudis: parametros mero modo iterat ----
 *
 * Praecursor idem est ac in persona_generare_rudis et
 * artista_generare_rudis, ut imagines comparari possint. Si hic
 * mutatur, persona.c et artista.c quoque mutandi sunt. */
static const char *const rudis_praecursor =
    "Generate a portrait. The subject's head is centered in the frame "
    "and the subject is facing the viewer. ";

char *bestia_generare_rudis(
    uint64_t semen,
    const BestiaOptiones *optiones,
    char *error_locus, size_t error_longitudo
) {
    static const BestiaOptiones vacua = {0};
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
            "This is a bestia: a theriomorphic portrait — a portrait in which "
            "the subject is either an animal, has the head of an animal, or "
            "otherwise bears a recognizable resemblance to an animal of your "
            "own choosing. "
        )
    ) goto defecit;
    if (!charta_adde(&out, "Make a random portrait of someone."))
        goto defecit;
    (void)semen;

    static const char *const claves_anglice[] = {
        "the animal species", "the hybrid degree", "the framing tradition",
        "the bearing", "the ornament at the shoulders", "the background"
    };
    const char *valores[6] = {
        optiones->species, optiones->gradus, optiones->ratio,
        optiones->gestus, optiones->amictus, optiones->fundus
    };
    for (int i = 0; i < 6; i++) {
        if (!valores[i])
            continue;
        if (
            !charta_scribe(
                &out, " Also %s should be %s.",
                claves_anglice[i], valores[i]
            )
        )
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

void bestia_usus(FILE *f) {
    usus_claves(
        f,
        "      --species X     ",
        "                      ",
        species_claves, SPC_N
    );
    usus_claves(
        f,
        "      --gradus X      ",
        "                      ",
        gradus_claves, GRD_N
    );
    usus_claves(
        f,
        "      --ratio X       ",
        "                      ",
        ratio_claves, RAT_N
    );
    usus_claves(
        f,
        "      --gestus X      ",
        "                      ",
        gestus_claves, GST_N
    );
    usus_claves(
        f,
        "      --amictus X     ",
        "                      ",
        amictus_claves, AMC_N
    );
    usus_claves(
        f,
        "      --fundus X      ",
        "                      ",
        fundus_claves, FND_N
    );
}
