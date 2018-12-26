#include <stdio.h>
#include <stdlib.h>

#include "structBase.h"
#include "deplacements.h"
#include "test.h"

int MAJDeplacements(struct echiquier* plateau, int echec, int couleur){
    int sortie=0;
    if(echec == 0){
	for (int i =0; i<8; i++){
	    for (int j = 0; j<8; j++){
		if((plateau->plateau[j][i].estVide == 0) && (plateau->plateau[j][i].piece.couleur == couleur)){
		    sortie += deplacement(&(plateau->plateau[j][i].piece), plateau);
		    //printf("(%d, %d) \t (%d, %d) \t %d \t %d\n", plateau.plateau[j][i].piece.positionX, plateau.plateau[j][i].piece.positionY, plateau.plateau[j][i].x, plateau.plateau[j][i].y, plateau.plateau[j][i].piece.nbDeplacements, plateau.plateau[j][i].piece.couleur);
		}
	    }
	}
    } else {
	for (int i =0; i<8; i++){
	    for (int j = 0; j<8; j++){
		if(plateau->plateau[j][i].estVide == 0){
		    sortie += deplacementEchec(&(plateau->plateau[j][i].piece), plateau);
		    //printf("(%d, %d) \t (%d, %d) \t %d \t %d\n", plateau.plateau[j][i].piece.positionX, plateau.plateau[j][i].piece.positionY, plateau.plateau[j][i].x, plateau.plateau[j][i].y, plateau.plateau[j][i].piece.nbDeplacements, plateau.plateau[j][i].piece.couleur);
		}
	    }
	}
    }
    return sortie;
}

int deplacement(struct piece* piece, struct echiquier* plateau){
    int sortie = 0;
    enum typePiece test = piece->type;
    piece->nbDeplacements =0;
    if (test == PION) {
	sortie += deplacementPion(piece, plateau);
	return sortie;
    }
    if (test == TOUR) {
	sortie += deplacementTour(piece, plateau);
	return sortie;
    }
    if (test == FOU) {
	sortie += deplacementFou(piece, plateau);
	return sortie;
    }
    if (test == CAVALIER) {
	sortie += deplacementCavalier(piece, plateau);
	return sortie;
    }
    if (test == DAME) {
	sortie += deplacementDame(piece, plateau);
	return sortie;
    }
    if (test == ROI) {
	sortie += deplacementRoi(piece, plateau);
	return sortie;
    }
    return sortie;
}

int deplacementPion(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    if (piece->couleur == 0){
	if ((plateau->plateau[x][y+1].estVide) && (y < 7)) {
	    piece->nbDeplacements++;
	    piece->deplacementsX[0] = x;
	    piece->deplacementsY[0] = y+1;
	}
	if ((plateau->plateau[x][y+1].estVide) && (y == 1) && (plateau->plateau[x][y+2].estVide)) {
	    piece->nbDeplacements++;
	    piece->deplacementsX[1] = x;
	    piece->deplacementsY[1] = y + 2;
	}
	if ((x<7 && y<7) && (plateau->plateau[x+1][y+1].estVide == 0)){
	    if (plateau->plateau[x+1][y+1].piece.couleur != couleur){
		piece->deplacementsX[piece->nbDeplacements] = x + 1;
		piece->deplacementsY[piece->nbDeplacements] = y + 1;
		piece->nbDeplacements++;
	    }
	}
	if ((x>0 && y<7) && (plateau->plateau[x-1][y+1].estVide == 0)){
	    if (plateau->plateau[x-1][y+1].piece.couleur != couleur){
		piece->deplacementsX[piece->nbDeplacements] = x - 1;
		piece->deplacementsY[piece->nbDeplacements] = y + 1;
		piece->nbDeplacements++;
	    }
	}
    } else if (piece->couleur == 1) {
	if ((plateau->plateau[x][y-1].estVide) && (y > 0)) {
	    piece->nbDeplacements++;
	    piece->deplacementsX[0] = x;
	    piece->deplacementsY[0] = y-1;
	}
	if ((plateau->plateau[x][y-1].estVide) && (y == 6) && (plateau->plateau[x][y-2].estVide)) {
	    piece->nbDeplacements++;
	    piece->deplacementsX[1] = x;
	    piece->deplacementsY[1] = y - 2;
	}
	if ((y<7 && x>0) && (plateau->plateau[x-1][y-1].estVide == 0)){
	    if (plateau->plateau[x-1][y-1].piece.couleur != couleur){
		piece->deplacementsX[piece->nbDeplacements] = x - 1;
		piece->deplacementsY[piece->nbDeplacements] = y - 1;
		piece->nbDeplacements++;
	    }
	}
	if ((y>0 && x<7) && (plateau->plateau[x+1][y-1].estVide == 0)){
	    if (plateau->plateau[x+1][y-1].piece.couleur != couleur){
		piece->deplacementsX[piece->nbDeplacements] = x + 1;
		piece->deplacementsY[piece->nbDeplacements] = y - 1;
		piece->nbDeplacements++;
	    }
	}
    }
    return piece->nbDeplacements;
}

