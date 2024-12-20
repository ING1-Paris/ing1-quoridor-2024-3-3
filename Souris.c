#include "souris.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include "Actions.h"
#include "Jeu.h"

//Fonctions qui catpure les coordonnées X et Y pour le déplacement du joueurs
int souris_joueurs(int positionValide[6][2], int* X, int* Y) {
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
            printf("Erreur de lecture de l'entree de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {

                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXY(&Xsouris, &Ysouris, X, Y);
                    
                    int vrai = 0;
                    for (i = 0; i < 6; i++) {
                            if (positionValide[i][0] == *Y && positionValide[i][1] == *X) {
                                vrai = 1;
                            }
                    }
                    if (vrai == 1) {
                        fin = 0;
                    }
                    else {
                        printf("\nLa position n'est pas convenable ! Veuillez cliquer a nouveau sur la case ou vous voulez vous deplacer.");
                    }
                }
            }
        }
    }
    return 0;
}

//Fonctions qui catpure les coordonnées X et Y pour le placement des barrières
int souris_barrieres(int* BX1, int* BY1, int* BX2, int* BY2, int plateau[17][17]) {
    // Ouvrir un handle pour l'entrée de la console
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Activer le mode pour lire les événements de la souris
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);

    int fin = 1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entree de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    *BX1 = 0, *BY1 = 0;
                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXY(&Xsouris, &Ysouris, BX1, BY1);

                    printf("\nLes coordonnees selectionnees sont X: %d, Y: %d", *BX1, *BY1);

                    if (mer.dwMousePosition.X < 3 || mer.dwMousePosition.X > 48 || mer.dwMousePosition.Y < 1 || mer.dwMousePosition.Y > 19) {
                        printf("La position n'est pas convenable\n");
                    }

                    else {
                        if (*BX1 % 2 == 0 && *BY1 % 2 == 0) {
                            printf("La position n'est pas convenable\n");
                        }
                        else {
                            if (*BX1 % 2 == 1 && *BY1 % 2 == 1) {
                                printf("La position n'est pas convenable\n");
                            }
                            else {
                                if (plateau[*BY1][*BX1] >= 5) {
                                    printf("Il y a deja une barriere a cet emplacement.\n");
                                }
                                else if (*BX1 % 2 == 0 && *BY1 % 2 == 1) {
                                    if (plateau[*BY1][*BX1 - 2] >= 5 && plateau[*BY1][*BX1 + 2] >= 5) {
                                        printf("Espace insuffisant, recliquez sur un emp1lacement valide.\n");
                                    }
                                    else if ((plateau[*BY1][*BX1 - 2] >= 5 && *BX1 == 16) || (plateau[*BY1][*BX1 + 2] >= 5 && *BX1 == 0)) {
                                        printf("Espace insuffisant, recliquez sur un emplacement valide.\n");
                                    }
                                    else {
                                        fin = 0;
                                    }
                                }
                                else if (*BX1 % 2 == 1 && *BY1 % 2 == 0) {
                                    if (plateau[*BY1 - 2][*BX1] >= 5 && plateau[*BY1 + 2][*BX1] >= 5) {
                                        printf("Espace insuffisant, recliquez sur un emplacement valide.\n");
                                    }
                                    else if ((plateau[*BY1 - 2][*BX1] >= 5 && *BY1 == 16) || (plateau[*BY1 + 2][*BX1] >= 5 && *BY1 == 0)) {
                                        printf("Espace insuffisant, recliquez sur un emplacement valide.\n");
                                    }
                                    else {
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
    fin = 1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entree de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    *BX2 = 0, *BY2 = 0;

                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXY(&Xsouris, &Ysouris, BX2, BY2);

                    printf("Les coordonnees selectionnees sont X: %d, Y: %d\n", *BX2, *BY2);
                    if (mer.dwMousePosition.X < 3 || mer.dwMousePosition.X > 48 || mer.dwMousePosition.Y < 1 || mer.dwMousePosition.Y > 19) {
                        printf("La position n'est pas convenable\n");
                    }
                    else {
                        if (*BX2 % 2 == 0 && *BY2 % 2 == 0) {
                            printf("La position n'est pas convenable\n");
                        }
                        else {
                            if (*BX2 % 2 == 1 && *BY2 % 2 == 1) {
                                printf("La position n'est pas convenable\n");
                            }
                            else {
                                if (*BX2 % 2 == 0 && *BY2 % 2 == 1) {
                                    if (plateau[*BY2][*BX2] >= 5) {
                                        printf("Il y a deja une barriere a cet emplacement.\n");
                                    }
                                    else {
                                        if (abs(*BX1 - *BX2) == 2 && abs(*BY1 - *BY2) == 0) {
                                            printf("La position de la deuxieme partie de la barrière est donc en X: %d, Y: %d.\n", *BX2, *BY2);
                                            fin = 0;
                                        }
                                        else {
                                            printf("La position n'est pas convenable\n");
                                        }
                                    }
                                }
                                else if (*BX2 % 2 == 1 && *BY2 % 2 == 0) {
                                    if (plateau[*BY2][*BX2] >= 5) {
                                        printf("Il y a deja une barriere a cet emplacement.\n");
                                    }
                                    else {
                                        if (abs(*BX1 - *BX2) == 0 && abs(*BY1 - *BY2) == 2) {
                                            printf("La position de la deuxieme partie de la barrière est donc en X: %d, Y: %d.\n", *BX2, *BY2);
                                            fin = 0;
                                        }
                                        else {
                                            printf("La position n'est pas convenable\n");
                                        }
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

void definitioncoordonneesXY(int* Xsouris, int* Ysouris, int* X, int* Y) {
    for (int i = 0; i < 16; i++) { // Récupération du X des coordonnees de la barriere si elle est au niveau des barrieres
        if (3 + 5*i == *Xsouris) {
            *X = 2*i - 1;
        }
    }
    for (int i = 0; i < 16; i++) { // Récupération du X des coordonnees de la barriere si elle est au niveau des joueurs
        if (4 + 5*i <= *Xsouris && *Xsouris <= 7 + 5*i) {
            *X = 2*i;
        }
    }
    for (int i = 0; i < 16; i++) { // Récupération du Y des coordonnees de la barriere
        if (3 + i == *Ysouris) {
            *Y = 1 + i;
        }
    }
}

/*
int remplacer_barrieres(int* BX1, int* BY1, int* BX2, int* BY2, int plateau[17][17]) {

    // Ouvrir un handle pour l'entrée de la console
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // Activer le mode pour lire les événements de la souris
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin, fdwMode);

    int fin = 1;
    // Boucle pour lire les événements de la console
    while (fin) {
        // Lire les événements de la console
        INPUT_RECORD irInBuf[128];
        DWORD cNumRead;
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            printf("Erreur de lecture de l'entree de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    *BX1 = 0, *BY1 = 0;
                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXY(&Xsouris, &Ysouris, BX1, BY1);

                    printf("Les coordonnees selectionnees sont X: %d, Y: %d\n", *BX1, *BY1);

                    if (plateau[*BY1][*BX1] >= 5) {
                        printf("Il y a bien une barriere a cet emplacement.\n");
                        fin = 0;
                    }
                    else {
                        printf("Il n'y a pas de barriere a cet emplacement\n");
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
            printf("Erreur de lecture de l'entree de la console.\n");
            return 1;
        }

        // Traiter chaque événement
        for (DWORD i = 0; i < cNumRead; i++) {
            // Vérifier si c'est un événement de souris
            if (irInBuf[i].EventType == MOUSE_EVENT) {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Où le clic gauche est pressé
                if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                    *BX2 = 0, *BY2 = 0;

                    int Xsouris = mer.dwMousePosition.X, Ysouris = mer.dwMousePosition.Y;

                    definitioncoordonneesXY(&Xsouris, &Ysouris, BX2, BY2);

                    printf("Les coordonnees selectionnees sont X: %d, Y: %d\n", *BX2, *BY2);

                    if (plateau[*BY2][*BX2] >= 5) {
                        printf("Il y a bien une barriere a cet emplacement.\n");
                        fin = 0;
                    }
                    else {
                        printf("Il n'y a pas de barriere a cet emplacement\n");
                    }
                }
            }
        }
    }
    return 0;
}
*/