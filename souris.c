#include "souris.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include "Actions.h"
#include "Jeu.h"

int cote_a_cote(int X, int Y, int position_jetonX, int position_jetonY) {
    int vrai = 0;
    if ((abs(X - position_jetonX) <= 7 && Y == position_jetonY) || (abs(Y - position_jetonY) <= 2 && abs(X - position_jetonX) <= 2)) {
        vrai = 1;
    }

    return vrai;
}

int souris(Joueur* J) {
    // Ouvrir un handle pour l'entrée de la console
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    /* Vérifier si le handle est valide
    if (hStdin == INVALID_HANDLE_VALUE) {
        printf("Erreur : Impossible d'obtenir le handle de la console.\n");
        return 1;
    }*/

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
                    printf("Clic gauche detecte a la position X: %d, Y: %d\n", mer.dwMousePosition.X, mer.dwMousePosition.Y);
                    if (mer.dwMousePosition.X < 3 || mer.dwMousePosition.X > 48 || mer.dwMousePosition.Y < 1 || mer.dwMousePosition.Y > 19) {
                        printf("La Position n'est pas convenable");
                    }
                    else {
                        if (mer.dwMousePosition.X % 5 == 3 || mer.dwMousePosition.Y % 2 == 1) {
                            printf("La Position n'est pas convenable");
                        }
                        else {
                            if (cote_a_cote(mer.dwMousePosition.X, mer.dwMousePosition.Y, J->x, J->y)) {
                                printf("La Position n'est pas convenable");
                            }
                            else {
                                printf("C'est bon");
                            }
                            //fin = 0;
                        }
                    }
                    //sleep(3);
                    //fin = 0;
                }
            }
        }
    }
    return 0;
}

