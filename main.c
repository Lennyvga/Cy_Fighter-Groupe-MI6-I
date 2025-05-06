#include <stdio.h>
#include <stdlib.h>
#include "perso.h"
#include "combat.h"
#include <time.h>
#include <string.h>
//#include "verif.h"

int main(){
srand(time(NULL));
int nbJ = 0;
Joueur *NomJoueur;
Joueur joueur;
int nbCombattant =  3;


Info *perso = malloc(nbJ * sizeof(Info));
if(perso == NULL){
  printf("Erreur d'allocation - 1 ");
  exit(1);
  };



int numPerso1, numPerso2;
//Info combatant1,combatant2;
 



 /*Info perso[3] = {
    {"Guerrier", 100, 20, 15, 10, 10}, //changer et mettre des pourcentage pour l'esquive etc
    {"Mage", 70, 30, 10, 15, 15},
    {"Archer", 80, 25, 12, 20, 20}
  };
*/

//testPerso(perso);
 nbJoueur(&nbJ);

 printf("Nombre de joueurs DANS LE MAIN TEST : %d\n", nbJ);

  // Allocation dynamique pour les noms des joueurs
 NomJoueur =  malloc(nbJ * sizeof(Joueur));
  if(NomJoueur == NULL){
    printf("Erreur d'allocation - 1 ");
    exit(1);
    }


 
 creationJoueur(NomJoueur, &nbJ);
 fichierPersos(perso,  "perso.txt");
 afficherPersos(perso);

 //printf("Nombre de joueurs DANS LE MAIN TEST 2  : %d\n", nbJ);

 choisirPersos(&joueur, &nbCombattant, nbJ, NomJoueur, perso);

 chargement(perso, NomJoueur, &numPerso1, &numPerso2, nbCombattant, &joueur);

 for (int i = 0; i < nbJ; i++) {
  free(NomJoueur[i].nom); // Libérer les noms des joueurs
}




free(NomJoueur);
}