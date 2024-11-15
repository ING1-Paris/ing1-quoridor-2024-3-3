#ifndef SOUSPROGRAMMES_H
#define SOUSPROGRAMMES_H
#include "Jeu.h"

void afficherBord(int angleDebut, int angleFin, int intersection, int ligne, int tableau[17][17]);
void afficher_ligne (int tableau[17][17], int ligne);
void afficher_interligne(int tableau[17][17], int ligne, char lettre, char Jetons[4]);
void affichagePlateau(int ligne, int plateau[17][17], char Jetons[4]);
void initialiserPlateau(int plateau[17][17], int nombreDeJoueur);
void ajouter_barriere(int plateau[17][17], char lettre1, char chiffre1, char lettre2, char chiffre2, char sens);

#endif //SOUSPROGRAMMES_H