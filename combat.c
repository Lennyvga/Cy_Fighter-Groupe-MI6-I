#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "perso.h"
#include <unistd.h>// Est ce qu'on a le droit ? C'est pour le sleep

void nettoyerEcran() {
  system("clear");  // Utilise "cls" sur Windows
}


 void nbJoueur(int *nbJ){
  int correct = 0;


while(!correct){
  printf("Nombre de joueur qui jouent : ");
    if (scanf("%d", nbJ) == 1 && (*nbJ == 1 || *nbJ == 2)){
      correct = 1;
    }
    else{
  printf("\nErreur. Veuilez saisir 1 ou 2 joueurs.\n ");
    }
    int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
}

}
  //printf("Nombre de joueurs :  %d\n", *nbJ);
 


void creationJoueur (Joueur NomJoueur[], int *nbJ){
  //printf("Nombre de joueurs : %d\n", *nbJ);

for(int i = 0; i< *nbJ; i++){

   NomJoueur[i].nom = malloc(20 * sizeof(char)); // Modification taille tableau nom du joueur avec le nom tampon
if(NomJoueur[i].nom == NULL){
  printf("Erreur d'allocation - 1 ");
  exit(1);
  }
}

for(int i = 0; i< *nbJ; i++){
printf("\nJoueur %d, Entrez votre nom : ", i+1);
scanf("%s", NomJoueur[i].nom);
}
for(int i = 0; i< *nbJ; i++){
printf("\n\nJoueur %d : %s\n ", i+1, NomJoueur[i].nom);
}
}

int fichierPersos(Info persos[], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        printf("\nLe fichier %s est ouvert  \n", nomFichier);
    }
    else {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return -1;
    }

    /*for (int i = 0; i < 3; i++) {
      persos[i].nom = malloc(50 * sizeof(char)); // Allouer de la mémoire pour le nom
      if (persos[i].nom == NULL) {
          printf("Erreur d'allocation mémoire pour le nom du personnage.\n");
          exit(1);
      }
  }*/

    for (int i = 0; i < 3; i++) {
       if( fscanf(fichier, "%s %d %d %d %d %d",
               persos[i].nom,
               &persos[i].pv,
               &persos[i].attaque,
               &persos[i].defense,
               &persos[i].agilite,
               &persos[i].vitesse) != 6) {
            printf("Erreur de lecture du fichier %s\n", nomFichier);
            fclose(fichier);
            return -1;};
    }

    fclose(fichier);
    return 0;
}


void afficherPersos(Info perso[]) {
  printf("\nListe des personnages disponibles :\n");
  for (int i = 0; i < 3; i++) {
      printf("\n%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
             i + 1, perso[i].nom, perso[i].pv, perso[i].attaque,  perso[i].defense, perso[i].agilite, perso[i].vitesse);
  }
}





