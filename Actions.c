#include <conio.h>
#include <stdio.h>
#include "Actions.h"
#include "Affichage.h"
#include "Plateau.h"
#include "Souris.h"
#include "Mouvement.h"
#include "Barrieres.h"

//Fonction pour effectuer l'action du joueur qui joue
char actionsJoueurs(Joueur* J, int plateau[17][17], int* tourPasse, int nombreDeJoueur, char Jetons[4]) {
    char annulation = '0';
    int anciennePosition[2] = {J->y, J->x}; //Pour effacer le jeton à l'ancienne position
    int BX1 = 0, BY1 = 0, BX2 = 0, BY2 = 0; //Positions des barrières
    do {
        char choix = '0';
        do{
            if (_kbhit()) {
                choix = _getch();
                switch (choix) {
                    case '1': // Mouvement
                        *tourPasse = 0;
                        if(!deplacerJoueur(J, plateau, anciennePosition)){
                            printf("\n\n   Erreur : Impossible pour le joueur de se deplacer !");
                            return 'E'; //Erreur, aucune cases valides
                        }
                        break;
                    case '2': //Poser barriere
                        *tourPasse = 0;
                        if(J->nb_barrieres > 0){
                            printf("\n\n   Cliquez donc sur les positions voulues (entre les cases) :");
                            souris_barrieres(&BX1, &BY1, &BX2, &BY2, plateau);
                            ajouterBarriere(plateau, BX1, BY1, BX2, BY2);
                            J->nb_barrieres--;
                        }else{
                            printf("\n\n   Erreur : le joueur n'a plus de barrieres !");
                            return 'E'; //Erreur, plus assez de barrières
                        }
                        break;
                    case '3': //Passer son tour
                        *tourPasse += 1;
                        break;
                    case '4': //Sauvegarde de la partie
                        return 'S';
                }
            }
        }while(!(choix == '1'||choix == '2'||choix == '3'));

        //Affiche les modifications
        affichageJeu(plateau, Jetons, nombreDeJoueur, J);

        //Annulation
        if (annulation == '0') { //Si le joueur n'a pas encore annuler son mouvement, alors on lui laisse le choix
            printf("\n\n   Voulez vous annuler votre coup ? Si oui, tapez 1, sinon tapez sur n'importe quelle autre touche...");
            do {
                if (_kbhit()) {
                    annulation = _getch();
                    if (annulation == '1') { //Annulation du coups
                        annulerCoup(plateau, J, choix, anciennePosition, tourPasse, BX1, BY1, BX2, BY2);
                        affichageJeu(plateau, Jetons, nombreDeJoueur, J);//Reafficher l'ancien plateau
                        printf("\n\n   Retapez alors l'action voulue :");
                    }
                }
            }while(annulation == '0');
        }else {
            break;
        }
    }while(annulation == '1');
    return 0;
}

// Fonction pour annuler le dernier coup
void annulerCoup(int plateau[17][17], Joueur* J, int choix, const int anciennePosition[2], int *tourPasse, int BX1, int BY1, int BX2, int BY2){
    switch(choix){
        case '1': //Action précédente = Mouvement.
            plateau[J->y][J->x] = 0;   //Efface le pion de la nouvelle coordonnées
            J->y = anciennePosition[0]; //Met les coordonnées de J aux anciennes
            J->x = anciennePosition[1];
            plateau[J->y][J->x] = J->numero; //Met le jeton de J aux anciennes coordonnées
            break;
        case '2': //Action précédente = placement barrière
            plateau[BY1][BX1] = 0; //Efface les barrières
            plateau[BY2][BX2] = 0;
            int intersectionY = (BY1+BY2)/2; //Efface les intersections
            int intersectionX = (BX1+BX2)/2;
            plateau[intersectionY][intersectionX] = 0;
            J->nb_barrieres ++;
            break;
        case '3': //Action précédente = passer tour
            *tourPasse -= 1;
            break;
    }
}

/**
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
        if (!isalpha(*lettre) || !1isdigit(*chiffre)) {
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

// FONCTION POUR PLACER LA BARRIERE ET DEMANDER LE SENS
void placer_barriere(Joueur* J, int plateau[17][17]) {
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