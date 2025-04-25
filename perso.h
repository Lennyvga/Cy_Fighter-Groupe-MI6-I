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
    }Info;

    extern Info perso[3];//A COMPRENDRE COMMENT ON UTILISE LE EXTERN !!!!!

typedef struct{
    char *nom;
    int *numEquipe;
    }Joueur;


// Déclarations des personnages
extern Info guerrier;
extern Info sorcier;
extern Info tank;

#endif
