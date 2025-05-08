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

    int numPerso[nbJ];
  

    for (int k=0;  k < nbJ; k++){
      for(int j=0; j < *nbCombattantsEquipe; j++){
        listeJoueurs[i].numPerso[j] = -1; // Initialiser le tableau à -1
    
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


void attaque(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int indicePerso) {
  Joueur attaquant = listeJoueurs[joueurQuiAttaque];
  Personnage p = perso[indicePerso];

  
  printf("\n  %s (joué par %s) attaque !\n", p.nom, attaquant.nom);
  printf("Stats — PV: %d | ATT: %d | DEF: %d | AGI: %d | VIT: %d\n\n",
         p.pv, p.attaque, p.defense, p.agilite, p.vitesse);

         sleep(1);

  printf("Choisis quel personnage tu veux attaquer :\n");

    // Liste plate des cibles disponibles
    int cibles[100];  // tu peux adapter la taille si besoin
    int nbCibles = 0;
  
    for (int k = 0; k < nbJ; k++) {
        if (k == joueurQuiAttaque) continue;
  
        printf("\nÉquipe de %s :\n\n", listeJoueurs[k].nom);
        for (int i = 0; i < nbCombattantsEquipe; i++) {
            int numPerso = listeJoueurs[k].numPerso[i];
  
            // Associer le numéro affiché à l’indice réel dans le tableau perso
            cibles[nbCibles] = numPerso;
  
            printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
                   nbCibles + 1, perso[numPerso].nom, perso[numPerso].pv,
                   perso[numPerso].attaque, perso[numPerso].defense,
                   perso[numPerso].agilite, perso[numPerso].vitesse);
  
            nbCibles++;
        }
    }
  
    int choixAttaque = -1;
    int correct = 0;
  
    while (!correct) {
        printf("\n\nChoisissez le personnage à attaquer (1 à %d) : ", nbCibles);
        if (scanf("%d", &choixAttaque) == 1 && choixAttaque >= 1 && choixAttaque <= nbCibles) {
            correct = 1;
        } else {
            printf("Erreur. Numéro invalide.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
  
    // Récupération du perso cible
    int indexCibleGlobal = cibles[choixAttaque - 1];
  
    printf("\n🗡 %s attaque %s !\n", p.nom, perso[indexCibleGlobal].nom);
  
    int degats = p.attaque - perso[indexCibleGlobal].defense;
    if (degats < 1) degats = 1;
  
    perso[indexCibleGlobal].pv -= degats;
    if (perso[indexCibleGlobal].pv < 0) perso[indexCibleGlobal].pv = 0;
  
    printf("→ %s perd %d PV. Il lui reste %d PV.\n",
           perso[indexCibleGlobal].nom, degats, perso[indexCibleGlobal].pv);
  

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
                attaque(listeJoueurs, perso, nbJ, nbCombattantsEquipe, indiceJoueur[compteur], indiceCombattant[compteur]);
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








int esquivePerso(Joueur NomJoueur[], Personnage perso[], int numPerso[]) {
 
  int alea = rand() % 100; // Génère un nombre entre 0 et 99
  if (alea < perso[*numPerso-1].agilite) {
      return 1; // Esquive réussie
  } else {
      return 0; // Esquive ratée
  }
}







/*void affichage(Joueur Nomjoueur[], Personnage perso[]){
  printf("Equipe de %s", Nomjoueur[0].nom);

  printf("%s   | 1 |                 %s   | 2 |           %s   | 3 |", perso[Nomjoueur[0].numEquipe[0]].nom, perso[Nomjoueur[0].numEquipe[1]].nom, perso[Nomjoueur[0].numEquipe[2]].nom);
  
}*/







   /* int esquive = esquivePerso( Nomjoueur, perso, numPerso1);

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





