#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "perso.h"


/*void testPerso(Info perso[]) {
  for (int i = 0; i < 3; i++) {
      printf("Personnage %d :\n", i + 1);
      printf("  Nom      : %s\n", perso[i].nom);
      printf("  PV       : %d\n", perso[i].pv);
      printf("  Attaque  : %d\n", perso[i].attaque);
      printf("  Defense  : %d\n", perso[i].defense);
      printf("  Agilité  : %d\n", perso[i].agilite);
      printf("  Vitesse  : %d\n", perso[i].vitesse);
      printf("\n");
  }
}*/

 void nbJoueur(int *nbJ){
  printf("Nombre de joueur qui jouent : ");
    scanf("%d", nbJ);
while(*nbJ != 1 && *nbJ != 2){
  printf("Veuilez saisir 1 ou 2 joueurs. ");
    scanf("%d", nbJ);
}
  printf("Nombre de joueurs :  %d\n", *nbJ);

}

void creationJoueur (Joueur NomJoueur[], int *nbJ){
for(int i = 0; i< *nbJ; i++){
   NomJoueur[i].nom = malloc(20 * sizeof(char)); // Modification taille tableau nom du joueur
if(NomJoueur[i].nom == NULL){
  printf("Erreur d'allocation");
  exit(1);
  }
}

for(int i = 0; i< *nbJ; i++){
printf("Joueur %d, Entrez votre nom :", i+1);
scanf("%s", NomJoueur[i].nom);
}
for(int i = 0; i< *nbJ; i++){
printf("Joueur %d : %s\n ", i+1, NomJoueur[i].nom);
}
}


void afficherPersos(Info perso[]) {
  printf("Liste des personnages disponibles :\n");
  for (int i = 0; i < 3; i++) {
      printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
             i + 1, perso[i].nom, perso[i].pv, perso[i].attaque,  perso[i].defense, perso[i].agilite, perso[i].vitesse);
  }
}

void choisirPersos(Joueur *joueur){
    int i = 0;
    int num;

    joueur->equipe = malloc(3 * sizeof(int) );
    if( joueur->equipe==NULL){
      printf("Erreur d'allocation");
      exit(2);
    }

    printf("Entrez les numéros des personnages pour votre équipe (entre 1 et 3).\n");
    while (i <3) {
      printf("Choix %d : ", i + 1);
      scanf("%d", &num);

        
     if (num >= 1 && num <= 3) {

            joueur->equipe[i] = num - 1;
            i++;
        } else {
            printf("Numéro invalide, réessayez.\n");
            printf("Choix %d : ", i + 1);
            scanf("%d", &num);
        }
    }
}



