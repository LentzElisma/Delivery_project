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