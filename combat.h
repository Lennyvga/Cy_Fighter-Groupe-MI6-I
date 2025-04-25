#ifndef COMBAT_H
#define COMBAT_H

#include "perso.h"

void nbJoueur(int *nbJ );
void creationJoueur(Joueur joueur[], int *nbJ);
void afficherPersos(Info perso[]);
void choisirPersos(Joueur *joueur, int *nbCombattant, int *nbJ, Joueur NomJoueur[]);
//void testPerso(Info perso[]);


#endif