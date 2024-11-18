#ifndef SOURIS_H
#define SOURIS_H
#include "Jeu.h"

int souris_joueurs(int positionValide[6][2], int* X, int* Y);
int souris_barrieres(int* BX1, int* BY1, int* BX2, int* BY2, int plateau[17][17]);
void definitioncoordonneesXYbarrieres(int* Xsouris, int* Ysouris, int* X, int* Y);

#endif //SOURIS_H
