#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H

void executionJeu(int nombreDeJoueur);

typedef struct{
    char pseudo[15];
    char pion;
    int x;         // Coordonnée x du joueur sur le plateau
    int y;         // Coordonnée y du joueur sur le plateau
    int nb_barrieres; // Nombre de barrières restant
    // le score se trouve dans un fichier alors pas ici ??
} structureJoueur;

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_JEU_H