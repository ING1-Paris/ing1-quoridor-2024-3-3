#ifndef SOUSPROGRAMMES_H
#define SOUSPROGRAMMES_H

void afficherBord(int angleDebut, int angleFin, int intersection, int ligne, int tableau[17][17]);
void afficher_ligne (int tableau[17][17], int ligne);
void afficher_interligne(int tableau[17][17], int ligne, char lettre, char Jetons[4]);
void affichagePlateau(int ligne, int plateau[17][17], char Jetons[4]);

#endif //SOUSPROGRAMMES_H
