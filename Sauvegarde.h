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
    Joueur J1; // Structure J1 qui sauvegarde/chargera les éléments de J1
    Joueur J2; // Structure J2 qui sauvegarde/chargera les éléments de J2
    Joueur J3; // Structure J3 qui sauvegarde/chargera les éléments de J3
    Joueur J4; // Structure J4 qui sauvegarde/chargera les éléments de J4
} SauvegardePartie;

SauvegardePartie iniSauvegarde(int plateau[17][17], int nombreDeJoueur, int tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4,
                           char jeton[4], int ordre[nombreDeJoueur], int tourPasse);
bool sauvegarder_partie(SauvegardePartie* partie);
void supprSauvegarde();

#endif //SAUVEGARDE_H
