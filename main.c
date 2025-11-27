#include "debugmalloc.h"
#include "board.h"
#include "game.h"
#include "history.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nev[50];
    int rows;
    int cols;
    int bombs;
} Beallitasok;

void menu_kiir() {
    printf("\n~~~ AKNAKERESO ~~~\n\n");
    printf("1. Jatek\n");
    printf("2. Nev\n");
    printf("3. Nehezseg\n");
    printf("4. Eredmenyek\n");
    printf("5. Eredmenyek torlese\n");
    printf("6. Kilepes\n\n");
    printf("Valasztas: ");
}

void nehezseg_menu(Beallitasok* b) {
    printf("\n1. Konnyu (8x8, 10)\n");
    printf("2. Kozepes (12x12, 20)\n");
    printf("3. Nehez (16x16, 40)\n");
    printf("4. Egyedi\n");
    printf("5. Vissza\n\n");
    printf("Valasztas: ");
    
    int v;
    scanf("%d", &v);
    
    switch(v) {
        case 1:
            b->rows = 8; b->cols = 8; b->bombs = 10;
            printf("Konnyu beallitva\n");
            break;
        case 2:
            b->rows = 12; b->cols = 12; b->bombs = 20;
            printf("Kozepes beallitva\n");
            break;
        case 3:
            b->rows = 16; b->cols = 16; b->bombs = 40;
            printf("Nehez beallitva\n");
            break;
        case 4:
            printf("Sorok: ");
            scanf("%d", &b->rows);
            printf("Oszlopok: ");
            scanf("%d", &b->cols);
            printf("Aknák: ");
            scanf("%d", &b->bombs);
            if (b->bombs >= b->rows * b->cols) {
                printf("Tul sok akna!\n");
                b->rows = 10; b->cols = 10; b->bombs = 15;
            }
            break;
    }
}

void jatek(Beallitasok* b) {
    kepernyo_torol();
    
    Cella** tabla = tabla_gen(b->rows, b->cols);
    bomba_gen(tabla, b->rows, b->cols, b->bombs);
    korulotte_szamit(tabla, b->rows, b->cols);
    
    time_t kezdes = time(NULL);
    int vege = 0;
    int gyozott = 0;
    
    while (!vege) {
        kepernyo_torol();
        
        int eltelt = (int)(time(NULL) - kezdes);
        printf("\nIdo: %d mp\n", eltelt);
        if (strcmp(b->nev, "guest") != 0) {
            printf("Jatekos: %s\n", b->nev);
        }
        printf("%dx%d, %d akna\n", b->rows, b->cols, b->bombs);
        
        tabla_kiir(tabla, b->rows, b->cols, 0);
        
        printf("Megnyitas: m sor:oszlop (pl: m 5:3)\n");
        printf("Flag: f sor:oszlop (pl: f 2:7)\n");
        printf("Kilepes: q\n\n");
        
        char teljes_input[30];
        printf("Parancs: ");
        scanf("%s", teljes_input);
        
        if (teljes_input[0] == 'q') {
            printf("Viszlat!\n");
            break;
        }
        
        // ha csak egy betut irt be, akkor kerjuk be a koordinatat is
        if (strlen(teljes_input) == 1 && (teljes_input[0] == 'm' || teljes_input[0] == 'f')) {
            char parancs = teljes_input[0];
            char coord[20];
            scanf("%s", coord);
            
            int sor, oszl;
            if (sscanf(coord, "%d:%d", &sor, &oszl) != 2) {
                printf("Hibas format! Nyomj entert...\n");
                getchar();
                continue;
            }
            
            if (sor < 0 || sor >= b->rows || oszl < 0 || oszl >= b->cols) {
                printf("Hibas koordinatak! Nyomj entert...\n");
                getchar();
                continue;
            }
            
            if (parancs == 'm') {
                int result = megnyit(tabla, sor, oszl, b->rows, b->cols);
                
                if (result == -1) {
                    kepernyo_torol();
                    tabla_kiir(tabla, b->rows, b->cols, 1);
                    printf("\n*** BUMM! Vesztettel! ***\n");
                    vege = 1;
                } else if (result == 0) {
                    printf("Mar meg van nyitva! Nyomj entert...\n");
                    getchar();
                }
                
                if (gyozelem_check(tabla, b->rows, b->cols)) {
                    kepernyo_torol();
                    tabla_kiir(tabla, b->rows, b->cols, 0);
                    printf("\n*** NYERTEL! ***\n");
                    vege = 1;
                    gyozott = 1;
                }
            } else if (parancs == 'f') {
                flag_valt(tabla, sor, oszl, b->rows, b->cols);
            }
        } else {
            // megprobaljuk egybol parseolni (pl: m5:3 formatumban)
            char parancs = teljes_input[0];
            if (parancs != 'm' && parancs != 'f') {
                printf("Rossz parancs! (m vagy f kell) Nyomj entert...\n");
                getchar();
                continue;
            }
            
            int sor, oszl;
            if (sscanf(teljes_input + 1, "%d:%d", &sor, &oszl) != 2) {
                printf("Hibas format! Hasznald: m sor:oszlop vagy f sor:oszlop\n");
                printf("Nyomj entert...\n");
                getchar();
                continue;
            }
            
            if (sor < 0 || sor >= b->rows || oszl < 0 || oszl >= b->cols) {
                printf("Hibas koordinatak! Nyomj entert...\n");
                getchar();
                continue;
            }
            
            if (parancs == 'm') {
                int result = megnyit(tabla, sor, oszl, b->rows, b->cols);
                
                if (result == -1) {
                    kepernyo_torol();
                    tabla_kiir(tabla, b->rows, b->cols, 1);
                    printf("\n*** BUMM! Veszitettel! ***\n");
                    vege = 1;
                } else if (result == 0) {
                    printf("Mar meg van nyitva! Nyomj entert...\n");
                    getchar();
                }
                
                if (gyozelem_check(tabla, b->rows, b->cols)) {
                    kepernyo_torol();
                    tabla_kiir(tabla, b->rows, b->cols, 0);
                    printf("\n*** NYERTEL! ***\n");
                    vege = 1;
                    gyozott = 1;
                }
            } else if (parancs == 'f') {
                flag_valt(tabla, sor, oszl, b->rows, b->cols);
            }
        }
    }
    
    if (gyozott && strcmp(b->nev, "guest") != 0) {
        int ido = (int)(time(NULL) - kezdes);
        eredmeny_ment(b->nev, ido, b->rows * b->cols);
        printf("Elmentve!\n");
    }
    
    printf("\nNyomj entert a folytatashoz...");
    getchar();
    getchar();
    
    free_table(tabla, b->rows);
}

int main() {
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
        
        int v;
        scanf("%d", &v);
        
        switch(v) {
            case 1:
                jatek(&b);
                break;
            case 2:
                printf("Nev: ");
                scanf("%s", b.nev);
                break;
            case 3:
                nehezseg_menu(&b);
                getchar();
                getchar();
                break;
            case 4:
                eredmenyek_kiir();
                printf("Enter...");
                getchar();
                getchar();
                break;
            case 5:
                printf("Torlod? (i/n): ");
                char c;
                scanf(" %c", &c);
                if (c == 'i') eredmenyek_torol();
                getchar();
                getchar();
                break;
            case 6:
                fut = 0;
                break;
        }
    }
    
    return 0;
}