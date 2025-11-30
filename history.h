#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include "board.h"

// history.csv letrehozasa vagy ellenorzese
void history_init();

// eredmeny mentese
void eredmeny_ment(const char* nev, int ido, int meret);

// eredmenyek kiolvasasa es listazasa
void eredmenyek_kiir();

// eredmenyek torlese
void eredmenyek_torol();

#endif