void choisirPersos(Joueur *combattant, int *nbCombattant, int nbJ, Joueur NomJoueur[], Info perso[]) {
    int i = 0;
    int num;
    
    for(int k = 0; k < nbJ; k++){
    combattant[k].numEquipe = malloc(*nbCombattant * sizeof(int) ); // tableau de structure
    if( combattant[k].numEquipe==NULL){
      printf("Erreur d'allocation - 2");
      exit(2);
    }
  }
  printf("\n\nNombre de joueurs dans la partie : %d\n", nbJ);
   
  for(int k = 0; k < nbJ; k++){
      for (int i = 0; i < *nbCombattant; i++){
        int correct = 0;
      while(!correct){
          printf("------------------------------------------------------------Choix %d ------------------------------------------------------------\n ", i + 1);

        printf(" %s, choisissez votre personnage :\n", NomJoueur[k].nom);

        printf("Entrez les numéros des personnages pour votre équipe (entre 1 et 3).\n");
          if (scanf("%d", &num) == 1 && (num == 1 || num == 2 || num == 3)) {
            int dejaChoisi = 0;
            for (int j = 0; j < i; j++) {
                if (combattant[k].numEquipe[j] == num-1) {
                    dejaChoisi = 1;
                    break;
                }
            }

            if (dejaChoisi) {
                printf("\nCe personnage a déjà été choisi. Veuillez en choisir un autre.\n");
            } else {
                combattant[k].numEquipe[i] = num-1; // Stocker le choix
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
            if (combattant[k].numEquipe[j] == num) {
                printf("\nCe personnage a déjà été choisi. Veuillez en choisir un autre.\n");
                i--; // Réduire le compteur pour redemander le choix
                break;
            }
        }

    
       
    
    printf("\nÉquipe du joueur %d:\n", k+1); 
    for (int i = 0; i < *nbCombattant; i++) {
        int numPerso = combattant[k].numEquipe[i];
        printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n\n",
               i + 1, perso[numPerso].nom, perso[numPerso].pv, perso[numPerso].attaque,
               perso[numPerso].defense, perso[numPerso].agilite, perso[numPerso].vitesse);
    }

    printf("\nÉquipe du joueur %d:\n", k + 1);
for (int i = 0; i < *nbCombattant; i++) {
    printf("Personnage %d : %d\n", i + 1, combattant[k].numEquipe[i]);
}

}



if(nbJ==1){
  printf("\nUn seul joueur, arrêt programme, à finaliser plus tard\n");
  exit(1);  
}
}// VERIFIER SI LES TABLEAUX D'EQUIPES SONT BIEN REMPLIS EN FONCTION DE PERSO CHOISIS.






int esquivePerso(Joueur NomJoueur[], Info perso[], int numPerso[]) {
 
  int alea = rand() % 100; // Génère un nombre entre 0 et 99
  if (alea < perso[*numPerso-1].agilite) {
      return 1; // Esquive réussie
  } else {
      return 0; // Esquive ratée
  }
}




void attaquePerso(Info perso[], int *numPerso1, int *numPerso2, int qui){
//printf("\nLa fonction tourne");

//printf("%s    Choisis quel personnage tu attaques :\n");

  if(qui == 1){
    printf("Le joueur 1 attaque le joueur 2 !\n");
    perso[*numPerso2-1].pv -= perso[*numPerso1-1].attaque * (100 - perso[*numPerso2-1].defense) / 100;
    sleep(1);
    printf("PV du joueur 2 : %d\n", perso[*numPerso2-1].pv);

    printf("Le joueur 2 attaque le joueur 1 !\n");
    perso[*numPerso1-1].pv -= perso[*numPerso2-1].attaque * (100 - perso[*numPerso1-1].defense) / 100;
    sleep(1);
    printf("PV du joueur 1 : %d\n", perso[*numPerso1-1].pv);
  }

  else if(qui == 2){
    printf("Le joueur 2 attaque le joueur 1 !\n");
    perso[*numPerso1-1].pv -= perso[*numPerso2-1].attaque * (100 - perso[*numPerso1-1].defense) / 100;
    sleep(1);
    printf("PV du joueur 1 : %d\n", perso[*numPerso1-1].pv);

    printf("Le joueur 1 attaque le joueur 2 !\n");
    perso[*numPerso2-1].pv -= perso[*numPerso1-1].attaque * (100 - perso[*numPerso2-1].defense) / 100;
    sleep(1);
    printf("PV du joueur 2 : %d\n", perso[*numPerso2-1].pv);
  }

  else if(qui == 3){
    printf("Les deux joueurs attaquent en même temps !\n");
    perso[*numPerso1-1].pv -= perso[*numPerso2-1].attaque * (100 - perso[*numPerso1-1].defense) / 100;
    perso[*numPerso2-1].pv -= perso[*numPerso1-1].attaque * (100 - perso[*numPerso2-1].defense) / 100;
    sleep(1);
    printf("PV du joueur 1 : %d\n", perso[*numPerso1-1].pv);
    printf("PV du joueur 2 : %d\n", perso[*numPerso2-1].pv);
    perso[*numPerso2-1].vitesse = 0;
    perso[*numPerso1-1].vitesse = 0;

  }

}

/*void affichage(Joueur Nomjoueur[], Info perso[]){
  printf("Equipe de %s", Nomjoueur[0].nom);

  printf("%s   | 1 |                 %s   | 2 |           %s   | 3 |", perso[Nomjoueur[0].numEquipe[0]].nom, perso[Nomjoueur[0].numEquipe[1]].nom, perso[Nomjoueur[0].numEquipe[2]].nom);
  
}*/


void chargement(Info perso[], Joueur Nomjoueur[], int *numPerso1, int *numPerso2, int nbCombattant, Joueur combattant[]) { 
  
  
 // int numPerso = combattant[i].numEquipe[0]; // Récupérer l'indice du personnage dans l'équipe
 // printf("%s : 🏁 ARRIVÉ 🏁\n", perso[numPerso].nom);
  printf("Début du combat !\n");
  printf("Choix du personnage qui commence l'attaque \n");


 //nettoyerEcran();
 printf("\n\n\nNombre de combattant : %d\n\n\n", nbCombattant);
 //affichage(Nomjoueur, perso);


  /*printf("\n%s, Choisis ton personnage : ", Nomjoueur[0].nom);
    scanf("%d", numPerso1); 


    printf("\n%s, Choisis ton personnage : ", Nomjoueur[1].nom);
    scanf("%d", numPerso2); 

    printf("\nVitesse du personnage du joueur 1 : %d\n", perso[*numPerso1-1].vitesse);
    printf("Vitesse du personnage du joueur 2 : %d\n", perso[*numPerso2-1].vitesse);*/


  printf("\n\nChargement des barres de vitesses\n");

int nbArrive1 = 0;
int nbArrive2 = 0;

int *persoArrive = malloc(nbCombattant * sizeof(int));
if(persoArrive == NULL){
  printf("Erreur d'allocation - 3");
  exit(3);
}

int *vitesse = malloc(nbCombattant * sizeof(int));
if(vitesse == NULL){
  printf("Erreur d'allocation - 4");
  exit(4);
}

for (int i = 0; i < nbCombattant; i++) {
  persoArrive[i] = 0;
}

for (int i = 0; i < nbCombattant; i++) {
  vitesse[i] = 0;
}


int places = 0;

  while (nbArrive1 < nbCombattant && nbArrive2 < nbCombattant) {
    printf("\n-- État des vitesses --\n");
    int i = 0;
    //for (int i = 0; i < nbCombattant; i++) {

        if (!persoArrive[i]) {
          int numPerso = combattant[i].numEquipe[0];
            vitesse[i] +=  perso[numPerso].vitesse; // PARTIR DE ZERO POUR LES VITESSE
            printf("%s : %d / 100\n", perso[numPerso].nom, vitesse[i]);

            if (vitesse[i] >= 100) {
                //attaque(i, places);
                printf("Perso %d a fini de charger: 🏁 ARRIVÉ 🏁\n", i + 1);
                persoArrive[i] = 1;
                places++;
                nbArrive1++;
            }

        } 
        
        else {
          int numPerso = combattant[i].numEquipe[0]; // Récupérer l'indice du personnage dans l'équipe
          printf("%s : 🏁 ARRIVÉ 🏁\n", perso[numPerso].nom);
        } 


        for (int i = 0; i < nbCombattant; i++) {
          int numPerso = combattant[i].numEquipe[1]; // Récupérer l'indice du personnage dans l'équipe
          if (!persoArrive[i]) {
              vitesse[i] += perso[numPerso].vitesse; // PARTIR DE ZERO POUR LES VITESSES
              printf("%s : %d / 100\n", perso[numPerso].nom, vitesse[i]);
              if (vitesse[i] >= 100) {
                  //attaque(i, places);
                  printf("Perso %d a fini de charger: 🏁 ARRIVÉ 🏁\n", i + 1);
                  persoArrive[i] = 1;
                  places++;
                  nbArrive2++;
              }
          } else {
              printf("Perso %d : 🏁 ARRIVÉ 🏁\n", i + 1);
          }
    }
    sleep(3); 
    i++;
}
  }



/*int qui = 0;

  while(perso[*numPerso1-1].pv > 0 && perso[*numPerso2-1].pv > 0){

    while(vitessePerso1 < 100 && vitessePerso2 < 100){

    vitessePerso1 += perso[*numPerso1].vitesse;
    sleep(1);
      printf("\n Vitesse du joueur 1 : %d\n", vitessePerso1);

    vitessePerso2 += perso[*numPerso2].vitesse;
    sleep(1);
      printf("Vitesse du joueur 2 : %d\n", vitessePerso2);

      if (vitessePerso1 >= 100 && vitessePerso2<100){
        printf("Le joueur 1 attaque en premier!\n");
        qui = 1;
      }
      else if (vitessePerso2 >= 100 && vitessePerso1<100){
        printf("Le joueur 2 attaque en premier!\n");
        qui = 2;
      }
      else if (vitessePerso1 >= 100 && vitessePerso2 >= 100){
        printf("Les deux joueurs attaquent en même temps !\n");
        qui = 3;
      }

    }

    int esquive = esquivePerso( Nomjoueur, perso, numPerso1);

    if (esquive == 1) {
        printf("%s a esquive l'attaque de %s !\n", perso[*numPerso1-1].nom, perso[*numPerso2-1].nom);
    } else if (esquive == 0) {
        printf("Esquive ratée !\n");
        attaquePerso(perso, numPerso1, numPerso2, qui);
        vitessePerso1 = 0; // Réinitialiser la vitesse du joueur 1
    }

    attaquePerso(perso, numPerso1, numPerso2, qui);


  }*/



  


  /*while(perso[0].vitesse < 100 && perso[1].vitesse < 100){
    printf("Vitesse du joueur 1 : %d\n", perso[0].vitesse);
    printf("Vitesse du joueur 2 : %d\n", perso[1].vitesse);
    sleep(1);
  }

  if(perso[0].vitesse > 100){
    printf("Le joueur 1 attaque !\n");// Appeler la fonction d'attaque
    
  }

  else if(perso[1].vitesse > 100){
    printf("Le joueur 2 attaque !\n");
    perso[0].pv -= perso[1].attaque;
    printf("PV du joueur 1 : %d\n", perso[0].pv);
    perso[1].vitesse = 0;
  }
} while(perso[0].vitesse <100 || perso[1].vitesse);*/





