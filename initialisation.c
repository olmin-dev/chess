#include <stdio.h>
#include <stdlib.h>

#include "structBase.h"
#include "initialisation.h"

struct piece createPiece(int x, int y, int type, int couleur){
    struct piece sortie;
    sortie.positionX = x;
    sortie.positionY = y;
    sortie.type = type;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct echiquier createPlateau(){
    struct echiquier sortie;
    sortie.nbBlanc = 0;
    sortie.nbNoir = 0;
    sortie.victoire = -1;
    sortie.player = 0; 
    for (int i = 0; i <8; i++){
	for (int j = 0; j < 8; j++) {
	    sortie.plateau[i][j].x = i;
	    sortie.plateau[i][j].y = j;
	    sortie.plateau[i][j].estVide = 1;
	    sortie.plateau[i][j].piece = createPiece(i, j, -1, 0);
	}
    }    
    return sortie;
}

void initEchiquier(struct echiquier* plateau){
    /*for (int i = 0; i <8; i++){
	plateau->plateau[i][1].piece = createPiont(i, 1, 0, plateau);
	plateau->nbBlanc++;
	plateau->plateau[i][1].estVide = 0;
	plateau->plateau[i][6].piece = createPiont(i, 6, 1, plateau);
	plateau->nbNoir++;
	plateau->plateau[i][6].estVide = 0;
    }*/
    struct piece sortie3 = createTour(0, 0, 0, plateau);
    plateau->plateau[0][0].piece = sortie3;
    struct piece sortie4 = createTour(0, 7, 1, plateau);
    plateau->plateau[0][7].piece = sortie4;
    struct piece sortie5 = createFou(2, 0, 0, plateau);
    plateau->plateau[2][0].piece = sortie5;
    struct piece sortie6 = createFou(2, 7, 1, plateau);
    plateau->plateau[2][7].piece = sortie6;
    struct piece sortie7 = createCavalier(1, 0, 0, plateau);
    plateau->plateau[1][0].piece = sortie7;
    struct piece sortie8 = createCavalier(1, 7, 1, plateau);
    plateau->plateau[1][7].piece = sortie8;
    struct piece sortie9 = createDame(3, 0, 0, plateau);
    plateau->plateau[3][0].piece = sortie9;
    struct piece sortie10 = createDame(4, 7, 1, plateau);
    plateau->plateau[4][7].piece = sortie10;
    struct piece sortie11 = createRoi(4, 0, 0, plateau);
    plateau->plateau[4][0].piece = sortie11;
    struct piece sortie12 = createRoi(3, 7, 1, plateau);
    plateau->plateau[3][7].piece = sortie12;
    struct piece sortie13 = createCavalier(6, 0, 0, plateau);
    plateau->plateau[6][0].piece = sortie13;
    struct piece sortie14 = createCavalier(6, 7, 1, plateau);
    plateau->plateau[6][7].piece = sortie14;
    struct piece sortie15 = createFou(5, 0, 0, plateau);
    plateau->plateau[5][0].piece = sortie15;
    struct piece sortie16 = createFou(5, 7, 1, plateau);
    plateau->plateau[5][7].piece = sortie16;
    struct piece sortie17 = createTour(7, 0, 0, plateau);
    plateau->plateau[7][0].piece = sortie17;
    struct piece sortie18 = createTour(7, 7, 1, plateau);
    plateau->plateau[7][7].piece = sortie18;
}

struct piece createPiont(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 0;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct piece createTour(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 1;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct piece createFou(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 2;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct piece createCavalier(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 3;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct piece createDame(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 4;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}

struct piece createRoi(int i, int j, int couleur, struct echiquier* plateau){
    struct piece sortie;
    plateau->plateau[i][j].estVide = 0;
    sortie.positionX = i;
    sortie.positionY = j;
    sortie.type = 5;
    sortie.couleur = couleur;
    sortie.nbDeplacements = 0;
    return sortie;
}
