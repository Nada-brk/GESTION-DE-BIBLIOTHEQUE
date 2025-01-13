#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "biblib.h"


FILE*fichier;
char nom_user[100];

// Fonction permettant de saisir le nom de l'utilisateur
void saisirNomUtilisateur()
{
    // Demande à l'utilisateur de saisir son nom
    printf("saisir votre nom pour utiliser l'application : ");

    // Lit la chaîne de caractères saisie par l'utilisateur (jusqu'à un retour à la ligne)
    scanf("%[^\n]", nom_user);

    // Vérifie si l'utilisateur a saisi "sortir"
    if(strcmp(nom_user, "sortir") == 0)
    {
        // Si l'utilisateur a saisi "sortir", affiche un message et termine
        printf("vous avez quitter l'application.\n");
    }
    else
    {
        // Sinon, affiche le menu principal de l'application
        afficherMenu();
    }
}

// Fonction permettant d'ajouter un livre dans le fichier "livres.csv"
void ajouterLivre()
{
    int ID_ajout; // ID du livre à ajouter
    system("cls"); // Efface l'écran (spécifique à Windows)
    fflush(stdin); // Vide le tampon d'entrée
    char buffer[1000]; // Tampon pour lire les lignes du fichier
    fichier = fopen("livres.csv", "r+"); // Ouvre le fichier en lecture/écriture

    // Vérifie si le fichier existe
    if (fichier == NULL)
    {
        printf("fichier introuvable");
        exit(1); // Quitte le programme en cas d'erreur
    }

    // Demande à l'utilisateur d'entrer l'ID du livre à ajouter
    printf("veuillez entrer l'ID du livre a ajouter:\n");
    scanf("%d", &ID_ajout);

    Livre p; // Structure pour stocker les informations du livre
    int trouve = 0; // Indicateur pour vérifier si le livre existe déjà
    fgets(buffer, sizeof(buffer), fichier); // Ignore la première ligne (en-tête)

    // Parcourt le fichier pour vérifier si l'ID du livre existe déjà
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur,
                  &p.prix, p.categorie, &p.disponibilite) == 8)
    {
        if (ID_ajout == p.ID)
        {
            trouve = 1; // Livre trouvé
            break;
        }
    }

    // Si le livre n'existe pas, ajoute les informations dans le fichier
    if (trouve == 0)
    {
        fseek(fichier, 0, SEEK_END); // Place le pointeur à la fin du fichier
        printf("le livre n'est pas disponible. Veuillez entrer les informations du livre:\n");
        fflush(stdin);

        // Saisie et écriture des informations du livre
        p.ID = ID_ajout;
        fprintf(fichier, "%d,", p.ID);
        fflush(stdin);

        printf("entrer le titre :\n");
        scanf("%[^\n]", p.titre);
        p.titre[0] = toupper(p.titre[0]); // Met la première lettre en majuscule
        fprintf(fichier, "%s,", p.titre);
        fflush(stdin);

        printf("entrer l'auteur:\n");
        scanf("%[^\n]", p.auteur);
        fprintf(fichier, "%s,", p.auteur);
        fflush(stdin);

        printf("entrer la description :\n");
        scanf("%[^\n]", p.description);
        fprintf(fichier, "%s,", p.description);
        fflush(stdin);

        // Associe le nom d'utilisateur courant
        strcpy(p.nom_d_utilisateur, nom_user);
        fprintf(fichier, "%s,", p.nom_d_utilisateur);
        fflush(stdin);

        printf("entrer le prix:\n");
        scanf("%f", &p.prix);
        fprintf(fichier, "%f,", p.prix);
        fflush(stdin);

        printf("entrer la categorie:\n");
        scanf("%[^\n]", p.categorie);
        fprintf(fichier, "%s,", p.categorie);
        fflush(stdin);

        // Définit la disponibilité à 1 (disponible)
        p.disponibilite = 1;
        fprintf(fichier, "%d\n", p.disponibilite);
    }

    fclose(fichier); // Ferme le fichier

    // Messages de confirmation selon le résultat
    if (trouve == 0)
    {
        printf("\nlivre ajouter avec success");
        sleep(2); // Pause de 2 secondes
    }
    if (trouve == 1)
    {
        printf("livre existe deja");
        sleep(2); // Pause de 2 secondes
    }
}


