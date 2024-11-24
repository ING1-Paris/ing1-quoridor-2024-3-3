#include "Menu.h"
#include "Jeu.h"
#include "ScoreCalcul.h"
#include <unistd.h>
#include <string.h>
#include <conio.h>

//Menu principale qui gère les différents menues
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
    printf("          1. Commencer partie\n");
    printf("          2. Continuer partie\n");
    printf("          3. Afficher aide\n");
    printf("          4. Afficher score\n");
    printf("          5. Quitter le jeu\n");
    printf("\n        - Choisissez un menu -");
}

//Menu pour choisir la fonctionnalité souhaitée
bool menuChoisir() {
    char choix;
    do{
        if (_kbhit()) {  // Vérifie si une touche a été pressée
            choix = _getch(); //Récupère la touche saisie par le clavier dans choix
            switch (choix) {
                case '1'://Commencer partie
                    system("cls");
                    executionJeu(menuModeDeJeu(), 0);
                    return 1;
                case '2'://Continuer partie
                    system("cls");
                    FILE *fichier = fopen("../sauvegarde.txt", "r");
                    if(fichier == NULL){ //Vérifie qu'il y a un fichier de sauvegarde avant de faire continuer
                        printf("Erreur : Il n'y a pas de sauvegarde.\n");
                        sleep(2);
                    }else{
                        executionJeu(0, 1);
                    }
                    return 1;
                case '3': //Afficher règles
                    system("cls");
                    reglesAfficher();
                    return 1;
                case '4': //Afficher score
                    system("cls");
                    scoreAfficher();
                    return 1;
                case '5': //Quitter
                    return 0;
            }
        }
    }while(1);
}

//Menu pour choisir le mode de jeu
int menuModeDeJeu() {
    char choix;
    printf("Choisissez votre mode de jeu :\n");
    printf("Tapez 1 : Mode 2 joueurs\n");
    printf("Tapez 2 : Mode 4 joueurs\n");

    do{
        choix = _getch(); //Récupère le touche saisie par le joueur dans choix
        if(choix == '1') { //Mode 2 joueur
            printf("\nVous avez choisi le mode 2 joueurs.");
            sleep(1);
            return 2;
        }else if (choix == '2'){ //Mode 2 joueur
            printf("\nVous avez choisi le mode 4 joueurs.");
            sleep(1);
            return 4;
        }
    }while(1);
}


//Menu pour personnaliser le joueur en début de partie
void menuPersonnalisation(int nombreDeJoueur, char jeton[4], char pseudo[4][21]) {
    for(int i=0; i < nombreDeJoueur; i++) {
        system("cls");
        menuPseudo(i, pseudo);
        jeton[i] = menuJeton();
    }
}

//Menu pour entrer le pseudo du joueur
void menuPseudo(int numero, char pseudo[numero + 1][21]) {
    bool duplicationPseudo;
    do {
        duplicationPseudo = 0; // Réinitialisation pour chaque tentative
        printf("          Joueur %d\n", numero + 1);
        printf("Entrez votre pseudo (20 caracteres maximum) : ");
        fgets(pseudo[numero], 21, stdin);
        pseudo[numero][strcspn(pseudo[numero], "\n")] = '\0'; // Suppression du '\n'
        for (int i = 0; i < numero; i++) {
            //Vérifie que le pseudo ne soit pas écrit en double
            if (!strcmp(pseudo[numero], pseudo[i])) {
                printf("Erreur, ce pseudo est deja inscrit.\n");
                duplicationPseudo = 1;
                sleep(2);
                system("cls");
                break; // Sortir de la boucle dès qu'un doublon est trouvé
            }
        }
    } while (duplicationPseudo);
}

//Menu pour entrer le jeton du joueur
char menuJeton() {
    char choix;
    printf("\nChoisissez votre Pion : \n");
    printf("Tapez 1 : %c\n", 0x03);
    printf("Tapez 2 : %c\n", 0x04);
    printf("Tapez 3 : %c\n", 0x05);
    printf("Tapez 4 : %c\n", 0x06);
    do{
        if (_kbhit()) {  // Vérifie si une touche a été pressée
            choix = _getch();
            switch (choix) {
                case '1'://Commencer partie
                    printf("\nVous avez choisi : %c\n", 0x03);
                    sleep(1);
                    return 0x03; // Coeur
                case '2':
                    printf("\nVous avez choisi : %c\n", 0x04);
                    sleep(1);
                    return 0x04; // Carreau
                case '3': //Afficher règles
                    printf("\nVous avez choisi : %c\n", 0x05);
                    sleep(1);
                    return 0x05; // Trèfle
                case '4': //Afficher score
                    printf("\nVous avez choisi : %c\n", 0x06);
                    sleep(1);
                    return 0x06; // Pique
            }
        }
    }while(1);
}

