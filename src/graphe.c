
#include "../include/graphe.h"
#define SEGMENTS 128



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

void initTab(int* tab, Point2D *position){


	/*De 1 à 1*/ /*De 1 à 2*/  /*De 1 à 3*/  /*De 1 à 4*/ /*De 1 à 5*/
	tab[0] = 0; tab[1] = 5;   tab[2] = 20;  tab[3] = 18;  tab[4] = 0;
	/*Position du noeud 1*/
	position[0].x = -8.5;
	position[0].y = 0;

	/*De 2 à 1*/ /*De 2 à 2*/  /*De 2 à 3*/  /*De 2 à 4*/ /*De 2 à 5*/
	tab[5] = 7; tab[6] = 0;   tab[7] = 0;  tab[8] = 27;  tab[9] = 0;
	/*Position du noeud 2*/
	position[1].x = -0.75;
	position[1].y = 6.5;

	/*De 3 à 1*/ /*De 3 à 2*/  /*De 3 à 3*/  /*De 3 à 4*/ /*De 3 à 5*/
	tab[10] = 9; tab[11] = 0;   tab[12] = 0;  tab[13] = 0;  tab[14] = 17;
	/*Position du noeud 3*/
	position[2].x = -0.75;
	position[2].y = -6.5;

	/*De 4 à 1*/ /*De 4 à 2*/  /*De 4 à 3*/  /*De 4 à 4*/ /*De 4 à 5*/
	tab[15] = 7; tab[16] = 6;   tab[17] = 0;  tab[18] = 0;  tab[19] = 0;
	/*Position du noeud 4*/
	position[3].x = 2.5;
	position[3].y = 0;	 

	/*De 5 à 1*/ /*De 5 à 2*/  /*De 5 à 3*/  /*De 5 à 4*/ /*De 5 à 5*/
	tab[20] = 0; tab[21] = 19;   tab[22] = 31;  tab[23] = 0;  tab[24] = 0;
	/*Position du noeud 5*/
	position[4].x = 8;
	position[4].y = -2.5;
}

void drawLines(Point2D p1, Point2D p2){
	glMatrixMode(GL_MODELVIEW);                
        glLoadIdentity(); 
        glPushMatrix();
        glScalef(0.1, 0.1, 1);

		glBegin(GL_LINES);
			glColor3ub(255,255,255);
			glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);
		glEnd();
	glPopMatrix();
}



void drawGraphe(Graphe *g, Point2D *position ){
	int i, j;
	gluOrtho2D(0., 5., 0., 5.);

	for (i = 0; i < g->nbsommets; i++)
	  {
	  	/********Création Matrice********/
	  	glMatrixMode(GL_MODELVIEW);                
        glLoadIdentity(); 
        glPushMatrix();
        glScalef(0.1, 0.1, 1);
        glTranslatef(position[i].x, position[i].y, 0);

	 	glBegin(GL_TRIANGLE_FAN);
			glColor3d(255,255,255);
			for (j = 0; j <= SEGMENTS; j++){
		      glVertex2f(cos(j*(M_PI/(SEGMENTS/2))), sin(j*(M_PI/(SEGMENTS/2))));
		 	}
		glEnd();
		glPopMatrix();
	 	

	 	for (j = 0; j < g->nbsommets; j++)
	 	{
	 		if (g->matrice[i*g->nbsommets + j] > 0)
	 		{
	 			drawLines(position[i], position[j]);
	 		}
	 	}


	 	/**********Fin Matrice**********/
	  } 
}