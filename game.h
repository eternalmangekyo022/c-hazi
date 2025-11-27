#ifndef GAME_H
#define GAME_H

#include "board.h"

// megjelenitese
void tabla_kiir(Cella** tabla, int rows, int cols, int mutasd_bombakat);
void kepernyo_torol();

// jatekmenet
int megnyit(Cella** tabla, int sor, int oszl, int rows, int cols);
void flag_valt(Cella** tabla, int sor, int oszl, int rows, int cols);

// gyozelem ellenorzes
int gyozelem_check(Cella** tabla, int rows, int cols);

#endif