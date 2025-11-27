#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// ANSI szinek
#define SZIN_RESET "\033[0m"
#define SZIN_CYAN "\033[36m"
#define SZIN_SARGA "\033[33m"
#define SZIN_PIROS "\033[31m"
#define SZIN_ZOLD "\033[32m"

void kepernyo_torol() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//tabla vizualizalasa
void tabla_kiir(Cella** tabla, int rows, int cols, int mutasd_bombakat) {
    // oszlopok szamai cyannal
    for (int j = 0; j < cols; j++) {
        printf(SZIN_CYAN "%2d " SZIN_RESET, j);
    }
    printf("\n");
    
    for (int i = 0; i < rows; i++) {
        // sor szama cyannal
        printf(SZIN_CYAN "%2d " SZIN_RESET, i);
        for (int j = 0; j < cols; j++) {
            if (tabla[i][j].isOpen) {
                if (tabla[i][j].isBomb) {
                    printf(SZIN_PIROS " B " SZIN_RESET);
                } else if (tabla[i][j].around == 0) {
                    printf("   ");
                } else {
                    // szamok zolddel
                    printf(SZIN_ZOLD " %d " SZIN_RESET, tabla[i][j].around);
                }
            } else if (tabla[i][j].isFlagged) {
                printf(SZIN_SARGA " * " SZIN_RESET);
            } else {
                if (mutasd_bombakat && tabla[i][j].isBomb) {
                    printf(SZIN_PIROS " B " SZIN_RESET);
                } else {
                    printf(" x ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

//cella megnyitasa. ha bomba vege, ha flag vagy mar nyitva van semmi nem tortenik
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

//toggle funkcio a cellak flagelesere
void flag_valt(Cella** tabla, int sor, int oszl, int rows, int cols) {
    if (sor < 0 || sor >= rows || oszl < 0 || oszl >= cols) {
        return;
    }
    
    if (!tabla[sor][oszl].isOpen) {
        tabla[sor][oszl].isFlagged = !tabla[sor][oszl].isFlagged;
    }
}

//ha talal olyan cellak amely nem bomba es nincs megnyitva, akkor meg nincs megnyerve
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