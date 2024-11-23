#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_CHARGEMENT_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_CHARGEMENT_H

#include "Sauvegarde.h"
#include <stdio.h>

SauvegardePartie iniChargement(FILE* fichier);
bool charger_sauvegarde(SauvegardePartie* partie);
void charger_partie(int plateau[17][17], int* nombreDeJoueur, int* tour, Joueur*J1, Joueur*J2, Joueur*J3, Joueur*J4,
                    char jeton[4], int ordre[*nombreDeJoueur], int* tourPasse, SauvegardePartie P);
Joueur attribuerJoueur(Joueur Jsource, int numero, int couleur);
#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_CHARGEMENT_H
