#include "Mouvement.h"
#include "Souris.h"
#include "Plateau.h"
#include <stdio.h>

//Vérifie que les coordonnées soit comprise dans celle du plateau
bool estDansPlateau(int Y, int X){
    return (X<=16 && X>=0 && Y<=16 && Y>=0);
}

//Vérifie si une case à Y : X contient un joueur ou un mur
bool presenceObjet(int Y, int X, int plateau[17][17]){
    return plateau[Y][X] > 0;
}

bool doublon(int Y, int X, int positionValide[6][2], int nombreElements){
    for(int i = 0; i < nombreElements; i++){
        if(positionValide[i][0] == Y && positionValide[i][1] == X){
            return 1;
        }
    }
    return 0;
}

//Ajoute les coordonnées dans positionValide
void ajouterTableau(int Y, int X, int positionValide[6][2], int *nombreElements){
    if(!doublon(Y, X, positionValide, *nombreElements)){
        *nombreElements += 1;
        positionValide[*nombreElements][0] = Y;
        positionValide[*nombreElements][1] = X;
    }
}

//HAUT : Signe Y = -1, SigneX = 0;
//BAS : Signe Y = 1, SigneX = 0;
//DROITE : Signe Y = 0, SigneX = +1;
//GAUCHE : Signe Y = 0, SigneX = -1;
//Trouve les coordonnées dans le plateau valides
void ChercherPositionsPlateau(int plateau[17][17], int positionValide[6][2], int* nombreElements, int Y, int X, int signeY, int signeX) {

    //Vérifie que les prochaines coordonnées soit dans le plateau
    int nextCaseY = Y + 2*signeY;
    int nextCaseX = X + 2*signeX;
    if (estDansPlateau(nextCaseY, nextCaseX)) {

        //Vérifie que joueur n'est pas face à un mur
        int nextWallY = nextCaseY - signeY;
        int nextWallX = nextCaseX - signeX;
        if (!presenceObjet(nextWallY, nextWallX, plateau)) {

            //Vérifie si la prochaine case est occupé par un joueur
            if (presenceObjet(nextCaseY, nextCaseX, plateau)) {

                //Vérifie si la 2ème prochaine case est séparé par un mur, ou qu'elle soit en dehors du plateau
                int nextNextWallY = nextWallY + 2*signeY;
                int nextNextWallX = nextWallX + 2*signeX;
                int nextNextCaseY = nextCaseY + 2*signeY;
                int nextNextCaseX = nextCaseX + 2*signeX;
                if (presenceObjet(nextNextWallY, nextNextWallX, plateau) || presenceObjet(nextNextCaseY, nextNextCaseX, plateau) ||
                    !estDansPlateau(nextNextCaseY, nextNextCaseX)) {

                    //Vérifie que mur et joueur ne bloque pas le côté gauche
                    int nextLeftWallY = nextCaseY - signeX;
                    int nextLeftWallX = nextCaseX + signeY;
                    int nextLeftCaseY = nextCaseY - 2 * signeX;
                    int nextLeftCaseX = nextCaseX + 2 * signeY;
                    if (!presenceObjet(nextLeftWallY, nextLeftWallX, plateau) &&
                        !presenceObjet(nextLeftCaseY, nextLeftCaseX, plateau)){

                        //Vérifie que la case de gauche ne soit pas en dehors du plateau
                        if (estDansPlateau(nextLeftCaseY, nextLeftCaseX)) {
                            //Ajouter case de gauche dans tableau
                            ajouterTableau(nextLeftCaseY, nextLeftCaseX, positionValide, nombreElements);
                        }
                    }

                    //Vérifie que mur et joueur ne bloque pas le côté droit
                    int nextRightWallY = nextCaseY + signeX;
                    int nextRightWallX = nextCaseX - signeY;
                    int nextRightCaseY = nextCaseY + 2 * signeX;
                    int nextRightCaseX = nextCaseX - 2 * signeY;
                    if (!presenceObjet(nextRightWallY, nextRightWallX, plateau) &&
                        !presenceObjet(nextRightCaseY, nextRightCaseX, plateau)){

                        //Vérifie que la case de droite ne soit pas en dehors du plateau
                        if(estDansPlateau(nextRightCaseY,  nextRightCaseX)){
                            //Ajouter case de droite dans tableau
                            ajouterTableau(nextRightCaseY, nextRightCaseX, positionValide, nombreElements);
                        }
                    }
                } else {
                    //Ajouter Prochaine prochaine case dans tableau
                    ajouterTableau(nextNextCaseY, nextNextCaseX, positionValide, nombreElements);
                }
            } else {
                //Ajouter case dans tableau
                ajouterTableau(nextCaseY, nextCaseX, positionValide, nombreElements);
            }
        }
    }
}

