#include "history.h"
#include "debugmalloc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FAJL_NEV "history.csv"

void history_init() {
    FILE* f = fopen(FAJL_NEV, "r");
    
    if (f == NULL) {
        f = fopen(FAJL_NEV, "w");
        if (f != NULL) {
            fprintf(f, "nev,ido,meret\n");
            fclose(f);
        }
        return;
    }
    
    char sor[100];
    if (fgets(sor, sizeof(sor), f) == NULL || 
        strncmp(sor, "nev,ido,meret", 13) != 0) {
        fclose(f);
        remove(FAJL_NEV);
        f = fopen(FAJL_NEV, "w");
        if (f != NULL) {
            fprintf(f, "nev,ido,meret\n");
            fclose(f);
        }
    } else {
        fclose(f);
    }
}

void eredmeny_ment(const char* nev, int ido, int meret) {
    FILE* f = fopen(FAJL_NEV, "a");
    if (f == NULL) {
        printf("Nem sikerult menteni!\n");
        return;
    }
    
    fprintf(f, "%s,%d,%d\n", nev, ido, meret);
    fclose(f);
}

void eredmenyek_kiir() {
    FILE* f = fopen(FAJL_NEV, "r");
    if (f == NULL) {
        printf("Nincs meg eredmeny!\n");
        return;
    }
    
    char sor[100];
    fgets(sor, sizeof(sor), f);
    
    printf("\n~~~ EREDMENYEK ~~~\n\n");
    printf("%-20s %-10s %-10s\n", "Nev", "Ido (mp)", "Meret");
    printf("------------------------------------\n");
    
    int van = 0;
    while (fgets(sor, sizeof(sor), f) != NULL) {
        char nev[50];
        int ido, meret;
        if (sscanf(sor, "%[^,],%d,%d", nev, &ido, &meret) == 3) {
            printf("%-20s %-10d %-10d\n", nev, ido, meret);
            van = 1;
        }
    }
    
    if (!van) {
        printf("Nincs meg eredmeny!\n");
    }
    
    printf("\n");
    fclose(f);
}

void eredmenyek_torol() {
    remove(FAJL_NEV);
    history_init();
    printf("Torolve!\n");
}