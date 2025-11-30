#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parancs.h"
#include "ui.h"
#include "debugmalloc.h"


// Ezzel a fuggvennyel kezeljuk a felhasznalo altal megadott parancsot. Lhet m 5:3, f 2:4,
// vagy kilepesnel 'q'. Ha hibas az input, az ki lesz szurve. A koordinatakat split-eli 2db számra.
// a cel, hogy fociklusban egyertelmu legyen milyen parancsot kaptunk.
int parancs_beolvas(char* parancs, int maxhossz, char* muvelet_out, int* sor_out, int* oszlop_out) {
    char buffer[64];

    // olvasas limitalva, hogy ne legyen tulcsordulas
    if (scanf("%63s", buffer) != 1) {
        return 0;
    }

    // csak "q"
    if (strcmp(buffer, "q") == 0) {
        *muvelet_out = 'q';
        return 1;
    }

    // elso karakter muvelet
    char muvelet = buffer[0];
    if (muvelet != 'm' && muvelet != 'f') {
        printf("Ismeretlen parancs! (m vagy f legyen)\nNyomj ENTER-t...");
        getchar(); getchar();
        return 0;
    }

    // ha csak m vagy f van beirva, akkor kulon kerjuk a koordinatat
    if (strlen(buffer) == 1) {
        char coord[32];
        printf("Add meg a koordinatat (pl. 4:2): ");
        if (scanf("%31s", coord) != 1) return 0;

        int sor, oszlop;
        if (sscanf(coord, "%d:%d", &sor, &oszlop) != 2) {
            printf("Hibas formatum!\nNyomj ENTER-t...");
            getchar(); getchar();
            return 0;
        }

        *muvelet_out = muvelet;
        *sor_out = sor;
        *oszlop_out = oszlop;
        return 1;
    }

    // osszevont parancs (m5:3 vagy f10:4)
    int sor, oszlop;
    if (sscanf(buffer + 1, "%d:%d", &sor, &oszlop) != 2) {
        printf("Hibas format! (pl. m 4:2 vagy m4:2)\nNyomj ENTER-t...");
        getchar(); getchar();
        return 0;
    }

    *muvelet_out = muvelet;
    *sor_out = sor;
    *oszlop_out = oszlop;

    return 1;
}


// A beolvasott es szurott parancsot vegrahajtja: flag toggle, vagy mezo megnyitas. a return ertek
// hogy vege lett e jateknak. 0 nem, 1 igen
int parancs_vegrehajtasa(Beallitasok* b, Cella** tabla, char muvelet, int sor, int oszlop, int* gyozott) {

    // mozgastartomany ellenorzes
    if (sor < 0 || sor >= b->rows || oszlop < 0 || oszlop >= b->cols) {
        printf("Koordinata kivul esik a palyan!\nNyomj ENTER-t...");
        getchar(); getchar();
        return 0;
    }

    if (muvelet == 'm') {
        int eredmeny = megnyit(tabla, sor, oszlop, b->rows, b->cols);

        if (eredmeny == -1) {
            kepernyo_torol();
            tabla_kiir(tabla, b->rows, b->cols, 1);
            printf("\n*** BUMM! Aknara leptel! ***\n");
            return 1;
        }

        if (eredmeny == 0) {
            printf("Ez a mezo mar meg van nyitva!\nNyomj ENTER-t...");
            getchar(); getchar();
            return 0;
        }

        // gyozelmi feltetel
        if (gyozelem_check(tabla, b->rows, b->cols)) {
            kepernyo_torol();
            tabla_kiir(tabla, b->rows, b->cols, 0);
            printf("\n*** GRATULALOK, NYERTEL! ***\n");
            *gyozott = 1;
            return 1;
        }

    } else if (muvelet == 'f') {
        flag_valt(tabla, sor, oszlop, b->rows, b->cols);
    }

    return 0;
}