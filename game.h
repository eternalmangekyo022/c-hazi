#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "parancs.h"
#include <time.h>

// mezo megnyitasa (rekurziv)
int megnyit(Cella** tabla, int sor, int oszl, int rows, int cols);

// flag valtas
void flag_valt(Cella** tabla, int sor, int oszl, int rows, int cols);

// gyozelem ellenorzese
int gyozelem_check(Cella** tabla, int rows, int cols);

// a jatek fo fuggvenye
void jatek(Beallitasok* b);

#endif