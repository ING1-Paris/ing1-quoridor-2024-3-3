#include <stdio.h>
#include "ScoreCalcul.h"

void attribuerScore() {      // cherhcer fichier text si pseudo deja existant sinon ajouter pseudo
    FILE* pf = fopen("./score.txt", "w");
    if (pf == NULL) {
        printf("Erreur d'ouverture de fichier.");
    }
}

void ajouterScore() {       // changer score du gagnant en ajoutant + 5
    FILE* pf = NULL;
}