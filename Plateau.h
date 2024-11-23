#ifndef SOUSPROGRAMMES_H
#define SOUSPROGRAMMES_H
#include "Jeu.h"

#define Cases 9     // nombre de cases par lignes/colonnes
#define BarreH 0xCD // Barres Horizontales
#define BarreV 0xBA // Barres Verticales
#define BarreC 0xCE // Barres Croix
#define Espace 0x20 // Espace

#define ROUGE 12
#define BLEU 9
#define JAUNE 14
#define VERT 10
#define BLANC 15

void afficherBord(int angleDebut, int angleFin, int intersection, int ligne, int tableau[17][17]);
void afficher_ligne (int tableau[17][17], int ligne);
void afficher_interligne(int tableau[17][17], int ligne, char lettre, char Jetons[4]);
void affichagePlateau(int ligne, int plateau[17][17], char Jetons[4]);
void initialiserPlateau(int plateau[17][17], int nombreDeJoueur);
void ajouterBarriere(int plateau[17][17], int X1, int Y1, int X2, int Y2);
void actuPlateauMouv(Joueur* J, const int anciennePosition[2], int plateau[17][17]);

#endif //SOUSPROGRAMMES_H