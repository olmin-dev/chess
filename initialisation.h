#ifndef _INITIALISATION_
#define _INITIALISATION_

// Prototypes de fonctions

struct echiquier createPlateau();

void initEchiquier(struct echiquier* plateau);

struct piece createPiont(int i, int j, int couleur, struct echiquier* plateau);

struct piece createTour(int i, int j, int couleur, struct echiquier* plateau);

struct piece createFou(int i, int j, int couleur, struct echiquier* plateau);

struct piece createCavalier(int i, int j, int couleur, struct echiquier* plateau);

struct piece createDame(int i, int j, int couleur, struct echiquier* plateau);

struct piece createRoi(int i, int j, int couleur, struct echiquier* plateau);

#endif
