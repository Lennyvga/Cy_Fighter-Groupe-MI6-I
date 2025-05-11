#include <stdio.h>
#include <stdlib.h>
#include "perso.h"
#include "combat.h"
#include <time.h>
#include <string.h>
//#include "verif.h"




int main(){
srand(time(NULL));

int nbJ = 6;

Joueur *listeJoueurs;
Personnage personnage;

int nbCombattantsEquipe = 3;



<<<<<<< HEAD
Personnage *perso = malloc(6 * sizeof(Personnage));
=======
// SK // Personnage *perso = malloc(nbJ * sizeof(Personnage));
Personnage *perso = malloc(nbCombattantsEquipe * sizeof(Personnage));
>>>>>>> 80721b34afa597ea15e15ddc8759d612243e175d
if(perso == NULL){
  printf("Erreur d'allocation - 1 ");
  exit(1);
  };





 nbJoueur(&nbJ);

 

  // Allocation dynamique pour les noms des joueurs
 listeJoueurs =  malloc(nbJ * sizeof(Joueur));
  if(listeJoueurs == NULL){
    printf("Erreur d'allocation - 1 ");
    exit(1);
    }


 
 creationJoueur(listeJoueurs, &nbJ);
 fichierPersos(perso,  "perso.txt");
 fichierCompetences(perso,  "compspe.txt");
 afficherPersos(perso);

 

 choisirPersos( &nbCombattantsEquipe, nbJ, listeJoueurs, perso); 
 




 chargement(nbJ, nbCombattantsEquipe, listeJoueurs, perso);

 for (int i = 0; i < nbJ; i++) {
  free(listeJoueurs[i].nom); // Libérer les noms des joueurs
}




free(listeJoueurs);
<<<<<<< HEAD

return 0;
}
=======
}
>>>>>>> 80721b34afa597ea15e15ddc8759d612243e175d
