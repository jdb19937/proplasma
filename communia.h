#ifndef COMMUNIA_H
#define COMMUNIA_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inquadramentum commune descriptionum. Tam persona (ad effigiem
 * realem describendam) quam artista (ad modum pictorium describendum)
 * hanc sententiam velut caput descriptionis emittunt. Ita matrix.py
 * per praefixum commune ex pluribus emissis facile extrahere potest. */
#define INQUADRAMENTUM \
    "Portrait of one person, facing the viewer with shoulders square " \
    "to the picture plane. The head is shown complete and is not " \
    "cropped at any edge; it fills approximately the upper two-thirds " \
    "of the frame. The shoulders and upper chest occupy the remaining " \
    "lower third. "

/* ---- alea: xorshift64*, ex semine determinata ----
 *
 * Status per filum tenetur (ubi compilator id permittit), ne
 * vocationes ex pluribus filis parallelis semina sua confundant.
 * Si compilator neque _Thread_local neque __thread agnoscit, ad
 * staticum communem retrocedimus: tunc filis non tutum est. */

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_THREADS__)
#  define PROP_TLS _Thread_local
#elif defined(__GNUC__) || defined(__clang__)
#  define PROP_TLS __thread
#else
#  define PROP_TLS
#endif

static PROP_TLS uint64_t alea_status;

static inline void alea_seminare(uint64_t s) {
    if (s == 0)
        s = 0x9E3779B97F4A7C15ULL;
    alea_status = s;
}

static inline uint64_t alea_sequens(void) {
    uint64_t x = alea_status;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    alea_status = x;
    return x * 0x2545F4914F6CDD1DULL;
}

static inline uint32_t alea_ambitus(uint32_t n) {
    return (uint32_t)(alea_sequens() % n);
}

static inline double alea_unitas(void) {
    return (alea_sequens() >> 11) * (1.0 / 9007199254740992.0);
}

static inline int alea_fors(double p) {
    return alea_unitas() < p;
}

/* ---- nuntius erroris ---- */

static inline void pone_errorem(char *capax, size_t longitudo, const char *fmt, ...) {
    if (!capax || longitudo == 0)
        return;
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(capax, longitudo, fmt, ap);
    va_end(ap);
}

/* ---- indicium clavis in tabula ---- */

static inline int indicium_clavis(const char *v, const char *const *claves, int n) {
    for (int i = 0; i < n; i++)
        if (!strcmp(v, claves[i]))
            return i;
    return -1;
}

/* ---- charta crescens ---- */

typedef struct {
    char *d;
    size_t n, cap;
} Charta;

static inline int charta_crescat(Charta *c, size_t plus) {
    if (c->n + plus + 1 <= c->cap)
        return 1;
    size_t nc = c->cap ? c->cap : 1024;
    while (nc < c->n + plus + 1)
        nc *= 2;
    char *nd = realloc(c->d, nc);
    if (!nd)
        return 0;
    c->d   = nd;
    c->cap = nc;
    return 1;
}

static inline int charta_adde(Charta *c, const char *s) {
    size_t len = strlen(s);
    if (!charta_crescat(c, len))
        return 0;
    memcpy(c->d + c->n, s, len + 1);
    c->n += len;
    return 1;
}

static inline int charta_scribe(Charta *c, const char *fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    return charta_adde(c, buf);
}

/* ---- usus: tabulam clavium in lineis involutis imprimere ----
 *
 * Primum linea cum `initium` (e.g. "      --artifex X     ") incipit.
 * Lineae continuatae `spatium` patiuntur (e.g. "                      ").
 * Claves per `|` separantur, in latitudine ~70 columnarum involvuntur. */

static inline void usus_claves(
    FILE *f,
    const char *initium,
    const char *spatium,
    const char *const *claves,
    int n
) {
    const int latitudo_max = 70;
    int col = fprintf(f, "%s", initium);
    for (int i = 0; i < n; i++) {
        int len = (int)strlen(claves[i]) + (i + 1 < n ? 1 : 0);  /* + "|" */
        if (i > 0 && col + len > latitudo_max) {
            fprintf(f, "\n%s", spatium);
            col = (int)strlen(spatium);
        }
        fprintf(f, "%s%s", claves[i], (i + 1 < n) ? "|" : "");
        col += len;
    }
    fputc('\n', f);
}

#endif
