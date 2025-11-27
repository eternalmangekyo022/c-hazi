#ifndef BOARD_H
#define BOARD_H

typedef struct {
    int isBomb;
    int isOpen;
    int isFlagged;
    int around;
} Cella;

// tabla kezeles
Cella** tabla_gen(int rows, int cols);
void bomba_gen(Cella** tabla, int rows, int cols, int bombs);
void korulotte_szamit(Cella** tabla, int rows, int cols);
void free_table(Cella** tabla, int rows);

#endif