// Fonction permettant de supprimer un livre du fichier "livres.csv"
void supprimerLivre()
{
    int ID_supp; // ID du livre à supprimer
    char buffer[1000]; // Tampon pour lire les lignes du fichier
    int trouve = 0; // Indicateur pour vérifier si le livre a été trouvé
    Livre p; // Structure pour stocker les informations du livre

    // Demande à l'utilisateur de saisir l'ID du livre à supprimer
    printf("veuillez entrer l'ID du livre que vous souhaiter supprimer : ");
    scanf("%d", &ID_supp);

    // Ouvre le fichier des livres en lecture et crée un fichier temporaire en écriture
    fichier = fopen("livres.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    // Vérifie si l'ouverture des fichiers a échoué
    if (fichier == NULL || temp == NULL)
    {
        printf("fichier introuvable");
        exit(1); // Quitte le programme en cas d'erreur
    }

    // Copie l'en-tête (première ligne) du fichier source vers le fichier temporaire
    fgets(buffer, sizeof(buffer), fichier);
    fputs(buffer, temp);

    // Parcourt les enregistrements du fichier des livres
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &p.ID, p.titre, p.auteur, p.description,
                  p.nom_d_utilisateur, &p.prix, p.categorie, &p.disponibilite) == 8)
    {
        // Si l'ID correspond à celui à supprimer, on ignore cet enregistrement
        if (p.ID == ID_supp)
        {
            trouve = 1; // Marque que le livre a été trouvé
            continue; // Passe au suivant sans écrire dans le fichier temporaire
        }

        // Sinon, écrit les informations dans le fichier temporaire
        fprintf(temp, "%d,%s,%s,%s,%s,%f,%s,%d\n",
                p.ID, p.titre, p.auteur, p.description,
                p.nom_d_utilisateur, p.prix, p.categorie, p.disponibilite);
    }

    // Ferme les fichiers
    fclose(fichier);
    fclose(temp);

    // Remplace l'ancien fichier par le nouveau
    remove("livres.csv"); // Supprime le fichier original
    rename("temp.csv", "livres.csv"); // Renomme le fichier temporaire

    // Affiche un message en fonction du résultat
    if (trouve == 1)
    {
        printf("le livre avec l'ID %d a ete supprime avec succes!", ID_supp);
        sleep(2); // Pause de 2 secondes
    }
    else if (trouve == 0)
    {
        printf("livre avec l'ID %d est introuvable!", ID_supp);
        sleep(2); // Pause de 2 secondes
    }
}


// Fonction permettant de trier les livres par titre (ordre alphabétique)
void trier_par_titre()
{
    Livre A; // Structure temporaire pour échanger les livres
    Livre book[255]; // Tableau pour stocker les livres (max 255 livres)
    char buffer[1000]; // Tampon pour lire les lignes du fichier
    int nbr_livres = 0; // Compteur du nombre de livres lus

    // Ouvre le fichier des livres en lecture
    fichier = fopen("livres.csv", "r");
    if (fichier == NULL)
    {
        printf("fichier introuvable");
        exit(1); // Quitte le programme en cas d'erreur
    }

    // Crée un fichier temporaire pour écrire les données triées
    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL)
    {
        printf("fichier introuvable");
        exit(2); // Quitte le programme en cas d'erreur
    }

    int i = 0;
    fgets(buffer, sizeof(buffer), fichier); // Lit l'en-tête du fichier original
    fputs(buffer, temp); // Écrit l'en-tête dans le fichier temporaire

    // Lit les livres depuis le fichier et les stocke dans le tableau `book`
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &book[nbr_livres].ID, book[nbr_livres].titre, book[nbr_livres].auteur,
                  book[nbr_livres].description, book[nbr_livres].nom_d_utilisateur,
                  &book[nbr_livres].prix, book[nbr_livres].categorie, &book[nbr_livres].disponibilite) == 8)
    {
        nbr_livres++; // Incrémente le compteur de livres
    }

    // Tri des livres par titre en utilisant l'algorithme de tri par échange (Bubble Sort)
    for (i = 0; i < nbr_livres - 1; i++)
    {
        for (int j = i + 1; j < nbr_livres; j++)
        {
            // Compare les titres des livres (ordre alphabétique)
            if (strcmp(book[i].titre, book[j].titre) > 0)
            {
                // Échange des livres si nécessaire
                A = book[i];
                book[i] = book[j];
                book[j] = A;
            }
        }
    }

    // Écrit les livres triés dans le fichier temporaire
    for (i = 0; i < nbr_livres; i++)
    {
        fprintf(temp, "%d,%s,%s,%s,%s,%f,%s,%d\n",
                book[i].ID, book[i].titre, book[i].auteur, book[i].description,
                book[i].nom_d_utilisateur, book[i].prix, book[i].categorie, book[i].disponibilite);
    }

    // Ferme les fichiers
    fclose(fichier);
    fclose(temp);

    // Remplace l'ancien fichier par le nouveau fichier trié
    remove("livres.csv"); // Supprime le fichier original
    rename("temp.csv", "livres.csv"); // Renomme le fichier temporaire

    // Affiche un message de confirmation
    printf("opertion avec success!");
    sleep(2); // Pause de 2 secondes
}

