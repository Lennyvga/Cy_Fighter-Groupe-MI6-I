#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "perso.h"
#include <unistd.h>// Est ce qu'on a le droit ? C'est pour le sleep
#include <string.h>

const int TAILLE_FICHIER = 6;
const int NB_COMBATTANTS_TOTAL = 6;
const int NB_COMP_COMB = 2;


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

   

    for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) {
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
            char c;
            while ((c = fgetc(fichier)) != '\n' && c != EOF);
    }

    fclose(fichier);
    return 0;
}

int fichierCompetences(Personnage persos[], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        printf("\nLe fichier %s est ouvert  \n", nomFichier);
    }
    else {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return -1;
    }

    for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) 
        for (int j = 0; j < NB_COMP_COMB; j++) 
        {
           if( fscanf(fichier, "%[^;];%[^;];%d;%d;%d;%d;%d",
//           if( fscanf(fichier, "%s %s %d %d %d %d %d",
                   persos[i].competences[j].nom,
                   persos[i].competences[j].desc,
                   &persos[i].competences[j].duree,
                   &persos[i].competences[j].recharge,
                   &persos[i].competences[j].valeur,
                   &persos[i].competences[j].cible,
                   &persos[i].competences[j].propriete) != 7) {
                printf("Erreur de lecture du fichier %s\n", nomFichier);
                fclose(fichier);
                return -1;};
                char c;
                while ((c = fgetc(fichier)) != '\n' && c != EOF);
                
            // Initialisation des propriétes compétences _en_cours
            persos[i].competences[j].duree_en_cours = 0;
            persos[i].competences[j].recharge_en_cours = 0;
            persos[i].competences[j].cible_en_cours = -1; // cible de l'action non définie
        }
        
      for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) 
        for (int j = 0; j < NB_COMP_COMB; j++) 
        {
           printf(" %s  %s  %d  %d  %d  %d  %d %d %d %d\n",
                   persos[i].competences[j].nom,
                   persos[i].competences[j].desc,
                   persos[i].competences[j].duree,
                   persos[i].competences[j].recharge,
                   persos[i].competences[j].valeur,
                   persos[i].competences[j].cible,
                   persos[i].competences[j].propriete,
                   persos[i].competences[j].duree_en_cours,
                    persos[i].competences[j].recharge_en_cours,
                     persos[i].competences[j].cible_en_cours);
        }

    fclose(fichier);
    return 0;
}

void afficherPersos(Personnage perso[]) {
  printf("\nListe des personnages disponibles :\n");
  for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) {
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
        //listeJoueurs[i].numPerso[j] = -1; // Initialiser le tableau à -1
        listeJoueurs[k].numPerso[j] = -1; // Initialiser le tableau à -1
    
  }
}

printf("\n\nNombre de joueurs dans la partie : %d\n", nbJ);
 
