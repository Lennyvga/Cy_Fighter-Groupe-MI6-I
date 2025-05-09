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
 


void creationJoueur (Joueur listeJoueurs[], int *nbJ){
  //printf("Nombre de joueurs : %d\n", *nbJ);

for(int i = 0; i< *nbJ; i++){

   listeJoueurs[i].nom = malloc(20 * sizeof(char)); // Modification taille tableau nom du joueur avec le nom tampon
if(listeJoueurs[i].nom == NULL){
  printf("Erreur d'allocation - 1 ");
  exit(1);
  }
}

for(int i = 0; i< *nbJ; i++){
printf("\nJoueur %d, Entrez votre nom : ", i+1);
scanf("%s", listeJoueurs[i].nom);
}
for(int i = 0; i< *nbJ; i++){
printf("\n\nJoueur %d : %s\n ", i+1, listeJoueurs[i].nom);
}


for(int i = 0; i< *nbJ; i++){
  printf("\nJoueur %d, Entrez votre nom : ", i+1);
  printf("%s", listeJoueurs[i].nom);
  }

}

int fichierPersos(Personnage persos[], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        printf("\nLe fichier %s est ouvert  \n", nomFichier);
    }
    else {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return -1;
    }

   

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


void afficherPersos(Personnage perso[]) {
  printf("\nListe des personnages disponibles :\n");
  for (int i = 0; i < 3; i++) {
      printf("\n%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
             i + 1, perso[i].nom, perso[i].pv, perso[i].attaque,  perso[i].defense, perso[i].agilite, perso[i].vitesse);
  }
}




