#include <stdio.h>
#include <stdlib.h>

#include "structBase.h"
#include "initialisation.h"
#include "sauvegarde.h"

struct ligne lectureLigne(FILE* sauv){
    struct ligne sortie;
    char type[8];
    int i = 0;
    char c = fgetc(sauv);
    while (c != ' '){
	type[i] = c;
	i++;
	c = fgetc(sauv);
    }
    printf("%s\n", type);
    if (type[0] == 'p'){
	sortie.type = PIONT;
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
    char x = fgetc(sauv);
    char y = fgetc(sauv);
    fgetc(sauv);
    printf("%d, %d\n", x, y);
    printf("%d, %d\n", sortie.type, sortie.couleur);
    return sortie;
}
/*
void DLSauvegarde(struct echiquier* plateau, FILE* sauv){
    printf("Aled");    
}

void ULSauvegarde(struct echiquier* plateau, FILE* sauv){
    printf("Aled");
    }*/