int deplacementTour(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 ; i++){
	if (plateau->plateau[i+x][y].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[i+x][y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 ; i++){
	if (plateau->plateau[x-i][y].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+y<8 ; i++){
	if (plateau->plateau[x][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x][y+i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; y-i>=0 ; i++){
	if (plateau->plateau[x][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementFou(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 && i+y<8 ; i++){
	if (plateau->plateau[i+x][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = i + y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[i+x][i + y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = i + y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && i+y<8 ; i++){
	if (plateau->plateau[x-i][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y+i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+x<8 && y-i>=0; i++){
	if (plateau->plateau[x+i][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x+i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x+i][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x+i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && y-i>=0; i++){
	if (plateau->plateau[x-i][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementCavalier(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    if ((x<7 && y<6) && (plateau->plateau[x+1][y+2].estVide || plateau->plateau[x+1][y+2].piece.couleur != couleur)){ //x+1 et y+2
	piece->deplacementsX[piece->nbDeplacements] = x+1;
	piece->deplacementsY[piece->nbDeplacements] = y+2;
	piece->nbDeplacements++;
    }
    if ((x<6 && y<7) && (plateau->plateau[x+2][y+1].estVide || plateau->plateau[x+2][y+1].piece.couleur != couleur)){ //x+2 et y+1
	piece->deplacementsX[piece->nbDeplacements] = x+2;
	piece->deplacementsY[piece->nbDeplacements] = y+1;
	piece->nbDeplacements++;
    }
    if ((x<7 && y>1) && (plateau->plateau[x+1][y-2].estVide || plateau->plateau[x+1][y-2].piece.couleur != couleur)){ //x+1 et y-2
	piece->deplacementsX[piece->nbDeplacements] = x+1;
	piece->deplacementsY[piece->nbDeplacements] = y-2;
	piece->nbDeplacements++;
    }
    if ((x<6 && y>0) && (plateau->plateau[x+2][y-1].estVide || plateau->plateau[x+2][y-1].piece.couleur != couleur)){ //x+2 et y-1
	piece->deplacementsX[piece->nbDeplacements] = x+2;
	piece->deplacementsY[piece->nbDeplacements] = y-1;
	piece->nbDeplacements++;
    }
    if ((x>0 && y<6) && (plateau->plateau[x-1][y+2].estVide || plateau->plateau[x-1][y+2].piece.couleur != couleur)){ //x-1 et y+2
	piece->deplacementsX[piece->nbDeplacements] = x-1;
	piece->deplacementsY[piece->nbDeplacements] = y+2;
	piece->nbDeplacements++;
    }
    if ((x>1 && y<7) && (plateau->plateau[x-2][y+1].estVide || plateau->plateau[x-2][y+1].piece.couleur != couleur)){ //x-2 et y+1
	piece->deplacementsX[piece->nbDeplacements] = x-2;
	piece->deplacementsY[piece->nbDeplacements] = y+1;
	piece->nbDeplacements++;
    }
    if ((x>0 && y>1) && (plateau->plateau[x-1][y-2].estVide || plateau->plateau[x-1][y-2].piece.couleur != couleur)){ //x-1 et y-2
	piece->deplacementsX[piece->nbDeplacements] = x-1;
	piece->deplacementsY[piece->nbDeplacements] = y-2;
	piece->nbDeplacements++;
    }
    if ((x>1 && y>0) && (plateau->plateau[x-2][y-1].estVide || plateau->plateau[x-2][y-1].piece.couleur != couleur)){ //x-2 et y-1
	piece->deplacementsX[piece->nbDeplacements] = x-2;
	piece->deplacementsY[piece->nbDeplacements] = y-1;
	piece->nbDeplacements++;
    }
    return piece->nbDeplacements;
}

int deplacementDame(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 ; i++){
	if (plateau->plateau[i+x][y].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[i+x][y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 ; i++){
	if (plateau->plateau[x-i][y].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+y<8 ; i++){
	if (plateau->plateau[x][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x][y+i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; y-i>=0 ; i++){
	if (plateau->plateau[x][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
        for(int i = 1; i+x<8 && i+y<8 ; i++){
	if (plateau->plateau[i+x][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = i + y;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[i+x][i + y].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = i + x;
	    piece->deplacementsY[piece->nbDeplacements] = i + y;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && i+y<8 ; i++){
	if (plateau->plateau[x-i][y+i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y+i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y+i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+x<8 && y-i>=0; i++){
	if (plateau->plateau[x+i][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x+i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x+i][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x+i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && y-i>=0; i++){
	if (plateau->plateau[x-i][y-i].estVide){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	} else if (plateau->plateau[x-i][y-i].piece.couleur != couleur){
	    piece->deplacementsX[piece->nbDeplacements] = x-i;
	    piece->deplacementsY[piece->nbDeplacements] = y-i;
	    piece->nbDeplacements++;
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementRoi(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    piece->nbDeplacements = 0;
    if ((x<7) && (plateau->plateau[x+1][y].estVide || plateau->plateau[x+1][y].piece.couleur != couleur)){ //x+1 et y
	piece->deplacementsX[piece->nbDeplacements] = x+1;
	piece->deplacementsY[piece->nbDeplacements] = y;
	piece->nbDeplacements++;
    }
    if ((x<7 && y>0) && (plateau->plateau[x+1][y-1].estVide || plateau->plateau[x+1][y-1].piece.couleur != couleur)){ //x+1 et y-1
	piece->deplacementsX[piece->nbDeplacements] = x+1;
	piece->deplacementsY[piece->nbDeplacements] = y-1;
	piece->nbDeplacements++;
    }
    if ((y>0) && (plateau->plateau[x][y-1].estVide || plateau->plateau[x][y-1].piece.couleur != couleur)){ //x et y-1
	piece->deplacementsX[piece->nbDeplacements] = x;
	piece->deplacementsY[piece->nbDeplacements] = y-1;
	piece->nbDeplacements++;
    }
    if ((x>0 && y>0) && (plateau->plateau[x-1][y-1].estVide || plateau->plateau[x-1][y-1].piece.couleur != couleur)){ //x-1 et y-1
	piece->deplacementsX[piece->nbDeplacements] = x-1;
	piece->deplacementsY[piece->nbDeplacements] = y-1;
	piece->nbDeplacements++;
    }
    if ((x>0) && (plateau->plateau[x-1][y].estVide || plateau->plateau[x-1][y].piece.couleur != couleur)){ //x-1 et y
	piece->deplacementsX[piece->nbDeplacements] = x-1;
	piece->deplacementsY[piece->nbDeplacements] = y;
	piece->nbDeplacements++;
    }
    if ((x>0 && y<7) && (plateau->plateau[x-1][y+1].estVide || plateau->plateau[x-1][y+1].piece.couleur != couleur)){ //x-1 et y+1
	piece->deplacementsX[piece->nbDeplacements] = x-1;
	piece->deplacementsY[piece->nbDeplacements] = y+1;
	piece->nbDeplacements++;
    }
    if ((y<7) && (plateau->plateau[x][y+1].estVide || plateau->plateau[x][y+1].piece.couleur != couleur)){ //x et y+1
	piece->deplacementsX[piece->nbDeplacements] = x;
	piece->deplacementsY[piece->nbDeplacements] = y+1;
	piece->nbDeplacements++;
    }
    if ((x<7 && y<7) && (plateau->plateau[x+1][y+1].estVide || plateau->plateau[x+1][y+1].piece.couleur != couleur)){ //x+1 et y+1
	piece->deplacementsX[piece->nbDeplacements] = x+1;
	piece->deplacementsY[piece->nbDeplacements] = y+1;
	piece->nbDeplacements++;
    }
    return piece->nbDeplacements;
}

void deplacer(int x1, int y1, int x2, int y2, struct echiquier* plateau){
    struct piece deplacer = plateau->plateau[x1][y1].piece;
    plateau->plateau[x1][y1].estVide = 1;
    if (plateau->plateau[x2][y2].estVide){
	plateau->plateau[x2][y2].estVide = 0;
	plateau->plateau[x2][y2].piece = deplacer;
	plateau->plateau[x2][y2].piece.positionX = x2;
	plateau->plateau[x2][y2].piece.positionY = y2;
    } else {
	plateau->plateau[x2][y2].piece = deplacer;
	plateau->plateau[x2][y2].piece.positionX = x2;
	plateau->plateau[x2][y2].piece.positionY = y2;
    }
}

int deplacementEchec(struct piece* piece, struct echiquier* plateau){
    int sortie = 0;
    enum typePiece test = piece->type;
    piece->nbDeplacements =0;
    if (test == PION) {
	sortie += deplacementPionEchec(piece, plateau);
	return sortie;
    }
    if (test == TOUR) {
	sortie += deplacementTourEchec(piece, plateau);
	return sortie;
    }
    if (test == FOU) {
	sortie += deplacementFouEchec(piece, plateau);
	return sortie;
    }
    if (test == CAVALIER) {
	sortie += deplacementCavalierEchec(piece, plateau);
	return sortie;
    }
    if (test == DAME) {
	sortie += deplacementDameEchec(piece, plateau);
	return sortie;
    }
    if (test == ROI) {
	sortie += deplacementRoiEchec(piece, plateau);
	return sortie;
    }
    return sortie;
}

int deplacementPionEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec = 1;
    piece->nbDeplacements = 0;
    if (piece->couleur == 0){
	if ((plateau->plateau[x][y+1].estVide) && (y < 7)) {
	    deplacer(x, y, x, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	}
	if ((plateau->plateau[x][y+1].estVide) && (y == 1) && (plateau->plateau[x][y+2].estVide)) {
	    deplacer(x, y, x, y+2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y+2;
		piece->nbDeplacements++;
	    }
	}
	if ((x<7 && y<7) && (plateau->plateau[x+1][y+1].estVide == 0)){
	    if (plateau->plateau[x+1][y+1].piece.couleur != couleur){
		struct piece tmp = plateau->plateau[x+1][y+1].piece;
		deplacer(x, y, x+1, y+1, plateau);
		echec = testEchec(plateau);
		deplacer(x+1, y+1, x, y, plateau);
		plateau->plateau[x+1][y+1].estVide = 0;
		plateau->plateau[x+1][y+1].piece = tmp;
		if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x + 1;
		    piece->deplacementsY[piece->nbDeplacements] = y + 1;
		    piece->nbDeplacements++;
		}
	    }
	}
	if ((x>0 && y<7) && (plateau->plateau[x-1][y+1].estVide == 0)){
	    if (plateau->plateau[x-1][y+1].piece.couleur != couleur){
		struct piece tmp = plateau->plateau[x-1][y+1].piece;
		deplacer(x, y, x-1, y+1, plateau);
		echec = testEchec(plateau);
		deplacer(x-1, y+1, x, y, plateau);
		plateau->plateau[x-1][y+1].estVide = 0;
		plateau->plateau[x-1][y+1].piece = tmp;
		if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x - 1;
		    piece->deplacementsY[piece->nbDeplacements] = y + 1;
		    piece->nbDeplacements++;
		}
	    }
	}
    } else if (piece->couleur == 1) {
	if ((plateau->plateau[x][y-1].estVide) && (y > 0)) {
	    deplacer(x, y, x, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	}
	if ((plateau->plateau[x][y-1].estVide) && (y == 6) && (plateau->plateau[x][y-2].estVide)) {
	    deplacer(x, y, x, y-2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-2;
		piece->nbDeplacements++;
	    }
	}
	if ((y<7 && x>0) && (plateau->plateau[x-1][y-1].estVide == 0)){
	    if (plateau->plateau[x-1][y-1].piece.couleur != couleur){
		struct piece tmp = plateau->plateau[x-1][y-1].piece;
		deplacer(x, y, x-1, y-1, plateau);
		echec = testEchec(plateau);
		deplacer(x-1, y-1, x, y, plateau);
		plateau->plateau[x-1][y-1].estVide = 0;
		plateau->plateau[x-1][y-1].piece = tmp;
		if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x - 1;
		    piece->deplacementsY[piece->nbDeplacements] = y - 1;
		    piece->nbDeplacements++;
		}
	    }
	}
	if ((y>0 && x<7) && (plateau->plateau[x+1][y-1].estVide == 0)){
	    if (plateau->plateau[x+1][y-1].piece.couleur != couleur){
		struct piece tmp = plateau->plateau[x+1][y-1].piece;
		deplacer(x, y, x+1, y-1, plateau);
		echec = testEchec(plateau);
		deplacer(x+1, y-1, x, y, plateau);
		plateau->plateau[x+1][y-1].estVide = 0;
		plateau->plateau[x+1][y-1].piece = tmp;
		if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x + 1;
		    piece->deplacementsY[piece->nbDeplacements] = y - 1;
		    piece->nbDeplacements++;
		}
	    }
	}
    }
    return piece->nbDeplacements;
}

int deplacementTourEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec =1;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 ; i++){
	if (plateau->plateau[i+x][y].estVide){
	    deplacer(x, y, x + i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[i+x][y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y].piece;
	    deplacer(x, y, x+i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y, x, y, plateau);
	    plateau->plateau[x+i][y].estVide = 0;
	    plateau->plateau[x+i][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 ; i++){
	if (plateau->plateau[x-i][y].estVide){
	    deplacer(x, y, x-i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	   
	} else if (plateau->plateau[x-i][y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y].piece;
	    deplacer(x, y, x-i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y, x, y, plateau);
	    plateau->plateau[x-i][y].estVide = 0;
	    plateau->plateau[x-i][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x - i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+y<8 ; i++){
	if (plateau->plateau[x][y+i].estVide){
	    deplacer(x, y, x, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	    
	} else if (plateau->plateau[x][y+i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x][y+i].piece;
	    deplacer(x, y, x, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+i, x, y, plateau);
	    plateau->plateau[x][y+i].estVide = 0;
	    plateau->plateau[x][y+i].piece = tmp;
	    if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x;
		    piece->deplacementsY[piece->nbDeplacements] = y+i;
		    piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; y-i>=0 ; i++){
	if (plateau->plateau[x][y-i].estVide){
	    deplacer(x, y, x, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }	    
	} else if (plateau->plateau[x][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x][y-i].piece;
	    deplacer(x, y, x, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-i, x, y, plateau);
	    plateau->plateau[x][y-i].estVide = 0;
	    plateau->plateau[x][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }	   
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementFouEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec = 1;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 && i+y<8 ; i++){
	if (plateau->plateau[i+x][y+i].estVide){
	    deplacer(x, y, x+i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[i+x][i + y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y+i].piece;
	    deplacer(x, y, x+i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y+i, x, y, plateau);
	    plateau->plateau[x+i][y+i].estVide = 0;
	    plateau->plateau[x+i][y+i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +i;
		piece->deplacementsY[piece->nbDeplacements] = y +i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && i+y<8 ; i++){
	if (plateau->plateau[x-i][y+i].estVide){
	    deplacer(x, y, x-i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x-i][y+i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y+i].piece;
	    deplacer(x, y, x-i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y+i, x, y, plateau);
	    plateau->plateau[x-i][y+i].estVide = 0;
	    plateau->plateau[x-i][y+i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -i;
		piece->deplacementsY[piece->nbDeplacements] = y +i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+x<8 && y-i>=0; i++){
	if (plateau->plateau[x+i][y-i].estVide){
	    deplacer(x, y, x+i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x+i][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y-i].piece;
	    deplacer(x, y, x+i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y-i, x, y, plateau);
	    plateau->plateau[x+i][y-i].estVide = 0;
	    plateau->plateau[x+i][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +i;
		piece->deplacementsY[piece->nbDeplacements] = y -i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && y-i>=0; i++){
	if (plateau->plateau[x-i][y-i].estVide){
	    deplacer(x, y, x-i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x-i][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y-i].piece;
	    deplacer(x, y, x-i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y-i, x, y, plateau);
	    plateau->plateau[x-i][y-i].estVide = 0;
	    plateau->plateau[x-i][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -i;
		piece->deplacementsY[piece->nbDeplacements] = y -i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementDameEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec = 1;
    piece->nbDeplacements = 0;
    for(int i = 1; i+x<8 && i+y<8 ; i++){
	if (plateau->plateau[i+x][y+i].estVide){
	    deplacer(x, y, x+i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[i+x][i + y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y+i].piece;
	    deplacer(x, y, x+i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y+i, x, y, plateau);
	    plateau->plateau[x+i][y+i].estVide = 0;
	    plateau->plateau[x+i][y+i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +i;
		piece->deplacementsY[piece->nbDeplacements] = y +i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && i+y<8 ; i++){
	if (plateau->plateau[x-i][y+i].estVide){
	    deplacer(x, y, x-i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x-i][y+i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y+i].piece;
	    deplacer(x, y, x-i, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y+i, x, y, plateau);
	    plateau->plateau[x-i][y+i].estVide = 0;
	    plateau->plateau[x-i][y+i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -i;
		piece->deplacementsY[piece->nbDeplacements] = y +i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+x<8 && y-i>=0; i++){
	if (plateau->plateau[x+i][y-i].estVide){
	    deplacer(x, y, x+i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x+i][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y-i].piece;
	    deplacer(x, y, x+i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y-i, x, y, plateau);
	    plateau->plateau[x+i][y-i].estVide = 0;
	    plateau->plateau[x+i][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +i;
		piece->deplacementsY[piece->nbDeplacements] = y -i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 && y-i>=0; i++){
	if (plateau->plateau[x-i][y-i].estVide){
	    deplacer(x, y, x-i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[x-i][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y-i].piece;
	    deplacer(x, y, x-i, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y-i, x, y, plateau);
	    plateau->plateau[x-i][y-i].estVide = 0;
	    plateau->plateau[x-i][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -i;
		piece->deplacementsY[piece->nbDeplacements] = y -i;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+x<8 ; i++){
	if (plateau->plateau[i+x][y].estVide){
	    deplacer(x, y, x + i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	} else if (plateau->plateau[i+x][y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x+i][y].piece;
	    deplacer(x, y, x+i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+i, y, x, y, plateau);
	    plateau->plateau[x+i][y].estVide = 0;
	    plateau->plateau[x+i][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; x-i>=0 ; i++){
	if (plateau->plateau[x-i][y].estVide){
	    deplacer(x, y, x-i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	   
	} else if (plateau->plateau[x-i][y].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x-i][y].piece;
	    deplacer(x, y, x-i, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-i, y, x, y, plateau);
	    plateau->plateau[x-i][y].estVide = 0;
	    plateau->plateau[x-i][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x - i;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; i+y<8 ; i++){
	if (plateau->plateau[x][y+i].estVide){
	    deplacer(x, y, x, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y+i;
		piece->nbDeplacements++;
	    }
	    
	} else if (plateau->plateau[x][y+i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x][y+i].piece;
	    deplacer(x, y, x, y+i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+i, x, y, plateau);
	    plateau->plateau[x][y+i].estVide = 0;
	    plateau->plateau[x][y+i].piece = tmp;
	    if(echec == 0){
		    piece->deplacementsX[piece->nbDeplacements] = x;
		    piece->deplacementsY[piece->nbDeplacements] = y+i;
		    piece->nbDeplacements++;
	    }
	    break;
	} else {
	    break;
	}
    }
    for(int i = 1; y-i>=0 ; i++){
	if (plateau->plateau[x][y-i].estVide){
	    deplacer(x, y, x, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-i, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }	    
	} else if (plateau->plateau[x][y-i].piece.couleur != couleur){
	    struct piece tmp = plateau->plateau[x][y-i].piece;
	    deplacer(x, y, x, y-i, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-i, x, y, plateau);
	    plateau->plateau[x][y-i].estVide = 0;
	    plateau->plateau[x][y-i].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-i;
		piece->nbDeplacements++;
	    }	   
	    break;
	} else {
	    break;
	}
    }
    return piece->nbDeplacements;
}

int deplacementCavalierEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec = 1;
    piece->nbDeplacements = 0;
    if ((x<7 && y<6) && (plateau->plateau[x+1][y+2].estVide || plateau->plateau[x+1][y+2].piece.couleur != couleur)){ //x+1 et y+2
	if(plateau->plateau[x+1][y+2].estVide){
	    deplacer(x, y, x+1, y+2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y+2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+1;
		piece->deplacementsY[piece->nbDeplacements] = y+2;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+1][y+2].piece;
	    deplacer(x, y, x+1, y+2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y+2, x, y, plateau);
	    plateau->plateau[x+1][y+2].estVide = 0;
	    plateau->plateau[x+1][y+2].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +1;
		piece->deplacementsY[piece->nbDeplacements] = y +2;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x<6 && y<7) && (plateau->plateau[x+2][y+1].estVide || plateau->plateau[x+2][y+1].piece.couleur != couleur)){ //x+2 et y+1
	if(plateau->plateau[x+2][y+1].estVide){
	    deplacer(x, y, x+2, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+2, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+2;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+2][y+1].piece;
	    deplacer(x, y, x+2, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+2, y+1, x, y, plateau);
	    plateau->plateau[x+2][y+1].estVide = 0;
	    plateau->plateau[x+2][y+1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +2;
		piece->deplacementsY[piece->nbDeplacements] = y +1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x<7 && y>1) && (plateau->plateau[x+1][y-2].estVide || plateau->plateau[x+1][y-2].piece.couleur != couleur)){ //x+1 et y-2
	if(plateau->plateau[x+1][y-2].estVide){
	    deplacer(x, y, x+1, y-2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y-2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+1;
		piece->deplacementsY[piece->nbDeplacements] = y-2;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+1][y-2].piece;
	    deplacer(x, y, x+1, y-2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y-2, x, y, plateau);
	    plateau->plateau[x+1][y-2].estVide = 0;
	    plateau->plateau[x+1][y-2].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +1;
		piece->deplacementsY[piece->nbDeplacements] = y -2;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x<6 && y>0) && (plateau->plateau[x+2][y-1].estVide || plateau->plateau[x+2][y-1].piece.couleur != couleur)){ //x+2 et y-1
	if(plateau->plateau[x+2][y-1].estVide){
	    deplacer(x, y, x+2, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+2, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+2;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+2][y-1].piece;
	    deplacer(x, y, x+2, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+2, y-1, x, y, plateau);
	    plateau->plateau[x+2][y-1].estVide = 0;
	    plateau->plateau[x+2][y-1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +2;
		piece->deplacementsY[piece->nbDeplacements] = y -1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>0 && y<6) && (plateau->plateau[x-1][y+2].estVide || plateau->plateau[x-1][y+2].piece.couleur != couleur)){ //x-1 et y+2
	if(plateau->plateau[x-1][y+2].estVide){
	    deplacer(x, y, x-1, y+2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y+2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-1;
		piece->deplacementsY[piece->nbDeplacements] = y+2;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-1][y+2].piece;
	    deplacer(x, y, x-1, y+2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y+2, x, y, plateau);
	    plateau->plateau[x-1][y+2].estVide = 0;
	    plateau->plateau[x-1][y+2].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -1;
		piece->deplacementsY[piece->nbDeplacements] = y +2;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>1 && y<7) && (plateau->plateau[x-2][y+1].estVide || plateau->plateau[x-2][y+1].piece.couleur != couleur)){ //x-2 et y+1
	if(plateau->plateau[x-2][y+1].estVide){
	    deplacer(x, y, x-2, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-2, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-2;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-2][y+1].piece;
	    deplacer(x, y, x-2, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-2, y+1, x, y, plateau);
	    plateau->plateau[x-2][y+1].estVide = 0;
	    plateau->plateau[x-2][y+1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -2;
		piece->deplacementsY[piece->nbDeplacements] = y +1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>0 && y>1) && (plateau->plateau[x-1][y-2].estVide || plateau->plateau[x-1][y-2].piece.couleur != couleur)){ //x-1 et y-2
	if(plateau->plateau[x-1][y-2].estVide){
	    deplacer(x, y, x-1, y-2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y-2, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-1;
		piece->deplacementsY[piece->nbDeplacements] = y-2;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-1][y-2].piece;
	    deplacer(x, y, x-1, y-2, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y-2, x, y, plateau);
	    plateau->plateau[x-1][y-2].estVide = 0;
	    plateau->plateau[x-1][y-2].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -1;
		piece->deplacementsY[piece->nbDeplacements] = y -2;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>1 && y>0) && (plateau->plateau[x-2][y-1].estVide || plateau->plateau[x-2][y-1].piece.couleur != couleur)){ //x-2 et y-1
	if(plateau->plateau[x-2][y-1].estVide){
	    deplacer(x, y, x-2, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-2, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-2;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-2][y-1].piece;
	    deplacer(x, y, x-2, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-2, y-1, x, y, plateau);
	    plateau->plateau[x-2][y-1].estVide = 0;
	    plateau->plateau[x-2][y-1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -2;
		piece->deplacementsY[piece->nbDeplacements] = y -1;
		piece->nbDeplacements++;
	    }
	}
    }
    return piece->nbDeplacements;
}

int deplacementRoiEchec(struct piece* piece, struct echiquier* plateau){
    int x = piece->positionX;
    int y = piece->positionY;
    int couleur = piece->couleur;
    int echec = 1;
    piece->nbDeplacements = 0;
    if ((x<7) && (plateau->plateau[x+1][y].estVide || plateau->plateau[x+1][y].piece.couleur != couleur)){ //x+1 et y
	if(plateau->plateau[x+1][y].estVide){
	    deplacer(x, y, x+1, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+1;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+1][y].piece;
	    deplacer(x, y, x+1, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y, x, y, plateau);
	    plateau->plateau[x+1][y].estVide = 0;
	    plateau->plateau[x+1][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +1;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x<7 && y>0) && (plateau->plateau[x+1][y-1].estVide || plateau->plateau[x+1][y-1].piece.couleur != couleur)){ //x+1 et y-1
	if(plateau->plateau[x+1][y-1].estVide){
	    deplacer(x, y, x+1, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+1;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+1][y-1].piece;
	    deplacer(x, y, x+1, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y-1, x, y, plateau);
	    plateau->plateau[x+1][y-1].estVide = 0;
	    plateau->plateau[x+1][y-1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +1;
		piece->deplacementsY[piece->nbDeplacements] = y -1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((y>0) && (plateau->plateau[x][y-1].estVide || plateau->plateau[x][y-1].piece.couleur != couleur)){ //x et y-1
	if(plateau->plateau[x][y-1].estVide){
	    deplacer(x, y, x, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x][y-1].piece;
	    deplacer(x, y, x, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y-1, x, y, plateau);
	    plateau->plateau[x][y-1].estVide = 0;
	    plateau->plateau[x][y-1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y -1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>0 && y>0) && (plateau->plateau[x-1][y-1].estVide || plateau->plateau[x-1][y-1].piece.couleur != couleur)){ //x-1 et y-1
	if(plateau->plateau[x-1][y-1].estVide){
	    deplacer(x, y, x-1, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y-1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-1;
		piece->deplacementsY[piece->nbDeplacements] = y-1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-1][y-1].piece;
	    deplacer(x, y, x-1, y-1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y-1, x, y, plateau);
	    plateau->plateau[x-1][y-1].estVide = 0;
	    plateau->plateau[x-1][y-1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -1;
		piece->deplacementsY[piece->nbDeplacements] = y -1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>0) && (plateau->plateau[x-1][y].estVide || plateau->plateau[x-1][y].piece.couleur != couleur)){ //x-1 et y
	if(plateau->plateau[x-1][y].estVide){
	    deplacer(x, y, x-1, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-1;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-1][y].piece;
	    deplacer(x, y, x-1, y, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y, x, y, plateau);
	    plateau->plateau[x-1][y].estVide = 0;
	    plateau->plateau[x-1][y].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -1;
		piece->deplacementsY[piece->nbDeplacements] = y;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x>0 && y<7) && (plateau->plateau[x-1][y+1].estVide || plateau->plateau[x-1][y+1].piece.couleur != couleur)){ //x-1 et y+1
	if(plateau->plateau[x-1][y+1].estVide){
	    deplacer(x, y, x-1, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x-1;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x-1][y+1].piece;
	    deplacer(x, y, x-1, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x-1, y+1, x, y, plateau);
	    plateau->plateau[x-1][y+1].estVide = 0;
	    plateau->plateau[x-1][y+1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x -1;
		piece->deplacementsY[piece->nbDeplacements] = y +1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((y<7) && (plateau->plateau[x][y+1].estVide || plateau->plateau[x][y+1].piece.couleur != couleur)){ //x et y+1
	if(plateau->plateau[x][y+1].estVide){
	    deplacer(x, y, x, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x][y+1].piece;
	    deplacer(x, y, x, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x, y+1, x, y, plateau);
	    plateau->plateau[x][y+1].estVide = 0;
	    plateau->plateau[x][y+1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x;
		piece->deplacementsY[piece->nbDeplacements] = y +1;
		piece->nbDeplacements++;
	    }
	}
    }
    if ((x<7 && y<7) && (plateau->plateau[x+1][y+1].estVide || plateau->plateau[x+1][y+1].piece.couleur != couleur)){ //x+1 et y+1
	if(plateau->plateau[x+1][y+1].estVide){
	    deplacer(x, y, x+1, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y+1, x, y, plateau);
	    if (echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x+1;
		piece->deplacementsY[piece->nbDeplacements] = y+1;
		piece->nbDeplacements++;
	    }
	} else {
	    struct piece tmp = plateau->plateau[x+1][y+1].piece;
	    deplacer(x, y, x+1, y+1, plateau);
	    echec = testEchec(plateau);
	    deplacer(x+1, y+1, x, y, plateau);
	    plateau->plateau[x+1][y+1].estVide = 0;
	    plateau->plateau[x+1][y+1].piece = tmp;
	    if(echec == 0){
		piece->deplacementsX[piece->nbDeplacements] = x +1;
		piece->deplacementsY[piece->nbDeplacements] = y +1;
		piece->nbDeplacements++;
	    }
	}
    }
    return piece->nbDeplacements;
}
