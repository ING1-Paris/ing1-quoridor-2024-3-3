#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include <stdlib.h>
#include <time.h>

int aleatoire(int nombredejoueurs) {
    int choix;
    srand(time(NULL));
    choix = rand();             // Fonction alétoire en fonction du temps
    if (nombredejoueurs == 2) { // S'il y a 2 joueurs
        if (choix % 10 < 5) {   // On définit une fonction qui prend uniquement le chiffre des unités
            choix = 1;          // Si il est inférieur ou égal à 4, c'est le premier joueur qui commence
        }
        else {                  // Sinon c'est le deuxième
            choix = 2;
        }
    }
    if (nombredejoueurs == 4) { // S'il y a 4 joueurs
        if (choix % 12 < 3) {   // On définit une fonction mudulo 12 car 12/3=4
            choix = 1;          // Même principe que pour 2 joueurs
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
    }
    return choix;
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

    int ordre = aleatoire(nombreDeJoueur);


    for(int i = ordre;; i = (i+1)%nombreDeJoueur){
        Joueur* JoueurActuel = ordreJoueur(&J1, &J2, &J3, &J4, ordre);

        //Modification matrice
        affichageJeu(plateau, jeton, nombreDeJoueur, JoueurActuel); //Affichage du Jeu
        if (conditionVictoire(ordre, JoueurActuel)){ //Condition victoire
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

Joueur* ordreJoueur(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int tour){
    if(tour== 1){
        return J1;
    }else if(tour== 2){
        return J2;
    }else if(tour== 3){
        return J3;
    }else{
        return J4;
    }
}

bool conditionVictoire(int tour, Joueur* J) {
    switch (tour) {
        case 1: //Condition Victoire J1
            if (J->x == 0) {
                return 1;
            }
        case 2: //Condition Victoire J2
            if (J->x == 16) {
                return 1;
            }
        case 3: //Condition Victoire J3
            if (J->y == 16) {
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