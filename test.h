#ifndef _TEST_
#define _TEST_

// Prototypes de fonctions

void printPlateau(struct echiquier plateau);

void afficherPlateau(struct echiquier* plateau);

void afficherDeplacements(struct piece piece, struct echiquier* plateau, int deplacements, int couleur);

void testVictoire(struct echiquier* plateau);

int testEchec(struct echiquier* plateau);

#endif
