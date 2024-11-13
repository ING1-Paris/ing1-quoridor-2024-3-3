#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#include <stdbool.h>

typedef struct {
    int x;         // Coordonnée x du joueur sur le plateau
    int y;         // Coordonnée y du joueur sur le plateau
    char pseudo[20]; // pseudo du joueur
    char jeton;      // pion du jouer
    int nb_barrieres; // Nombre de barrières restant
    int score;  // score du joueur
}Joueur;

Joueur initialiserJoueur(int x, int y, char pseudo[], char jeton, int nombreDeJoueur);
Joueur *ordreJoueur(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int tour);
bool conditionVictoire(int tour, Joueur* J, int nombreDeJoueur);
void executionJeu(int nombreDeJoueur);
void aleatoire(int nombredejoueurs, int ordrealeatoire[nombredejoueurs]);
#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H