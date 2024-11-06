#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "Menu.h"

int main() {
    bool execution = 1;
    while(execution) {
        execution = menu();
        system("cls");
    }
    return 0;
}

//Fonction qui permet de mettre de la couleur dans la console
void Color(int couleurDuTexte,int couleurDeFond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}