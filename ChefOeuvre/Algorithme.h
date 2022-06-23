#ifndef ALGORITHME_H
#define ALGORITHME_H

int ** creer_tableau(int nb_lignes, int nb_colonnes);
void liberer_tableau(int ** tableau, int nb_lignes);
void afficher_tableau(int ** tableau, int nb_lignes, int nb_colonnes);
void InitialisationSerpent(int **tableau);
void decalagedroite(int **serpent, int direction, int aManger, int * taille_serpent);


#endif