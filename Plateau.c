#include <stdio.h>
#include "main.h"

#define Cases 9 // nombre de cases par lignes/colonnes
#define BarreH 0xCD // Barres Horizontales
#define BarreV 0xBA // Barres Verticales
#define BarreC 0xCE // Barres Croix
#define Espace 0x20 // Espace

//Fonction qui affiche les bords inférieur et supérieur du plateau
//IN :  angleDebut (hexa ANSI), angleFin (hexa ANSI), intersection (hexa ANSI), ligne(numéro ligne), tableau(plateau)
//OUT : affichage bord supérieur et inférieur
void afficherBord(int angleDebut, int angleFin, int intersection, int ligne, int tableau[17][17]){
    printf("\n   ");     //Décalage pour les lettres
    printf("%c", angleDebut); //Ecriture de l'angle de début
    for (int i =0; i < 2*(Cases - 1); i+=2) { //augmente de 2 par 2 pour accéder à la zone barrière et joueur
        for (int j = 0; j < 4; j++) { //4 barre horizontale pour le côté haut de la première case
            printf("%c", BarreH);
        }
        if(tableau[2*ligne][i+1] >= 5){ //Vérifie qu'une barre en contact avec le bord
            printf("%c", intersection);//S'il y a contact entre barrière et bord, fait un T
        }else{
            printf("%c", BarreH); //Sinon fait une simple barre
        }
    }
    for (int j = 0; j < 4; j++) { //Dernière barrière horizontales
        printf("%c", BarreH);
    }
    printf("%c", angleFin); //Ecriture du dernier angle
}

//Fonction qui les lignes du plateau
//IN :  ligne(numéro ligne), tableau(plateau)
//OUT : affichage des lignes
void afficher_ligne (int tableau[17][17], int ligne) {
    printf("\n   "); //Décalage pour les lettres
    if(tableau[1 + 2*ligne][0] >= 5){ //Vérification si une barrière touche le bord gauche
        printf("%c", 0xCC); //S'il le touche, affiche |-
    }else{
        printf("%c", BarreV); //sinon seulement une barre verticale
    }
    for (int i = 0; i < 2*(Cases - 1); i+=2) {
        if(tableau[1 + 2*ligne][i] >= 5){ //Si une barrière est présente dans le plateau:
            for (int j = 0; j < 4; j++) { //écrit 4 barres horizontales pour la représenter
                printf("%c", BarreH);
            }
        }else{
            for (int j = 0; j < 4; j++) {
                printf("%c", Espace); //Sinon écrit 4 espaces
            }
        }
        switch(tableau[1 + 2*ligne][i+1]){ //Si dans l'intersection entre deux barrières :
            case 5:
                printf("%c", BarreH); //il y a une barrière horizontal (5) la représente
                break;
            case 6:
                printf("%c", BarreV); //il y a une barrière verticale (6) la représente
                break;
            case 7:
                printf("%c", BarreC); //il y a une barrière en croix (7) la représente
                break;
            default :
                printf("%c", 0xFA); //sinon on met un point
        }
    }
    if(tableau[1 + 2*ligne][16] >= 5){ //Si une barrière est présente à la case 16:
        for (int j = 0; j < 4; j++) {
            printf("%c", BarreH); //écrit 4 barres horizontales pour la représenter
        }
    }else{
        for (int j = 0; j < 4; j++) {
            printf("%c", Espace); //Sinon écrit 4 espaces
        }
    }
    if(tableau[1 + 2*ligne][16] >= 5){ //Vérification si une barrière touche le bord droit
        printf("%c", 0xB9); //S'il le touche, affiche -|
    }else{
        printf("%c", BarreV);//sinon seulement une barre verticale
    }
}

//Fonctions qui affiche les interlignes du plateau
//IN :  angleDebut (hexa ANSI), angleFin (hexa ANSI), intersection (hexa ANSI), ligne(numéro ligne), tableau(plateau)
//OUT : affichage des interlignes
void afficher_interligne(int tableau[17][17], int ligne, char lettre, char Jetons[4]){
    printf("\n%c  ", lettre);  //Affichage des lettres pour représenter l'indice des cases
    printf("%c", BarreV); //Affiche le bord gauche
    for (int j = 0; j <= 2*(Cases - 1); j+=2) { //Pour représenter la case sur un espacement de 4n on écrit 2 espaces
        for (int i = 0; i < 2; i++) {   //Pour représenter la case sur un espacement de 4n on écrit d'abord 2 espaces
            printf("%c",  Espace);
        }
        switch(tableau[2*ligne][j]){ //Puis on cherche à savoir si un jour est sur la case du plateau :
            case 1: //Si c'est le joueur 1, on écrit son jeton en bleu foncé
                Color(1, 0);
                printf("%c", Jetons[0]);
                Color(15, 0);
                break;
            case 2: //Si c'est le joueur 2, on écrit son jeton en rouge foncé
                Color(4, 0);
                printf("%c", Jetons[1]);
                Color(15, 0);
                break;
            case 3: //Si c'est le joueur 3, on écrit son jeton en jaune
                Color(14, 0);
                printf("%c", Jetons[2]);
                Color(15, 0);
                break;
            case 4: //Si c'est le joueur 4, on écrit son jeton en vert
                Color(2, 0);
                printf("%c", Jetons[4]);
                Color(15, 0);
                break;
            default :
                printf("%c", Espace); //Sinon on écrit un espace
        }
        printf("%c",  Espace); // Dernier espace pour remplir la case sur 4 caractères
        if (j!=16){
            if(tableau[2*ligne][j+1] >= 5){ //S'il y a contact entre barrière et bord, remplace la barre verticale
                printf("%c", BarreV);
            }else{
                printf("%c", Espace);  //Sinon on écrit un espace
            }
        }
    }
    printf("%c", BarreV);// Barre Verticale représentant le bord droit
}

//Fonctions qui gère les sous-programmes afin d'afficher le plateau
//IN :  angleDebut (hexa ANSI), angleFin (hexa ANSI), intersection (hexa ANSI), tableau(plateau)
//OUT : affichage des interlignes
void affichagePlateau(int ligne, int plateau[17][17], char Jetons[4]){
    if (ligne == 0) {
        printf(" ");
        for (int i = 1; i < 10; i++) {
            printf("    %d", i);
        }
        afficherBord(0xC9, 0xBB, 0xCB, 0, plateau);
    } else if (ligne == 9) {
        afficher_interligne(plateau, 8, 'I', Jetons);
        afficherBord(0xC8, 0xBC, 0xCA, 8, plateau);
    } else {
        afficher_interligne(plateau, ligne-1, 'A' + ligne-1, Jetons);
        afficher_ligne(plateau, ligne-1);
    }
}
