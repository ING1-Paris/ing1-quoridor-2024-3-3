#include "souris.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include "Actions.h"
#include "Jeu.h"

int cote_a_cote(int X, int Y, int position_jetonX, int position_jetonY) {
    int vrai = 0;
    if (abs(X - position_jetonX) == 2 && Y == position_jetonY) {
        vrai = 1;
    }
    if (abs(Y - position_jetonY) == 2 && X == position_jetonX) {
        vrai = 1;
    }
    return vrai;
}


int souris_joueurs(Joueur* J, int positionValide[6][2], int* X, int* Y) {
    // Ouvrir un handle pour l'entrée de la console
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Activer le mode pour lire les événements de la souris
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);


    int fin =1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entrée de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    for (i = 0; i < 16; i++) {
                        if (4 + 5*i <= mer.dwMousePosition.X && mer.dwMousePosition.X <= 7 + 5*i) {
                            *X = 2*i;
                        }
                    }
                    for (i = 0; i < 16; i++) {
                        if (2 + 2*i == mer.dwMousePosition.Y) {
                            *Y = 2*i;
                        }
                    }
                    //printf("Clic gauche detecte a la position X: %d, Y: %d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
                    //printf("Les coordonnées dans la matrice sont X: %d, Y: %d\n", *X, *Y);
                    int vrai = 0;
                    for (i = 0; i < 6; i++) {
                            if (positionValide[i][0] == *Y && positionValide[i][1] == *X) {
                                vrai = 1;
                            }
                    }
                    if (vrai == 1) {
                        printf("C'est bon\n");
                        fin = 0;
                    }
                    else {
                        printf("La position n'est pas convenable ! Veuillez cliquer a nouveau sur la case ou vous voulez vous deplacer.\n");
                    }
                }
            }
        }
    }
    return 0;
}

int souris_barrieres() {
    // Ouvrir un handle pour l'entrée de la console
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Activer le mode pour lire les événements de la souris
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);

    int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;

    int fin = 1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entrée de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    X1 = 0, Y1 = 0;
                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXYbarrieres(&Xsouris, &Ysouris, &X1, &Y1);

                    printf("Les coordonnées sélectionnées sont X: %d, Y: %d\n", X1, Y1);

                    if (mer.dwMousePosition.X < 3 || mer.dwMousePosition.X > 48 || mer.dwMousePosition.Y < 1 || mer.dwMousePosition.Y > 19) {
                        printf("La Position n'est pas convenable\n");
                    }

                    else {
                        if (X1 % 2 == 0 && Y1 % 2 == 0) {
                            printf("La Position n'est pas convenable\n");
                        }
                        else {
                            if (X1 % 2 == 1 && Y1 % 2 == 1) {
                                printf("La Position n'est pas convenable\n");
                            }
                            else {
                                printf("La position de la premiere partie de la barrière est donc en X: %d, Y: %d.\n", X1, Y1);
                                fin = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    fin = 1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entrée de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    X2 = 0, Y2 = 0;

                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXYbarrieres(&Xsouris, &Ysouris, &X2, &Y2);

                    printf("Les coordonnées sélectionnées sont X: %d, Y: %d\n", X2, Y2);
                    if (mer.dwMousePosition.X < 3 || mer.dwMousePosition.X > 48 || mer.dwMousePosition.Y < 1 || mer.dwMousePosition.Y > 19) {
                        printf("La Position n'est pas convenable\n");
                    }
                    else {
                        if (X2 % 2 == 0 && Y2 % 2 == 0) {
                            printf("La Position n'est pas convenable\n");
                        }
                        else {
                            if (X2 % 2 == 1 && Y2 % 2 == 1) {
                                printf("La Position n'est pas convenable\n");
                            }
                            else {
                                if (X2 % 2 == 1 && Y2 % 2 == 0) {
                                    if (abs(X1 - X2) == 2 && abs(Y1 - Y2) == 0) {
                                        printf("La position de la deuxieme partie de la barrière est donc en X: %d, Y: %d.\n", X2, Y2);
                                        fin = 0;
                                    }
                                }
                                else if (X2 % 2 == 0 && Y2 % 2 == 1) {
                                    if (abs(X1 - X2) == 2 && abs(Y1 - Y2) == 0) {
                                        printf("La position de la deuxieme partie de la barrière est donc en X: %d, Y: %d.\n", X2, Y2);
                                        fin = 0;
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


void definitioncoordonneesXYbarrieres(int* Xsouris, int* Ysouris, int* X, int* Y) {
    for (int i = 0; i < 16; i++) {
        if (3 + 5*i == *Xsouris) {
            *X = 2*i - 1;
        }
    }
    for (int i = 0; i < 16; i++) {
        if (4 + 5*i <= *Xsouris && *Xsouris <= 7 + 5*i) {
            *X = 2*i;
        }
    }
    for (int i = 0; i < 16; i++) {
        if (3 + i == *Ysouris) {
            *Y = 1 + i;
        }
    }
}