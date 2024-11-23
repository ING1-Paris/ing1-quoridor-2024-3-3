#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sauvegarde.h"
#include "Jeu.h"

#define ROUGE 12
#define BLEU 9
#define JAUNE 14
#define VERT 10

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
    fprintf(fichier, "Joueur 1 : %s\n", partie->J1.pseudo);
    fprintf(fichier, "Joueur 2 : %s\n", partie->J2.pseudo);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : %s\n", partie->J3.pseudo);
        fprintf(fichier, "Joueur 4 : %s\n", partie->J4.pseudo);
    }

    // Sauvegarde des positions des joueurs
    fprintf(fichier, "Positions des joueurs :\n");
    fprintf(fichier, "Joueur 1 : (%d, %d)\n", partie->J1.x, partie->J1.y);
    fprintf(fichier, "Joueur 2 : (%d, %d)\n", partie->J2.x, partie->J2.y);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : (%d, %d)\n", partie->J3.x, partie->J3.y);
        fprintf(fichier, "Joueur 4 : (%d, %d)\n", partie->J4.x, partie->J4.y);
    }

    // Sauvegarde des barrières restantes pour chaque joueur
    fprintf(fichier, "Barrières restantes pour chaque joueur :\n");
    fprintf(fichier, "Joueur 1 : %d barrières restantes\n", partie->J1.nb_barrieres);
    fprintf(fichier, "Joueur 2 : %d barrières restantes\n", partie->J2.nb_barrieres);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "Joueur 3 : %d barrières restantes\n", partie->J3.nb_barrieres);
        fprintf(fichier, "Joueur 4 : %d barrières restantes\n", partie->J4.nb_barrieres);
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
    fprintf(fichier, "Ordre de chaque joueur :\n");
    fprintf(fichier, "1er, joueur numéro : %d\n", partie->ordre[0]);
    fprintf(fichier, "2nd, joueur numéro : %d\n", partie->ordre[1]);
    if(partie->nb_joueurs>2){
        fprintf(fichier, "3eme, joueur numéro : %d\n", partie->ordre[2]);
        fprintf(fichier, "4eme, joueur numéro : %d\n", partie->ordre[3]);
    }

    // Sauvegarde du tour actuel
    fprintf(fichier, "indice du tableau ordre (tour du joueur) : %d\n", partie->tour_joueur);

    // Sauvegarde le nombre de tour passés d'affilé
    fprintf(fichier, "Nombre de tour passés : %d\n", partie->tourPasse);

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

// Fonction pour insérer les élements de la partie dans "partie"
SauvegardePartie iniSauvegarde(int plateau[17][17], int nombreDeJoueur, int tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4, char jeton[4], int ordre[nombreDeJoueur], int tourPasse){
    SauvegardePartie P;
    for (int x = 0; x < 17; x++) {
        for (int y = 0; y < 17; y++) {
            P.plateau[x][y] = plateau[x][y];
        }
    }
    P.nb_joueurs = nombreDeJoueur;
    P.tour_joueur = tour;
    P.J1 = *J1;
    P.J2 = *J2;
    if(nombreDeJoueur > 2){
        P.J3 = *J3;
        P.J4 = *J4;
    }
    strcpy(P.jeton, jeton);
    for (int i = 0; i < nombreDeJoueur; i++) {
        P.ordre[i] = ordre[i];
    }
    P.tourPasse = tourPasse;
    return P;
}