//fonction permettant d afficher le menu
void afficherMenu()
{
    int choix; // Variable pour stocker le choix de l'utilisateur
    while(1) // Boucle infinie pour afficher le menu jusqu'à ce que l'utilisateur choisisse de quitter
    {
        system("cls"); // Efface l'écran (spécifique à Windows)

        // Affichage du menu avec les différentes options disponibles
        printf("\n Gestion de Bibliotheque \n");
        printf("1. Ajouter un livre\n");
        printf("2. supprimerLivres\n");
        printf("3. rechercheLivres\n");
        printf("4. trierLivres\n");
        printf("5. modifier livres \n");
        printf("6. afficher tous les livres \n");
        printf("0. Quitter\n");

        // Demande à l'utilisateur de saisir un choix
        printf("\n Entrez votre choix : ");
        scanf("%d", &choix);

        // Traitement du choix de l'utilisateur avec une structure switch
        switch (choix)
        {
        case 1:
            // Appelle la fonction pour ajouter un livre
            ajouterLivre();
            break;
        case 2:
            // Appelle la fonction pour supprimer un livre
            supprimerLivre();
            break;
        case 3:
            // Appelle la fonction pour rechercher un livre
            rechercheLivre();
            break;
        case 4:
            // Appelle la fonction pour trier les livres par titre
            trier_par_titre();
            break;
        case 5:
            // Appelle la fonction pour modifier un livre
            modifierLivre();
            break;
        case 6:
            // Appelle la fonction pour afficher tous les livres
            afficher_liste_Livre();
            break;
        case 0:
            // Affiche un message de fin et sort de la boucle (ferme l'application)
            printf("\nMerci d'avoir utiliser  l'application. Au revoir !\n");
            break; // Quitte la boucle infinie
        default:
            // Si l'utilisateur entre un choix invalide, un message d'erreur s'affiche
            printf("\nChoix invalide. Veuillez ressayer.\n");
        }
    }
}

//fonction permettantde rechercher un livre dans le fichier "livres.csv"
void rechercheLivre()
{
    fichier = fopen("livres.csv","r"); // Ouverture du fichier "livres.csv" en lecture
    if (fichier == NULL) // Vérification si le fichier ne s'est pas ouvert correctement
    {
        printf("Erreur d'ouverture du fichier.\n"); // Affichage d'un message d'erreur si le fichier ne peut pas être ouvert
        return 1; // Retourne 1 en cas d'erreur (sortie de la fonction)
    }

    char buffer[1000]; // Buffer pour lire les lignes du fichier
    int nbLivres = 0; // Compteur pour le nombre de livres (non utilisé ici)
    char titre_rech[30]; // Tableau pour stocker le titre recherché
    char auteur_rech[30]; // Tableau pour stocker l'auteur recherché
    Livre p; // Structure pour stocker un livre temporairement

    int trouve = 0; // Variable pour indiquer si le livre a été trouvé

    // Demande à l'utilisateur de saisir le titre du livre à rechercher
    printf("\nEntrez le titre du livre a rechercher : ");
    while (getchar() != '\n'); // Vide le buffer d'entrée
    scanf("%[^\n]", titre_rech); // Lit le titre recherché

    // Demande à l'utilisateur de saisir l'auteur du livre à rechercher
    printf("\nEntrez l'auteur du livre a rechercher : ");
    while (getchar() != '\n'); // Vide à nouveau le buffer d'entrée
    scanf("%[^\n]", auteur_rech); // Lit l'auteur recherché

    fgets(buffer, sizeof(buffer), fichier); // Ignore la première ligne (en-têtes des colonnes)

    // Parcours du fichier ligne par ligne pour rechercher le livre
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur,
                  &p.prix, p.categorie, &p.disponibilite) == 8) // Si la ligne est lue correctement
    {
        // Si le titre et l'auteur correspondent aux critères de recherche
        if (strcmp(p.titre, titre_rech) == 0 && strcmp(p.auteur, auteur_rech) == 0)
        {
            trouve = 1; // Livre trouvé
            break; // Sort de la boucle dès qu'on trouve le livre
        }
    }

    fclose(fichier); // Ferme le fichier après la lecture

    if (trouve == 0) // Si le livre n'a pas été trouvé
    {
        printf("Le livre que vous recherchez n'existe pas !!"); // Affichage d'un message d'erreur
        sleep(2); // Pause de 2 secondes avant de retourner au menu
    }
    if (trouve == 1) // Si le livre a été trouvé
    {
        system("cls"); // Efface l'écran (spécifique à Windows)
        // Affiche les informations du livre trouvé
        printf("%d\t%s\t%s\t%s\t%s\t%f\t%s\t%d\n", p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur, p.prix, p.categorie, p.disponibilite);
        getch(); // Attente d'une touche de l'utilisateur pour continuer
    }
}