void choisirPersos( int *nbCombattantsEquipe, int nbJ, Joueur listeJoueurs[], Personnage perso[]) {
  int i = 0;
  int num;

  //int numPerso[nbJ];


  for (int k=0;  k < nbJ; k++){
    for(int j=0; j < *nbCombattantsEquipe; j++){
      // SK // listeJoueurs[i].numPerso[j] = -1; // Initialiser le tableau à -1
      listeJoueurs[k].numPerso[j] = -1; // Initialiser le tableau à -1
  
    printf("%d", listeJoueurs[k].numPerso[j]);
  }
}

printf("\n\nNombre de joueurs dans la partie : %d\n", nbJ);
 
for(int k = 0; k < nbJ; k++){
    for (int i = 0; i < *nbCombattantsEquipe; i++){
      int correct = 0;

    while(!correct){
        printf("--------------------------------------------------Choix %d --------------------------------------------------\n ", i + 1);

      printf(" %s, choisissez votre personnage :\n", listeJoueurs[k].nom);

      printf("Entrez les numéros des personnages pour votre équipe (entre 1 et 3).\n");
        if (scanf("%d", &num) == 1 && (num == 1 || num == 2 || num == 3)) {
          int dejaChoisi = 0;

          for (int j = 0; j < i; j++) {
            if (listeJoueurs[k].numPerso[j] == num - 1) {
                dejaChoisi = 1;
                break;
            }
        }

          if (dejaChoisi) {
              printf("\nCe personnage a déjà été choisi. Veuillez en choisir un autre.\n");
          }
          
          else {
              listeJoueurs[k].numPerso[i] = num-1; // Stocker le choix
              //listeJoueurs[k].persos[i] = perso[num - 1]; // Copier le personnage choisi

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
    
   //Vérification si le personnage a déjà été choisi
      for (int j = 0; j < i; j++) {
          if (listeJoueurs[k].numPerso[i] == num) {
              printf("\nCe personnage a déjà été choisi. Veuillez en choisir un autre.\n");
              i--; // Réduire le compteur pour redemander le choix
              break;
          }
      }

  
     
  
  printf("\nÉquipe du joueur %d:\n", k+1); 
  for (int i = 0; i < *nbCombattantsEquipe; i++) {
      int numPerso = listeJoueurs[k].numPerso[i];
      printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n\n",
             i + 1, perso[numPerso].nom, perso[numPerso].pv, perso[numPerso].attaque,
             perso[numPerso].defense, perso[numPerso].agilite, perso[numPerso].vitesse);
  }

 
}

if(nbJ==1){
printf("\nUn seul joueur, arrêt programme, à finaliser plus tard\n");
exit(1);  
}
}



int esquivePerso(Joueur NomJoueur[], Personnage perso[], int numPerso[]) {
 
  int alea = rand() % 100; // Génère un nombre entre 0 et 99
  if (alea < perso[*numPerso-1].agilite) {
      return 1; // Esquive réussie
  } else {
      return 0; // Esquive ratée
  }
}


void attaqueNormale(Joueur listeJoueurs[], Personnage perso[], int joueurQuiAttaque, int indicePerso, int cible) {
  
  int degats = perso[indicePerso].attaque * (100 - perso[cible].defense) / 100;
  if (degats < 0) degats = 0;

  perso[cible].pv -= degats;

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[cible].nom);
  printf("Dégâts infligés : %d\n", degats);
  printf("%s a maintenant %d PV.\n", perso[cible].nom, perso[cible].pv);
}







void attaque(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int indicePerso) {
  Joueur attaquant = listeJoueurs[joueurQuiAttaque];
  //Personnage p = perso[indicePerso];

  
  printf("\n  %s (joué par %s) attaque !\n", perso[indicePerso].nom, attaquant.nom);
  printf("Stats — PV: %d | ATT: %d | DEF: %d | AGI: %d | VIT: %d\n\n",
         perso[indicePerso].pv, perso[indicePerso].attaque, perso[indicePerso].defense, perso[indicePerso].agilite, perso[indicePerso].vitesse);

         sleep(3);

  //printf("Choisis quel personnage tu veux attaquer :\n");

  int *persoVise = malloc(100 * sizeof(int)); // taille assez grande mais imprécise pour éviter d'avoir un segmentation fault
  if (persoVise == NULL) {
      printf("Erreur d'allocation mémoire pour persoVise.\n");
      exit(1);
  }


  int nbPersoVise = 0;


  for (int k = 0; k < nbJ; k++) {
      if (k == joueurQuiAttaque) continue; // Pour ne pas avoir les infos concernant le joueur attaquant

      printf("\nÉquipe de %s :\n\n", listeJoueurs[k].nom);
      for (int i = 0; i < nbCombattantsEquipe; i++) {
          int num_Perso = listeJoueurs[k].numPerso[i];
          
          persoVise[nbPersoVise] = num_Perso; // Récupérer le numéro des personnages de l'équipe adverse

          
          printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",  //num_Perso équivalent à l'entier et pas au tableau 
                 i + 1, perso[num_Perso].nom, perso[num_Perso].pv,
                 perso[num_Perso].attaque, perso[num_Perso].defense,
                 perso[num_Perso].agilite, perso[num_Perso].vitesse);

         
                 nbPersoVise++;   
      }
        
  }



  int choixAttaque = -1; //permet de vérifier plus rapidement si le "choixAttaque" du scanf est valide
  int correct = 0;
  
  //On demande à l'utilisateur de choisir un personnage à attaquer et on vérifie si son choix est valide 
  while (!correct) {
      printf("\n\nChoisissez le personnage à attaquer : ");

      if (scanf("%d", &choixAttaque) == 1 && choixAttaque >= 1 && choixAttaque <= nbCombattantsEquipe) {
         
        correct = 1;
      } 
      
      else {
          printf("\n\nErreur. Veuillez choisir un nombre entre 1 et %d.\n", nbCombattantsEquipe);
          
          int c;
          while ((c = getchar()) != '\n' && c != EOF) ;
      }
  }

  int cible = persoVise[choixAttaque - 1]; // On récupère le numéro du personnage visé par l'attaque

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[cible].nom);

  printf("Choisir quel type d'attaque :\n");
  printf("1. Attaque normale\n");
  printf("2. Attaque spéciale\n");
  int choixAttaqueType = -1;
  correct = 0;
  while (!correct) {
      printf("Choix : ");
      if (scanf("%d", &choixAttaqueType) == 1 && (choixAttaqueType == 1 || choixAttaqueType == 2)) {
          correct = 1;
      } else {
          printf("Erreur. Veuillez choisir 1 ou 2.\n");
          int c;
          while ((c = getchar()) != '\n' && c != EOF) ;
      }
  }
  if(choixAttaqueType == 1){

    esquivePerso(listeJoueurs, perso, &cible);

    int esquive = esquivePerso(listeJoueurs, perso, &cible);

    if(esquive == 1){
      printf("%s a esquivé l'attaque de %s !\n", perso[cible].nom, perso[indicePerso].nom);
    }
    else{
      printf("Esquive ratée !\n");
      attaqueNormale(listeJoueurs, perso, joueurQuiAttaque, indicePerso, cible);
    }
    

  }

  free(persoVise);
}

