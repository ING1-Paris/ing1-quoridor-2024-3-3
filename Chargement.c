#include "Chargement.h"
#include "Sauvegarde.h"
#include "ScoreCalcul.h"
#include <stdlib.h>
#include <string.h>

// FONCTION POUR CHARGER UNE SAUVEGARDE
bool charger_sauvegarde(SauvegardePartie* partie){

    // Pointeur sur le fichier de sauvegarde souhaité
    FILE* fichier = fopen("../sauvegarde.txt", "r");

    //Vérifie que le fichier soit accessible
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    //Initialise "partie" avec les éléments de la sauvegarde
    *partie = iniChargement(fichier);

    //Initialise les éléments du jeu avec les éléments de "partie"

    return 1;
}

// FONCTION POUR CHARGER LES ELEMENTS DE LA SAUVEGARDE DANS "PARTIE"
SauvegardePartie iniChargement(FILE* fichier){

    //Déclare une variable SauvegardePartie qui va contenir les éléments qu'on voudra retourner
    SauvegardePartie partie;

    // Récupération du plateau
    fscanf(fichier, "Plateau :\n");
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fscanf(fichier, "%d", &partie.plateau[i][j]);
        }
    }

    // Récupération du nombre de joueurs
    fscanf(fichier, "\nNombre de joueurs : %d\n", &partie.nb_joueurs);

    // Récupération des pseudos des joueurs
    fscanf(fichier, "Pseudos des joueurs :\n");
    fscanf(fichier, "Joueur 1 : %s\n", partie.J1.pseudo);
    fscanf(fichier, "Joueur 2 : %s\n", partie.J2.pseudo);
    if (partie.nb_joueurs > 2) {
        fscanf(fichier, "Joueur 3 : %s\n", partie.J3.pseudo);
        fscanf(fichier, "Joueur 4 : %s\n", partie.J4.pseudo);
    }

    // Récupération des positions des joueurs
    fscanf(fichier, "Positions des joueurs :\n");
    fscanf(fichier, "Joueur 1 : (%d, %d)\n", &partie.J1.x, &partie.J1.y);
    fscanf(fichier, "Joueur 2 : (%d, %d)\n", &partie.J2.x, &partie.J2.y);
    if (partie.nb_joueurs > 2) {
        fscanf(fichier, "Joueur 3 : (%d, %d)\n", &partie.J3.x, &partie.J3.y);
        fscanf(fichier, "Joueur 4 : (%d, %d)\n", &partie.J4.x, &partie.J4.y);
    }

    // Récupération des barrières restantes
    fscanf(fichier, "Barrières restantes pour chaque joueur :\n");
    fscanf(fichier, "Joueur 1 : %d barrières restantes\n", &partie.J1.nb_barrieres);
    fscanf(fichier, "Joueur 2 : %d barrières restantes\n", &partie.J2.nb_barrieres);
    if (partie.nb_joueurs > 2) {
        fscanf(fichier, "Joueur 3 : %d barrières restantes\n", &partie.J3.nb_barrieres);
        fscanf(fichier, "Joueur 4 : %d barrières restantes\n", &partie.J4.nb_barrieres);
    }

    // Récupération des jetons
    fscanf(fichier, "Jetons de chaque joueur :\n");
    fscanf(fichier, "Jeton joueur 1 : %d\n", &partie.jeton[0]);
    fscanf(fichier, "Jeton joueur 2 : %d\n", &partie.jeton[1]);
    partie.J1.jeton = partie.jeton[0];
    partie.J2.jeton = partie.jeton[1];
    if (partie.nb_joueurs > 2) {
        fscanf(fichier, "Jeton joueur 3 : %d\n", &partie.jeton[2]);
        fscanf(fichier, "Jeton joueur 4 : %d\n", &partie.jeton[3]);
        partie.J3.jeton = partie.jeton[2];
        partie.J4.jeton = partie.jeton[3];
    }

    // Récupération de l'ordre des joueurs
    fscanf(fichier, "Ordre de chaque joueur :\n");
    fscanf(fichier, "1er, joueur numéro : %d\n", &partie.ordre[0]);
    fscanf(fichier, "2nd, joueur numéro : %d\n", &partie.ordre[1]);
    if (partie.nb_joueurs > 2) {
        fscanf(fichier, "3eme, joueur numéro : %d\n", &partie.ordre[2]);
        fscanf(fichier, "4eme, joueur numéro : %d\n", &partie.ordre[3]);
    }

    // Récupération du tour actuel
    fscanf(fichier, "indice du tableau ordre (tour du joueur) : %d\n", &partie.tour_joueur);

    // Récupération du nombre de tours passés
    fscanf(fichier, "Nombre de tour passés : %d\n", &partie.tourPasse);

    fclose(fichier);
    return partie;
}

// FONCTION POUR CHARGER UNE PARTIE
void charger_partie(int plateau[17][17], int* nombreDeJoueur, int* tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4,
                    char jeton[4], int ordre[*nombreDeJoueur], int* tourPasse, SauvegardePartie partie){
    for (int x = 0; x < 17; x++) {
        for (int y = 0; y < 17; y++) {
            plateau[x][y] = partie.plateau[x][y];
        }
    }
    *nombreDeJoueur = partie.nb_joueurs ;
    *tour = partie.tour_joueur;

    *J1 = attribuerJoueur(partie.J1, 1, BLEU);
    *J2 = attribuerJoueur(partie.J2, 2, ROUGE);
    if(*nombreDeJoueur > 2){
        *J3 = attribuerJoueur(partie.J3, 3, JAUNE);
        *J4 = attribuerJoueur(partie.J4, 4, VERT);
    }
    strcpy(jeton, partie.jeton);
    for (int i = 0; i < *nombreDeJoueur; i++) {
        ordre[i] = partie.ordre[i];
    }
    *tourPasse = partie.tourPasse;
}

Joueur attribuerJoueur(Joueur Jsource, int numero, int couleur){
    Joueur J = Jsource;
    J.numero = numero;
    J.couleur = couleur;
    initialisationScore(&J);
    return J;
}