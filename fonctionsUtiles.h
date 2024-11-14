#ifndef BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_FONCTIONSUTILES_H
#define BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_FONCTIONSUTILES_H
#include "windows.h"

//Fonction qui permet de mettre de la couleur dans la console
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond * 16 + couleurDuTexte);
}

#endif //BENOIT_SERGENT_ING1_QUORIDOR_2024_GROUPE3_EQUIPE3_FONCTIONSUTILES_H