void afficherBarreVitesse(int vitesse) {
  int nbHashtag = vitesse / 5; // 100 vitesse correpond à 20 #
  for (int i = 0; i < nbHashtag; i++) {
      printf("#");
  }
  printf(" (%d)", vitesse); // Affiche aussi la vitesse en la valeur numérique correpondante
  printf("\n");
}


void chargement(int nbJ, int nbCombattantsEquipe, Joueur listeJoueurs[], Personnage perso[]) {
  
  
  int nbCombattantsTotal = nbJ * nbCombattantsEquipe;
  
  int *vitesseTour = malloc(nbCombattantsTotal * sizeof(int));
  if (vitesseTour == NULL) {
      printf("Erreur d'allocation mémoire pour vitesseTour.\n");
      exit(1);
  }

  int *indiceCombattant = malloc(nbCombattantsTotal * sizeof(int));
  if (indiceCombattant == NULL) {
      printf("Erreur d'allocation mémoire pour indiceCombattant.\n");
      exit(1);
  }

  int *indiceJoueur = malloc(nbCombattantsTotal * sizeof(int));
  if (indiceJoueur == NULL) {
      printf("Erreur d'allocation mémoire pour indiceJoueur.\n");
      exit(1);
  }

  // Initialisation
  for (int i = 0; i < nbCombattantsTotal; i++) {
      vitesseTour[i] = 0;
  }

 
  int compteur = 0;
  for (int k = 0; k < nbJ; k++) {
      for (int i = 0; i < nbCombattantsEquipe; i++) {
          indiceCombattant[compteur] = listeJoueurs[k].numPerso[i];
          indiceJoueur[compteur] = k;
          compteur++;
      }
  }

  printf("\n>>> Début du chargement des vitesses <<<\n");

  int tour = 0;
  while (1) {
      printf("\n==================== TOUR %d ====================\n", tour);

      for (int k = 0; k < nbJ; k++) {
          printf("\n%s\n", listeJoueurs[k].nom);

          for (int i = 0; i < nbCombattantsTotal; i++) {
              if (indiceJoueur[i] == k) {
                  int copiePerso = indiceCombattant[i];
                  printf("%s :\n", perso[copiePerso].nom);


                  
                 
                  // Ajout de la vitesse
                  vitesseTour[i] += perso[copiePerso].vitesse;


                  afficherBarreVitesse(vitesseTour[i]);
                    
                 
                 
              }
              while (vitesseTour[i] >= 100) {
                attaque(listeJoueurs, perso, nbJ, nbCombattantsEquipe, indiceJoueur[i], indiceCombattant[i]);
                vitesseTour[i] -= 100;
               // printf(" Nouvelle vitesse : %d (surplus)\n", vitesseTour[i]);
            }
          }
      }

      tour++;
      sleep(3);

      //condition d'arrêt
      int combatTermine = 1; 
      for (int i = 0; i < nbCombattantsTotal; i++) {
          if (perso[indiceCombattant[i]].pv > 0) {
              combatTermine = 0;
              break;
          }
      }
      if (combatTermine) {
          printf("\n>>> Le combat est terminé <<<\n");
          break;
      }
  }
}















