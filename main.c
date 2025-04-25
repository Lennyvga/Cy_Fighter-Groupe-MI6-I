#include <stdio.h>
#include "perso.h"
#include "combat.h"
//#include "verif.h"

int main(){
int nbJ;
Joueur NomJoueur[nbJ];
//Info perso[3];
Joueur joueur;
int nbCombattant =  3;

//testPerso(perso);
 nbJoueur(&nbJ);
 creationJoueur(NomJoueur, &nbJ);
 afficherPersos(perso);
 choisirPersos(&joueur, &nbCombattant, &nbJ, NomJoueur);

}