//Trouve toutes les cases valides pour un joueur
int trouverCasesValides(Joueur* J, int plateau[17][17], int positionValide[6][2]) {
    int nombreElements = 0;
    ChercherPositionsPlateau(plateau, positionValide, &nombreElements, J->y, J->x, -1, 0); //Cherche les positions en Haut
    ChercherPositionsPlateau(plateau, positionValide, &nombreElements, J->y, J->x, 1, 0); //Cherche les positions en Bas
    ChercherPositionsPlateau(plateau, positionValide, &nombreElements, J->y, J->x, 0, -1); //Cherche les positions à gauche
    ChercherPositionsPlateau(plateau, positionValide, &nombreElements, J->y, J->x, 0, 1); //Cherche les positions à droite
    return nombreElements;
}

bool deplacerJoueur(Joueur* J, int plateau[17][17], int anciennePosition[2]){
    int positionValide[6][2] = {{-1}}; // 6 : correspond nombre maximal de cases, 2 : Y et X
    int nmbCases = trouverCasesValides(J, plateau, positionValide);
    if (nmbCases == 0) {
        return 0; //Erreur, aucune cases valides
    }
    printf("\n\n   Cliquez sur la case que vous souhaitez selectionner...");
    int newXJ = 0, newYJ = 0;
    souris_joueurs(positionValide, &newXJ, &newYJ);
    J->y = newYJ;
    J->x = newXJ;
    actuPlateauMouv(J, anciennePosition, plateau);
    return 1;
}
/**
// FONCTION POUR DEPLACER LE JOUEUR AVEC LES TOUCHES z, q, s, d
void deplacer_joueur(Joueur* J, int plateau[17][17]) {
    int positionValide[6][2] = {{-1}};
    int nombreDeCases = 0;

    if (J->y > 0 && plateau[J->y - 1][J->x] == 0) { //Vérifie que joueur non au bord ni face à mur
        if (plateau[J->y - 2][J->x] > 0) { //Vérifie si la prochaine case est occupé par un joueur
            if (plateau[J->y - 3][J->x] > 0 ||
                J->y == 2) { //Vérifie si la 2ème prochaine case est séparé par un mur, ou que le joueur soi à y =2
                if (plateau[J->y - 2][J->x + 1] == 0 && plateau[J->y - 2][J->x + 2] == 0 &&
                    J->x < 16) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y - 2;
                    positionValide[nombreDeCases][1] = J->x + 2;
                }
                if (plateau[J->y - 2][J->x - 1] == 0 && plateau[J->y - 2][J->x - 2] == 0 && J->x > 0) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y - 2;
                    positionValide[nombreDeCases][1] = J->x - 2;
                }
            } else {
                nombreDeCases++;
                positionValide[nombreDeCases][0] = J->y - 4;
                positionValide[nombreDeCases][1] = J->x;
            }
        } else {
            nombreDeCases++;
            positionValide[nombreDeCases][0] = J->y - 2;
            positionValide[nombreDeCases][1] = J->x;
        }
    }
    if (J->y < 16 && plateau[J->y + 1][J->x] == 0) { //Vérifie que joueur non au bord ni face à mur
        if (plateau[J->y + 2][J->x] > 0) { //Vérifie si la prochaine case est occupé par un joueur
            if (plateau[J->y + 3][J->x] > 0 ||
                J->y == 14) { //Vérifie si la 2ème prochaine case est séparé par un mur, ou que le joueur soi à y =2
                if (plateau[J->y + 2][J->x + 1] == 0 && plateau[J->y + 2][J->x + 2] == 0 &&
                    J->x < 16) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y + 2;
                    positionValide[nombreDeCases][1] = J->x + 2;
                }
                if (plateau[J->y + 2][J->x - 1] == 0 && plateau[J->y + 2][J->x - 2] == 0 &&
                    J->x > 0) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y + 2;
                    positionValide[nombreDeCases][1] = J->x - 2;
                }
            } else {
                nombreDeCases++;
                positionValide[nombreDeCases][0] = J->y + 4;
                positionValide[nombreDeCases][1] = J->x;
            }
        } else {
            nombreDeCases++;
            positionValide[nombreDeCases][0] = J->y + 2;
            positionValide[nombreDeCases][1] = J->x;
        }
    }
    if (J->x > 0 && plateau[J->y][J->x - 1] == 0) { //Vérifie que joueur non au bord ni face à mur
        if (plateau[J->y][J->x - 2] > 0) { //Vérifie si la prochaine case est occupé par un joueur
            if (plateau[J->y][J->x - 3] > 0 ||
                J->x == 2) { //Vérifie si la 2ème prochaine case est séparé par un mur, ou que le joueur soi à y =2
                if (plateau[J->y + 1][J->x - 2] == 0 && plateau[J->y + 2][J->x - 2] == 0 &&
                    J->y < 16) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y + 2;
                    positionValide[nombreDeCases][1] = J->x - 2;
                }
                if (plateau[J->y - 1][J->x - 2] == 0 && plateau[J->y - 2][J->x - 2] == 0 &&
                    J->y > 0) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y - 2;
                    positionValide[nombreDeCases][1] = J->x - 2;
                }
            } else {
                nombreDeCases++;
                positionValide[nombreDeCases][0] = J->y;
                positionValide[nombreDeCases][1] = J->x - 4;
            }
        } else {
            nombreDeCases++;
            positionValide[nombreDeCases][0] = J->y;
            positionValide[nombreDeCases][1] = J->x - 2;
        }
    }
    if (J->x < 16 && plateau[J->y][J->x + 1] == 0) { //Vérifie que joueur non au bord ni face à mur
        if (plateau[J->y][J->x + 2] > 0) { //Vérifie si la prochaine case est occupé par un joueur
            if (plateau[J->y][J->x + 3] > 0 ||
                J->x == 14) { //Vérifie si la 2ème prochaine case est séparé par un mur, ou que le joueur soi à y =2
                if (plateau[J->y + 1][J->x + 2] == 0 && plateau[J->y + 2][J->x + 2] == 0 &&
                    J->y < 16) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y + 2;
                    positionValide[nombreDeCases][1] = J->x + 2;
                }
                if (plateau[J->y - 1][J->x + 2] == 0 && plateau[J->y - 2][J->x + 2] == 0 &&
                    J->y > 0) { //Vérifie que mur et joueur ne bloque pas côté droit
                    nombreDeCases++;
                    positionValide[nombreDeCases][0] = J->y - 2;
                    positionValide[nombreDeCases][1] = J->x + 2;
                }
            } else {
                nombreDeCases++;
                positionValide[nombreDeCases][0] = J->y;
                positionValide[nombreDeCases][1] = J->x + 4;
            }
        } else {
            nombreDeCases++;
            positionValide[nombreDeCases][0] = J->y;
            positionValide[nombreDeCases][1] = J->x + 2;
        }
    }
}
 **/