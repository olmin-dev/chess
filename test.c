#include <stdio.h>
#include <stdlib.h>

#include "structBase.h"
#include "initialisation.h"
#include "deplacements.h"
#include "test.h"

char piece[6][10];
char abscisses[8];

void printPlateau(struct echiquier plateau){
    printf("Il y a %d pieces blanches sur le plateau et %d pieces noires\n", plateau.nbRouge, plateau.nbBleu);
    if (plateau.nbRouge + plateau.nbBleu > 0){
	printf("\033[31mLes différentes pieces et leurs positions sont :\033[00m\n");
    } else {
	return;
    }
    for (int i = 7; i>=0; i--){
	for (int j = 7; j>=0; j--){
	    if (plateau.plateau[j][i].estVide == 0 && plateau.plateau[j][i].piece.type != 3){
		printf("%s \t ", piece[plateau.plateau[j][i].piece.type]);
		printf("%c%d\n", abscisses[j], i);
	    } else if (plateau.plateau[j][i].estVide == 0 && plateau.plateau[j][i].piece.type == 3){
		printf("%slier ", piece[plateau.plateau[j][i].piece.type]);
		printf("%c%d\n", abscisses[j], i);
	    }
	}
    }
}

void afficherPlateau(struct echiquier* plateau){
    for (int i =0; i<8; i++){
	    printf("\t-----------------------------------------------------------------\n");
	    printf("\t|\t|\t|\t|\t|\t|\t|\t|\t|\n");
	    printf("    %d\t", i);
	for (int j = 0; j<8; j++){
	    if (plateau->plateau[j][i].estVide == 0){
		if (plateau->plateau[j][i].piece.couleur == 0){
		    if (plateau->plateau[j][i].piece.nbDeplacements && plateau->plateau[j][i].piece.couleur == plateau->player){
			printf("|\033[32m  %s\t\033[00m", piece[plateau->plateau[j][i].piece.type]);
		    } else {
			printf("|\033[31m  %s\t\033[00m", piece[plateau->plateau[j][i].piece.type]);
		    }
		} else if (plateau->plateau[j][i].piece.couleur == 1) {
		    if (plateau->plateau[j][i].piece.nbDeplacements && plateau->plateau[j][i].piece.couleur == plateau->player){
			printf("|\033[32m  %s\t\033[00m", piece[plateau->plateau[j][i].piece.type]);
		    } else {
			printf("|\033[34m  %s\t\033[00m", piece[plateau->plateau[j][i].piece.type]);
		    }
		} else {
		    if (plateau->plateau[j][i].piece.couleur == -1){
			printf("|\033[33m  %s\t\033[00m", piece[plateau->plateau[j][i].piece.type]);	
		    } else {
			printf("|   \033[33mX\033[00m\t");
		    }
		}
	    } else {
		printf("|\t");
	    }
	}
	printf("|");
	printf("\n");
	printf("\t|\t|\t|\t|\t|\t|\t|\t|\t|\n");
    }
    printf("\t-----------------------------------------------------------------\n");
    printf("\t    A       B       C       D       E       F       G       H    \n");
}

void afficherDeplacements(struct piece piece, struct echiquier* plateau, int deplacements, int couleur){
    if(deplacements){ // mettre a jour le plateau pour afficher les changements
	for(int i =0; i<piece.nbDeplacements; i++){ // ajout des cases de déplacements
	    int x = piece.deplacementsX[i];
	    int y = piece.deplacementsY[i];
	    if (plateau->plateau[x][y].estVide){
		plateau->plateau[x][y].estVide = 0;
		plateau->plateau[x][y].piece = createPion(x, y, -2, plateau);
	    } else {
		plateau->plateau[x][y].piece.couleur = -1;
	    }
	}
	plateau->player = -1;
    } else { // Remettre le plateau comme il etait avant pour pouvoir deplacer apres
	for(int i =0; i<8; i++){ // retrait des cases de deplacements
	    for(int j =0; j<8; j++){
		if(plateau->plateau[i][j].estVide == 0){
		    if (plateau->plateau[i][j].piece.couleur == -2){
			plateau->plateau[i][j].estVide = 1;
		    } else if (plateau->plateau[i][j].piece.couleur == -1){
			plateau->plateau[i][j].piece.couleur = (couleur+1)%2;
		    }
		}
	    }
	}
    }	
}

void testVictoire(struct echiquier* plateau){
    int rouge = 0;
    int bleu = 0;
    for(int i = 0; i<8; i++){
	for(int j = 0; j<8; j++){
	    if (plateau->plateau[i][j].piece.type == ROI){
		if (plateau->plateau[i][j].piece.couleur == 0){
		    rouge = 1;
		} else if (plateau->plateau[i][j].piece.couleur == 1){
		    bleu = 1;
		} else {
		    return;
		}
	    }
	}
    }
    if (rouge == 0) {
	plateau->victoire = 1;
    } else if (bleu == 0) {
	plateau->victoire = 0;
    }
}

int testEchec(struct echiquier* plateau){
    MAJDeplacements(plateau, 0, (plateau->player+1)%2);
    int couleur = plateau->player;
    for (int i = 0; i<8; i++){
	for (int j = 0;j<8; j++){
	    if ((plateau->plateau[i][j].estVide == 0) && (plateau->plateau[i][j].piece.couleur == (couleur+1)%2)){
		int n = plateau->plateau[i][j].piece.nbDeplacements;
		for (int k=0; k<n; k++){
		    if((plateau->plateau[plateau->plateau[i][j].piece.deplacementsX[k]][plateau->plateau[i][j].piece.deplacementsY[k]].estVide == 0) && (plateau->plateau[plateau->plateau[i][j].piece.deplacementsX[k]][plateau->plateau[i][j].piece.deplacementsY[k]].piece.type == ROI)){
			return 1;
		    }
		}
	    }
	}
    }
    return 0;
}
