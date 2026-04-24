#include "artista.h"
#include "bestia.h"
#include "persona.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Usum programmatis exhibere. Sectiones modorum ex ipsis modulis
 * trahuntur, ut cum tabulis internis non discrepent. */
static void usus(const char *nomen) {
    fprintf(
        stderr,
        "usus: %s [-s semen] [--modus persona|artista|bestia] [-r] [selectiones]\n"
        "  -s, --semen N       semen generatoris (ex /dev/urandom si abest)\n"
        "      --modus M       persona (default) | artista | bestia\n"
        "  -r, --rudis         variatio rudis (parametros mero modo iterat)\n"
        "  -h, --auxilium      hunc textum exhibere\n"
        "\n"
        "Selectiones modi persona (quaeque ex semine alia defaltit):\n",
        nomen
    );
    persona_usus(stderr);
    fputs(
        "\nSelectiones modi artista (quaeque ex semine alia defaltit):\n",
        stderr
    );
    artista_usus(stderr);
    fputs(
        "\nSelectiones modi bestia (quaeque ex semine alia defaltit):\n",
        stderr
    );
    bestia_usus(stderr);
}

/* Semen ex /dev/urandom legere. */
static int semen_ex_urandom(uint64_t *semen) {
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f) {
        perror("/dev/urandom");
        return 0;
    }
    if (fread(semen, sizeof *semen, 1, f) != 1) {
        perror("read");
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}

int main(int argc, char **argv) {
    uint64_t semen    = 0;
    int habet_semen   = 0;
    int rudis         = 0;
    const char *modus = "persona";
    ArtistaOptiones aopt = {0};
    PersonaOptiones popt = {0};
    BestiaOptiones  bopt = {0};
    const char *arg_fundus = NULL;

    static struct option optiones_longae[] = {
        {"semen",       required_argument, 0, 's'},
        {"modus",       required_argument, 0, 'm'},
        {"rudis",       no_argument,       0, 'r'},
        {"sexus",       required_argument, 0, 2000},
        {"aetas",       required_argument, 0, 2001},
        {"pulchritudo", required_argument, 0, 2002},
        {"vestitus",    required_argument, 0, 2003},
        {"cutis",       required_argument, 0, 2004},
        {"artifex",     required_argument, 0, 1000},
        {"medium",      required_argument, 0, 1001},
        {"palaestra",   required_argument, 0, 1002},
        {"habitus",     required_argument, 0, 1003},
        {"fundus",      required_argument, 0, 1004},
        {"species",     required_argument, 0, 3000},
        {"gradus",      required_argument, 0, 3001},
        {"ratio",       required_argument, 0, 3002},
        {"gestus",      required_argument, 0, 3003},
        {"amictus",     required_argument, 0, 3004},
        {"auxilium",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int signum;
    while ((signum = getopt_long(argc, argv, "s:m:rh", optiones_longae, NULL)) != -1) {
        switch (signum) {
        case 's':
            semen       = strtoull(optarg, NULL, 0);
            habet_semen = 1;
            break;
        case 'm':
            modus = optarg;
            break;
        case 'r':
            rudis = 1;
            break;
        case 2000:
            popt.sexus       = optarg;
            break;
        case 2001:
            popt.aetas       = optarg;
            break;
        case 2002:
            popt.pulchritudo = optarg;
            break;
        case 2003:
            popt.vestitus    = optarg;
            break;
        case 2004:
            popt.cutis       = optarg;
            break;
        case 1000:
            aopt.artifex     = optarg;
            break;
        case 1001:
            aopt.medium      = optarg;
            break;
        case 1002:
            aopt.palaestra   = optarg;
            break;
        case 1003:
            aopt.habitus     = optarg;
            break;
        case 1004:
            arg_fundus = optarg;
            break;
        case 3000:
            bopt.species     = optarg;
            break;
        case 3001:
            bopt.gradus      = optarg;
            break;
        case 3002:
            bopt.ratio       = optarg;
            break;
        case 3003:
            bopt.gestus      = optarg;
            break;
        case 3004:
            bopt.amictus     = optarg;
            break;
        case 'h':
            usus(argv[0]);
            return 0;
        default:
            usus(argv[0]);
            return 2;
        }
    }

    if (!habet_semen && !semen_ex_urandom(&semen))
        return 1;

    char error[256] = {0};
    char *descriptio = NULL;
    if (strcmp(modus, "persona") == 0) {
        if (arg_fundus)
            popt.fundus = arg_fundus;
        descriptio = rudis
            ? persona_generare_rudis(semen, &popt, error, sizeof error)
            : persona_generare(semen, &popt, error, sizeof error);
    } else if (strcmp(modus, "artista") == 0) {
        if (arg_fundus)
            aopt.fundus = arg_fundus;
        descriptio = rudis
            ? artista_generare_rudis(semen, &aopt, error, sizeof error)
            : artista_generare(semen, &aopt, error, sizeof error);
    } else if (strcmp(modus, "bestia") == 0) {
        if (arg_fundus)
            bopt.fundus = arg_fundus;
        descriptio = rudis
            ? bestia_generare_rudis(semen, &bopt, error, sizeof error)
            : bestia_generare(semen, &bopt, error, sizeof error);
    } else {
        fprintf(stderr, "modus ignotus: %s (persona|artista|bestia expectatur)\n", modus);
        return 2;
    }

    if (!descriptio) {
        fprintf(stderr, "%s\n", error[0] ? error : "generare defecit");
        return 1;
    }

    fputs(descriptio, stdout);
    /* Semen imprimere ut exsecutiones repeti possint. */
    printf("\n[semen: %llu]\n", (unsigned long long)semen);
    free(descriptio);
    return 0;
}
