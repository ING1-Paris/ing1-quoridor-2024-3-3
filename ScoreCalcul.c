#include <stdio.h>
#include <string.h>
#include "ScoreCalcul.h"

// Fonction qui cherche si le joueur est présent dans le fichier
int chercherJoueur(const char *pseudo) {
    FILE* pf = fopen("../score.txt", "r");
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 0;
    }

    char pseudo_lu[20];
    int score_lu;

    // Parcours du fichier pour chercher le pseudo
    while (fscanf(pf, "%s %d", pseudo_lu, &score_lu) != EOF) {
        if (strcmp(pseudo_lu, pseudo) == 0) {
            fclose(pf);
            pf = NULL;
            return 1; // Joueur trouvé
        }
    }

    fclose(pf);
    pf = NULL;
    return 0; // Joueur non trouvé
}

// Fonction qui ajoute un joueur avec un score de 0 s'il n'est pas déjà présent
void ajouterJoueur(const char *pseudo) {
    if (!chercherJoueur(pseudo)) {
        FILE* pf = fopen("../score.txt", "a"); // Ouvrir en mode ajout
        if (pf == NULL) {
            printf("Erreur lors de l'ouverture du fichier pour l'ajout\n");
            return;
        }
        fprintf(pf, "%s 0\n", pseudo);
        fclose(pf);
        pf = NULL;
    }
}

// Fonction qui ajoute des points au joueur gagnant
void ajouterPointGagnant(const char *pseudo) {
    FILE* pf = fopen("../score.txt", "r");
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    char pseudo_lu[21];
    int score_lu;

    // Fichier temporaire pour réécrire les scores - cela réduit la possibilité d'erreur
    FILE *temp_file = fopen("temp_score.txt", "w");
    if (temp_file == NULL) {
        printf("Erreur lors de la création du fichier temporaire\n");
        fclose(pf);
        pf = NULL;
        return;
    }

    // Parcours du fichier pour modifier le score du joueur
    while (fscanf(pf, "%s %d", pseudo_lu, &score_lu) != EOF) {
        if (strcmp(pseudo_lu, pseudo) == 0) {
            score_lu += 5;    // ajout des 5 points de la victoire
        }
        fprintf(temp_file, "%s %d\n", pseudo_lu, score_lu);
    }

    fclose(pf);
    pf = NULL;
    fclose(temp_file);
    temp_file = NULL;

    // Remplacement du fichier original par le fichier temporaire
    remove("score.txt");
    rename("temp_score.txt", "score.txt");
}