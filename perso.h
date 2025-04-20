#ifndef PERSO_H
#define PERSO_H

typedef struct{
    char nom[20];
    int pv;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    }Info;

    extern Info perso[3];//A COMPRENDRE COMMENT ON UTILISE !!!!!

typedef struct{
    char *nom;
    int *equipe;
    }Joueur;
    
typedef struct{
    char nom;
    int damage;
    int temps;
    }CompSpe;
    

// Déclarations des personnages
extern Info guerrier;
extern Info sorcier;
extern Info tank;

#endif
