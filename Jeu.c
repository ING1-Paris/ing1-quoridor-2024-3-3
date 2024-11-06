#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "stdbool.h"

// Fonction qui exécute le jeu et qui correspond à la boucle de jeu
void executionJeu(int nombreDeJoueur) {
    int plateau[17][17] = {{0}}; // matrice[ligne][colonne] : 9 cases Joueur, 8 cases barrières.
    //menuPersonnalisation(nombreDeJoueur);
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
        affichageJeu(plateau, Jetons, nombreDeJoueur);
        while (tourJoueur) {
            // Mouvement Joueur
            // Placer barrière
            // Annuler tour
            // Passer tour
        }
    }
}

// Fonction pour initialiser un joueur
void initialiserJoueur() {
    int nbJoueurs = menuModeDeJeu();
    // Tableaux pour stocker les pseudos et les jetons
    char Jeton[4];
    char pseudo[4][20];

    menuPersonnalisation(nbJoueurs, Jeton, pseudo);

    // Dans le cas basique  nous avons 2 joueurs à initialiser
    structureJoueur Joueur1;
    Joueur1.x = 16;   // placement du joueur 1 en bas au milieu
    Joueur1.y = 8;
    strcpy(Joueur1.pseudo, pseudo[0]);
    Joueur1.pion = Jeton[0];
    Joueur1.nb_barrieres = 10;

    structureJoueur Joueur2;
    Joueur2.x = 0;    // placement du joueur 2 en haut au milieu
    Joueur2.y = 8;
    strcpy(Joueur2.pseudo, pseudo[1]);
    Joueur2.pion = Jeton[1];
    Joueur2.nb_barrieres = 10;

    structureJoueur Joueur4;
    structureJoueur Joueur3;

    // Si l'utilisateur choisi le mode de jeu 4 joueurs alors on initialise 2 joueurs de plus
    if (nbJoueurs == 4) {
        Joueur1.nb_barrieres = 5;
        Joueur2.nb_barrieres = 5;

        Joueur3.x = 8;    // placement du joueur 3 a gauche au milieu
        Joueur3.y = 0;
        strcpy(Joueur3.pseudo, pseudo[2]);
        Joueur3.pion = Jeton[2];
        Joueur3.nb_barrieres = 5;

        Joueur4.x = 8;    // placement du joueur 4 a droite au milieu
        Joueur4.y = 16;
        strcpy(Joueur4.pseudo, pseudo[3]);
        Joueur4.pion = Jeton[3];
        Joueur4.nb_barrieres = 5;
    }
}