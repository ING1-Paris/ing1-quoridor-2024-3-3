#include "Affichage.h"
#include "Plateau.h"
#include <stdio.h>
#include "windows.h"

//Fonction qui affiche le Jeu
void affichageJeu(int plateau[17][17], char Jetons[4], int nombreDeJoueur, Joueur* J) {
    system("cls");
    for(int i = 0; i < 10; i++) {  //Affiche pour chaque ligne
        affichagePlateau(i, plateau, Jetons); //Le plateau
        affichageInformations(i, nombreDeJoueur, J);
    }
}

//Fonction qui affiche les informations à droite du plateau
void affichageInformations(int ligne, int nombreDeJoueur, Joueur* J) {
    switch(ligne) {
        case 0:
            printf("    Nombre de joueurs : %d", nombreDeJoueur);
            break;
        case 1:
            printf("    C'est au tour de : %s", J->pseudo);
            break;
        case 2:
            //printf("    Score du joueur : %d");
            break;
        case 3:
            printf("    Jeton du joueur : %c", J->jeton);
            break;
        case 4:
            printf("    Nombre de barrieres : %d", J->nb_barrieres);
            break;
        case 5:
            printf("    Tapez 1: Deplacer le pion");
            break;
        case 6:
            printf("    Tapez 2: Placer une barriere");
            break;
        case 7:
            printf("    Tapez 3: Annuler le dernier coups");
            break;
        case 8:
            printf("    Tapez 4: Passez votre tour");
            break;
        case 9:
            printf("    Tapez 5: Interrompre et sauvegarder la partie");
            break;
    }
}