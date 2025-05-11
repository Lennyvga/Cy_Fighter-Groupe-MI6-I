#ifndef PERSO_H
#define PERSO_H

//const int TAILLE_FICHIER = 6;

typedef enum {
    ALL, ADV
/*  0  , 1. , 2  , 3  */
} Type_combattant;

typedef enum {
    ATT, DEF, AGI, PV
/*  0  , 1. , 2  , 3  */
} Type_propriete;
    
typedef struct{
    char nom[50];
    char desc[100];
    int duree;
    int recharge;
    int duree_en_cours; //variable
    int recharge_en_cours; //variable
    int valeur;
    int cible_en_cours; //variable
    int cible; /* ALL=0, ADV=1 */
    int propriete; /*  ATT=0, DEF=1, AGI=2, PV=3 */
}CompSpe;
    
typedef struct{
    char nom[20];
    int pv; //variable
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    CompSpe competences[2];
}Personnage;

typedef struct{
    char *nom;
    int numPerso[3]; // Tableau pour stocker les numéros des personnages choisis //Changer la taille en fonction du nombre de personnages
    //Personnage persos[3];
}Joueur;




#endif