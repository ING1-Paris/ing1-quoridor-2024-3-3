#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#include <stdbool.h>

#define ROUGE 12
#define BLEU 9
#define JAUNE 14
#define VERT 10

typedef struct {
    int x;         // Coordonnée x du joueur sur le plateau
    int y;         // Coordonnée y du joueur sur le plateau
    char pseudo[21]; // pseudo du joueur
    char jeton;      // pion du jouer
    int nb_barrieres; // Nombre de barrières restant
    int score;  // score du joueur
    int numero; // numero joueur
    int couleur; //Couleur du joueur
}Joueur;

Joueur initialiserJoueur(int x, int y, char pseudo[], char jeton, int nombreDeJoueur, int numero, int couleur);
Joueur *ordreJoueur(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int tour);
bool conditionVictoire(int tour, Joueur* J, int nombreDeJoueur);
void executionJeu(int nombreDeJoueur, bool partieCharge);
void aleatoire(int nombredejoueurs, int ordrealeatoire[nombredejoueurs]);
void ecranMatchNul();
void ecranVictoire(Joueur* J);
void Color(int couleurDuTexte,int couleurDeFond);

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H