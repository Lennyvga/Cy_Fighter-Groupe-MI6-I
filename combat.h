#ifndef COMBAT_H
#define COMBAT_H

#include "perso.h"

void nbJoueur(int *nbJ );
void creationJoueur(Joueur joueur[], int *nbJ);
int fichierPersos(Personnage persos[], const char *nomFichier);
int fichierCompetences(Personnage persos[], const char *nomFichier); 

void afficherPersos(Personnage perso[]);
void choisirPersos( int *nbCombattant, int nbJ, Joueur listeJoueurs[], Personnage perso[]);
//void testPerso(Personnage perso[]);
//void chargement(Personnage perso[], Joueur NomJoueur[], int nbCombattant, Joueur combattant[]);
void chargement(int nbJ, int nbCombattantsEquipe, Joueur listeJoueurs[], Personnage perso[]);

#endif