#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
#include "Jeu.h"

char actionsJoueurs(Joueur* J);
void deplacer_joueur(Joueur* J);
int conversion_chiffre(char chiffre);
int conversion_lettre(char lettre);
void demander_coordonnees(char* lettre, char* chiffre);
int cote_a_cote(char lettre1, char chiffre1, char lettre2, char chiffre2);
void placer_barriere();

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_ACTIONS_H
