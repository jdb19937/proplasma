#include "artista.h"
#include "bestia.h"
#include "persona.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int proba(const char *nomen, char *textus, uint64_t semen) {
    if (textus == NULL) {
        fprintf(stderr, "proba %s defecit (semen=%llu)\n",
                nomen, (unsigned long long)semen);
        return 1;
    }
    if (strlen(textus) == 0) {
        fprintf(stderr, "proba %s: textus vacuus (semen=%llu)\n",
                nomen, (unsigned long long)semen);
        free(textus);
        return 1;
    }
    printf("== %s (semen=%llu) ==\n%s\n\n",
           nomen, (unsigned long long)semen, textus);
    free(textus);
    return 0;
}

int main(void) {
    int defectus = 0;
    const uint64_t semen = 1729;
    char error[256];

    error[0] = 0;
    defectus += proba("persona",
        persona_generare(semen, NULL, error, sizeof error), semen);
    error[0] = 0;
    defectus += proba("artista",
        artista_generare(semen, NULL, error, sizeof error), semen);
    error[0] = 0;
    defectus += proba("bestia",
        bestia_generare(semen, NULL, error, sizeof error), semen);
    error[0] = 0;
    defectus += proba("persona_rudis",
        persona_generare_rudis(semen, NULL, error, sizeof error), semen);
    error[0] = 0;
    defectus += proba("artista_rudis",
        artista_generare_rudis(semen, NULL, error, sizeof error), semen);
    error[0] = 0;
    defectus += proba("bestia_rudis",
        bestia_generare_rudis(semen, NULL, error, sizeof error), semen);

    if (defectus != 0) {
        fprintf(stderr, "probae %d defecerunt\n", defectus);
        return 1;
    }
    printf("omnes probae bene evenerunt\n");
    return 0;
}
