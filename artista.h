#ifndef ARTISTA_H
#define ARTISTA_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Optiones picturae describendae. Campi per litteras NULL vacant,
 * eosdem valores accipiunt quos argumenta lineae mandatorum.
 *
 * Inquadramentum semper idem est: effigies dimidii corporis, humeris
 * ad spectatorem conversis. Persona ipsa hic non describitur (ad id
 * videatur persona.h); hic tantum modus pingendi describitur.
 *
 * Cave: quamquam claves artifices propriis nominibus notant, textus
 * emissus nomen artificis numquam profert — solum res ipsas in tela
 * visas (horologium liquescens, tessellae aureae, cancelli primi,
 * et cetera). */
typedef struct {
    const char *artifex;   /* dalius | klimtius | mondrianus | vermerus |
                              escherus | kandinskius | magrittius | pollockius |
                              picassonus | vangoghus | warholus | schieleus |
                              baconius | hopperus | hokusaius | munchius |
                              lichtensteinius | modiglianius | rembrandtus |
                              hockneius | freudus | basquiatus | seuratus |
                              rivereus | velaspinus | crispulus | nimbulus |
                              echokus | fulguritus | tesselarius | obscurus |
                              filumentus | chronofugus | somniator |
                              vacuarius | mortuarius | algorithmicus |
                              holographus | cryptolalus | interstitius */
    const char *medium;    /* oleum | tempera | acrylicum | gouache |
                              atramentum | fresca | collage | musivum */
    const char *palaestra; /* calida | frigida | saturata | muta |
                              monochroma | primaria | terrea */
    const char *habitus;   /* serenus | turbulentus | melancholicus | iubilans |
                              solemnis | tensus */
    const char *fundus;    /* planum | ornatum | paesagium | abstractum |
                              tenebrosum | luminosum */
} ArtistaOptiones;

/* Picturam describens generare.
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
char *artista_generare(
    uint64_t semen,
    const ArtistaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

/* Variatio naiva: eodem modo vocatur ac artista_generare, sed textus
 * emissus picturam non describit. Potius parametros mero modo iterat,
 * ut "Generate a portrait ... whatever you think seed N should look
 * like. Also style should be X. Also palette should be Y." Praecursor
 * idem est ac in persona_generare_rudis, ut imagines comparari
 * possint. */
char *artista_generare_rudis(
    uint64_t semen,
    const ArtistaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

/* Selectiones modi in f imprimit, claves ex tabulis internis sumens,
 * ut textus usus cum tabulis non discrepet. */
void artista_usus(FILE *f);

#endif
