#include <stdio.h>
#include <stdlib.h>
#include "Sauvegarde.h"

// FONCTION POUR SAUVEGARDER UNE PARTIE EN COURS
void sauvegarder_partie(SauvegardePartie* partie) {
    FILE* fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Sauvegarde du nombre de joueurs
    fprintf(fichier, "Nombre de joueurs : %d\n", partie->nb_joueurs);

    // Sauvegarde des pseudos des joueurs
    fprintf(fichier, "Pseudos des joueurs :\n");
    for (int i = 0; i < partie->nb_joueurs; i++) {
        fprintf(fichier, "Joueur %d : %s\n", i + 1, partie->pseudos[i]);
    }

    // Sauvegarde du plateau
    fprintf(fichier, "Plateau :\n");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fprintf(fichier, "%d ", partie->plateau[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde des positions des joueurs
    fprintf(fichier, "Positions des joueurs :\n");
    for (int i = 0; i < partie->nb_joueurs; i++) {
        fprintf(fichier, "Joueur %d : (%d, %d)\n", i+1, partie->positions_joueurs[i][0], partie->positions_joueurs[i][1]);
    }

    // Sauvegarde des barrières restantes pour chaque joueur
    fprintf(fichier, "Barrières restantes pour chaque joueur :\n");
    for (int i = 0; i < partie->nb_joueurs; i++) {
        fprintf(fichier, "Joueur %d : %d barrières restantes\n", i+1, partie->nb_barrieres[i]);
    }

    // Sauvegarde du tour actuel
    fprintf(fichier, "Joueur à qui le tour : %d\n", partie->tour_joueur);

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}
