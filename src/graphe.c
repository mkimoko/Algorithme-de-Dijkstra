
#include "../include/graphe.h"



void initGraphe(Graphe * g, int * m, int nbsommets)
{
	int i, j;
	g->nbsommets = nbsommets;
	g->matrice = (int *)malloc(sizeof(int)*nbsommets*nbsommets);
	for (i=0; i<nbsommets; i++) {
		
		for (j=0; j<nbsommets; j++) g->matrice[i*nbsommets + j] = m[i*nbsommets + j];	
	}
}


/*Affiche un graphe avec son nombre de sommets*/
void afficheGraphe(const Graphe * G)
{
	
	int i, j;
	printf("Nombre de sommets : %d \n\n",G->nbsommets);
	printf("Matrice d'adjacence : \n\n");
	for (i=0; i<G->nbsommets; i++) {
		
		printf("\t");
		for (j=0; j<G->nbsommets; j++) printf("%d ",G->matrice[i*G->nbsommets + j]);
		printf("\n");
	}
}

void initTab(int* tab){


	/*De 1 à 1*/ /*De 1 à 2*/  /*De 1 à 3*/  /*De 1 à 4*/ /*De 1 à 5*/
	tab[0] = 0; tab[1] = 5;   tab[2] = 20;  tab[3] = 18;  tab[4] = 0;

	/*De 2 à 1*/ /*De 2 à 2*/  /*De 2 à 3*/  /*De 2 à 4*/ /*De 2 à 5*/
	tab[5] = 7; tab[6] = 0;   tab[7] = 0;  tab[8] = 27;  tab[9] = 0;

	/*De 3 à 1*/ /*De 3 à 2*/  /*De 3 à 3*/  /*De 3 à 4*/ /*De 3 à 5*/
	tab[10] = 9; tab[11] = 0;   tab[12] = 0;  tab[13] = 0;  tab[14] = 17;

	/*De 4 à 1*/ /*De 4 à 2*/  /*De 4 à 3*/  /*De 4 à 4*/ /*De 4 à 5*/
	tab[15] = 7; tab[16] = 6;   tab[17] = 0;  tab[18] = 0;  tab[19] = 0;	 

	/*De 5 à 1*/ /*De 5 à 2*/  /*De 5 à 3*/  /*De 5 à 4*/ /*De 5 à 5*/
	tab[20] = 0; tab[21] = 19;   tab[22] = 31;  tab[23] = 0;  tab[24] = 0;


}