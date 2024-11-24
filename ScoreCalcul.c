#include <stdio.h>
#include <string.h>
#include "ScoreCalcul.h"

// Fonction qui renvoie le score du joueur, et renvoie -1 s'il n'est pas présent dans le fichier
int chercherScoreJoueur(const char *pseudo) {
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
            return score_lu; // Renvoie le score quand le joueur est trouvé
        }
    }

    fclose(pf);
    return -1; // Joueur non trouvé
}

// Fonction qui ajoute un joueur avec un score de 0 s'il n'est pas déjà présent
void ajouterJoueur(const char *pseudo) {
    FILE* pf = fopen("../score.txt", "a"); // Ouvrir en mode ajout
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour l'ajout\n");
        return;
    }
    fprintf(pf, "%s 0\n", pseudo);
    fclose(pf);
}

//Fonction qui intialise le score d'un joueur
void initialisationScore(Joueur* J) {
    int scoreJoueur = chercherScoreJoueur(J->pseudo);
    if (scoreJoueur == -1) {
        ajouterJoueur(J->pseudo); // Ajoute le score
        J->score = 0;
    } else {
        J->score = scoreJoueur;
    }
}

// Fonction qui ajoute des points au joueur gagnant sans ajouter le joueur s'il n'existe pas
void ajouterPointGagnant(const char *pseudo) {
    FILE* pf = fopen("../score.txt", "r+");  // Ouvre le fichier en lecture/écriture
    if (pf == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    char pseudo_lu[21];
    int score_lu;
    long pos;

    // Parcours du fichier pour modifier le score du joueur
    while (fscanf(pf, "%s %d", pseudo_lu, &score_lu) != EOF) {
        if (strcmp(pseudo_lu, pseudo) == 0) {
            pos = ftell(pf);  // Position après lecture
            score_lu += 5;    // Ajout des 5 points de la victoire

            // Repositionnement précis pour l'écriture
            fseek(pf, pos - (strlen(pseudo_lu) + 1 + snprintf(NULL, 0, "%d", score_lu - 5) + 1), SEEK_SET);

            fprintf(pf, "%s %d\n", pseudo_lu, score_lu);
            fflush(pf);  // Force l'écriture dans le fichier
            fclose(pf);  // On ferme après modification
            return;
        }
    }

    fclose(pf);
    printf("Le joueur n'a pas été trouvé dans le fichier.\n");
}
