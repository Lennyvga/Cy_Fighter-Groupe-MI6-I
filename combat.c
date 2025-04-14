#include <stdio.h>
#include "combat.h"

creactionJoueur (Joueur joueur1){
    joueur1.nom = malloc(20 * sizeof(char));
if(joueur1.nom == NULL){
  printf("Erreur d'allocation");
  exit(0);
}

printf("Entrez votre nom :");
scanf("%s", joueur1.nom);
printf("Joueur 1 : %s");
}