#ifndef PERSONA_H
#define PERSONA_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* Optiones personam generandi. Campi per litteras NULL vacant,
 * eosdem valores accipiunt quos argumenta lineae mandatorum. */
typedef struct {
    const char *sexus;          /* "m" | "f" | "mas" | "femina" */
    const char *aetas;          /* numerus integer, 1..120 */
    const char *pulchritudo;    /* "0".."4" */
    const char *vestitus;       /* "formalis" | "cotidianus" | "insolitus" | "nudus" */
    const char *cutis;          /* "clara" | "media" | "obscura" */
    const char *fundus;         /* "planum" | "candidum" | "ater" | "coloratum" |
                                   "textura" | "ambitus" | "exterior" */
} PersonaOptiones;

/* Personam describens generare.
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
char *persona_generare(
    uint64_t semen,
    const PersonaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

/* Variatio rudis: eodem modo vocatur ac persona_generare, sed textus
 * emissus personam non describit. Potius parametros mero modo iterat,
 * ut "Generate a portrait ... whatever you think seed N should look
 * like. Also age should be X. Also sex should be Y." Praecursor idem
 * est ac in artista_generare_rudis, ut imagines comparari possint. */
char *persona_generare_rudis(
    uint64_t semen,
    const PersonaOptiones *optiones,
    char *error_locus, size_t error_longitudo
);

/* Selectiones modi in f imprimit. */
void persona_usus(FILE *f);

#endif
