//
// Created by lentz on 09/11/2022.
//

#include "tableau.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
# include <unistd.h>



void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}
///////////////////////////////////////////////////////////////////////////////////
int ** creer_matrice(int size) {
    int** Mat;
    int i;

    Mat = (int **) malloc(size * sizeof(int *));
    for ( i = 0; i < size; i++) {
        Mat[i] = (int *) malloc(size* sizeof(int));
    }
    return Mat;
}
////////////////////////////////////////////////////////////////
int nombre_case_vide(int** grille_jeu,int taille) {
    int i, j, cpt = 0;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            if ((grille_jeu[i][j] != 0) && (grille_jeu[i][j] != 1)) {
                cpt ++;
            }
        }
    }
    return cpt;
}
//////////////////////////////////////////////////////////////
void verifier_les_0_et_les_1(int **Matrice, int taille) {
    int i;
    int j = 0, cpt_ligne = 0, cpt_colonne = 0;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            cpt_ligne = cpt_ligne + Matrice[i][j];
        }
        if (cpt_ligne > 2) {
            printf("Les saisies faites a la  ligne  %d sont incorrectes ", i++);
        } else
            printf("Les saisies faites a la  ligne %d sont correctes", i++);
    }
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            cpt_colonne = cpt_colonne + Matrice[i][j];
        }
        if (cpt_colonne > 2) {
            printf("Les saisies faites a la  ligne  %d sont incorrectes ", j++);
        } else
            printf("Les saisies faites a la  ligne  %d sont correctes ", j++);
    }
}

int **remplir_matrice_4x4(int size){
    int i, j;
    int Matrice_solution_4X4 [4][4]={
            {1,0,0,1},
            {1,0,1,0},
            {0,1,1,0},
            {0,1,0,1}
    };
    int** Matrice_sol_4x4= creer_matrice(size);

    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++) {
            Matrice_sol_4x4[i][j] = Matrice_solution_4X4[i][j];
        }
    }

    return Matrice_sol_4x4;
}

int ** remplir_matrice_8x8 (int size){
    int i, j;
    int Matrice_solution_8x8[8][8] = {
            {1, 0, 1, 1, 0, 1, 0, 0},
            {1, 0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 1, 0},
            {1, 0, 1, 0, 0, 1, 0, 1},
            {0, 1, 0, 0, 1, 0, 1, 1},
            {0, 0, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 0, 1, 0, 0, 1}
    };
    int**Matrice_sol_8x8= creer_matrice(size);
    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++) {
            Matrice_sol_8x8[i][j] = Matrice_solution_8x8[i][j];
        }
    }
    return Matrice_sol_8x8;
}

void regles_du_jeu() {
    printf("-----------------------------------------\n");
    printf(" | Lisez attentivement les regles du jeu |\n");
    printf("-----------------------------------------\n");
    printf("1-Dans une ligne, il doit y avoir autant de 0 que de 1. \n");
    printf("2-Dans une colonne, il doit y avoir autant de 0 que de 1. \n");
    printf("3-Il ne peut pas y avoir deux lignes identiques dans une grille. \n");
    printf("4-Il ne peut pas y avoir deux colonnes identiques dans une grille. \n");
    printf("5-Dans une ligne ou une colonne, il ne peut y avoir plus de deux 0 ou deux 1 à la suite. \n");
}
void afficher_matrice(int** Matrice, int dim) {
    int i, j;
    char caractere='a';
    for (i=0;i<dim;i++){
        printf ("  %d ",i); // bordure
    }
    printf("\n");
    for (i = 0; i < dim; i++) {
    }
    for (i = 0; i < dim; i++) {
        printf("%c||",caractere); // bordure
        for (j = 0; j < dim; j++) {
            if (Matrice[i][j]==9){
                printf("_ |");
            } else
            {
                printf(" %d |", Matrice[i][j]);
            }
        } caractere++;
        printf("\n");
        printf("  -----------------------------\n");

    }


}

int ** creer_masque_manuel(int size) {
    int i, j, valeur;
    printf("-- Masque manuel --\n");
    int **masque = creer_matrice(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            do {
                printf("Saisir les donnees du masque pour la ligne: %d, et la colonne %d:\n",i,j);
                scanf("%d", &masque[i][j]);
            }
            while (masque[i][j] > 1 || masque[i][j] <0);
        }
    }
    return masque;
}

int ** creer_masque_aleatoire(int size) {
    int i, j;
    srand(time(NULL));
    int **masque;
    masque = creer_matrice(size);
    printf("-- Masque aleatoire --\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            masque[i][j] = rand() % 2;
        }

    }

    return masque ;
}
int** generer_jeu(int** solution,int** masque,int size){
    int i,j;
    printf("-- Grille de jeu --\n");
    int** grille_jeu= creer_matrice(size);
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(masque[i][j]==1){
                grille_jeu[i][j]=solution[i][j];
            } else{
                grille_jeu[i][j]=9;
            }
        }
    }
    return grille_jeu;
}


void begin_the_game_manuel() {
    int dimension_choisie;
    char user_name[30];
    printf(" Saissez vote username :\n");
    scanf("%s", &user_name);

    Color(12, 0);
    printf(" |1| Bienvenue dans le jeu de Takuzu - %s - |0| \n", user_name);
    Color(15, 0);
    printf(" \n");
    do {
        printf("Saisir le type de la grille de jeu,  4 ou 8 : ");
        scanf("%d", &dimension_choisie);
    } while (dimension_choisie != 4 && dimension_choisie != 8);
    int** solution;
    if(dimension_choisie==4){
        solution = remplir_matrice_4x4(dimension_choisie);
    }
    else
    {
        solution = remplir_matrice_8x8(dimension_choisie);

    }

    int** masque = creer_masque_manuel(dimension_choisie);
    afficher_matrice(masque,dimension_choisie);
    printf("\n");
    int** grille_jeu = generer_jeu(solution, masque, dimension_choisie);
    afficher_matrice(grille_jeu, dimension_choisie);
    saisir_chiffre_utilisateur(grille_jeu, solution, dimension_choisie);
}



