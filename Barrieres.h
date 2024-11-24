#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_BARRIERES_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_BARRIERES_H
#include "Jeu.h"
#include "Mouvement.h"

int dfs(int x, int y, int objectifX, int objectifY, int plateau[17][17]);
bool objectifRealisable(Joueur* joueur, int objectifX, int objectifY, int plateau[17][17]);
bool blocage(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int plateau[17][17], int nombreDeJoueur);
#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_BARRIERES_H
