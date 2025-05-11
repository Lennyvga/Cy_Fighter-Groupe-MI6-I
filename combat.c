#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "perso.h"
#include <unistd.h>
#include <string.h>


const int NB_COMBATTANTS_TOTAL = 6;
const int NB_COMP_COMB = 2;


void nettoyerEcran() {
  system("clear");  // Utilise "cls" sur Windows
}


/******** MESSAGE D'ACCUEIL et CHOIX NOMBRE JOUEURS *****/
void nbJoueur(int *nbJ){
    
    
    printf("╔══════════════════════════════════════════════╗\n");
    printf("║                                              ║\n");
    printf("║           BIENVENUE DANS CY_FIGHTERS         ║\n");
    printf("║                                              ║\n");
    printf("║     Prépare-toi à entrer dans l’arène !      ║\n");
    printf("║        Que le meilleur joueur gagne !        ║\n");
    printf("║                                              ║\n");
    printf("╚══════════════════════════════════════════════╝\n\n");
  
    int correct = 0;
    while(!correct){
      printf("Nombre de joueurs désirés : ");
//      if (scanf("%d", nbJ) == 1 && (*nbJ == 1 || *nbJ == 2)){ // QUAND LA VERSION VS ORDINATEUR SERA IMPLEMENTEE
        if (scanf("%d", nbJ) == 1 && (*nbJ == 2)){
          correct = 1;
        }
        else{
//      printf("\nErreur. Veuilez saisir 1 ou 2 joueurs.\n ");
        printf("\nErreur. Seule la version 2 joueurs est disponible.\n");
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) ;
    }

}

/*************************************************************************************************************/
/* CREATION JOUEUR */
/*************************************************************************************************************/  
void creationJoueur (Joueur listeJoueurs[], int nbJ){

    
    strcpy(listeJoueurs[0].nom, "EQUIPE1");
    strcpy(listeJoueurs[1].nom, "EQUIPE2");
    

}

/*************************************************************************************************************/
/* EXTRACTION COMBATTANTS */
/*************************************************************************************************************/  
int fichierPersos(Personnage persos[], const char *nomFichier) {
    
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
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

/*************************************************************************************************************/
/* EXTRACTION COMPETENCES */
/*************************************************************************************************************/  
int fichierCompetences(Personnage persos[], const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        //printf("\nLe fichier %s est ouvert  \n", nomFichier);
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
                   &persos[i].competences[j].type_cible,
                   &persos[i].competences[j].propriete) != 7) {
                printf("Erreur de lecture du fichier %s\n", nomFichier);
                fclose(fichier);
                return -1;};
                char c;
                while ((c = fgetc(fichier)) != '\n' && c != EOF);
                
            // Initialisation des propriétes compétences _en_cours
            persos[i].competences[j].duree_en_cours = 0;
            persos[i].competences[j].recharge_en_cours = 0;
            persos[i].competences[j].cible_en_cours = 0; // cible de l'action non définie
        }
        
/*      for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) 
        for (int j = 0; j < NB_COMP_COMB; j++) 
        {
           printf(" %s  %s  %d  %d  %d  %d  %d %d %d %d\n",
                   persos[i].competences[j].nom,
                   persos[i].competences[j].desc,
                   persos[i].competences[j].duree,
                   persos[i].competences[j].recharge,
                   persos[i].competences[j].valeur,
                   persos[i].competences[j].type_cible,
                   persos[i].competences[j].propriete,
                   persos[i].competences[j].duree_en_cours,
                    persos[i].competences[j].recharge_en_cours,
                     persos[i].competences[j].cible_en_cours);
        }
*/
    fclose(fichier);
    return 0;
}

/*************************************************************************************************************/
/* AFFICHER LISTE PERSO  */
/*************************************************************************************************************/  
void afficherPersos(Personnage perso[]) {
  printf("\nListe des personnages disponibles :\n");
  for (int i = 0; i < NB_COMBATTANTS_TOTAL; i++) {
      printf("\n%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",
             i + 1, perso[i].nom, perso[i].pv, perso[i].attaque,  perso[i].defense, perso[i].agilite, perso[i].vitesse);
  }
}