// Fonction pour afficher les règles du Quoridor
void reglesAfficher() {

    printf("    _    _     _                ____  __        _            \n");
    printf("   / \\  (_) __| | ___          |  _ \\ \\_\\  __ _| | ___  ___  \n");
    printf("  / _ \\ | |/ _` |/ _ \\  _____  | |_) / _ \\/ _` | |/ _ \\/ __| \n");
    printf(" / ___ \\| | (_| |  __/ |_____| |  _ <  __/ (_| | |  __/\\__ \\ \n");
    printf("/_/   \\_\\_|\\__,_|\\___|         |_| \\_\\___|\\__, |_|\___||___/  \n");
    printf("                                          |___/               \n");
    printf("\n********** Aide - Regles du QUORIDOR **********\n\n");
    printf("Objectif :\n");
    printf("    Chaque joueur doit atteindre la ligne opposee du plateau.\n");
    printf("    Le premier joueur a y parvenir gagne la partie.\n\n");
    printf("1. Le jeu se joue sur un plateau de 9x9 cases.\n");
    printf("2. Chaque joueur commence au centre de sa premiere ligne.\n");
    printf("3. Les joueurs se deplacent d'une case a la fois (verticalement ou horizontalement).\n");
    printf("4. Chaque joueur dispose de barrieres qui empechent les autres joueurs d'avancer lorsqu'ils se trouvent devant.\n");
    printf("5. Chaque joueur dispose de 10 barrieres pour une partie a 2 joueurs ou 5 barrieres s'il y a 4 joueurs.\n");
    printf("6. Les barrieres ne doivent pas completement bloquer l'acces a la ligne d'arrivee.\n");
    printf("7. Si un joueur est directement en face de l'autre, il peut sauter par-dessus lui.\n");
    printf("8. Le joueur peut soit se deplacer, soit placer une barriere a chaque tour.\n");
    printf("9. Si la partie est bloquée, par l'inaction des joueurs ou par un blocage complet des barrières, il y a match nul.\n");
    printf("\n************************************************\n\n");
    system("pause");
}

// Fonction menu Score
void scoreAfficher() {
    char pseudo[100][21];
    int scores[100];
    int n = 0;

    // Ouverture du fichier en mode lecture
    FILE *file = fopen("../score.txt", "r");
    if (file == NULL) {
        printf("Erreur: impossible d'ouvrir le fichier.\n");
    }

    // Lecture du fichier et stockage des pseudos et scores
    while (fscanf(file, "%s %d", pseudo[n], &scores[n]) != EOF) {
        n++;
    }
    fclose(file);

    // Tri à bulle pour trier les scores du plus grand au plus petit
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                // Échange des scores
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

                // Échange des pseudos correspondants
                char tempPseudo[100];
                strcpy(tempPseudo, pseudo[j]);
                strcpy(pseudo[j], pseudo[j + 1]);
                strcpy(pseudo[j + 1], tempPseudo);
            }
        }
    }

    // Affichage des résultats
    printf(" _   _ _       _           ____                          \n");
    printf("| | | (_) __ _| |__  ___  / ___|  ___ ___  _ __ ___  ___ \n");
    printf("| |_| | |/ _` | '_ \\/ __| \\___ \\ / __/ _ \\| '__/ _ \\/ __|\n");
    printf("|  _  | | (_| | | | \\__ \\  ___) | (_| (_) | | |  __/\\__ \\\n");
    printf("|_| |_|_|\\__, |_| |_|___/ |____/ \\___\\___/|_|  \\___||___/\n");
    printf("         |___/                                           \n");
    printf("                 Tableau des scores:\n");
    for (int i = 0; i < 5; i++) {
        printf("                     %d : %s %d\n", i + 1, pseudo[i], scores[i]);
    }
    printf("\n        ");
    system("pause");
}