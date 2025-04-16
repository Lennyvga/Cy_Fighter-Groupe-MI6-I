#include <stdio.h>
#include "combat.h"

 nbJoueur(int *nbJ){
  printf("Nombre de joueur qui jouent : ");
    scanf("%d", &nbJ);
while(*nbJ != 1 && *nbJ != 2){
  printf("Veuilez saisir 1 ou 2 joueurs. ");
    scanf("%d", &nbJ);
}
}

 creationJoueur (Joueur joueur[], int *nbJ){
for(int i = 0; i<= *nbJ; i++){
    joueur[i].nom = malloc(20 * sizeof(char));
if(joueur[i].nom == NULL){
  printf("Erreur d'allocation");
  exit(0);
}

printf("Entrez votre nom :");
scanf("%s", joueur[i].nom);
printf("Joueur 1 : %s");

}
}

void afficherPersos(Info perso[], int nombre) {
  printf("Liste des personnages disponibles :\n");
  for (int i = 0; i < nombre; i++) {
      printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
             i + 1, perso[i].nom, perso[i].pv, perso[i].attaque,  perso[i].defense, perso[i].agilite, perso[i].vitesse);
  }
}

