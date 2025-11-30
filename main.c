#include <stdio.h>
#include <string.h>
#include "board.h"
#include "ui.h"
#include "game.h"
#include "history.h"
#include "parancs.h"
#include "debugmalloc.h"

//uj forditas: gcc main.c ui.c parancs.c board.c game.c history.c -o aknakereso

// a kovetkezo fuggveny segit a nehezseg beallitasaban. rossz inputra warning.
// nem tul komplex beolvasas.
void nehezseg_beallitasa(Beallitasok* b)
{
    while (1) {
        nehezseg_menu_kiir();

        int valasz = 0;
        if (scanf("%d", &valasz) != 1) {
            printf("Hibas bemenet!\nNyomj ENTER-t...");
            getchar(); getchar();
            continue;
        }

        if (valasz == 1) {
            b->rows = 8;
            b->cols = 8;
            b->bombs = 10;
            printf("Konnyu nehezseg beallitva.\n");
            break;

        } else if (valasz == 2) {
            b->rows = 12;
            b->cols = 12;
            b->bombs = 20;
            printf("Kozepes nehezseg beallitva.\n");
            break;

        } else if (valasz == 3) {
            b->rows = 16;
            b->cols = 16;
            b->bombs = 40;
            printf("Nehez nehezseg beallitva.\n");
            break;

        } else if (valasz == 4) {
            printf("Add meg a sorok szamat: ");
            scanf("%d", &b->rows);

            printf("Add meg az oszlopok szamat: ");
            scanf("%d", &b->cols);

            printf("Add meg az aknak szamat: ");
            scanf("%d", &b->bombs);

            if (b->bombs <= 0 || b->bombs >= b->rows * b->cols) {
                printf("Tul sok akna vagy ervenytelen meret!\nNyomj ENTER-t...");
                getchar(); getchar();
                continue;
            }

            printf("Egyedi nehezseg beallitva: %dx%d, %d akna.\n", b->rows, b->cols, b->bombs);
            break;

        } else if (valasz == 5) {
            return;

        } else {
            printf("Ervenytelen valasztas!\nNyomj ENTER-t...");
            getchar(); getchar();
        }
    }

    printf("Nyomj ENTER-t a folytatashoz...");
    getchar(); getchar();
}


// program entry pointja. inicializalom a history file-t,
// kiiratom a menut, es az input alapjan meghivom a megfelelo funkciot
int main()
{
    history_init();

    Beallitasok b;
    strcpy(b.nev, "guest");
    b.rows = 10;
    b.cols = 10;
    b.bombs = 15;

    int fut = 1;

    while (fut) {
        kepernyo_torol();
        menu_kiir();

        int valasz = 0;
        if (scanf("%d", &valasz) != 1) {
            printf("Hibas bemenet!\nNyomj ENTER-t...");
            getchar(); getchar();
            continue;
        }

        switch (valasz) {

            case 1:
                jatek(&b);
                break;

            case 2:
                printf("Add meg az uj neved: ");
                scanf("%49s", b.nev);
                printf("Nev beallitva: %s\n", b.nev);
                printf("Nyomj ENTER-t a folytatashoz...");
                getchar(); getchar();
                break;

            case 3:
                nehezseg_beallitasa(&b);
                break;

            case 4:
                eredmenyek_kiir();
                printf("Nyomj ENTER-t...");
                getchar(); getchar();
                break;

            case 5: {
                printf("Biztosan torlod az eredmenyeket? (i/n): ");
                char c;
                scanf(" %c", &c);
                if (c == 'i' || c == 'I') {
                    eredmenyek_torol();
                } else {
                    printf("Megsem toroltem.\n");
                }
                printf("ENTER...");
                getchar(); getchar();
                break;
            }

            case 6:
                printf("Kilepes...\n");
                fut = 0;
                break;

            default:
                printf("Ismeretlen valasztas!\nNyomj ENTER-t...");
                getchar(); getchar();
                break;
        }
    }

    return 0;
}