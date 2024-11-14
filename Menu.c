#include "Menu.h"
#include "Jeu.h"
#include <unistd.h>

//Menu principale qui gère les différents menues
//IN : rien
//OUT : 1 si le joueur décide de jouer sinon 0 lorsqu'il décide de quitter
bool menu() {
    menuAfficher();
    return menuChoisir();
}

//Menu qui affiche le menu pricipale
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
bool menuChoisir() {
    int choix;
    scanf("%d", &choix);
    system("cls");
    switch(choix) {
        case 1://Commencer partie
            executionJeu(menuModeDeJeu());
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
            sleep(3);
            return 1;
    }
}

//Menu pour choisir le mode de jeu
int menuModeDeJeu() {
    int choix;
    while(1){
        printf("Choissisez votre mode de jeu\n");
        printf("Tapez 1 : Mode 2 joueurs\n");
        printf("Tapez 2 : Mode 4 joueurs\n");
        scanf("%d", &choix);
        system("cls");
        if (choix==1||choix ==2) {
            return choix * 2;
        }
        printf("Erreur, rentrez un nombre valide");
        sleep(2);
        system("cls");
        while(getchar()!= '\n');
    }
}

//Menu pour personnaliser le joueur en début de partie
void menuPersonnalisation(int nombreDeJoueur, char jeton[4], char pseudo[4][20]) {
    for(int i=0; i<nombreDeJoueur; i++) {
        menuPseudo(i, pseudo);
        jeton[i] = menuJeton();
        system("cls");
    }
}

//Menu pour entrer le pseudo du joueur
void menuPseudo(int numero, char pseudo[numero+1][20]){
    bool duplicationPseudo;
    do {
        duplicationPseudo = 0; // Réinitialisation pour chaque tentative
        printf("          Joueur %d\n", numero+1);
        printf("Entrez votre pseudo (20 caracteres maximum) : ");
        while(getchar() != '\n');
        fgets(pseudo[numero], 20, stdin);
        pseudo[numero][strcspn(pseudo[numero], "\n")] = '\0'; // Suppression du '\n'
        for (int i = 0; i < numero; i++) {
            if (!strcmp(pseudo[numero], pseudo[i])) {
                printf("Erreur, ce pseudo est deja inscrit.\n");
                duplicationPseudo = true;
                sleep(2);
                system("cls");
                break; // Sortir de la boucle dès qu'un doublon est trouvé
            }
        }
    } while (duplicationPseudo);
}

//Menu pour entrer le jeton du joueur
char menuJeton() {
    int choix;
    do {
        printf("\nChoisissez votre Pion : \n");
        printf("Tapez 1 : %c\n", 0x03);
        printf("Tapez 2 : %c\n", 0x04);
        printf("Tapez 3 : %c\n", 0x05);
        printf("Tapez 4 : %c\n", 0x06);
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                return 0x03; // Coeur
            case 2:
                return 0x04; // Carreau
            case 3:
                return 0x05; // Trèfle
            case 4 :
                return 0x06; // Pique
            default :
                system("cls");
                printf("Erreur, rentrez un nombre valide");
                while(getchar()!= '\n');
                sleep(2);
        }
    } while(!(choix < 5 && choix > 0));
}

// Fonction pour Continuer la partie du Quoridor

// Fonction pour afficher les règles du Quoridor
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
    printf("\n************************************************\n\n");
    system("pause");
}

// Fonction menu Score
