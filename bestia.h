#ifndef BESTIA_H
#define BESTIA_H

#include <stddef.h>
#include <stdint.h>

/* Optiones describendae effigiei theriomorphae. Campi per litteras
 * NULL vacant, eosdem valores accipiunt quos argumenta lineae
 * mandatorum.
 *
 * Inquadramentum idem est ac in artista et persona: effigies dimidii
 * corporis, humeris ad spectatorem conversis. Differentia haec est:
 * persona hominem describit, artista modum pingendi describit,
 * bestia autem rationem qua imago humana cum animali misceatur —
 * vel prorsus in animal vertatur.
 *
 * Traditio vetus: Giambattista della Porta (1586) voltus humanos
 * cum bestiarum comparavit; Grandville et Tenniel animalia vestibus
 * induerunt; Aegyptii deos theriocephalos pinxerunt. Hoc generator
 * eadem vena utitur.
 *
 * Cave: textus emissus clavem Latinam numquam profert — tantum res
 * ipsas quae in tela videantur (vulpem, corvum, caput ibis, pellem
 * rufam, et cetera). */
typedef struct {
    const char *species;   /* vulpes | corvus | bubo | lupus | lepus |
                              felis | aquila | cervus | serpens | simia |
                              ursus | piscis | mustela | testudo | aries |
                              taurus | aranea | equus | canis | leo |
                              hircus | delphinus | vespertilio | pavo |
                              hydrochoerus | diomedea | elephas |
                              camelus | rhinoceros | tigris | pardus |
                              lynx | hyaena | aper | meles | sciurus |
                              erinaceus | gorilla | camelopardalis |
                              cygnus | ciconia | ibis | psittacus |
                              gallus | falco | crocodilus | chamaeleon |
                              rana | carcharias | polypus | apis |
                              papilio | scorpio | cuniculus | mus |
                              passer | castor | lutra | mantis |
                              cicada | salmo */
    const char *gradus;    /* adumbratio   (voltus humanus animali similis)
                            * mixtura      (lineamenta commixta — oculi, aures)
                            * theriocephalus (caput animalis in corpore humano)
                            * bestia_ipsa  (animal ipsum in habitu personae) */
    const char *ratio;     /* physiognomonicus (more della Portae)
                            * totemicus        (animal iuxta sedet vel umbram facit)
                            * fabularis        (Aesopi, Grandville: vestitum, loquens)
                            * mythicus         (Anubis, Bastis, Ganesius)
                            * lusorius         (imago latrunculi scaccorum: bestia
                            *                   ut lapis in tabula picta stat) */
    const char *gestus;    /* vigil | dormiens | venans | fugiens |
                              superbus | solemnis | pavidus | quietus |
                              iratus | ridens | meditans | supplex */
    const char *amictus;   /* nullus | nemes | collare | lorica | stola |
                              pelta | sertum | latrunculus | corona |
                              velum | infula | torquis —
                              ornamentum rationi congruens */
    const char *fundus;    /* planum | tenebrosum | luminosum | aureum |
                              paesagium | ornatum | silva | templum |
                              coloratum | aquaticum | nocturnum |
                              crepusculum */
} BestiaOptiones;

/* Picturam theriomorpham describens generare.
 *
 * Semen necessarium est: vocans ipse dare debet (e.g. ex /dev/urandom).
 *
 * Si res bene evenit, reddit catenam characterum in acervo dispositam
 * (vocantis est free() vocare).
 *
 * Si quid mali accidit, reddit NULL; si error_locus non NULL et
 * error_longitudo > 0, nuntius ibi scribitur.
 *
 * Optiones NULL idem valent ac structura tota zeris impleta. */
char *bestia_generare(
    uint64_t semen,
    const BestiaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

/* Variatio rudis: eodem modo vocatur ac bestia_generare, sed textus
 * emissus picturam non describit. Potius parametros mero modo iterat,
 * ut "Generate a portrait ... Also species should be X. Also the
 * hybrid degree should be Y." Praecursor idem est ac in
 * persona_generare_rudis et artista_generare_rudis, ut imagines
 * comparari possint. */
char *bestia_generare_rudis(
    uint64_t semen,
    const BestiaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

#endif
