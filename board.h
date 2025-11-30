#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int isBomb;
    int isOpen;
    int isFlagged;
    int around;
} Cella;

typedef struct {
    char nev[50];
    int rows;
    int cols;
    int bombs;
} Beallitasok;

// tabla letrehozasa
Cella** tabla_gen(int rows, int cols);

// bombak generalasa
void bomba_gen(Cella** tabla, int rows, int cols, int bombs);

// korulotte levo bombak megszamlalasa
void korulotte_szamit(Cella** tabla, int rows, int cols);

// memoria felszabaditasa
void free_table(Cella** tabla, int rows);

#endif