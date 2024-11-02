#include "Jeu.h"
#include "Affichage.h"
#include "stdbool.h"
#include "windows.h"

// Fonction qui exécute le jeu et qui correspond à la boucle de jeu
// IN :
// OUT :
void executionJeu(int nombreDeJoueur) {
    int plateau[17][17] = {{0}}; // matrice[ligne][colonne] : 9 cases Joueur, 8 cases barrières.
    char Jetons[4];
    Jetons[0] = '#'; // Jeton J1
    Jetons[1] = '@'; // Jeton J2
    plateau[8][0] = 1; // Positionne le Joueur 1 sur le bord gauche au milieu
    plateau[8][16] = 2; // Positionne le Joueur 2 sur le bord droit au milieu
    if (nombreDeJoueur == 4) {
        Jetons[2] = '&'; // Jeton J3
        Jetons[3] = '$'; // Jeton J4
        plateau[0][8] = 3; // Positionne le Joueur 3 sur le bord du haut au milieu
        plateau[16][8] = 4; // Positionne le Joueur 4 sur le bord du bas au milieu
    }
    bool execution = 1, tourJoueur = 1;
    while (execution) {
        affichageJeu(plateau, Jetons, 4);
        while (tourJoueur) {
            // Mouvement Joueur
            // Placer barrière
            // Annuler tour
            // Passer tour
        }
    }
}
