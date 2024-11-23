#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include "ScoreCalcul.h"
#include "Sauvegarde.h"
#include "Chargement.h"

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Fonction qui permet de décider de l'aléatoire pour l'ordre des joueurs
void aleatoire(int nombredejoueurs, int ordrealeatoire[nombredejoueurs]) {
    int choix;
    srand(time(NULL));
    choix = rand();

    //Cas où il y a seulement deux joueurs :
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
    //Cas où il y a 4  joueurs : (On fait une boucle afin de vérifier que l'on n'ait pas 2 fois le même joueur)
    else if (nombredejoueurs == 4) {
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
void executionJeu(int nombreDeJoueur, bool partieCharge) {

    //DECLARATION
    int plateau[17][17] = {{0}}; // matrice[colonne][ligne] : 9 cases Joueur, 8 cases barrières
    //éléments en fonction du chiffre :
    // 1 = J1; 2 = J2; 3 = J3; 4 = J4; 5 = barrière horizontale; 6 = barrière verticale 7 = barrière en croix
    Joueur J1, J2, J3, J4; //Déclaration des joueurs
    char pseudo[4][21]; // Tableaux pour stocker les pseudos
    char jeton[4]; // Tableaux pour stocker les jetons
    int ordre[nombreDeJoueur]; // Déclaration du tableau pour l'odre des joueurs
    int tourPasse; // Déclaration de tour passées
    int tour;  // Déclaration du tour auquel la partie commence

    //INITIALISATION
    if(partieCharge){
        //Initialisation de la données dans laquelle on mettra les éléments de la sauvegarde
        SauvegardePartie partie;

        //Vérifie que la sauvegarde soit chargé
        if(charger_sauvegarde(&partie)){
            charger_partie(plateau, &nombreDeJoueur, &tour, &J1, &J2, &J3, &J4, jeton, ordre, &tourPasse, partie);
        }else{ //Si elle n'est pas chargé, renvoie au menu
            system("cls");
            printf("Erreur : impossible de charger la sauvegarde");
            return;
        }
    }else{
        //Initialisation du Jeu
        initialiserPlateau(plateau, nombreDeJoueur); //Initialise les joueurs sur le plateau
        menuPersonnalisation(nombreDeJoueur, jeton, pseudo); //Initialise jetons et pseudo afin de les remplir
        J1 = initialiserJoueur(0, 8, pseudo[0], jeton[0], nombreDeJoueur, 1, BLEU);
        J2 = initialiserJoueur(16, 8, pseudo[1], jeton[1], nombreDeJoueur, 2, ROUGE);
        if(nombreDeJoueur>2) {
            J2.x = 8;
            J2.y = 0;
            J3 = initialiserJoueur(16, 8, pseudo[2], jeton[2], nombreDeJoueur, 3, JAUNE);
            J4 = initialiserJoueur(8, 16, pseudo[3], jeton[3], nombreDeJoueur, 4, VERT);
        }
        aleatoire(nombreDeJoueur, ordre);
        tourPasse = 0;
        tour = 0;
    }

    for(int i = tour;; i = (i + 1) % nombreDeJoueur) {
        Joueur* JoueurActuel = ordreJoueur(&J1, &J2, &J3, &J4, ordre[i]);

        //1er Affichage du Jeu
        affichageJeu(plateau, jeton, nombreDeJoueur, JoueurActuel);

        //      Partie action du joueur :
        char action = actionsJoueurs(JoueurActuel, plateau, &tourPasse, nombreDeJoueur, jeton); //Renvoie S si le joueur interromp la partie, E s'il fait une erreur, N si match nul
        if (action == 'S') {
            SauvegardePartie partie = iniSauvegarde(plateau, nombreDeJoueur, tour, &J1, &J2, &J3, &J4, jeton, ordre, tourPasse);
            sauvegarder_partie(&partie);
            break;
        } else if(action == 'E'){
            sleep(2);
            system("cls");
            i--;
        }else{
            //      Test pour voir si la partie doit continuer :
            if (conditionVictoire(ordre[i], JoueurActuel, nombreDeJoueur)) {  //Condition victoire
                ecranVictoire(JoueurActuel);  //Affiche écran de victoire
                ajouterPointGagnant(JoueurActuel->pseudo);
                if(partieCharge){
                    //Lorsque la partie vient du partie chargé, supprime cette dernière
                    if(remove("../sauvegarde.txt") !=0){
                        system("cls");
                        printf("Erreur : la supression de la sauvegarde ne fonctionne pas.\n");
                        sleep(2);
                    }
                }
                break;
            }
            if(tourPasse == nombreDeJoueur*2){ //Condition match nul
                ecranMatchNul(); //Affiche écran de match nul
                break;
            }
        }
    }
}

// Fonction pour initialiser un joueur
Joueur initialiserJoueur(int x, int y, char pseudo[], char jeton, int nombreDeJoueur, int numero, int couleur) {
    Joueur J;
    J.x = x;   // placement du joueur 1 en bas au milieu
    J.y = y;
    strcpy(J.pseudo, pseudo);
    J.jeton = jeton;
    J.numero = numero;
    J.couleur = couleur;
    initialisationScore(&J);
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
    printf("        Blocage de la partie : match nul ...");
    sleep(3);
}

//Fonction qui permet de mettre de la couleur dans la console
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond * 16 + couleurDuTexte);
}