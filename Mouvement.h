#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MOUVEMENT_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MOUVEMENT_H
#include "Jeu.h"

bool deplacerJoueur(Joueur* J, int plateau[17][17], int anciennePosition[2]);
int trouverCasesValides(Joueur* J, int plateau[17][17], int positionValide[6][2]);
void ChercherPositionsPlateau(int plateau[17][17], int positionValide[6][2], int* nombreElements, int Y, int X, int signeY, int signeX);
void ajouterTableau(int Y, int X, int positionValide[6][2], int *nombreElements);
bool doublon(int Y, int X, int positionValide[6][2], int nombreElements);
bool presenceObjet(int Y, int X, int plateau[17][17]);
bool estDansPlateau(int Y, int X);
#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MOUVEMENT_H
