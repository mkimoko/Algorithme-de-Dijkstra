
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
		printf("\n\n");
	}
}

void initTab(int* tab, Point2D *position){


	/*De 1 à 1*/ /*De 1 à 2*/  /*De 1 à 3*/  /*De 1 à 4*/ /*De 1 à 5*/
	tab[0] = 0; tab[1] = 7;   tab[2] = 9;  tab[3] = 18;  tab[4] = 0;
	/*Position du noeud 1*/
	position[0].x = -8.8;
	position[0].y = 0;

	/*De 2 à 1*/ /*De 2 à 2*/  /*De 2 à 3*/  /*De 2 à 4*/ /*De 2 à 5*/
	tab[5] = 7; tab[6] = 0;   tab[7] = 0;  tab[8] = 27;  tab[9] = 19;
	/*Position du noeud 2*/
	position[1].x = -0.75;
	position[1].y = 6.5;

	/*De 3 à 1*/ /*De 3 à 2*/  /*De 3 à 3*/  /*De 3 à 4*/ /*De 3 à 5*/
	tab[10] = 9; tab[11] = 0;   tab[12] = 0;  tab[13] = 0;  tab[14] = 17;
	/*Position du noeud 3*/
	position[2].x = -1;
	position[2].y = -6.5;

	/*De 4 à 1*/ /*De 4 à 2*/  /*De 4 à 3*/  /*De 4 à 4*/ /*De 4 à 5*/
	tab[15] = 18; tab[16] = 27;   tab[17] = 0;  tab[18] = 0;  tab[19] = 0;
	/*Position du noeud 4*/
	position[3].x = 2.5;
	position[3].y = 0;

	/*De 5 à 1*/ /*De 5 à 2*/  /*De 5 à 3*/  /*De 5 à 4*/ /*De 5 à 5*/
	tab[20] = 0; tab[21] = 19;   tab[22] = 17;  tab[23] = 0;  tab[24] = 0;
	/*Position du noeud 5*/
	position[4].x = 7.5;
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
	char *txt;
	gluOrtho2D(0., 5., 0., 5.);
	void *font = malloc(sizeof(void));
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	txt = malloc(sizeof(char));

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
		sprintf(txt, "%d", i+1);
		glPopMatrix();
		ecrire(position[i].x+1.75, position[i].y+0.9,txt ,font); 

	 	

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

void ecrire(int x, int y, char *string, void *font){
	int len,i; // len donne la longueur de la chaîne de caractères
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	glMatrixMode(GL_MODELVIEW);                
	    glLoadIdentity(); 
	    glPushMatrix();
	    glColor3f(255, 255, 255);
	    glScalef(0.1, 0.1, 1);
		glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	
		
		for (i = 0; i < len; i++){
			glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
		}
		glPopMatrix();

}

void Dijkstra(Graphe *g, int depart, int arrive){
	int poids[g->nbsommets];
	int antecedant[g->nbsommets];
	int parcourue[g->nbsommets];
	int affiche[g->nbsommets*g->nbsommets];
	int i = 0;
	int courant = 0;/*variable test du poids*/
	int min = -1; 
	int boo = 0;

	for(i = 0; i < g->nbsommets; i++){
		poids[i] = 999999; /* Poids infini */
		antecedant[i] = -1; /* Aucun noeud n'as d'antécédent */
		parcourue[i] = 0; /*Boolean aucun sommet n'as été parcourue*/
		affiche[i] = -1;
	}
	poids[depart-1] = 0; /*Étant positionnée sur le noeud de départ sa distance par rapport à elle même est 0*/ 

	parcourue[depart-1] = 1;
	courant = depart-1;

	/*Tant que le poids d'arrive n'est pas le plus faible*/
	while( boo == 0){
		/*printf("yes\n");*/
		/*On recherche les voisin de noeud courant*/
		printf("antecedant 1 = %d - antecedant 4 = %d\n\n",antecedant[1],antecedant[4] );
		for(i = courant*g->nbsommets; i < (courant+1)*g->nbsommets; i++ )
		{
			boo = 1;
			if (g->matrice[i] > 0 && parcourue[i-courant*g->nbsommets] == 0 && poids[courant] + g->matrice[i] < poids[i-courant*g->nbsommets])
			{
				poids[i-courant*g->nbsommets] = poids[courant] + g->matrice[i];
				antecedant[i-courant*g->nbsommets] = courant;
			}
			

			printf("Poids[%d] = %d\n",i-courant*g->nbsommets, poids[i-courant*g->nbsommets] );
			printf("antecedant[%d] = %d\n",i-courant*g->nbsommets, antecedant[i-courant*g->nbsommets] );
			printf("parcourue[%d] = %d\n",i-courant*g->nbsommets, parcourue[i-courant*g->nbsommets] );
			printf("\n\n");

		}
	}

		
}