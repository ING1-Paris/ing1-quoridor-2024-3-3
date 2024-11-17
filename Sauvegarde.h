#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

typedef struct {
    int plateau[17][17]; // Le plateau de jeu en l'état actuel
    int positions_joueurs[4][2]; // Positions des joueurs [n° du joueur][position : ligne, colonne]
    int nb_joueurs; // Nombre de joueurs
    char pseudos[4][20]; // Pseudos des joueurs
    int nb_barrieres[4]; // Barrières restantes pour chaque joueur
    int tour_joueur; // Le joueur qui doit jouer
} SauvegardePartie;

#endif //SAUVEGARDE_H
