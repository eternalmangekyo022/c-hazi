#include "history.h"
#include <string.h>
#include <stdlib.h>
#include "debugmalloc.h"

#define HISTORY_FILE "history.csv"


// ellenorzi, hogy letezik e HOSTORY_FILE nevu fajl, es ha nem letrehoz egyet.
// ha hibas a formatum, torli es letrehoz egyet, odafigyelve hogy a fejlecet csak 13 karakterig
//olvassa.
void history_init() {
    FILE* f = fopen(HISTORY_FILE, "r");

    if (f == NULL) {
        f = fopen(HISTORY_FILE, "w");
        if (f != NULL) {
            fprintf(f, "nev,ido,meret\n");
            fclose(f);
        }
        return;
    }

    char sor[128];
    if (!fgets(sor, sizeof(sor), f) || strncmp(sor, "nev,ido,meret", 13) != 0) {
        fclose(f);
        remove(HISTORY_FILE);
        f = fopen(HISTORY_FILE, "w");
        if (f != NULL) {
            fprintf(f, "nev,ido,meret\n");
            fclose(f);
        }
        return;
    }

    fclose(f);
}


// hozzaadja a jatekos eredmenyet a fajlhoz. ha nem sikerul, csak kiirja,
// hogy nem sikerult
void eredmeny_ment(const char* nev, int ido, int meret) {
    FILE* f = fopen(HISTORY_FILE, "a");
    if (!f) {
        printf("Nem sikerult megnyitni a history fajlt!\n");
        return;
    }

    fprintf(f, "%s,%d,%d\n", nev, ido, meret);
    fclose(f);
}


// kiirja a fajlban levo osszes eredmenyt, ha van.
// a fejlecet atugorjuk, hogy csak az adatok legyenek
void eredmenyek_kiir() {
    FILE* f = fopen(HISTORY_FILE, "r");
    if (!f) {
        printf("Nincs elerheto eredmeny.\n");
        return;
    }

    char sor[128];

    // fejlec atlepese
    fgets(sor, sizeof(sor), f);

    printf("\n=== EREDMENYEK ===\n\n");
    printf("%-20s %-10s %-10s\n", "Nev", "Ido (mp)", "Meret");
    printf("----------------------------------\n");

    int van = 0;

    while (fgets(sor, sizeof(sor), f)) {
        char nev[50];
        int ido, meret;

        if (sscanf(sor, "%49[^,],%d,%d", nev, &ido, &meret) == 3) {
            printf("%-20s %-10d %-10d\n", nev, ido, meret);
            van = 1;
        }
    }

    if (!van) {
        printf("Még nincsenek mentett eredmenyek.\n");
    }

    printf("\n");
    fclose(f);
}


// reseteli az eredmenyeket. torli a fajlt es letrehoz egyet a history_init segitsegevel.
void eredmenyek_torol() {
    remove(HISTORY_FILE);
    history_init();
    printf("Eredmenyek torolve.\n");
}