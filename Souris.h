#ifndef SOURIS_H
#define SOURIS_H
#include "Jeu.h"

int souris_joueurs(Joueur* J, int positionValide[6][2], int* X, int* Y);
int cote_a_cote(int X, int Y, int position_jetonX, int position_jetonY);
int souris_barrieres(int* BX1, int* BY1, int* BX2, int* BY2);
void definitioncoordonneesXYbarrieres(int* Xsouris, int* Ysouris, int* X, int* Y);

#endif //SOURIS_H
