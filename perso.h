#ifndef PERSO_H
#define PERSO_H

    
typedef struct{
    char nom;
    int damage;
    int temps;
    }CompSpe;
    

typedef struct{
    char nom[20];
    int pv;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    CompSpe competence;
    }Personnage;

   

typedef struct{
    char *nom;
    int numPerso[3]; // Tableau pour stocker les numéros des personnages choisis //Changer la taille en fonction du nombre de personnages
    Personnage *personnages;
    }Joueur;




#endif
