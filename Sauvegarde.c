#include <stdio.h>
#include <stdlib.h>
#include "Sauvegarde.h"
#include "Jeu.h"

// FONCTION POUR SAUVEGARDER UNE PARTIE EN COURS
void sauvegarder_partie(SauvegardePartie* partie, Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4) {
    FILE* fichier = fopen("../sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Sauvegarde du nombre de joueurs
    fprintf(fichier, "Nombre de joueurs : %d\n", partie->nb_joueurs);

    // Sauvegarde des pseudos des joueurs
    fprintf(fichier, "Pseudos des joueurs :\n");
    if (J1) fprintf(fichier, "Joueur 1 : %s\n", J1->pseudo);
    if (J2) fprintf(fichier, "Joueur 2 : %s\n", J2->pseudo);
    if (J3) fprintf(fichier, "Joueur 3 : %s\n", J3->pseudo);
    if (J4) fprintf(fichier, "Joueur 4 : %s\n", J4->pseudo);

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
    if (J1) fprintf(fichier, "Joueur 1 : (%d, %d)\n", J1->x, J1->y);
    if (J2) fprintf(fichier, "Joueur 2 : (%d, %d)\n", J2->x, J2->y);
    if (J3) fprintf(fichier, "Joueur 3 : (%d, %d)\n", J3->x, J3->y);
    if (J4) fprintf(fichier, "Joueur 4 : (%d, %d)\n", J4->x, J4->y);

    // Sauvegarde des barrières restantes pour chaque joueur
    fprintf(fichier, "Barrières restantes pour chaque joueur :\n");
    if (J1) fprintf(fichier, "Joueur 1 : %d barrières restantes\n", J1->nb_barrieres);
    if (J2) fprintf(fichier, "Joueur 2 : %d barrières restantes\n", J2->nb_barrieres);
    if (J3) fprintf(fichier, "Joueur 3 : %d barrières restantes\n", J3->nb_barrieres);
    if (J4) fprintf(fichier, "Joueur 4 : %d barrières restantes\n", J4->nb_barrieres);

    // Sauvegarde du tour actuel
    fprintf(fichier, "Joueur à qui le tour : %d\n", partie->tour_joueur);

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

// FONCTION POUR CHARGER LA DERNIERE PARTIE SAUVEGARDEE
void charger_partie(SauvegardePartie* partie, Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4) {
    FILE* fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier de sauvegarde.\n");
        return;
    }

    // Chargement du nombre de joueurs
    fscanf(fichier, "Nombre de joueurs : %d\n", &partie->nb_joueurs);
    printf("Nombre de joueurs chargé : %d\n", partie->nb_joueurs);

    // Chargement des pseudos des joueurs
    fscanf(fichier, "Pseudos des joueurs :\n");
    if (J1) fscanf(fichier, "Joueur 1 : %s\n", J1->pseudo);
    if (J2) fscanf(fichier, "Joueur 2 : %s\n", J2->pseudo);
    if (J3) fscanf(fichier, "Joueur 3 : %s\n", J3->pseudo);
    if (J4) fscanf(fichier, "Joueur 4 : %s\n", J4->pseudo);

    // Chargement du plateau
    fscanf(fichier, "Plateau :\n");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fscanf(fichier, "%d", &partie->plateau[i][j]);
        }
    }
    printf("Plateau chargé.\n");

    // Chargement des positions des joueurs
    fscanf(fichier, "Positions des joueurs :\n");
    if (J1) fscanf(fichier, "Joueur 1 : (%d, %d)\n", &J1->x, &J1->y);
    if (J2) fscanf(fichier, "Joueur 2 : (%d, %d)\n", &J2->x, &J2->y);
    if (J3) fscanf(fichier, "Joueur 3 : (%d, %d)\n", &J3->x, &J3->y);
    if (J4) fscanf(fichier, "Joueur 4 : (%d, %d)\n", &J4->x, &J4->y);

    // Chargement des barrières restantes pour chaque joueur
    fscanf(fichier, "Barrières restantes pour chaque joueur :\n");
    if (J1) fscanf(fichier, "Joueur 1 : %d barrières restantes\n", &J1->nb_barrieres);
    if (J2) fscanf(fichier, "Joueur 2 : %d barrières restantes\n", &J2->nb_barrieres);
    if (J3) fscanf(fichier, "Joueur 3 : %d barrières restantes\n", &J3->nb_barrieres);
    if (J4) fscanf(fichier, "Joueur 4 : %d barrières restantes\n", &J4->nb_barrieres);

    // Chargement du tour actuel
    fscanf(fichier, "Joueur à qui le tour : %d\n", &partie->tour_joueur);
    printf("Joueur à qui le tour : %d\n", partie->tour_joueur);

    fclose(fichier);
    printf("Partie chargée avec succès.\n");
}




