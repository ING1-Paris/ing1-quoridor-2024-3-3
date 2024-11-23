#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "Jeu.h"

typedef struct {
    int plateau[17][17]; // Le plateau de jeu en l'état actuel
    int nb_joueurs; // Nombre de joueurs
    int tour_joueur; // Le joueur qui doit jouer
    char jeton[4]; // Jetons des joueurs
    int ordre[4]; // Tableau correspondant à l'ordre définit des joueurs
    int tourPasse; // variable qui correspond au nombre de tour passé par le joueur
    Joueur* J1; // Pointeur vers J1
    Joueur* J2; // Pointeur vers J2
    Joueur* J3; // Pointeur vers J3
    Joueur* J4; // Pointeur vers J4
} SauvegardePartie;

SauvegardePartie iniPartie(int plateau[17][17], int nombreDeJoueur, int tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4,
                           char jeton[4], int ordre[nombreDeJoueur], int tourPasse);
void sauvegarder_partie(SauvegardePartie* partie);
void charger_partie(SauvegardePartie* partie);

#endif //SAUVEGARDE_H
