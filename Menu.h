#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H
#include <stdbool.h>
#include <stdio.h>
#include "windows.h"

bool menu();
void menuAfficher();
bool menuChoisir();
void reglesAfficher();
int menuModeDeJeu();
int menuPersonnalisation(int modeDeJeu, char* Jeton, char* pseudo);

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_MENU_H