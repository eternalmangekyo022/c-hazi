#ifndef UI_H
#define UI_H

#include <time.h>
#include "board.h"

// képernyő törlése (platformfüggő)
void kepernyo_torol();

// játék közbeni kijelzés (idő, név, méret, stb.)
void jatek_allapot(Beallitasok* b, Cella** tabla, time_t kezdes);

// tábla kirajzolása szép igazítással
void tabla_kiir(Cella** tabla, int rows, int cols, int mutasd_bombakat);

// főmenü kiírása
void menu_kiir();

// nehézség menü kiírása
void nehezseg_menu_kiir();

#endif