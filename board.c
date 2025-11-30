#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "debugmalloc.h"


// tabal dinamikus letrehozasaert felelos. minden sorhoz kulon memoria lesz allokalva,
// kezdetben minden mezo "ures" allapotban van(se bomba, se megnyitva)
Cella** tabla_gen(int rows, int cols) {
    Cella** tabla = (Cella**) malloc(rows * sizeof(Cella*));
    for (int i = 0; i < rows; i++) {
        tabla[i] = (Cella*) malloc(cols * sizeof(Cella));
        for (int j = 0; j < cols; j++) {
            tabla[i][j].isBomb = 0;
            tabla[i][j].isOpen = 0;
            tabla[i][j].isFlagged = 0;
            tabla[i][j].around = 0;
        }
    }
    return tabla;
}


//be-seedelem a random fuggvenyt, majd annyi bombat rakok le a palyara random, amennyi a 
// bombs parameterben jott
void bomba_gen(Cella** tabla, int rows, int cols, int bombs) {
    srand(time(NULL));
    int count = 0;


    while (count < bombs) {
        int r = rand() % rows;
        int c = rand() % cols;

        if (tabla[r][c].isBomb == 0) {
            tabla[r][c].isBomb = 1;
            count++;
        }
    }
}


// megszamolja egy mezo korul hany bomba van
void korulotte_szamit(Cella** tabla, int rows, int cols) {
    for (int sor = 0; sor < rows; sor++) {
        for (int oszlop = 0; oszlop < cols; oszlop++) {

            if (tabla[sor][oszlop].isBomb) continue;

            int bomba_szam = 0;

            // szomszedok ellenorzese

            for (int sor_elteres = -1; sor_elteres <= 1; sor_elteres++) {
                for (int oszlop_elteres = -1; oszlop_elteres <= 1; oszlop_elteres++) {
                    if (sor_elteres == 0 && oszlop_elteres == 0) continue;

                    int szomszed_sor = sor + sor_elteres;

                    int szomszed_oszlop = oszlop + oszlop_elteres;

                    if (szomszed_sor >= 0 && szomszed_sor < rows && 
                        szomszed_oszlop >= 0 && szomszed_oszlop < cols) {
                        if (tabla[szomszed_sor][szomszed_oszlop].isBomb) {
                            bomba_szam++;
                        }
                    }
                }
            }

            tabla[sor][oszlop].around = bomba_szam;
        }
    }
}


//parameterkent megkapjuk a tabla kezdetenek pointeret, majd ahany sor van vegigiteralunk annyiszor es
// free. a vegen meg a tabla listajanak pointeret is felszabaditjuk.
void free_table(Cella** tabla, int rows) {
    for (int i = 0; i < rows; i++) {
        free(tabla[i]);
    }
    free(tabla);
}