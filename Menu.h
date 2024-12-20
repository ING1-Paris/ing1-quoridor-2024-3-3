#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H
#include <stdbool.h>
#include <stdio.h>
#include "windows.h"

bool menu();
void menuAfficher();
bool menuChoisir();
int menuModeDeJeu();
void menuPersonnalisation(int nombreDeJoueur, char jeton[4], char pseudo[4][21]);
void menuPseudo(int numero, char pseudo[numero+1][21]);
char menuJeton();
void reglesAfficher();
void scoreAfficher();

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H