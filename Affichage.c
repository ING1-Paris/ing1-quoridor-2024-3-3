#include "Affichage.h"
#include "Plateau.h"
#include <stdio.h>
#include "windows.h"

//Fonction qui affiche le Jeu
//IN :  plateau, Jetons, Pseudos, nombreDeJoueur
//OUT : affichage plateau avec
void affichageJeu(int plateau[17][17], char Jetons[4], int nombreDeJoueur){
    system("cls");
    for(int i=0; i<10; i++){  //Affiche pour chaque ligne
        affichagePlateau(i, plateau, Jetons); //Le plateau
        affichageInformations(i, nombreDeJoueur);
    }
}

void affichageInformations(int ligne, int nombreDeJoueur){
    switch(ligne){
        case 0:
            printf("    Nombre de joueurs : %d", nombreDeJoueur);
            break;
        case 1:
            //printf("    C'est au tour de : %s", pseudo);
            break;
        case 2:
            //printf("    Score du joueur : %d");
            break;
        case 3:
            break;

    }
}
