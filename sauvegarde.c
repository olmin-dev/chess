#include <stdio.h>
#include <stdlib.h>

#include "structBase.h"
#include "initialisation.h"
#include "sauvegarde.h"

char piece[6][10];
char color[2];
char alphabet[8];

struct ligne lectureLigne(FILE* sauv){
    struct ligne sortie;
    char type[4];
    int i = 0;
    char c = fgetc(sauv);
    while (c != ' '){
	type[i] = c;
	i++;
	c = fgetc(sauv);
    }
    if (type[0] == 'p'){
	sortie.type = PION;
    }
    if (type[0] == 't'){
	sortie.type = TOUR;
    }
    if (type[0] == 'c'){
	sortie.type = CAVALIER;
    }
    if (type[0] == 'f'){
	sortie.type = FOU;
    }
    if (type[0] == 'd'){
	sortie.type = DAME;
    }
    if (type[0] == 'r'){
	sortie.type = ROI;
    };
    char couleur = fgetc(sauv);
    if (couleur == 'R'){
	sortie.couleur = 0;
    }
    if (couleur == 'B'){
	sortie.couleur = 1;
    }
    fgetc(sauv);
    char x = fgetc(sauv);
    char y = fgetc(sauv);
    fgetc(sauv);
    if(x < 60){
	sortie.exist = 0;
    } else {
	sortie.exist = 1;
	sortie.x = x - 65;
	sortie.y = y - 48;
    }
    return sortie;
}

void UPSauvegarde(struct echiquier* plateau, FILE* sauv){
    if (plateau->victoire != -1) {
	fprintf(sauv, "0");
    } else {
	fprintf(sauv, "%d\n", plateau->player + 1);
	int ligne = 0;
	for(int i = 0; i<8; i++){
	    for(int j = 0; j<8; j++){
		if(plateau->plateau[i][j].estVide == 0){
		    fprintf(sauv, "%s %c %c%d\n", piece[plateau->plateau[i][j].piece.type], color[plateau->plateau[i][j].piece.couleur], alphabet[i], j);
		    ligne++;
		}
	    }
	}
	if (ligne < 32){
	    for (int k; k + ligne < 32; k++){
	    fprintf(sauv, "ALED R XX\n");
	    }
	}
    }
}

void DLSauvegarde(struct echiquier* plateau, FILE* sauv){
    struct ligne sauvegarde[32];
    for(int i = 0; i<32; i++){
	sauvegarde[i] = lectureLigne(sauv);
    }
    for(int j = 0; j<32; j++){
	if(sauvegarde[j].exist){
	    if(sauvegarde[j].type == PION){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createPion(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	    if(sauvegarde[j].type == TOUR){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createTour(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	    if(sauvegarde[j].type == FOU){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createFou(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	    if(sauvegarde[j].type == CAVALIER){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createCavalier(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	    if(sauvegarde[j].type == DAME){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createDame(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	    if(sauvegarde[j].type == ROI){
		plateau->plateau[sauvegarde[j].x][sauvegarde[j].y].piece = createRoi(sauvegarde[j].x, sauvegarde[j].y, sauvegarde[j].couleur, plateau);
	    }
	}
    }
}
