#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include <stdlib.h>
#include <time.h>

void aleatoire(int nombredejoueurs, int ordrealeatoire[nombredejoueurs]) {
    int choix;
    srand(time(NULL));
    choix = rand();
    if (nombredejoueurs == 2) {
        if (choix % 10 < 5) {
            ordrealeatoire[0] = 1;
            ordrealeatoire[1] = 2;
        }
        else {
            ordrealeatoire[0] = 2;
            ordrealeatoire[1] = 1;
        }
    }
    if (nombredejoueurs == 4) {
        for (int i = 0; i < 4; i++) {
            do {
                choix = rand();
                if (choix % 12 < 3) {
                    choix = 1;
                }
                else if (choix % 12 < 6) {
                    choix = 2;
                }
                else if (choix % 12 < 9) {
                    choix = 3;
                }
                else {
                    choix = 4;
                }
            } while (choix == ordrealeatoire[0] || choix == ordrealeatoire[1] || choix == ordrealeatoire[2]);
            ordrealeatoire[i] = choix;
        }
    }
}

// Fonction qui exécute le jeu et qui correspond à la boucle de jeu
void executionJeu(int nombreDeJoueur) {
    int plateau[17][17] = {{0}}; // matrice[ligne][colonne] : 9 cases Joueur, 8 cases barrières.
    initialiserPlateau(plateau, nombreDeJoueur); //Initialise les joueurs sur le plateau

    char pseudo[4][20]; // Tableaux pour stocker les pseudos
    char jeton[4]; // Tableaux pour stocker les jetons
    menuPersonnalisation(nombreDeJoueur, jeton, pseudo); //Initialise jetons et pseudo afin de les remplir

    Joueur J1, J2, J3, J4;
    J1 = initialiserJoueur(0, 8, pseudo[0], jeton[0], nombreDeJoueur);
    J2 = initialiserJoueur(16, 8, pseudo[1], jeton[1], nombreDeJoueur);
    if(nombreDeJoueur>2){
        J2.x = 8;
        J2.y = 0;
        J3 = initialiserJoueur(16, 8, pseudo[2], jeton[2], nombreDeJoueur);
        J4 = initialiserJoueur(8, 16, pseudo[3], jeton[3], nombreDeJoueur);
    }

    int ordre[nombreDeJoueur];
    aleatoire(nombreDeJoueur, ordre);


    for(int i = 0;; i = (i+1)%nombreDeJoueur){
        Joueur* JoueurActuel = ordreJoueur(&J1, &J2, &J3, &J4, ordre[i]);

        //Modification matrice
        affichageJeu(plateau, jeton, nombreDeJoueur, JoueurActuel); //Affichage du Jeu
        if (conditionVictoire(ordre[i], JoueurActuel, nombreDeJoueur)){ //Condition victoire
            break;
        }
        actionsJoueurs(JoueurActuel);//Actions
        system("pause");
    }
}

// Fonction pour initialiser un joueur
Joueur initialiserJoueur(int x, int y, char pseudo[], char jeton, int nombreDeJoueur) {
    Joueur J;
    J.x = x;   // placement du joueur 1 en bas au milieu
    J.y = y;
    strcpy(J.pseudo, pseudo);
    J.jeton = jeton;
    if(nombreDeJoueur ==2){
        J.nb_barrieres = 10;
    }else{
        J.nb_barrieres = 5;
    }
    return J;
}

Joueur* ordreJoueur(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int ordre){
    if(ordre== 1){
        return J1;
    }else if(ordre== 2){
        return J2;
    }else if(ordre== 3){
        return J3;
    }else{
        return J4;
    }
}

bool conditionVictoire(int tour, Joueur* J, int nombreDeJoueur) {
    switch (tour) {
        case 1: //Condition Victoire J1
            if (J->x == 16) {
                return 1;
            }
        case 2: //Condition Victoire J2
            if (nombreDeJoueur == 4) {
                if (J->y == 16) {
                    return 1;
                }
            }
            else {
                if (J->x == 0) {
                    return 1;
                }
            }
        case 3: //Condition Victoire J3
            if (J->x == 0) {
                return 1;
            }
        case 4: //Condition Victoire J4
            if (J->y == 0) {
                return 1;
            }
        default :  //Condition de non-Victoire
            return 0;
    }
}