//fonction permettant de modifier les informations d un livre dans le fichier "livres.csv"
void modifierLivre()
{
    Livre p; // Déclare une variable de type Livre pour stocker les informations d'un livre
    int ID_mod; // ID du livre à modifier
    int trouve = 0; // Variable pour vérifier si le livre a été trouvé
    int choix; // Variable pour stocker le choix de modification
    char buffer[1000]; // Buffer pour lire les lignes du fichier
    fichier = fopen("livres.csv", "r"); // Ouvre le fichier des livres en lecture
    if (fichier == NULL) // Si le fichier ne peut pas être ouvert
    {
        printf("Erreur d'ouverture du fichier.\n"); // Affiche un message d'erreur
        return 1; // Retourne 1 pour indiquer une erreur
    }

    // Ouvre un fichier temporaire pour stocker les livres après modification
    FILE* temp = fopen("temp.csv", "w");
    if (temp == NULL) // Si le fichier temporaire ne peut pas être ouvert
    {
        printf("Erreur d'ouverture du fichier.\n"); // Affiche un message d'erreur
        return 1; // Retourne 1 pour indiquer une erreur
    }

    // Demande à l'utilisateur d'entrer l'ID du livre à modifier
    printf("Entrez l'ID du livre à modifier : ");
    scanf("%d", &ID_mod); // Lit l'ID du livre

    fgets(buffer, sizeof(buffer), fichier); // Ignore la première ligne (en-têtes)
    fputs(buffer, temp); // Copie l'en-tête dans le fichier temporaire

    // Parcours le fichier des livres ligne par ligne
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur,
                  &p.prix, p.categorie, &p.disponibilite) == 8) // Si la ligne est lue correctement
    {
        if (p.ID == ID_mod) // Si l'ID du livre correspond à celui saisi
        {
            trouve = 1; // Livre trouvé, on peut le modifier
            printf("\nModification du livre\n");
            printf("1. Auteur\n");
            printf("2. Titre\n");
            printf("3. Description\n");
            printf("4. Nom d'utilisateur\n");
            printf("5. Prix\n");
            printf("6. Catégorie\n");
            printf("7. Disponibilité\n");
            printf("0. Quitter\n");
            printf("Entrez votre choix : ");
            scanf("%d", &choix); // Lit le choix de modification

            switch (choix)
            {
            case 1:
                // Modifie l'auteur du livre
                printf("Entrez l'auteur : ");
                while (getchar() != '\n'); // Vide le buffer d'entrée
                scanf("%[^\n]", p.auteur); // Lit le nouvel auteur
                break;
            case 2:
                // Modifie le titre du livre
                printf("Entrez le titre : ");
                while (getchar() != '\n');
                scanf("%[^\n]", p.titre); // Lit le nouveau titre
                break;
            case 3:
                // Modifie la description du livre
                printf("Entrez la description : ");
                while (getchar() != '\n');
                scanf("%[^\n]", p.description); // Lit la nouvelle description
                break;
            case 4:
                // Modifie le nom de l'utilisateur
                printf("Entrez le nom de l'utilisateur : ");
                while (getchar() != '\n');
                scanf("%[^\n]", p.nom_d_utilisateur); // Lit le nouveau nom d'utilisateur
                break;
            case 5:
                // Modifie le prix du livre
                printf("Entrez le prix : ");
                while (getchar() != '\n');
                scanf("%f", &p.prix); // Lit le nouveau prix
                break;
            case 6:
                // Modifie la catégorie du livre
                printf("Entrez la catégorie : ");
                while (getchar() != '\n');
                scanf("%[^\n]", p.categorie); // Lit la nouvelle catégorie
                break;
            case 7:
                // Modifie la disponibilité du livre
                printf("Entrez la disponibilité : ");
                while (getchar() != '\n');
                scanf("%d", &p.disponibilite); // Lit la nouvelle disponibilité
                break;
            case 0:
                // Quitte le processus de modification
                printf("Quittez !!!! ");
                while (getchar() != '\n');
                break;
            default:
                // Si le choix est invalide, affiche un message d'erreur
                printf("Choix invalide. Veuillez réessayer.");
            }
        }
        // Écrit les informations du livre (modifiées ou non) dans le fichier temporaire
        fprintf(temp, "%d,%s,%s,%s,%s,%f,%s,%d\n", p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur, p.prix, p.categorie, p.disponibilite);
    }

    fclose(temp); // Ferme le fichier temporaire
    fclose(fichier); // Ferme le fichier original

    // Remplace le fichier original par le fichier temporaire
    remove("livres.csv");
    rename("temp.csv", "livres.csv");

    if (trouve == 0) // Si le livre n'a pas été trouvé
    {
        printf("Le livre n'est pas trouvé !"); // Affiche un message d'erreur
        sleep(3); // Attends 3 secondes
    }
    else if (trouve == 1) // Si le livre a été modifié avec succès
    {
        printf("Le livre est modifié avec succès !"); // Affiche un message de confirmation
        sleep(3); // Attends 3 secondes
    }
}

