#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structBase.h"
#include "initialisation.h"
#include "deplacements.h"
#include "test.h"
#include "sauvegarde.h"

// Donnees pour la representation du jeu

char piece[6][10] = {"pion", "tour", "fou", "cava", "dame", "roi"};
char abscisses[8] = "ABCDEFGH";
char couleurTab[2][20] = {"\033[31mrouge\033[00m", "\033[34mbleu\033[00m"};
char color[2] = "RB";
char alphabet[8] = "ABCDEFGH";

int main(){      
    struct echiquier plateau = createPlateau();
    FILE* sauvegarde;
    sauvegarde = fopen("sauvegarde.txt", "r");
    struct echiquier* changePlateau = &plateau;
    char fini = fgetc(sauvegarde);
    fgetc(sauvegarde);
    if(fini == '0'){
	initEchiquier(changePlateau);
    } else {
	DLSauvegarde(changePlateau, sauvegarde);
    }
    fclose(sauvegarde);
    int abandon = 1;
    char lecture[10];
    int deplacements = 1;
    int x = -1;
    int y = -1;
    int x0 = -1;
    int y0 = -1;
    int couleur = -1;
    int echec = 0;
    int nbDeplacements = MAJDeplacements(changePlateau, echec, plateau.player);
    while (abandon && plateau.victoire == -1){

	// enregistrement de la partie en cours
	sauvegarde = fopen("sauvegarde.txt","w");
	UPSauvegarde(changePlateau, sauvegarde);
	fclose(sauvegarde);
	
	//system("clear"); // clean du terminal
	echec = testEchec(changePlateau);
	nbDeplacements = MAJDeplacements(changePlateau, echec, plateau.player);
	if((nbDeplacements == 0) && deplacements){
	    printf("Bravo %s vous avait gangez car votre adversaire ne peut plus bouger!\n", couleurTab[(plateau.player + 1)%2]);
	    plateau.victoire = (plateau.player + 1) %2;
	}
	afficherPlateau(changePlateau);
	testVictoire(changePlateau);
	if (plateau.victoire != -1){
	    printf("Bravo %s vous avait gagné!/n", couleurTab[plateau.victoire]);
	}else if(deplacements){ // si on ne cherche pas a deplacer une piece
	    if(echec) {
		printf("ECHEC\nVotre roi est en danger, protégez le!\n");
	    }
	    couleur = plateau.player;
	    printf("Selectionnez la piece que vous voulez bouger/abandon\n");
	    fgets(lecture,10, stdin);
	    // Systeme d'abandon
	    if (strcmp("abandon", lecture) == -10){
		printf("annuler ou la couleur de vos pions (rouge ou bleu)\n");
		char lecture[10];
		fgets(lecture, 10, stdin);
		if (strcmp("rouge",lecture) == -10){
		    printf("Félicitaion \033[34mbleu\033[00m! Vous gagnez par abandon.\n");
		    return 0;
		} else if (strcmp("bleu", lecture) == -10){
		    printf("Félicitation \033[31mrouge\033[00m! Vous gagnez par abandon.\n");
		    return 0;
		}
	    }
	    // Systeme de jeu
	    else {
		x = lecture[0]-65;
		if (x > 7){
		    x = lecture[0] - 97;
		}
		y = lecture[1] - 48;
		if (plateau.plateau[x][y].estVide){
		    printf("La case est vide veuillez recommenser\n");
		} else if(plateau.plateau[x][y].piece.couleur != plateau.player){
		    printf("Hop Hop c'est pas à toi ça!\n");
		} else if(plateau.plateau[x][y].piece.nbDeplacements == 0){
		    printf("Fichtre, cette piece ne peut pas bouger!\n");
		} else {
		    printf("Les différents mouvements sont:\n");
		    afficherDeplacements(plateau.plateau[x][y].piece, changePlateau, 1, -1);
		    x0 = x;
		    y0 = y;
		    deplacements = 0;
		}
	    }
	} else {
	    printf("Veuillez choisir le coup que vous voulez jouer (annuler)\n");
	    fgets(lecture, 10, stdin);
	    if (strcmp(lecture, "annuler") == 10) {
		printf("Mouvement annulé \n");
		afficherDeplacements(plateau.plateau[x][y].piece, changePlateau, 0, couleur);
		plateau.player = couleur;
		deplacements = 1;
	    } else {
		x = lecture[0]-65;
		if (x > 7){
		    x = lecture[0] - 97;
		}
		y = lecture[1] - 48;
		if ((plateau.plateau[x][y].estVide == 0) && (plateau.plateau[x][y].piece.couleur < 0)){
		    afficherDeplacements(plateau.plateau[x][y].piece, changePlateau, 0, couleur);
		    deplacer(x0, y0, x, y, changePlateau);
		    printf("C'est bon \n");
		    plateau.player = (couleur+1)%2;
		    deplacements = 1;
		} else {
		    printf("Ce n'est pas un déplacement autorisé ! Recommence\n");
		}
	    }
	}
    }
    sauvegarde = fopen("sauvegarde.txt","w");
    UPSauvegarde(changePlateau, sauvegarde);
    fclose(sauvegarde);
    return EXIT_SUCCESS;
}
