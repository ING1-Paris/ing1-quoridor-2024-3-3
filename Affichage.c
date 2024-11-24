#include "Affichage.h"
#include "Plateau.h"
#include "windows.h"
#include "Jeu.h"
#include <stdio.h>

#define BLANC 15

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
        case 0: //Affiche à la ligne 0
            printf("    Nombre de joueurs : %d", nombreDeJoueur);
        break;
        case 1: //Affiche à la ligne 1
            printf("    C'est au tour du joueur %d : ", J->numero);
            Color(J->couleur, 0);
            printf("%s", J->pseudo);
            Color(BLANC, 0);
        break;
        case 2: //Affiche à la ligne 2
            printf("    Score du joueur : %d", J->score);
                break;
        case 3: //Affiche à la ligne 3
            printf("    Jeton du joueur : %c", J->jeton);
        break;
        case 4: //Affiche à la ligne 4
            printf("    Nombre de barrieres : %d", J->nb_barrieres);
        break;
        case 5: //Affiche à la ligne 5
            printf("    1. Deplacer le pion");
        break;
        case 6: //Affiche à la ligne 6
            printf("    2. Placer une barriere");
        break;
        case 7: //Affiche à la ligne 7
            printf("    3. Passez votre tour");
        break;
        case 8: //Affiche à la ligne 8
            printf("    4. Interrompre et sauvegarder la partie");
        break;
        case 9: //Affiche à la ligne 9
            printf("    Tapez le chiffre correspondant a l'action que vous voulez faire :");
        break;
    }
}