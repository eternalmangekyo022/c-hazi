#ifndef PARANCS_H
#define PARANCS_H

#include "board.h"
#include "game.h"

// parancs beolvasasa es feldolgozasa
int parancs_beolvas(
    char* parancs, 
    int maxhossz, 
    char* muvelet_out, 
    int* sor_out, 
    int* oszlop_out
);

// parancs vegrehajtasa (megnyitas, flag, stb.)
int parancs_vegrehajtasa(
    Beallitasok* b, 
    Cella** tabla, 
    char muvelet, 
    int sor, 
    int oszlop, 
    int* gyozott
);

#endif