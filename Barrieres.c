#include "Barrieres.h"

// Fonction qui utilise un algorithme DFS avec pile afin de vérifier si un joueur peut atteindre son objectif
int dfs(int x, int y, int objectifX, int objectifY, int plateau[17][17]) {

    bool caseVisitee[9][9] = {{0}}; // Pour stocker les positions déjà visitées
    int stack[81][2];  // Pile pour stocker les positions (x, y)
    int top = -1; //Initialiser la pile vide (à -1)

    // Ajout de la position initiale dans la pile
    top++;
    stack[top][0] = x;
    stack[top][1] = y;

    // Marquer la case actuelle comme visitée
    caseVisitee[y/2][x/2] = 1;

    while (top >= 0) {
        // Extraire la position courante
        int cx = stack[top][0];
        int cy = stack[top][1];
        top--;

        // Vérifie si la ligne objectif est atteinte
        if (cx == objectifX || cy == objectifY) {
            return 1; // Si l'objectif est atteignable
        }

        // Initialise le tableau avec les futurs positions valides du joueur
        int positionValide[6][2];

        // Initialise le nombre de cases accessible à cx et cy, et applique les positions des cases valides dans positionValide
        int nombreCases = trouverCasesValides(cx, cy, plateau, positionValide);

        // Explorer les cases disponible
        for (int i = 0; i < nombreCases; i++) {
            int nx = positionValide[i][1];
            int ny = positionValide[i][0];

            // Vérifier que la case est non visitée
            if (!caseVisitee[nx/2][ny/2]) {
                caseVisitee[nx/2][ny/2] = 1; // Marquer la case comme visitée
                top++;
                stack[top][0] = nx; // Ajouter à la pile
                stack[top][1] = ny;
            }
        }
    }
    return 0; // Aucun chemin trouvé
}

// Vérifie si un joueur peut atteindre le côté lui permettant de gagner. renvoie 1 si oui, sinon 0
bool objectifRealisable(Joueur* joueur, int objectifX, int objectifY, int plateau[17][17]) {
    return dfs(joueur->x, joueur->y, objectifX, objectifY, plateau);
}

// Test si la barrière bloque un chemin pour un joueur. Si oui renvoie 1, sinon 0
bool blocage(Joueur* J1, Joueur* J2, Joueur* J3, Joueur* J4, int plateau[17][17], int nombreDeJoueur){
    //Initialise etatBlocage, qui enregistre le nombre de joueurs qui joue bloqué
    int etatBlocage = nombreDeJoueur, objectifJ2X = 0, objectifJ2Y = -1;

    //Change les conditions de victoires de J2 en fonction du nombre de joueurs (2Js : x==0, 4Js : y==16)
    if(nombreDeJoueur > 2){
        objectifJ2X = -1;
        objectifJ2Y = 16;
    }

    //Vérifie que les joueurs puissent gagner et modifie etatBlocage
    etatBlocage -= objectifRealisable(J1, 16, -1, plateau);//Test J1
    etatBlocage -= objectifRealisable(J2, objectifJ2X, objectifJ2Y, plateau);//Test J2
    if(nombreDeJoueur > 2){
        etatBlocage -= objectifRealisable(J3, 0, -1, plateau);//Test J3
        etatBlocage-= objectifRealisable(J4, -1, 0, plateau);//Test J4
    }
    return etatBlocage; //Si etatBlocage > 0, alors un des joueurs est bloqué, et envoie donc blocage à 1.
}

