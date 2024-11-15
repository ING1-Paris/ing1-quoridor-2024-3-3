#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include "ScoreCalcul.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ScoreCalcul.h"

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
    int plateau[17][17] = {{0}}; // matrice[colonne][ligne] : 9 cases Joueur, 8 cases barrières
    //éléments en fonction du chiffre :
    // 1 = J1; 2 = J2; 3 = J3; 4 = J4; 5 = barrière horizontale; 6 = barrière verticale 7 = barrière en croix
    initialiserPlateau(plateau, nombreDeJoueur); //Initialise les joueurs sur le plateau

    char pseudo[4][21]; // Tableaux pour stocker les pseudos
    char jeton[4]; // Tableaux pour stocker les jetons
    menuPersonnalisation(nombreDeJoueur, jeton, pseudo); //Initialise jetons et pseudo afin de les remplir

    Joueur J1, J2, J3, J4;
    J1 = initialiserJoueur(0, 8, pseudo[0], jeton[0], nombreDeJoueur, 1);
    J2 = initialiserJoueur(16, 8, pseudo[1], jeton[1], nombreDeJoueur, 2);
    if(nombreDeJoueur>2) {
        J2.x = 8;
        J2.y = 0;
        J3 = initialiserJoueur(16, 8, pseudo[2], jeton[2], nombreDeJoueur, 3);
        J4 = initialiserJoueur(8, 16, pseudo[3], jeton[3], nombreDeJoueur, 4);
    }

    int ordre[nombreDeJoueur];
    aleatoire(nombreDeJoueur, ordre);


    for(int i = 0, tourPasse = 0;; i = (i + 1) % nombreDeJoueur) {
        Joueur* JoueurActuel = ordreJoueur(&J1, &J2, &J3, &J4, ordre[i]);

        affichageJeu(plateau, jeton, nombreDeJoueur, JoueurActuel); //Affichage du Jeu
        if (conditionVictoire(ordre[i], JoueurActuel, nombreDeJoueur)) { //Condition victoire
            ecranVictoire(JoueurActuel);
            ajouterPointGagnant(JoueurActuel->pseudo);
            break;
        }

        char action = actionsJoueurs(JoueurActuel, plateau, &tourPasse); //Renvoie S si le joueur interromp la partie, E s'il fait une erreur, N si match nul
        if (action == 'S') {
            //Sauvegarde de la partie
            break;
        }
        else if(action == 'E'){
            printf("\nErreur : Nombre invalide");
            sleep(2);
            system("cls");
            i--;
        }
        if(tourPasse == nombreDeJoueur*2){
            ecranMatchNul();
            break;
        }
    }
}

// Fonction pour initialiser un joueur
Joueur initialiserJoueur(int x, int y, char pseudo[], char jeton, int nombreDeJoueur, int numero) {
    Joueur J;
    J.x = x;   // placement du joueur 1 en bas au milieu
    J.y = y;
    strcpy(J.pseudo, pseudo);
    J.jeton = jeton;
    J.numero = numero;
    if(nombreDeJoueur ==2) {
        J.nb_barrieres = 10;
    }
    else {
        J.nb_barrieres = 5;
    }
    return J;
}

Joueur* ordreJoueur(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int ordre) {
    if(ordre== 1) {
        return J1;
    }
    else if(ordre== 2) {
        return J2;
    }
    else if(ordre== 3) {
        return J3;
    }
    else {
        return J4;
    }
}

bool conditionVictoire(int tour, Joueur* J, int nombreDeJoueur) {
    switch (tour) {
        case 1: //Condition Victoire J1
            if (J->x == 16) {
                return 1;
            }
            break;
        case 2: //Condition Victoire J2
            if (nombreDeJoueur == 4 && J->y == 16) {
                return 1;
            }
            if (nombreDeJoueur == 2 && J->x == 0) {
                return 1;
            }
            break;
        case 3: //Condition Victoire J3
            if (J->x == 0) {
                return 1;
            }
            break;
        case 4: //Condition Victoire J4
            if (J->y == 0) {
                return 1;
            }
            break;
    }
    return 0; //Condition de non-Victoire
}

void ecranVictoire(Joueur* J){
    system("cls");
    printf("__     ___      _        _            _   _   _ \n");
    printf("\\ \\   / (_) ___| |_ ___ (_)_ __ ___  | | | | | |\n");
    printf(" \\ \\ / /| |/ __| __/ _ \\| | '__/ _ \\ | | | | | |\n");
    printf("  \\ V / | | (__| || (_) | | | |  __/ |_| |_| |_|\n");
    printf("   \\_/  |_|\\___|\\__\\___/|_|_|  \\___| (_) (_) (_)\n");
    printf("         %s gagne cette partie ! Bravo !", J->pseudo);
    sleep(3);
}

void ecranMatchNul(){
    system("cls");
    printf(" __  __       _       _                   _             \n");
    printf("|  \\/  | __ _| |_ ___| |__    _ __  _   _| |            \n");
    printf("| |\\/| |/ _` | __/ __| '_ \\  | '_ \\| | | | |            \n");
    printf("| |  | | (_| | || (__| | | | | | | | |_| | |  _   _   _ \n");
    printf("|_|  |_|\\__,_|\\__\\___|_| |_| |_| |_|\\__,_|_| (_) (_) (_)\n");
    printf("         Blocage de la partie : match nul ...");
    sleep(3);
}