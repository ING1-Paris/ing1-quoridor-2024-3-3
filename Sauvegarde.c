#include <stdio.h>
#include <stdlib.h>
#include "Sauvegarde.h"
#include <string.h>
#include "Jeu.h"

// FONCTION POUR SAUVEGARDER UNE PARTIE EN COURS
void sauvegarder_partie(SauvegardePartie* partie) {
    FILE* fichier = fopen("../sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Sauvegarde du plateau
    fprintf(fichier, "Plateau :\n");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fprintf(fichier, "%d ", partie->plateau[i][j]);
        }
        fprintf(fichier, "\n");
    }

    // Sauvegarde du nombre de joueurs
    fprintf(fichier, "Nombre de joueurs : %d\n", partie->nb_joueurs);

    // Sauvegarde des pseudos des joueurs
    fprintf(fichier, "Pseudos des joueurs :\n");
    fprintf(fichier, "Joueur 1 : %s\n", partie->J1->pseudo);
    fprintf(fichier, "Joueur 2 : %s\n", partie->J2->pseudo);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : %s\n", partie->J3->pseudo);
        fprintf(fichier, "Joueur 4 : %s\n", partie->J4->pseudo);
    }

    // Sauvegarde des positions des joueurs
    fprintf(fichier, "Positions des joueurs :\n");
    fprintf(fichier, "Joueur 1 : (%d, %d)\n", partie->J1->x, partie->J1->y);
    fprintf(fichier, "Joueur 2 : (%d, %d)\n", partie->J2->x, partie->J2->y);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : (%d, %d)\n", partie->J3->x, partie->J3->y);
        fprintf(fichier, "Joueur 4 : (%d, %d)\n", partie->J4->x, partie->J4->y);
    }

    // Sauvegarde des barrières restantes pour chaque joueur
    fprintf(fichier, "Barrières restantes pour chaque joueur :\n");
    fprintf(fichier, "Joueur 1 : %d barrières restantes\n", partie->J1->nb_barrieres);
    fprintf(fichier, "Joueur 2 : %d barrières restantes\n", partie->J2->nb_barrieres);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : %d barrières restantes\n", partie->J3->nb_barrieres);
        fprintf(fichier, "Joueur 4 : %d barrières restantes\n", partie->J4->nb_barrieres);
    }

    // Sauvegarde des jetons de chaque joueur en entier
    fprintf(fichier, "Jetons de chaque joueur :\n");
    fprintf(fichier, "Jeton joueur 1 : %d\n", partie->jeton[0]);
    fprintf(fichier, "Jeton joueur 2 : %d\n", partie->jeton[1]);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Jeton joueur 3 : %d\n", partie->jeton[2]);
        fprintf(fichier, "Jeton joueur 4 : %d\n", partie->jeton[3]);
    }

    // Sauvegarde de l'ordre des joueurs
    fprintf(fichier, "Ordre chaque joueur :\n");
    fprintf(fichier, "1er, joueur numéro : %d\n", partie->ordre[0]);
    fprintf(fichier, "2nd, joueur numéro : %d\n", partie->ordre[1]);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "3eme, joueur numéro : %d\n", partie->ordre[2]);
        fprintf(fichier, "4eme, joueur numéro : %d\n", partie->ordre[3]);
    }

    // Sauvegarde du tour actuel
    fprintf(fichier, "Joueur à qui le tour : %d\n", partie->tour_joueur);

    // Sauvegarde le nombre de tour passés d'affilé
    fprintf(fichier, "Nombre de tour passés : %d\n", partie->tourPasse);

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

SauvegardePartie iniPartie(int plateau[17][17], int nombreDeJoueur, int tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4, char jeton[4], int ordre[nombreDeJoueur], int tourPasse){
    SauvegardePartie P;
    for (int x = 0; x < 17; x++) {
        for (int y = 0; y < 17; y++) {
            P.plateau[x][y] = plateau[x][y];
        }
    }
    P.nb_joueurs = nombreDeJoueur;
    P.tour_joueur = tour;
    P.J1 = J1;
    P.J2 = J2;
    if(nombreDeJoueur > 2){
        P.J3 = J3;
        P.J4 = J4;
    }
    strcpy(P.jeton, jeton);
    for (int i = 0; i < nombreDeJoueur; i++) {
        P.ordre[i] = ordre[i];
    }
    P.tourPasse = tourPasse;
    return P;
}

// FONCTION POUR CHARGER LA DERNIERE PARTIE SAUVEGARDEE
void charger_partie(SauvegardePartie* partie, Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4) {
    FILE* fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier de sauvegarde.\n");
        return;
    }

    // Chargement du plateau
    fscanf(fichier, "Plateau :\n");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fscanf(fichier, "%d", &partie->plateau[i][j]);
        }
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




