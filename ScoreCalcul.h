#ifndef SCORECALCUL_H
#define SCORECALCUL_H
#include "Jeu.h"
int chercherScoreJoueur(const char *pseudo);
void ajouterJoueur(const char *pseudo);
void ajouterPointGagnant(const char *pseudo);
void initialisationScore(Joueur* J);

#endif //SCORECALCUL_H