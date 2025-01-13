#ifndef BIBLIB_H_INCLUDED
#define BIBLIB_H_INCLUDED
#define MAX_TAILLE 100
#include <conio.h>

typedef struct{
int ID;
char titre[100];
char auteur[100];
char description[100];
char nom_d_utilisateur[100];
float prix;
char categorie[100];
int disponibilite;//disponible ou non disponible
}Livre;

void saisirNomUtilisateur(); //valide
void ajouterLivre(); //valide
void supprimerLivre(); //valide
void rechercheLivre(); //valide
void trier_par_titre(); //valide
void afficherMenu(); //valide
void modifierLivre(); //valide
void afficher_liste_Livre(); //valide


#endif // BIBLIB_H_INCLUDED
