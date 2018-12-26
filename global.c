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

// Fonction principale: Dissocier l'interface et la gestion de la lecture

int main(){
    // Initialisation du jeu
    
    struct echiquier plateau = createPlateau();
    FILE* sauvegarde;
    sauvegarde = fopen("sauvegarde.txt", "r");
    struct echiquier* changePlateau = &plateau;
    char fini = fgetc(sauvegarde);
    fgetc(sauvegarde);
    if(fini == '0'){
	initEchiquier(changePlateau);
    } else {
	printf("Voulez vous recommencer une partie ? (oui/non)\n");
	char reponse[3];
	fgets(reponse, 10, stdin);
	if(reponse[0] == 'o'){
	    initEchiquier(changePlateau);
	} else {
	    DLSauvegarde(changePlateau, sauvegarde);
	}
    }
    fclose(sauvegarde);

    // Variable de gestions
    
    int abandon = 1; // abandon demande
    char lecture[10]; // interaction utilisateur
    int deplacements = 1; // situation de deplacement ou de choix de pion
    int x = -1; // abscisse de la piece à bouger
    int y = -1; // ordonnee de la piece a bouger
    int x0 = -1; // abscisse de la destination du mouvement
    int y0 = -1; // ordonne de la destination du mouvement
    int couleur = -1; // couleur actuel du joueur
    int rockTab[4] = {1, 1, 1, 1}; // tableau d'aide pour le rock
    int echec = rockTab[0] - 1; // situation d'echec
    int nbDeplacements = MAJDeplacements(changePlateau, echec, plateau.player); // verification de situation d'echec et math
    while (abandon && plateau.victoire == -1){

	// enregistrement de la partie en cours
	sauvegarde = fopen("sauvegarde.txt","w");
	UPSauvegarde(changePlateau, sauvegarde);
	fclose(sauvegarde);

	// Interface de jeu
	system("clear"); // clean du terminal
	echec = testEchec(changePlateau); // test d'echec
	nbDeplacements += MAJDeplacements(changePlateau, echec, plateau.player); // mise à jour des deplacements possibles : rajouter le rock
	if((nbDeplacements == 0) && deplacements){ // pas de deplacements possibles
	    printf("Bravo %s vous avait gangez car votre adversaire ne peut plus bouger!\n", couleurTab[(plateau.player + 1)%2]);
	    plateau.victoire = (plateau.player + 1) %2;
	}
	afficherPlateau(changePlateau); // affichage du plateau
	testVictoire(changePlateau);
	if (plateau.victoire != -1){
	    printf("Bravo %s vous avait gagné!/n", couleurTab[plateau.victoire]);
	}else if(deplacements){ // si on ne cherche pas a deplacer une piece
	    if(echec) { // situation d'echec gere dans le cas general
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
		    plateau.victoire = 0;
		    sauvegarde = fopen("sauvegarde.txt","w");
		    UPSauvegarde(changePlateau, sauvegarde);
		    fclose(sauvegarde);
		    return 0;
		} else if (strcmp("bleu", lecture) == -10){
		    printf("Félicitation \033[31mrouge\033[00m! Vous gagnez par abandon.\n");
		    plateau.victoire = 1;
		    sauvegarde = fopen("sauvegarde.txt","w");
		    UPSauvegarde(changePlateau, sauvegarde);
		    fclose(sauvegarde);
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

		// Mise a jour pour le rock
		if((x0 == 4 && y0 == 0) || (x == 4 && y ==0)){
		    rockTab[0] = 0;
		    rockTab[1] = 0;
		}
		if((x0 == 3 && y0 == 7) || (x == 3 && y ==7)){
		    rockTab[2] = 0;
		    rockTab[3] = 0;
		}
		if((x0 == 0 && y0 == 0) || (x == 0 && y ==0)){
		    rockTab[0] = 0;
		}
		if((x0 == 7 && y0 == 0) || (x == 7 && y ==0)){
		    rockTab[1] = 0;
		}
		if((x0 == 0 && y0 == 7) || (x == 0 && y ==7)){
		    rockTab[2] = 0;
		}
		if((x0 == 7 && y0 == 7) || (x == 7 && y ==7)){
		    rockTab[3] = 0;
		}
		
		if ((plateau.plateau[x][y].estVide == 0) && (plateau.plateau[x][y].piece.couleur < 0)){ // choix correcte: le deplacement s'effectue
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
