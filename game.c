#include <stdio.h>
#include <string.h>
#include "game.h"
#include "ui.h"
#include "parancs.h"
#include "history.h"
#include "debugmalloc.h"


// ez a fuggveny megnyit egy adott mezot, ha nem letezik 0 a ret erteke.
// ha bomba, visszater -1 el.
// ha nem bomba szo szerint meg is nyitja, es a korulotte levo mezoket amik nem bombak
// megnyitja rekurzivan
int megnyit(Cella** tabla, int sor, int oszl, int rows, int cols) {
    if (sor < 0 || sor >= rows || oszl < 0 || oszl >= cols) {
        return 0;
    }

    if (tabla[sor][oszl].isOpen || tabla[sor][oszl].isFlagged) {
        return 0;
    }

    tabla[sor][oszl].isOpen = 1;

    if (tabla[sor][oszl].isBomb) {
        return -1;
    }

    if (tabla[sor][oszl].around == 0) {
        for (int sor_valtozas = -1; sor_valtozas <= 1; sor_valtozas++) {
            for (int oszlop_valtozas = -1; oszlop_valtozas <= 1; oszlop_valtozas++) {
                if (sor_valtozas == 0 && oszlop_valtozas == 0) continue;
                int uj_sor = sor + sor_valtozas;

                int uj_oszlop = oszl + oszlop_valtozas;

                megnyit(tabla, uj_sor, uj_oszlop, rows, cols);
            }
        }
    }

    return 1;
}


// ez a fuggveny egy flag-toggle, amely ki-be kapcsolja a flag-state-et egy mezon,
// ha meg nincs megnyitva
void flag_valt(Cella** tabla, int sor, int oszl, int rows, int cols) {
    if (sor < 0 || sor >= rows || oszl < 0 || oszl >= cols) {
        return;
    }

    if (!tabla[sor][oszl].isOpen) {
        tabla[sor][oszl].isFlagged = !tabla[sor][oszl].isFlagged;
    }
}


// ellenorzi, hogy minden nem-bomba mezo megvan-e nyitva. ha igen, gyozelem, return 1
int gyozelem_check(Cella** tabla, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!tabla[i][j].isBomb && !tabla[i][j].isOpen) {
                return 0;
            }
        }
    }
    return 1;
}


// ez a fuggveny a fo ciklust tartalmazza. kezeli a gyozelmet, veszteseget,
// parancsokat es a kijelzest. a parancsokat a parancs modullal dolgozza fel, hogy ne legyen annyi
// sor es modularisabb legyen a program
void jatek(Beallitasok* b) {

    Cella** tabla = tabla_gen(b->rows, b->cols);
    bomba_gen(tabla, b->rows, b->cols, b->bombs);
    korulotte_szamit(tabla, b->rows, b->cols);

    time_t kezdes = time(NULL);
    int vege = 0;
    int gyozott = 0;

    while (!vege) {

        kepernyo_torol();
        jatek_allapot(b, tabla, kezdes);

        char muvelet;
        int sor, oszlop;

        char inputbuf[64];
        printf("Parancs: ");

        // beolvasas a parancs modulbol
        if (!parancs_beolvas(inputbuf, 64, &muvelet, &sor, &oszlop)) {
            continue;
        }

        // kilepes
        if (muvelet == 'q') {
            printf("Kilepes...\n");
            vege = 1;
            break;
        }

        // parancs vegrehajtasa
        vege = parancs_vegrehajtasa(b, tabla, muvelet, sor, oszlop, &gyozott);
    }

    if (gyozott && strcmp(b->nev, "guest") != 0) {
        int ido = (int)(time(NULL) - kezdes);
        eredmeny_ment(b->nev, ido, b->rows * b->cols);
        printf("Eredmeny elmentve!\n");
    }

    printf("Nyomj ENTER-t a folytatashoz...");
    getchar(); getchar();

    free_table(tabla, b->rows);
}