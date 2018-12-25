#ifndef _STRUCT_BASE
#define _STRUCT_BASE

// Definition de constantes

#define DEP_MAX 28

// Enum de bases

enum typePiece {
    NON=-1, PIONT, TOUR, FOU, CAVALIER, DAME, ROI, // ensemble des pieces du jeu
    NB_TYPE                                        // nombre de type de pieces differentes
};

// Structure de bases

struct piece {
    int positionX;                   // position de la piece en abscisses
    int positionY;                   // position de la piece en ordonnées
    enum typePiece type;             // type du piont
    int couleur;                     // 0 = Blanc et 1 = Noir
    int nbDeplacements;              // nombre de dplacements autorise
    int deplacementsX[DEP_MAX];      // ensemble des abscisses des deplacements possibles (à créer à chaque tour avec la fonction deplacement)
    int deplacementsY[DEP_MAX];      // ensemble des ordonnées des deplacements possibles (à créer à chaque tour avec la fonction deplacement)
};

struct cellule {
    int x;               // position en abscisses de a=1 à h=8
    int y;               // position en ordonnées de 1 à 8
    int estVide;         // piece sur la case ou non
    struct piece piece;  // piece sur la case
};

struct echiquier {
    int nbBlanc;                  // nombre de pieces blanches sur le terrain
    int nbNoir;                   // nombre de pieces noires sur le terrain
    struct cellule plateau[8][8]; // ensemble des cases de l'echiquier
    int victoire;                 // -1 = pas de victoire, 0 =  victoire blancs, 1 = victoire noirs
    int player;                   // 0 = blanc doit jouer, 1 = noir doit jouer
};

struct player {
    int couleur; // 0 = blanc et 1 = noir
    char* nom;   // nom du joueur
};
    
#endif
