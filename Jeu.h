#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H

void executionJeu(int nombreDeJoueur);

typedef struct {
    char pseudo[20];
    char pion;
    int x;         // Coordonnée x du joueur sur le plateau
    int y;         // Coordonnée y du joueur sur le plateau
    int nb_barrieres; // Nombre de barrières restant
    int score;
} structureJoueur;

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H