/*************************************************************************************************************/
/* AFFICHER LISTE PERSONNAGE  */
/*************************************************************************************************************/  
void choisirPersos( int *nbCombattantsEquipe, int nbJ, Joueur listeJoueurs[], Personnage perso[]) {

    int i = 0;
    int num;
    
    // INITIALISATION DES NUMEROS DE PERSONNAGES A -1
    for (int k=0;  k < nbJ; k++){
        for(int j=0; j < *nbCombattantsEquipe; j++){
    
            listeJoueurs[k].numPerso[j] = -1; // Initialiser le tableau à -1
        
      }
    }
    printf("\n\nNombre de joueurs dans la partie : %d\n", nbJ);
     
    // SAISIE DES CHOIX PAR EQUIPE
    for(int k = 0; k < nbJ; k++){
        for (int i = 0; i < *nbCombattantsEquipe; i++){
            int correct = 0;
    
            while(!correct){
                  printf("--------------------------------------------------Choix %d --------------------------------------------------\n", i + 1);
            
                  printf("%s, Entrez les numéros des personnages pour votre équipe (entre 1 et %d).\n", listeJoueurs[k].nom, NB_COMBATTANTS_TOTAL);
                  
                  if (scanf("%d", &num) == 1 && num >= 1 && num <= NB_COMBATTANTS_TOTAL) {
                      int dejaChoisi = 0;
            
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
        
        // Affiche l'équipe du joueur k
        printf("\nÉquipe du joueur %d:\n", k+1); 
        for (int i = 0; i < *nbCombattantsEquipe; i++) {
          int numPerso = listeJoueurs[k].numPerso[i];
          printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n\n",
                 i + 1, perso[numPerso].nom, perso[numPerso].pv, perso[numPerso].attaque,
                 perso[numPerso].defense, perso[numPerso].agilite, perso[numPerso].vitesse);
       }

    }
    // CONDITION DE SECURITE MAIS ERREUR DEJA GEREE AVANT
    if(nbJ==1){
    printf("\nUn seul joueur, arrêt programme, à finaliser plus tard\n");
    exit(1);  
    }
}

/*************************************************************************************************************/
/* ESQUIVE NORMALE */
/*************************************************************************************************************/  

int esquivePerso(Personnage perso[], int nbJ, int nbCombattantsEquipe, int cible) {
 
  int nbCombattantsTotal = nbJ * nbCombattantsEquipe;
  int agilite_cible_postaction = 0;
  
  agilite_cible_postaction = perso[cible].agilite;
  
  for (int ind_comb = 0; ind_comb < nbCombattantsTotal; ind_comb++)
  {
      for (int j = 0; j < NB_COMP_COMB; j++)
      {
        // DIMINUTION DE L'AGILITE DE LA CIBLE  
        if(perso[ind_comb].competences[j].cible_en_cours == cible // La compétence cible la cible et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == AGI
            && perso[ind_comb].competences[j].type_cible == ADV )
            
        {    agilite_cible_postaction = perso[cible].agilite * (100 - perso[ind_comb].competences[j].valeur) / 100;  }
        

        // AUGMENTATION DE L'AGILITE DE LA CIBLE  
        if(perso[ind_comb].competences[j].cible_en_cours == cible // La compétence cible la cible et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == AGI
            && perso[ind_comb].competences[j].type_cible == ALL )
            
        {    agilite_cible_postaction = perso[cible].agilite * (100 + perso[ind_comb].competences[j].valeur) / 100;  }
      }

  }

  // VERIFICATION DE LA REUSSITE DE L'ESQUIVE
  int alea = rand() % 100; // Génère un nombre entre 0 et 99
  if (alea < agilite_cible_postaction) {
      
      return 1; // Esquive réussie
  } else {
      
      return 0; // Esquive ratée
  }
}


/*************************************************************************************************************/
/* ATTAQUE NORMALE */
/*************************************************************************************************************/  

void attaqueNormale(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int attaquant, int cible) {
  
  int nbCombattantsTotal = nbJ * nbCombattantsEquipe;
  int attaque_attaquant_postaction = 0;
  int defense_cible_postaction = 0;
  
  attaque_attaquant_postaction = perso[attaquant].attaque;
  defense_cible_postaction = perso[cible].defense;
  
  for (int ind_comb = 0; ind_comb < nbCombattantsTotal; ind_comb++)
  {
      for (int j = 0; j < NB_COMP_COMB; j++)
      {
        // DIMINUTION DE LA DEFENSE DE LA CIBLE  
        if(perso[ind_comb].competences[j].cible_en_cours == cible // La compétence cible la cible et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == DEF
            && perso[ind_comb].competences[j].type_cible == ADV )
            
        {    defense_cible_postaction = perso[cible].defense * (100 - perso[ind_comb].competences[j].valeur) / 100;  }
        
       
        // AUGMENTATION DE L'ATTAQUE DE L'ATTAQUANT
        if(perso[ind_comb].competences[j].cible_en_cours == attaquant // La compétence cible l'attaquant et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == ATT
            && perso[ind_comb].competences[j].type_cible == ALL )
            
        {    attaque_attaquant_postaction = perso[attaquant].attaque * (100 + perso[ind_comb].competences[j].valeur) / 100;  }    
        
        
        // AUGMENTATION DE LA DEFENSE DE LA CIBLE  
        if(perso[ind_comb].competences[j].cible_en_cours == cible // La compétence cible la cible et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == DEF
            && perso[ind_comb].competences[j].type_cible == ALL )
            
        {    defense_cible_postaction = perso[cible].defense * (100 + perso[ind_comb].competences[j].valeur) / 100;  }

       
        // DIMINUTION DE L'ATTAQUE DE L'ATTAQUANT
        if(perso[ind_comb].competences[j].cible_en_cours == attaquant // La compétence cible l'attaquant et est active   
            && perso[ind_comb].competences[j].duree_en_cours > 0
            && perso[ind_comb].competences[j].propriete == ATT
            && perso[ind_comb].competences[j].type_cible == ADV )
            
        {    attaque_attaquant_postaction = perso[attaquant].attaque * (100 - perso[ind_comb].competences[j].valeur) / 100;   } 
        
       
      }
  }

  int degats = attaque_attaquant_postaction * (100 - defense_cible_postaction) / 100;
  if (degats < 0) degats = 0;
  
  perso[cible].pv -= degats;
 
  printf("%s attaque %s !\n", perso[attaquant].nom, perso[cible].nom);
  printf("Dégâts infligés : %d\n", degats);
  printf("%s a maintenant %d PV.\n", perso[cible].nom, perso[cible].pv);
}


/*************************************************************************************************************/
/* ACTION SPECIALE */
/*************************************************************************************************************/  

void actionSpeciale(Personnage perso[], int attaquant, int cible, int choixCompetence) {
  
 // JE DEMARRE LE CYCLE DE L'ACTION EN COURS
 perso[attaquant].competences[choixCompetence].cible_en_cours = cible;
 perso[attaquant].competences[choixCompetence].duree_en_cours = perso[attaquant].competences[choixCompetence].duree;
 perso[attaquant].competences[choixCompetence].recharge_en_cours = perso[attaquant].competences[choixCompetence].recharge;

 printf("\n%s lance une action sur %s\n [%s] (durée en cours %d / recharge en cours %d)\n     <>%s\n", 
                 perso[attaquant].nom,
                 perso[cible].nom,
                 perso[attaquant].competences[choixCompetence].nom, 
                 perso[attaquant].competences[choixCompetence].duree_en_cours,
                 perso[attaquant].competences[choixCompetence].recharge_en_cours,
                 perso[attaquant].competences[choixCompetence].desc);
}



/*************************************************************************************************************/
/* RENVOIE LE NBR DE COMPETENCES ACTIVES DE L'ATTAQUANT */
/*************************************************************************************************************/
int nbrCompSpecialesActives(Personnage perso[],int attaquant)
{
    int nbrCompActives = 0;
    // Afficher la liste des compétences de l'attaquant
    for(int ind_comp = 0; ind_comp < NB_COMP_COMB; ind_comp++) {
        // Competence Active si duree_en_cours == 0 && recharge_en_cours == 0
        if(perso[attaquant].competences[ind_comp].duree_en_cours == 0
            && perso[attaquant].competences[ind_comp].recharge_en_cours == 0)
            nbrCompActives ++;
    }
    // Renvoie le nombre de compétences nbrCompActives
    return nbrCompActives;
}


/*************************************************************************************************************/
/*************************************************************************************************************/
/* ATTAQUE */
/*************************************************************************************************************/
/*************************************************************************************************************/

void attaque(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int indicePerso) {

/*************************************************************************************************************/
/* LISTE DES PERSO DU JOUEUR CIBLE et LES ALLIES DE L'ATTAQUANT */
/*************************************************************************************************************/  

  int *persoVise = malloc(nbCombattantsEquipe * nbJ * sizeof(int)); // taille assez grande mais imprécise pour éviter d'avoir un segmentation fault
  if (persoVise == NULL) {
      printf("Erreur d'allocation mémoire pour persoVise.\n");
      exit(1);
  }

  int nbPersoVise = 0;
  
    // On affiche les infos des combattants du joueur attaqué    
  for (int k = 0; k < nbJ; k++) {

      printf("\nÉquipe de %s :\n\n", listeJoueurs[k].nom);
      for (int i = 0; i < nbCombattantsEquipe; i++) {
          

            // Affichage du Combattant ATTAQUANT
            if (listeJoueurs[k].numPerso[i] == indicePerso) 
            {   // Affichage de l'attaquant mais non sélectionnable
                printf("ATTAQUANT. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n", 
                 perso[indicePerso].nom, perso[indicePerso].pv,
                 perso[indicePerso].attaque, perso[indicePerso].defense,
                 perso[indicePerso].agilite, perso[indicePerso].vitesse);
                continue; // Pour ne pas avoir de chiffre de sélection du combattant
            } 
          
             int num_Perso = listeJoueurs[k].numPerso[i];
            
            // Affichage des Combattants HORS JEU cad si PV <= 0
            if (perso[num_Perso].pv <= 0) 
            {   // Affichage du combattant hors jeu mais non sélectionnable
                printf("MORT. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n", 
                 perso[num_Perso].nom, perso[num_Perso].pv,
                 perso[num_Perso].attaque, perso[num_Perso].defense,
                 perso[num_Perso].agilite, perso[num_Perso].vitesse);
                continue; // Pour ne pas avoir de chiffre de sélection du combattant
            } 
          
          
          // Affichage des Combattants SELECTIONNABLES
          
          persoVise[nbPersoVise] = num_Perso; // Récupérer le numéro des personnages de l'équipe adverse et de mes alliés

          
          printf("%d. %s (PV: %d, ATT: %d, DEF: %d, AG: %d, VIT: %d)\n",  //num_Perso équivalent à l'entier et pas au tableau 
                 nbPersoVise + 1, perso[num_Perso].nom, perso[num_Perso].pv,
                 perso[num_Perso].attaque, perso[num_Perso].defense,
                 perso[num_Perso].agilite, perso[num_Perso].vitesse);

                 nbPersoVise++;
                 
      }
        
  }


/*************************************************************************************************************/
/* LISTE DES ATTAQUES DISPONIBLES DE L'ATTAQUANT */
/*************************************************************************************************************/  

  int attaqueVise[NB_COMP_COMB + 1]; // 1 Attaque normale + NB_COMP_COMB compétences spéciales

  int nbAttaqueVise = 0;
  
  printf("\n1. Attaque Normale\n"); // Dans le tableau attaqueVise, la valeur sera -1 pour se différencier des compétences 0 ou 1
  
  attaqueVise[nbAttaqueVise] = -1;
  
  nbAttaqueVise++;
  
  for(int ind_comp = 0; ind_comp < NB_COMP_COMB; ind_comp++)
  {
       
            // Affichage de la compétence NON sélectionnable
            if (perso[indicePerso].competences[ind_comp].duree_en_cours > 0 || perso[indicePerso].competences[ind_comp].recharge_en_cours > 0) 
            {   
                 printf("INACTIVE. [%s] (durée en cours %d / recharge en cours %d)\n     <>%s\n", 
                 perso[indicePerso].competences[ind_comp].nom, 
                 perso[indicePerso].competences[ind_comp].duree_en_cours,
                 perso[indicePerso].competences[ind_comp].recharge_en_cours,
                 perso[indicePerso].competences[ind_comp].desc);
                 continue; // Pour ne pas avoir de chiffre de sélection de la compétence
            } 
          
          
            // Affichage de la compétence sélectionnable
          
            attaqueVise[nbAttaqueVise] = ind_comp; // Récupérer le num de compétence active de l'attaquant
                
            printf("%d. [%s] (durée %d / recharge %d)\n     <>%s\n", 
            nbAttaqueVise + 1,
            perso[indicePerso].competences[ind_comp].nom, 
            perso[indicePerso].competences[ind_comp].duree,
            perso[indicePerso].competences[ind_comp].recharge,
            perso[indicePerso].competences[ind_comp].desc);
                
            nbAttaqueVise++;
  }
  

/*************************************************************************************************************/
/* CHOIX DU PERSO CIBLEE */
/*************************************************************************************************************/  
  
  int choixAttaque = -1; //permet de vérifier plus rapidement si le "choixAttaque" du scanf est valide
  int correct = 0;
  
  // On demande à l'utilisateur de choisir un personnage à attaquer et on vérifie si son choix est valide 
  while (!correct) {
      printf("\nChoisissez le personnage à cibler : ");

        if (scanf("%d", &choixAttaque) == 1 && choixAttaque >= 1 && choixAttaque <= nbPersoVise) {
         
        correct = 1;
      } 
      
      else {
          printf("\nErreur. Choisissez un personnage entre 1 et %d.\n", nbPersoVise);
          
          int c;
          while ((c = getchar()) != '\n' && c != EOF) ;
      }
  }
  
/*************************************************************************************************************/
/* CHOIX DE l'ATTAQUE A LANCER */
/*************************************************************************************************************/  
  
  int choixAttaqueType = -1; //permet de vérifier plus rapidement si le "choixAttaqueType" du scanf est valide
  correct = 0;
  
  // On demande à l'utilisateur de choisir une attaque ou action à lancer et on vérifie si son choix est valide 
  while (!correct) {
      printf("\nChoisissez l'attaque ou l'action à lancer : ");

      if (scanf("%d", &choixAttaqueType) == 1 && choixAttaqueType >= 1 && choixAttaqueType <= nbAttaqueVise) {
         
        correct = 1;
      } 
      
      else {
          printf("\nErreur. Choisissez une attaque/action entre 1 et %d.\n", nbAttaqueVise);
          
          int d;
          while ((d = getchar()) != '\n' && d != EOF) ;
      }
  }

/*************************************************************************************************************/
/* DEMARRAGE DE L'ATTAQUE */
/*************************************************************************************************************/  

  int cible = persoVise[choixAttaque - 1]; // On récupère le numero du personnage visé par l'attaque = index dans le tableau perso[]
  int ind_AttaqueAction = attaqueVise[choixAttaqueType - 1]; // On récupère le numéro attaque à lancer soit -1 donc attaque normale soit 0/1 action speciale

  printf("%s attaque %s !\n", perso[indicePerso].nom, perso[cible].nom);


    /* ATTAQUE NORMALE */

  if(ind_AttaqueAction == -1){ 

    int esquive = esquivePerso(perso, nbJ, nbCombattantsEquipe, cible);

    if(esquive == 1){
      printf("%s a esquivé l'attaque de %s !\n", perso[cible].nom, perso[indicePerso].nom);
    }
    else{
      printf("Esquive ratée !\n");
      // void attaqueNormale(Joueur listeJoueurs[], Personnage perso[], int nbJ, int nbCombattantsEquipe, int joueurQuiAttaque, int attaquant, int cible) 
      attaqueNormale(listeJoueurs, perso, nbJ, nbCombattantsEquipe, joueurQuiAttaque, indicePerso, cible);
    }

  }
  
  /* ACTION SPECIALE */
  
  if(ind_AttaqueAction != -1){

    // void actionSpeciale(Personnage perso[], int attaquant, int cible, int choixCompetence) 
    actionSpeciale(perso, indicePerso, cible, ind_AttaqueAction); 

  }    
    
  free(persoVise);
}

int VerifFinCombat(int nbJ, int nbCombattantsEquipe, Joueur listeJoueurs[], Personnage perso[]) 
{
     
      // CONDITION D'ARRET
     int combattants_en_vie;
     int indPersoVerifie;
     
     for (int x = 0; x < nbJ; x++) {
          combattants_en_vie = nbCombattantsEquipe;
          for (int y = 0; y < nbCombattantsEquipe; y++) {
            indPersoVerifie = listeJoueurs[x].numPerso[y];
            
            if (perso[indPersoVerifie].pv <= 0)
                combattants_en_vie --;
            
          }
          if(combattants_en_vie <= 0)
          {    
                printf("\n>>> L'équipe %s a perdu <<<\n", listeJoueurs[x].nom );
                printf("\n>>> Le combat est terminé <<<\n");
                return 1; // Retourne VRAI si TERMINE
          }    
     }
     
     return 0; // Retourne FAUX si NON TERMINE

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

  int cible;
  int tour = 0;
  while (1) {
      printf("\n==================== TOUR %d ====================\n", tour);

      // Je mets à jour l'ensemble des actions spéciales en cours
      for (int ind_comb = 0; ind_comb < nbCombattantsTotal; ind_comb++)
      {
        for (int j = 0; j < NB_COMP_COMB; j++)
        {
        
            // DIMINUTION DU PV DE LA CIBLE  
            if( perso[ind_comb].competences[j].duree_en_cours > 0 // ACTION ACTIVE
                && perso[ind_comb].competences[j].propriete == PV
                && perso[ind_comb].competences[j].type_cible == ADV )
                
            {   cible = perso[ind_comb].competences[j].cible_en_cours;
                perso[cible].pv = perso[cible].pv * (100 - perso[ind_comb].competences[j].valeur) / 100; printf("DIMINUTION DU PV DE LA CIBLE "); }
            
            // VERIFICATION SI FIN DE COMBAT
            if(VerifFinCombat(nbJ, nbCombattantsEquipe, listeJoueurs, perso) == 1)
            {
                free(vitesseTour);
                free(indiceCombattant);
                free(indiceJoueur);
                exit(0); // SORTIE NORMALE DU PROGRAMME
            }
            
            // AUGMENTATION DU PV DE LA CIBLE  
            if( perso[ind_comb].competences[j].duree_en_cours > 0 // ACTION ACTIVE
                && perso[ind_comb].competences[j].propriete == PV
                && perso[ind_comb].competences[j].type_cible == ALL )
                
            {   cible = perso[ind_comb].competences[j].cible_en_cours; 
                perso[cible].pv = perso[cible].pv * (100 + perso[ind_comb].competences[j].valeur) / 100; printf("AUGMENTATION DU PV DE LA CIBLE"); }
    
            
            // DECREMENTATION DES INDICATEURS D'ACTIVITE DE L'ACTION  
            if( perso[ind_comb].competences[j].duree_en_cours > 0 ) perso[ind_comb].competences[j].duree_en_cours--;
            if( perso[ind_comb].competences[j].duree_en_cours <= 0
                && perso[ind_comb].competences[j].recharge_en_cours > 0 ) perso[ind_comb].competences[j].recharge_en_cours--;
            if( perso[ind_comb].competences[j].duree_en_cours <= 0
                && perso[ind_comb].competences[j].recharge_en_cours <= 0 ) perso[ind_comb].competences[j].cible_en_cours = 0;   // cible non définie si action non active
            
        }

      }
      
      // On parcours tous les combattants pour augmenter les vitesses et lancer les attaques
      for (int k = 0; k < nbJ; k++) {
          printf("\n%s\n", listeJoueurs[k].nom);

          for (int i = 0; i < nbCombattantsTotal; i++) {
              if (indiceJoueur[i] == k) {
                  int copiePerso = indiceCombattant[i];
                  printf("%s :\n", perso[copiePerso].nom);

                  // Ajout de la vitesse slt si combattant en vie
                  if (perso[indiceCombattant[i]].pv > 0)
                  vitesseTour[i] += perso[copiePerso].vitesse;

                  afficherBarreVitesse(vitesseTour[i]);
              }
              // JE NE PEUX ATTAQUER QUE SI JE SUIS EN VIE
              while (vitesseTour[i] >= 100 && perso[indiceCombattant[i]].pv > 0) {
                
                attaque(listeJoueurs, perso, nbJ, nbCombattantsEquipe, indiceJoueur[i], indiceCombattant[i]);
                
                // VERIFICATION SI FIN DE COMBAT
                if(VerifFinCombat(nbJ, nbCombattantsEquipe, listeJoueurs, perso) == 1)
                {
                    free(vitesseTour);
                    free(indiceCombattant);
                    free(indiceJoueur);
                    exit(0); // SORTIE NORMALE DU PROGRAMME
                }
                
                vitesseTour[i] -= 100;
               
              }
          }
      }

      tour++;
      sleep(3);

  }
}














