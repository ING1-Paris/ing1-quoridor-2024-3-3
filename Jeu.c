#include "Jeu.h"
#include "Affichage.h"
#include "stdbool.h"
#include "windows.h"

//Fonction qui execute le jeu et qui correspond à la boucle de jeu
//IN :
//OUT :
void executionJeu(int nombreDeJoueur){
    int plateau[17][17] = {{0}};
    char Jetons[4] = {'0'};
    bool execution = 1;
    while(execution){
        affichageJeu(plateau, Jetons, 4);
        system("pause");
    }
}