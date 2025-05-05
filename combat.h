#ifndef COMBAT_H
#define COMBAT_H

#include "perso.h"

void nbJoueur(int *nbJ );
void creationJoueur(Joueur joueur[], int *nbJ);
int fichierPersos(Info persos[], const char *nomFichier);
void afficherPersos(Info perso[]);
void choisirPersos(Joueur *joueur, int *nbCombattant, int nbJ, Joueur NomJoueur[], Info perso[]);
//void testPerso(Info perso[]);
void combattre(Info perso[], Joueur NomJoueur[], int *numPerso1, int *numPerso2);


#endif