//fonction permettant d afficher la liste des livres
void afficher_liste_Livre()
{
    Livre p; // Déclare une variable de type Livre pour stocker les informations de chaque livre
    char buffer[1000]; // Buffer pour lire les lignes du fichier
    int num_livre = 1; // Compteur pour numéroter les livres à afficher
    fichier = fopen("livres.csv", "r"); // Ouvre le fichier des livres en lecture
    if (fichier == NULL) // Si le fichier ne peut pas être ouvert
    {
        printf("Erreur d'ouverture du fichier.\n"); // Affiche un message d'erreur
        return 1; // Retourne 1 pour indiquer une erreur
    }

    system("cls"); // Efface l'écran pour afficher la liste des livres proprement
    fgets(buffer, sizeof(buffer), fichier); // Lit et ignore la première ligne (en-tête du fichier)

    // Lit chaque ligne du fichier contenant les informations d'un livre
    while (fscanf(fichier, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%d\n",
                  &p.ID, p.titre, p.auteur, p.description, p.nom_d_utilisateur,
                  &p.prix, p.categorie, &p.disponibilite) == 8) // Si la ligne est lue correctement
    {
        // Affiche les informations du livre avec un formatage
        printf("Le livre %d:\t", num_livre);
        printf("%d\t", p.ID); // Affiche l'ID du livre
        printf("%-20s\t", p.titre); // Affiche le titre du livre avec un alignement de 20 caractères
        printf("%-20s\t", p.auteur); // Affiche l'auteur du livre
        printf("%-20s\t", p.description); // Affiche la description du livre
        printf("%-20s\t", p.nom_d_utilisateur); // Affiche le nom de l'utilisateur
        printf("%-f\t", p.prix); // Affiche le prix du livre
        printf("%-20s\t", p.categorie); // Affiche la catégorie du livre
        printf("%-d\n", p.disponibilite); // Affiche la disponibilité du livre
        num_livre++; // Incrémente le compteur de livres
    }

    fclose(fichier); // Ferme le fichier une fois que tous les livres ont été affichés
    getch(); // Attend une touche de l'utilisateur avant de poursuivre
}

