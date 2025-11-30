#include <stdio.h>
#include <string.h>
#include "ui.h"
#include "debugmalloc.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


//Ezzel a fuggvennyel torlodik a terminal, ergo a "kepfrissites" hatas.
//Linux-on vagy Mac-en clear, windowson pedig cls parancs szukseges
//Minden lepes utna meghivom, hogy frissuljon a kep 
void kepernyo_torol() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


//Kiirja a jelenlegi allapotot: eltelt ido, nev(ha van), es palya meret. Minden lepes elott meghivom
void jatek_allapot(Beallitasok* b, Cella** tabla, time_t kezdes) {
    int eltelt = (int)(time(NULL) - kezdes);

    printf("\nIdo: %d mp\n", eltelt);

    if (strcmp(b->nev, "guest") != 0) {
        printf("Jatekos: %s\n", b->nev);
    }

    printf("%dx%d, %d akna\n", b->rows, b->cols, b->bombs);
    printf("\n");

    tabla_kiir(tabla, b->rows, b->cols, 0);

    printf("Megnyitas: m sor:oszlop  (pl: m 5:3)\n");
    printf("Flag:      f sor:oszlop  (pl: f 2:7)\n");
    printf("Kilepes:   q\n\n");
}

//Ezzel a fuggvennyel irja ki a tablat. Az elcsuszas fixelve lett, 10 feletti palyame-
//retnel sem okoz gondot. A mutasd_bombakat egy olyan parameter, ami ugye egy int pointer,
//es ezzel adjuk meg hogy a bombakat mutassa-e a fuggveny lefutasa utan vagy sems.
void tabla_kiir(Cella** tabla, int rows, int cols, int mutasd_bombakat) {
    printf("    ");
    for (int j = 0; j < cols; j++) {
        printf("%3d ", j);
    }
    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("%3d ", i);

        for (int j = 0; j < cols; j++) {
            Cella c = tabla[i][j];

            if (c.isOpen) {
                if (c.isBomb) {
                    printf("  B ");
                } else if (c.around == 0) {
                    printf("    ");
                } else {
                    printf("%3d ", c.around);
                }
            } else if (c.isFlagged) {
                printf("  * ");
            } else {
                if (mutasd_bombakat && c.isBomb) {
                    printf("  B ");
                } else {
                    printf("  x ");
                }
            }
        }
        printf("\n");
    }

    printf("\n");
}


//A fomenu csak kiirja a valaszthato opciokat. Main.c-ben kerul meghivasra ez is.
void menu_kiir() {
    printf("\n~~~ AKNAKERESO ~~~\n\n");
    printf("1. Uj jatek\n");
    printf("2. Nev beallitasa\n");
    printf("3. Nehezseg\n");
    printf("4. Eredmenyek megtekintese\n");
    printf("5. Eredmenyek torlese\n");
    printf("6. Kilepes\n\n");
    printf("Valasztas: ");
}


//ez a fuggvceny is csak kiirja a valaszthato nehezsegeket, konkret logikaja nincs. A parancskezelo
// modul fogja feldolgozni majd a kivalasztott opciot
void nehezseg_menu_kiir() {
    printf("\n~~~ NEHEZSEG BEALLITASA ~~~\n\n");
    printf("1. Konnyu  (8x8, 10 akna)\n");
    printf("2. Kozepes (12x12, 20 akna)\n");
    printf("3. Nehez   (16x16, 40 akna)\n");
    printf("4. Egyedi meret\n");
    printf("5. Vissza\n\n");
    printf("Valasztas: ");
}