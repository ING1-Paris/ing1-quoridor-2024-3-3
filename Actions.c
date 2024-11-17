#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Affichage.h"
#include "Menu.h"
#include "Actions.h"
#include "Plateau.h"
#include "Souris.h"
#include "Mouvement.h"

char actionsJoueurs(Joueur* J, int plateau[17][17], int* tourPasse) {
    int choix,annulation = 0;
    do {
        while(getchar()!= '\n');
        scanf("%d", &choix);
        switch(choix) {
            case 1: // Mouvement
                *tourPasse = 0;
                int positionValide[6][2] = {{-1}}; // 6 : correspond nombre maximal de cases, 2 : Y et X
                int nmbCases = deplacerJoueur(J, plateau, positionValide);
                if (nmbCases==0){
                    printf("\nErreur : Impossible pour le joueur de se deplacer !");
                    return 'E'; //Erreur, aucune cases valides
                }else{
                    printf("\nCliquer sur la case que vous souhaitez selectionner...");
                    int newXJ = 0, newYJ = 0;
                    souris_joueurs(positionValide, &newXJ, &newYJ);
                    int anciennePosition[2] = {J->y, J->x}; //Pour effacer le jeton à l'ancienne position
                    J->y = newYJ;
                    J->x = newXJ;
                    actuPlateauMouv(J, anciennePosition, plateau);
                }
                break;
            case 2: //Poser barriere
                *tourPasse = 0;
                int BX1 = 0, BY1 = 0, BX2 = 0, BY2 = 0;
                souris_barrieres(&BX1, &BY1, &BX2, &BY2);
                break;
            case 3: //Passer son tour
                *tourPasse+= 1;
                break;
            case 4: //Sauvegarde de la partie
                return 'S';
            default://Cas où l'entrée dans la console ne correspond à rien
                printf("\nErreur : Nombre invalide");
                return 'E';
        }
        //Afficher modifications
        if (annulation == 0) {
            printf("\nVoulez vous annuler votre coup ? Si oui, tapez 1, sinon tapez 2 :");
            while(getchar()!= '\n');
            scanf("%d", &annulation);

            if (annulation == 1) {
                //annuler coup //Si passez tour : diminuez tourPasse, si barrière enlever barrière, si déplacement, remettre à ancienne coordonnées
                //Reafficher l'ancien plateau
                printf("\nRetapez alors l'action voulue :");
            }
            else if(annulation != 2) {
                printf("\nErreur : Nombre invalide");
                return 'E';
            }
        }
        else {
            break;
        }
    } while(annulation==1);
    return 0;
}


// FONCTIONS POUR CONVERTIR LES COORDONNEES DU PLATEAU (ex : A1, B5) EN COORDONNEES DE LA MATRICE
int conversion_lettre(char lettre) { // On convertit la lettre en une colonne
    return (lettre - 'A') * 2;
}
int conversion_chiffre(char chiffre) { // On convertit le chiffre en une ligne
    return (chiffre - '1') * 2;
}
/**
// FONCTION POUR DEMANDER LES COORDONNEES DE LA BARRIERE
void demander_coordonnees(char* lettre, char* chiffre) {
    do {
        printf("Entrez les coordonnees (exemple : A1) : ");
        scanf(" %c%c", lettre, chiffre);

        // Vérification des coordonnées rentrées par le joueur
        if (!isalpha(*lettre) || !1isdigit(*chiffre)) {
            printf("Erreur : La coordonnee doit etre une lettre suivie d'un chiffre.\n");
        } else if (*lettre < 'A' || *lettre > 'I') {
            printf("Erreur : La lettre doit etre comprise entre A et I inclus.\n");
        } else if (*chiffre < '1' || *chiffre > '9') {
            printf("Erreur : Le chiffre doit etre compris entre 1 et 9 inclus.\n");
        }
    } while (!(isalpha(*lettre) && isdigit(*chiffre) && (*lettre >= 'A' && *lettre <= 'I') && (*chiffre >= '1' && *chiffre <= '9')));
}
**/
// FONCTION POUR VERIFIER SI LES DEUX CASES SONT COTE A COTE
/*int cote_a_cote(char lettre1, char chiffre1, char lettre2, char chiffre2) {
    return (abs(lettre1 - lettre2) == 1 && chiffre1 == chiffre2) || (abs(chiffre1 - chiffre2) == 1 && lettre1 == lettre2);
}*/
/**
// FONCTION POUR PLACER LA BARRIERE ET DEMANDER LE SENS
/*void placer_barriere(Joueur* J, int plateau[17][17]) {
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
    int aligne_horizontalement = (lettre1 == lettre2);
    int aligne_verticalement = (chiffre1 == chiffre2);

    do {
        printf("Indiquez le sens pour placer la barriere par rapport aux cases (H = haut, B = bas, D = droite, G = gauche) : \n");
        scanf(" %c", &sens);

        // Vérification que le sens est valide
        if ((aligne_horizontalement && (sens != 'H' && sens != 'B')) || (aligne_verticalement && (sens != 'D' && sens != 'G'))) {
            printf("Erreur : le sens est invalide par rapport aux cases. \n");
        }
    } while ((aligne_horizontalement && (sens != 'H' && sens != 'B')) || (aligne_verticalement && (sens != 'D' && sens != 'G')));

    // AFFICHAGE DU PLATEAU AVEC LA BARRIERE PLACEE
    ajouter_barriere(plateau, lettre1, chiffre1, lettre2, chiffre2, sens);

    // MISE A JOUR DES STOCKS DU NOMBRE DE BARRIERES DU JOUEUR
    J->nb_barrieres -= 1;
}
**/
