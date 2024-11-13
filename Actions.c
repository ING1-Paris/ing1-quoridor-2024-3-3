#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jeu.h"
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"

void actionsJoueurs(Joueur* J){
    bool tourDuJoueur;
    while(tourDuJoueur){
        //Mouvement
        //Poser
        //Annuler
        //Passer
    }
}

// FONCTION POUR DEPLACER LE JOUEUR
void deplacer_joueur(Joueur* J) {
    if (_kbhit()) {  // Vérifie si une touche a été pressée
        char deplacement = _getch();

        switch (deplacement) {
            case 'z':  // Déplace le joueur vers le haut
                if (J->y > 0) { // Vérifie que le joueur ne se trouve pas tout en haut du plateau
                    J->y -= 2;
                }
            break;
            case 's':  // Déplace le joueur vers le bas
                if (J->y < 17 - 1) { // Vérifie que le joueur ne se trouve pas tout en bas du plateau
                    J->y += 2;
                }
            break;
            case 'q':  // Déplace le joueur vers la gauche
                if (J->x > 0) { // Vérifie que le joueur ne se trouve pas tout à gauche du plateau
                    J->x -= 2;
                }
            break;
            case 'd':  // Déplace le joueur vers la droite
                if (J->x < 17 - 1) { // Vérifie que le joueur ne se trouve pas tout à droite du plateau
                    J->x += 2;
                }
            break;
        }
    }
}


// FONCTIONS POUR CONVERTIR LES COORDONNEES DU PLATEAU (ex : A1, B5) EN COORDONNEES DE LA MATRICE
int conversion_lettre(char lettre) { // On convertit la lettre en une colonne
    return (lettre - 'A') * 2;
}
int conversion_chiffre(char chiffre) { // On convertit le chiffre en une ligne
    return (chiffre - '1') * 2;
}

// FONCTION POUR PLACER UNE BARRIERE SUR LE PLATEAU
void demander_coordonnees(char* lettre, char* chiffre) {
    do {
        printf("Entrez les coordonnees (exemple : A1) : ");
        scanf(" %c%c", lettre, chiffre);  // Espaces pour ignorer les caractères indésirables

        // Vérification des coordonnées
        if (!isalpha(*lettre) || !isdigit(*chiffre)) {
            printf("Erreur : La coordonnee doit etre une lettre suivie d'un chiffre.\n");
        } else if (*lettre < 'A' || *lettre > 'I') {
            printf("Erreur : La lettre doit etre comprise entre A et I inclus.\n");
        } else if (*chiffre < '1' || *chiffre > '9') {
            printf("Erreur : Le chiffre doit etre compris entre 1 et 9 inclus.\n");
        }
    } while (!(isalpha(*lettre) && isdigit(*chiffre) && (*lettre >= 'A' && *lettre <= 'I') && (*chiffre >= '1' && *chiffre <= '9')));
}

// FONCTION POUR VERIFIER SI LES DEUX CASES SONT COTE A COTE
int cote_a_cote(char lettre1, char chiffre1, char lettre2, char chiffre2) {
    return (abs(lettre1 - lettre2) == 1 && chiffre1 == chiffre2) || (abs(chiffre1 - chiffre2) == 1 && lettre1 == lettre2);
}

// FONCTION
void placer_barriere() {
    char lettre1, chiffre1, lettre2, chiffre2, sens;

    // Saisie et validation des coordonnées de la première case
    printf("Saisie de la 1ere case : \n");
    demander_coordonnees(&lettre1, &chiffre1);

    // Saisie et validation des coordonnées de la deuxième case
    printf("Saisie de la 2eme case : \n");
    demander_coordonnees(&lettre2, &chiffre2);

    // Vérification que les cases sont côte à côte, et ressaisir les coordonnées si ce n'est pas le cas
    while (!cote_a_cote(lettre1, chiffre1, lettre2, chiffre2)) {
        printf("Erreur : Les deux cases ne sont pas cote a cote. Veuillez ressaisir les coordonnees.\n");

        printf("Saisie de la 1ere case :\n");
        demander_coordonnees(&lettre1, &chiffre1);

        printf("Saisie de la 2eme case : \n");
        demander_coordonnees(&lettre2, &chiffre2);
    }

    // Saisie du sens de la barrière
    do {
        printf("Indiquez le sens pour placer la barriere par rapport aux cases (H = haut, B = bas, G = gauche, D = droite) : ");
        scanf(" %c", &sens);  // Espaces pour ignorer d'éventuels caractères indésirables

        // Vérification que le sens est valide
        if (sens != 'H' && sens != 'B' && sens != 'G' && sens != 'D') {
            printf("Erreur : Le sens doit etre l'une des lettres suivantes : H, B, G, D.\n");
        }
    } while (sens != 'H' && sens != 'B' && sens != 'G' && sens != 'D');
}