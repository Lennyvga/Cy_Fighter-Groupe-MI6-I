#ifndef PERSO_H
#define PERSO_H

typedef struct{
    char nom[20];
    int pv;
    int pvMAx;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    }Info;

typedef struct{
    char nom;
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