for(int k = 0; k < nbJ; k++){
    for (int i = 0; i < *nbCombattantsEquipe; i++){
      int correct = 0;

    while(!correct){
        printf("--------------------------------------------------Choix %d --------------------------------------------------\n ", i + 1);

      printf(" %s, choisissez votre personnage :\n", listeJoueurs[k].nom);

      printf("Entrez les numéros des personnages pour votre équipe (entre 1 et %d).\n", NB_COMBATTANTS_TOTAL);
        if (scanf("%d", &num) == 1 && num >= 1 && num <= NB_COMBATTANTS_TOTAL) {
          int dejaChoisi = 0;

/*          for (int j = 0; j < i; j++) {
            if (listeJoueurs[k].numPerso[j] == num - 1) {
                dejaChoisi = 1;
                break;
            }
        }*/
            /* Vérification que le combattant a déjà été choisi ou pas dans tous les combattants pour tous les joueurs */
            for(int ind_joueur = 0; ind_joueur < nbJ; ind_joueur++) {
                for (int ind_comb = 0; ind_comb < *nbCombattantsEquipe; ind_comb++) {
                    if (listeJoueurs[ind_joueur].numPerso[ind_comb] == num - 1) {
                        dejaChoisi = 1;
                        break;
                    }
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
          printf("Erreur. Veuillez choisir un nombre entre 1 et %d.\n", NB_COMBATTANTS_TOTAL);
          int c;
          while ((c = getchar()) != '\n' && c != EOF) ;
        }

        }
      }
    
   //Vérification si le personnage a déjà été choisi
      for (int j = 0; j < i; j++) {
          if (listeJoueurs[k].numPerso[i] == num) {
              printf("\nCe personnage a déjà été choisi. *******Veuillez en choisir un autre.\n");
              i--; // Réduire le compteur pour redemander le choix
              break;
          }
      }

  
     
  // Affiche l'équipe du joueur k
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



int esquivePerso(Joueur NomJoueur[], Personnage perso[], int cible) {
 
  int alea = rand() % 101; // On génére un nombre aléatoire entre 0 et 100

  printf("\n\nValeur aléatoire : %d\n\n", alea);


  if (alea < perso[cible].agilite) {
      return 1; // Esquive réussie
  } else {
      return 0; // Esquive ratée
  }
}

/*************************************************************************************************************/
/* AATTAQUE NORMALE */
/*************************************************************************************************************/  

void attaqueNormale(Joueur listeJoueurs[], Personnage perso[], int joueurQuiAttaque, int indicePerso, int cible, int esquive) {
  

  if(esquive == 1){
   return;

  }
  else{
  int degats = perso[indicePerso].attaque * (100 - perso[cible].defense) / 100;
  if (degats < 0) degats = 0;

  perso[cible].pv -= degats;

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[cible].nom);
  printf("Dégâts infligés : %d\n", degats);
  printf("%s a maintenant %d PV.\n", perso[cible].nom, perso[cible].pv);
}

}
/*************************************************************************************************************/
/* ACTION SPECIALE */
/*************************************************************************************************************/  
/*
void actionSpeciale(Joueur listeJoueurs[], Personnage perso[], int joueurQuiAttaque, int attaquant, int cible) {
  
// CHOIX DE LA COMPETENCE 

    // Afficher la liste des compétences de l'attaquant
    for(int ind_comp = 0; ind_comp < NB_COMP_COMB; ind_comp++) {
        
        printf("|%d| %s — PV: %d | ATT: %d | DEF: %d | AGI: %d | VIT: %d\n\n",
            ind_comp + 1,
            perso[attaquant].competences[ind_comp].nom,
            perso[attaquant].competences[ind_comp].nom,
            perso[attaquant].competences[ind_comp].nom,
            perso[attaquant].competences[ind_comp].nom,
            perso[attaquant].competences[ind_comp].nom,
            
            perso[indicePerso].pv, perso[indicePerso].attaque, perso[indicePerso].defense, perso[indicePerso].agilite, perso[indicePerso].vitesse);

        
        
        perso[attaquant].competences[ind_comp]
    }

  int choixCompetence = -1; //permet de vérifier plus rapidement si le "choixCompetence" du scanf est valide
  int correct = 0;
 
  // On demande à l'utilisateur de choisir une competence à utiliser et on vérifie si son choix est valide 
  while (!correct) {
      printf("\n\nChoisissez la compétence à utiliser : ");

      if (scanf("%d", &choixCompetence) == 1 && choixCompetence >= 1 && choixCompetence <= NB_COMP_COMB) {
         
        correct = 1;
      } 
      
      else {
          printf("\n\nErreur. Veuillez choisir un nombre entre 1 et %d.\n", NB_COMP_COMB);
          
          int c;
          while ((c = getchar()) != '\n' && c != EOF) ;
      }
  }

  
  
  for(int ind_comp = 0; ind_comp < NB_COMP_COMB; ind_comp++)
    
  
  int degats = perso[indicePerso].attaque * (100 - perso[cible].defense) / 100;
  if (degats < 0) degats = 0;

  perso[cible].pv -= degats;

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[cible].nom);
  printf("Dégâts infligés : %d\n", degats);
  printf("%s a maintenant %d PV.\n", perso[cible].nom, perso[cible].pv);
}

*/



void attaque(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int indicePerso) {
  //Joueur attaquant = listeJoueurs[joueurQuiAttaque];
  //Personnage p = perso[indicePerso];


/*************************************************************************************************************/
/* STATS DU COMBATTANT ATTAQUANT */
/*************************************************************************************************************/  
    /* Modif SK */
  //printf("\n  %s (joué par %s) attaque !\n", perso[indicePerso].nom, attaquant.nom);

  printf("\n  %s (joué par %s) attaque !\n", perso[indicePerso].nom, listeJoueurs[joueurQuiAttaque].nom);
  printf("Stats — PV: %d | ATT: %d | DEF: %d | AGI: %d | VIT: %d\n\n",
         perso[indicePerso].pv, perso[indicePerso].attaque, perso[indicePerso].defense, perso[indicePerso].agilite, perso[indicePerso].vitesse);

        // sleep(3);

  //printf("Choisis quel personnage tu veux attaquer :\n");


/*************************************************************************************************************/
/* LISTE DES PERSO DU JOUEUR ATTAQUE */
/*************************************************************************************************************/  

  int *persoVise = malloc(nbCombattantsEquipe * sizeof(int)); 
  if (persoVise == NULL) {
      printf("Erreur d'allocation mémoire pour persoVise.\n");
      exit(1);
  }

  int nbPersoVise = 0;

    // On affiche les infos des combattants du joueur attaqué    
  for (int k = 0; k < nbJ; k++) {
      if (k == joueurQuiAttaque) continue; // Pour ne pas avoir les infos concernant le joueur attaquant

      printf("\nÉquipe de %s :\n\n", listeJoueurs[k].nom);
      for (int i = 0; i < nbCombattantsEquipe; i++) {
          int num_Perso = listeJoueurs[k].numPerso[i];
          
          persoVise[nbPersoVise] = num_Perso; // Récupérer le numéro des personnages de l'équipe adverse

          printf("Tableau PersoVise : %d\n", persoVise[nbPersoVise]);

          if(perso[num_Perso].pv < 0){
            printf(" %s ☠️☠️☠️ !\n", perso[num_Perso].nom);
            //nbPersoVise--; // Réduire le compteur si le personnage est KO
            //continue; // Passer au personnage suivant
            nbPersoVise++; 
          }

          else{
          printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",  //num_Perso équivalent à l'entier et pas au tableau 
                 i + 1, perso[num_Perso].nom, perso[num_Perso].pv,
                 perso[num_Perso].attaque, perso[num_Perso].defense,
                 perso[num_Perso].agilite, perso[num_Perso].vitesse);

         
                 nbPersoVise++;   

          }
      }
        
  }


/*************************************************************************************************************/
/* CHOIX DU PERSO ATTAQUE */
/*************************************************************************************************************/  
  
  int choixAttaque = -1; //permet de vérifier plus rapidement si le "choixAttaque" du scanf est valide
  int correct = 0;
  
  // On demande à l'utilisateur de choisir un personnage à attaquer et on vérifie si son choix est valide 
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

/*************************************************************************************************************/
/* DEMARRAGE DE L'ATTAQUE */
/*************************************************************************************************************/  

if(joueurQuiAttaque == 0){
  choixAttaque = choixAttaque + 3;
}

printf("\n\n\n Choix de qui on attaque : %d\n", choixAttaque);

printf("nPv de SUDO : %d\n", perso[choixAttaque-1].pv);
printf("Qui on attaque : %d\n\n\n\n", perso[choixAttaque - 1].agilite);
printf("Qui on attaque : %s\n\n\n\n", perso[choixAttaque - 1].nom);


if( perso[choixAttaque - 1].pv < 0){

  printf("\n\n\n Choix de qui on attaque : %d\n\n\n", choixAttaque);


    printf("Le personnage %s est KO !\n", perso[persoVise[choixAttaque - 1]].nom);
    printf("Choisissez un autre personnage à attaquer :\n");
    for (int i = 0; i < nbPersoVise; i++) {

      if(perso[persoVise[i]].pv < 0){
        printf("%d. %s ☠️☠️☠️ !\n", i + 1, perso[persoVise[i]].nom);
      }

       // else (persoVise[i] > 0)

        else {
            printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
                   i + 1, perso[persoVise[i]].nom, perso[persoVise[i]].pv,
                   perso[persoVise[i]].attaque, perso[persoVise[i]].defense,
                   perso[persoVise[i]].agilite, perso[persoVise[i]].vitesse);
        }
    }
    //free(persoVise);
    
int choixAttaque1 = -1; 

    correct = 0;
    while (!correct) {
        printf("\n\nChoix : ");
        if (scanf("%d", &choixAttaque1) == 1 && choixAttaque1 != choixAttaque && perso[choixAttaque1 - 1].pv > 0) {
            correct = 1;
            memcpy(&choixAttaque, &choixAttaque1, sizeof(choixAttaque1));
        } else {
            printf("Erreur. \n\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) ;
        }
    }
}


  int cible = persoVise[choixAttaque - 1]; // On récupère le numéro du personnage visé par l'attaque

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[choixAttaque - 1].nom);

  printf("Choisir quel type d'attaque :\n");
  printf("1. Attaque normale\n");
  printf("2. Action spéciale\n");
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
  
    /* ATTAQUE NORMALE */

  if(choixAttaqueType == 1){

    //esquivePerso(listeJoueurs, perso, &cible);

    //int esquive = esquivePerso(listeJoueurs, perso, &cible);
    int esquive = esquivePerso(listeJoueurs, perso, choixAttaque - 1);

    if(esquive == 1){
      printf("%s a esquivé l'attaque de %s !\n", perso[choixAttaque - 1].nom, perso[indicePerso].nom);
    }

    else{
      printf("Esquive ratée !\n");
      attaqueNormale(listeJoueurs, perso, joueurQuiAttaque, indicePerso, choixAttaque - 1, esquive);
    }

  }
  
    /* ACTION SPECIALE */
  
  if(choixAttaqueType == 2){

  //  actionSpeciale(listeJoueurs, perso, joueurQuiAttaque, indicePerso, cible);  

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

                  if(perso[copiePerso].pv <= 0){
                    printf(" ☠️☠️☠️ !\n");
                    vitesseTour[i] = 0; // Réinitialiser la vitesse si le personnage est KO
                  }
                  else{
                    afficherBarreVitesse(vitesseTour[i]);
                  }

                 
                    
                 
                 
              }
              while (vitesseTour[i] >= 100) {
                attaque(listeJoueurs, perso, nbJ, nbCombattantsEquipe, indiceJoueur[i], indiceCombattant[i]);
                
                vitesseTour[i] -= 100; // Calcul du surplus
              
            }
          }
      }

      tour++;
     // sleep(3);

      //condition d'arrêt
    
int Equipe0morte = 1;
int Equipe1morte = 1;

for (int i = 0; i < nbCombattantsEquipe; i++) {
    if (perso[listeJoueurs[0].numPerso[i]].pv > 0) {
      Equipe0morte = 0;
    }
    if (perso[listeJoueurs[1].numPerso[i]].pv > 0) {
      Equipe1morte = 0;
    }
}

if (Equipe0morte || Equipe1morte) {
    printf("\n>>> Le combat est terminé <<<\n");
    break;
}

  }
}














