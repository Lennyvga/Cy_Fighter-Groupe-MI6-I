#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "perso.h"




 void nbJoueur(int *nbJ){
  int correct = 0;

while(!correct){
  printf("Nombre de joueur qui jouent : ");
    if (scanf("%d", nbJ) == 1 && (*nbJ == 1 || *nbJ == 2)){
      correct = 1;
    }
    else{
  printf("Erreur. Veuilez saisir 1 ou 2 joueurs.\n ");
    }
    int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
}

}
  //printf("Nombre de joueurs :  %d\n", *nbJ);
 


void creationJoueur (Joueur NomJoueur[], int *nbJ){
for(int i = 0; i< *nbJ; i++){

   NomJoueur[i].nom = malloc(20 * sizeof(char)); // Modification taille tableau nom du joueur avec le nom tampon
if(NomJoueur[i].nom == NULL){
  printf("Erreur d'allocation - 1 ");
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

void choisirPersos(Joueur *combattant, int *nbCombattant, int *nbJ, Joueur NomJoueur[]) {
    int i = 0;
    int num;
    for(int k = 0; k < *nbJ; k++){

    combattant->numEquipe = malloc(*nbCombattant * sizeof(Joueur) ); // tableau de structure
    if( combattant->numEquipe==NULL){
      printf("Erreur d'allocation - 2");
      exit(2);
    }
  }
   
  for(int k = 0; k < *nbJ; k++){
      for (int i = 0; i < *nbCombattant; i++){
        int correct = 0;
      while(!correct){
          printf("Choix %d : ", i + 1);

        printf(" %s, choisissez votre personnage :\n", NomJoueur[k].nom);

        printf("Entrez les numéros des personnages pour votre équipe (entre 1 et 3).\n");
          if (scanf("%d", &num) == 1 && (num == 1 || num == 2 || num == 3)) {
            int dejaChoisi = 0;
            for (int j = 0; j < i; j++) {
                if (combattant->numEquipe[j] == num) {
                    dejaChoisi = 1;
                    break;
                }
            }

            if (dejaChoisi) {
                printf("Ce personnage a déjà été choisi. Veuillez en choisir un autre.\n");
            } else {
                combattant->numEquipe[i] = num; // Stocker le choix
            correct = 1;
          }
        }
          else{
            printf("Erreur. Veuillez choisir un nombre entre 1 et 3.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) ;
          }

          }
        }
         
        
          
      

        // Vérification si le personnage a déjà été choisi
        for (int j = 0; j < i; j++) {
            if (combattant->numEquipe[j] == num) {
                printf("Ce personnage a déjà été choisi. Veuillez en choisir un autre.\n");
                i--; // Réduire le compteur pour redemander le choix
                break;
            }
        }

    printf("\nÉquipe du joueur %d:\n", k); 
    for (int i = 0; i < *nbCombattant; i++) {
        int index = combattant->numEquipe[i];
        printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
               i + 1, perso[index].nom, perso[index].pv, perso[index].attaque,
               perso[index].defense, perso[index].agilite, perso[index].vitesse);
    }
}

}// VERIFIER SI LES TABLEAUX D'EQUIPES SONT BIEN REMPLIS EN FONCTION DE PERSO CHOISIS.


