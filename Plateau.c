#include <stdio.h>
#include <stdlib.h>
#define ligne 21
#define colonne 45

void afficher_ligne (int matrice[][colonne], int lignes, int debut, int fin, int intersection) {
    printf("\n  ");
    matrice[lignes][0] = debut; // Premier caractère
    matrice[lignes][colonne] = fin; // Dernier caractère
    //printf("%c", matrice[lignes][1]);

    for (int j = 1; j < colonne; j++) { // Barres Horizontales
        matrice[lignes][j] = 0xC4;
    }

    for (int j = 5; j < colonne; j+=5) { // Barres en 'T'
        matrice[lignes][j] = intersection;
    }

    for (int j = 0; j <= colonne; j++) { // Print de la ligne
        printf("%c", matrice[lignes][j]);
    }

}

void afficher_interligne(int matrice[][colonne], int lignes) {
    printf("\n  ");
    for (int j = 0; j <= colonne; j++) { // Espace
        matrice[lignes][j] = 0x20;
    }
    for (int j = 0; j <= colonne; j+=5) { // Barres Verticales
        matrice[lignes][j] = 0xB3;
    }
    //matrice[lignes][colonne] = 0xB3;
    for (int j = 0; j <= colonne; j++) { // Print de la ligne
        printf("%c", matrice[lignes][j]);
    }
    //printf("%c", matrice[lignes][colonne]);

}

void plateau() {
    system("cls");
    int matrice[ligne][colonne];
    printf("    ");

    for (int i = 1; i < 10; i++) { // Afficher le numéro des colonnes
        matrice[i][1] = i;
        printf("%d    ", matrice[i][1]);

    }

    // Première ligne
    afficher_ligne(matrice, ligne, 0xDA, 0xBF, 0xC2);
    afficher_interligne(matrice, ligne);

    // Toutes les lignes de 2 à 8
    for (int i = 5; i < ligne ; i+=2) { // Initialisation à la troisième car la première c'est les nombres au dessus
        afficher_ligne(matrice, i, 0xC3, 0xB4, 0xC5); //modifier le i++ pour avoir des écarts et insérer les barres verticales
        afficher_interligne(matrice, i);
    }



    // Dernière ligne
    afficher_ligne(matrice, ligne, 0xC0, 0xD9, 0xC1);

}
