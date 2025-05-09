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
Joueur *listeJoueurs;
Personnage personnage;
//Joueur joueur;
int nbCombattantsEquipe =  3;



Personnage *perso = malloc(nbJ * sizeof(Personnage));
if(perso == NULL){
  printf("Erreur d'allocation - 1 ");
  exit(1);
  };



int numPerso1, numPerso2;
//Personnage combatant1,combatant2;
 



 /*Personnage perso[3] = {
    {"Guerrier", 100, 20, 15, 10, 10}, //changer et mettre des pourcentage pour l'esquive etc
    {"Mage", 70, 30, 10, 15, 15},
    {"Archer", 80, 25, 12, 20, 20}
  };
*/

//testPerso(perso);
 nbJoueur(&nbJ);

 printf("Nombre de joueurs DANS LE MAIN TEST : %d\n", nbJ);

  // Allocation dynamique pour les noms des joueurs
 listeJoueurs =  malloc(nbJ * sizeof(Joueur));
  if(listeJoueurs == NULL){
    printf("Erreur d'allocation - 1 ");
    exit(1);
    }


 
 creationJoueur(listeJoueurs, &nbJ);
 fichierPersos(perso,  "perso.txt");
 afficherPersos(perso);

 

 choisirPersos( &nbCombattantsEquipe, nbJ, listeJoueurs, perso); 
 




 chargement(nbJ, nbCombattantsEquipe, listeJoueurs, perso);

 for (int i = 0; i < nbJ; i++) {
  free(listeJoueurs[i].nom); // Libérer les noms des joueurs
}




free(listeJoueurs);
}