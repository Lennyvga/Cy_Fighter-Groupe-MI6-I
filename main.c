#include <stdio.h>
#include <stdlib.h>
#include "perso.h"
#include "combat.h"
#include <time.h>
#include <string.h>
//#include "verif.h"


int main(){
    
    srand(time(NULL));
    int nbJ = 0;
    Joueur *listeJoueurs;
    int nbCombattantsEquipe = 3;
    
    // Allocation des personnages pour toutes les équipes
    Personnage *perso = malloc(6 * sizeof(Personnage));
    if(perso == NULL){
      printf("Erreur d'allocation - 1 ");
      exit(1);
    };
    
    // Message d'accueil et choix du nombre de joueurs
    nbJoueur(&nbJ);
    
    
    // Allocation dynamique pour les noms des joueurs
    listeJoueurs =  malloc(nbJ * sizeof(Joueur));
    if(listeJoueurs == NULL){
        printf("Erreur d'allocation - 1 ");
        exit(1);
    }

    // Creation des Joueurs
    creationJoueur(listeJoueurs, nbJ);
     
    // Extraction des infos des combattants du fichier
    fichierPersos(perso,  "perso.txt");
     
    // Extraction des infos des compétences du fichier
    fichierCompetences(perso,  "compspe.txt");
     
    // Affichage de tous les combattants
    afficherPersos(perso);
    
    // Choix des combattants par équipe/joueur
    choisirPersos( &nbCombattantsEquipe, nbJ, listeJoueurs, perso); 
    
    // Démarrage du combat
    chargement(nbJ, nbCombattantsEquipe, listeJoueurs, perso);
    
    for (int i = 0; i < nbJ; i++) {
      free(listeJoueurs[i].nom); // Libérer les noms des joueurs
    }

    free(listeJoueurs);
}
