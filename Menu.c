#include "Menu.h"
#include "Jeu.h"

//Menu principale qui gère les différents menues
//IN : rien
//OUT : 1 si le joueur décide de jouer sinon 0 lorsqu'il décide de quitter
bool menu() {
    menuAfficher();
    return menuChoisir();
}

//Menu qui affiche le menu pricipale
//IN : rien
//OUT : rien
void menuAfficher() {
    printf("  ___                   _     _            \n");
    printf(" / _ \\ _   _  ___  _ __(_) __| | ___  _ __ \n");
    printf("| | | | | | |/ _ \\| '__| |/ _` |/ _ \\| '__|\n");
    printf("| |_| | |_| | (_) | |  | | (_| | (_) | |   \n");
    printf(" \\__\\_\\\\__,_|\\___/|_|  |_|\\__,_|\\___/|_|   \n");
    printf("          Commencer partie\n");
    printf("          Continuer partie\n");
    printf("          Afficher aide\n");
    printf("          Afficher score\n");
    printf("          Quitter le jeu\n");
}

//Menu pour choisir la fonctionnalité souhaitée
//IN : rien
//OUT : menu souhaité (1 : Commencer partie, 2 : continuer, 3 : aides, 4 : Scores, 5: Quitter)
bool menuChoisir() {
    int choix;
    scanf("%d", &choix);
    system("cls");
    switch(choix){
        case 1://Commencer partie
            executionJeu(4);
            return 1;
        case 2:
            //Continuer partie
            return 1;
        case 3: //Afficher règles
            reglesAfficher();
            return 1;
        case 4:
            //menu score
            return 1;
        case 5: //Quitter
            return 0;
        default://Cas où l'entré dans la console ne correspond à rien
            printf("Erreur : Nombre invalide");
            while(getchar()!= '\n');
            return 1;
    }
}

//Menu pour choisir le mode de jeu
//IN : rien
//OUT : mode de jeu (1 : 2 joueurs, 2 : 4 joueurs)
//Non utilisé car doit fonctionner avec MenuPersonnalisation
int menuModeDeJeu() {
    int choix;
    printf("Choissisez votre mode de jeu");
    printf("Tapez 1 : Mode 2 joueurs\n");
    printf("Tapez 2 : Mode 4 joueurs\n");
    scanf("%d", &choix);
    return choix;
}

//Menu pour personnaliser le joueur en début de partie.
//IN : mode de jeu (1 : 2 joueurs, 2 : 4 joueurs)
//OUT : pseudo et pion de chaque joueur
//Non finit car compétences requises trop haut niveau pour l'instant (chaine de caractère)
int menuPersonnalisation(int modeDeJeu) {
    int choix;
    char pseudo, pion;
    for(int i=1; i<=2*modeDeJeu; i++){
        printf("Joueur %d :\n", i);
        printf("Entrez votre pseudo :\n");
        //Scanf chaine de caractère
        do {
            printf("Choisissez votre Pion :\n");
            printf("Tapez 1 : %c\n", 0x03);
            printf("Tapez 2 : %c\n", 0x04);
            printf("Tapez 3 : %c\n", 0x05);
            printf("Tapez 4 : %c\n", 0x06);
            scanf("%d", &choix);
            switch (choix) {
                case 1:
                    //choix coeur
                    break;
                case 2:
                    //choix trèfle
                    break;
                case 3:
                    //choix carreau
                    break;
                case 4 :
                    //choix pique
                    break;
                default :
                    printf("Erreur, rentrez un nombre valide");
                    while(getchar()!= '\n');
            }
        } while(!(choix<5 && choix>0));
    }
}

// Fonction pour Continuer la partie du Quoridor

// Fonction pour afficher les règles du Quoridor
//IN : rien
//OUT :rien
void reglesAfficher() {
    printf("\n********** Aide - Regles du QUORIDOR **********\n\n");
    printf("Objectif :\n");
    printf("    Chaque joueur doit atteindre la ligne opposee du plateau.\n");
    printf("    Le premier joueur a y parvenir gagne la partie.\n\n");
    printf("1. Le jeu se joue sur un plateau de 9x9 cases.\n");
    printf("2. Chaque joueur commence au centre de sa premiere ligne.\n");
    printf("3. Les joueurs se deplacent d'une case a la fois (verticalement ou horizontalement).\n");
    printf("4. Chaque joueur dispose de 10 barrieres pour une partie a 2 joueurs ou 5 barrieres s'il y a 4 joueurs.\n");
    printf("6. Les barrieres ne doivent pas completement bloquer l'acces a la ligne d'arrivee.\n");
    printf("7. Si un joueur est directement en face de l'autre, il peut sauter par-dessus lui.\n");
    printf("8. Le joueur peut soit se deplacer, soit placer une barriere a chaque tour.\n");
    printf("\n***********************************************\n");
    system("pause");
}

// Fonction menu Score

