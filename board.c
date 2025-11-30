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
    int elhelyezve = 0;

    while (elhelyezve < bombs) {
        int sor = rand() % rows;
        int oszl = rand() % cols;

        if (tabla[sor][oszl].isBomb == 0) {
            tabla[sor][oszl].isBomb = 1;
            elhelyezve++;
        }
    }
}


// megszamolja egy mezo korul hany bomba van
void korulotte_szamit(Cella** tabla, int rows, int cols) {
    for (int sor = 0; sor < rows; sor++) {
        for (int oszlop = 0; oszlop < cols; oszlop++) {

            if (tabla[sor][oszlop].isBomb) continue;

            int bomba_db = 0;

            for (int sor_valt = -1; sor_valt <= 1; sor_valt++) {
                for (int oszl_valt = -1; oszl_valt <= 1; oszl_valt++) {

                    if (sor_valt == 0 && oszl_valt == 0) continue;

                    int uj_sor = sor + sor_valt;
                    int uj_oszl = oszlop + oszl_valt;

                    if (uj_sor >= 0 && uj_sor < rows &&
                        uj_oszl >= 0 && uj_oszl < cols) 
                    {
                        if (tabla[uj_sor][uj_oszl].isBomb) {
                            bomba_db++;
                        }
                    }
                }
            }

            tabla[sor][oszlop].around = bomba_db;
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