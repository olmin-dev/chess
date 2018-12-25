#ifndef _DEPLACEMENTS_
#define _DEPLACEMENTS_ 

// Prototypes de fonctions

int MAJDeplacements(struct echiquier* plateau, int echec, int couleur);

int deplacement(struct piece* piece, struct echiquier* plateau);

int deplacementPiont(struct piece* piece, struct echiquier* plateau);

int deplacementTour(struct piece* piece, struct echiquier* plateau);

int deplacementFou(struct piece* piece, struct echiquier* plateau);

int deplacementCavalier(struct piece* piece, struct echiquier* plateau);

int deplacementDame(struct piece* piece, struct echiquier* plateau);

int deplacementRoi(struct piece* piece, struct echiquier* plateau);

int deplacementEchec(struct piece* piece, struct echiquier* plateau);

int deplacementPiontEchec(struct piece* piece, struct echiquier* plateau);

int deplacementTourEchec(struct piece* piece, struct echiquier* plateau);

int deplacementFouEchec(struct piece* piece, struct echiquier* plateau);

int deplacementCavalierEchec(struct piece* piece, struct echiquier* plateau);

int deplacementDameEchec(struct piece* piece, struct echiquier* plateau);

int deplacementRoiEchec(struct piece* piece, struct echiquier* plateau);

void deplacer(int x1, int y1, int x2, int y2, struct echiquier* plateau);

#endif

