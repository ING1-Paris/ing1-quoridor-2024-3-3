#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include "souris.h"


char actionsJoueurs(Joueur* J) {
    int choix,annulation = 0;
    do {
        while(getchar()!= '\n');
        scanf("%d", &choix);
        switch(choix) {
            case 1: // Mouvement
                souris_joueurs(J);
                break;
            case 2: //Poser barriere
                souris_barrieres();
                break;
            case 3: //Passer son tour
                break;
            case 4: //Sauvegarde de la partie
                return 'S';
            default://Cas où l'entrée dans la console ne correspond à rien
                return 'E';
        }
        //Afficher modifications
        if (annulation == 0) {
            printf("\nVoulez vous annuler votre coup ? Si oui, tapez 1, sinon tapez 2 :");
            scanf("%d", &annulation);

            if (annulation == 1) {
                //annuler coup
                //Reafficher l'ancien plateau
                printf("\nRetapez alors l'action voulue :");
            }else if(annulation != 2){
                return 'E';
            }
        }
        else {
            break;
        }
    } while(annulation==1);
    return 0;
}

// FONCTION POUR DEPLACER LE JOUEUR AVEC LES TOUCHES z, q, s, d
void deplacer_joueur(Joueur* J) {
    int verif = 1;
    do {
        if (_kbhit()) {  // Vérifie si une touche a été pressée
            char deplacement = _getch();

            switch (deplacement) {
                case 'z':  // Déplace le joueur vers le haut
                    if (J->y > 0) { // Vérifie que le joueur ne se trouve pas tout en haut du plateau
                        J->y -= 2;
                        verif = 0;
                    }
                break;
                case 's':  // Déplace le joueur vers le bas
                    if (J->y < 17 - 1) { // Vérifie que le joueur ne se trouve pas tout en bas du plateau
                        J->y += 2;
                        verif = 0;
                    }
                break;
                case 'q':  // Déplace le joueur vers la gauche
                    if (J->x > 0) { // Vérifie que le joueur ne se trouve pas tout à gauche du plateau
                        J->x -= 2;
                        verif = 0;
                    }
                break;
                case 'd':  // Déplace le joueur vers la droite
                    if (J->x < 17 - 1) { // Vérifie que le joueur ne se trouve pas tout à droite du plateau
                        J->x += 2;
                        verif = 0;
                    }
                break;
            }
        }
    } while (verif);
}

// FONCTIONS POUR CONVERTIR LES COORDONNEES DU PLATEAU (ex : A1, B5) EN COORDONNEES DE LA MATRICE
int conversion_lettre(char lettre) { // On convertit la lettre en une colonne
    return (lettre - 'A') * 2;
}
int conversion_chiffre(char chiffre) { // On convertit le chiffre en une ligne
    return (chiffre - '1') * 2;
}

// FONCTION POUR DEMANDER LES COORDONNEES DE LA BARRIERE
void demander_coordonnees(char* lettre, char* chiffre) {
    do {
        printf("Entrez les coordonnees (exemple : A1) : ");
        scanf(" %c%c", lettre, chiffre);

        // Vérification des coordonnées rentrées par le joueur
        if (!isalpha(*lettre) || !isdigit(*chiffre)) {
            printf("Erreur : La coordonnee doit etre une lettre suivie d'un chiffre.\n");
        } else if (*lettre < 'A' || *lettre > 'I') {
            printf("Erreur : La lettre doit etre comprise entre A et I inclus.\n");
        } else if (*chiffre < '1' || *chiffre > '9') {
            printf("Erreur : Le chiffre doit etre compris entre 1 et 9 inclus.\n");
        }
    } while (!(isalpha(*lettre) && isdigit(*chiffre) && (*lettre >= 'A' && *lettre <= 'I') && (*chiffre >= '1' && *chiffre <= '9')));
}

// FONCTION POUR PLACER LA BARRIERE ET DEMANDER LE SENS
void placer_barriere() {
    char lettre1, chiffre1, lettre2, chiffre2, sens;

    // Saisie et validation des coordonnées de la première case
    printf("Saisie de la 1ere case :\n");
    demander_coordonnees(&lettre1, &chiffre1);

    // Saisie et validation des coordonnées de la deuxième case
    printf("Saisie de la 2eme case :\n");
    demander_coordonnees(&lettre2, &chiffre2);

    // Vérification que les cases sont côte à côte
    while (!cote_a_cote(lettre1, chiffre1, lettre2, chiffre2)) {
        printf("Erreur : Les deux cases ne sont pas cote a cote. Veuillez ressaisir les coordonnees.\n");
        printf("Saisie de la 1ere case :\n");
        demander_coordonnees(&lettre1, &chiffre1);
        printf("Saisie de la 2eme case :\n");
        demander_coordonnees(&lettre2, &chiffre2);
    }

    // Saisie du sens de la barrière
    do {
        printf("Indiquez le sens pour placer la barriere par rapport aux cases (H = haut, B = bas, G = gauche, D = droite) : ");
        scanf(" %c", &sens);

        // Vérification que le sens est valide
        if (sens != 'H' && sens != 'B' && sens != 'G' && sens != 'D') {
            printf("Erreur : Le sens doit etre l'une des lettres suivantes : H, B, G, D.\n");
        }
    } while (sens != 'H' && sens != 'B' && sens != 'G' && sens != 'D');
}