#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
#include "Jeu.h"

char actionsJoueurs(Joueur* J, int plateau[17][17], int *tourPasse, int nombreDeJoueur, char Jetons[4]);
int conversion_chiffre(char chiffre);
int conversion_lettre(char lettre);
void demander_coordonnees(char* lettre, char* chiffre);
void placer_barriere();
void annulerCoup(int plateau[17][17], Joueur* J, int choix, const int anciennePosition[2], int *tourPasse);

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
