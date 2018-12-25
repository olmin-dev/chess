#ifndef _SAUVEGARDE_
#define _SAUVEGARDE_

#include "structBase.h"

// Structures

struct ligne {
    int couleur;         // la couleur de la piece
    int exist;           // existence de la piece
    int x;               // abscisses de la piece
    int y;               // ordonnees de la piece
    enum typePiece type; // type de la piece
};

// Prototypes de fonctions

struct ligne lectureLigne(FILE* sauv);

void DLSauvegarde(struct echiquier* plateau, FILE* sauv);

void ULSauvegarde(struct echiquier* plateau, FILE* sauv);

#endif
