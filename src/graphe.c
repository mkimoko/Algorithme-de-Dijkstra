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



void drawGraphe(Graphe *g, Point2D *position, int boo ){
	int i, j;
	char *txt, txt2;
	gluOrtho2D(0., 5., 0., 5.);
	void *font = malloc(sizeof(void));
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	txt = malloc(sizeof(char));
	txt2 = malloc(sizeof(char));

	if (boo == 1)
	{
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

int Dijkstra(Graphe *g, int depart, int arrive, Point2D *position,int boo){
	int poids[g->nbsommets];
	int antecedant[g->nbsommets];
	int parcourue[g->nbsommets];
	int i = 0, j = 0;
	int courant = 0;/*variable test du poids*/
	int min = -1;
	int poidsmin = 9999999;
	int chemin[g->nbsommets];
	int continuer = 1;
	int step = 0; 
	int affiche = 1;

	SDL_Event e;

	if(boo == 0)
	{
		drawGraphe(g, position, 1 );

		for(i = 0; i < g->nbsommets; i++){
			poids[i] = 999999; /* Poids infini */
			antecedant[i] = -1; /* Aucun noeud n'as d'antécédent */
			parcourue[i] = 0; /*Boolean aucun sommet n'as été parcourue*/
			chemin[i] = -1;
		}
		poids[depart-1] = 0; /*Étant positionnée sur le noeud de départ sa distance par rapport à elle même est 0*/ 

		parcourue[depart-1] = 1;
		courant = depart-1;	

			


		/*Tant que le poids d'arrive n'est pas le plus faible*/
		while( poids[min] != poids[arrive-1]){
			/*On recherche les voisin de noeud courant*/
			for(i = courant*g->nbsommets; i < (courant+1)*g->nbsommets; i++ )
			{
				while(continuer == 1){
					printf("1\n");
					circleColor(position[courant], 1, 1);
					while(SDL_PollEvent(&e)){
						switch(e.type){
							case SDL_KEYDOWN:
								if( e.key.keysym.sym == SDLK_p){
									continuer = 0;
								}

								if( e.key.keysym.sym == SDLK_ESCAPE){
									printf("hdscnqkljqsl\n");
									boo = 0;
									return 0;
								} 

							break;
						}
					}
				}
				continuer = 1;
				
				/*Si un noeud rempli les conditions*/
				if (g->matrice[i] > 0 && parcourue[i-courant*g->nbsommets] == 0 && poids[courant] + g->matrice[i] < poids[i-courant*g->nbsommets])
				{

					while(continuer == 1){
						printf("2\n");
						drawColor(position[courant], position[i-courant*g->nbsommets], 0,1);
						circleColor(position[i-courant*g->nbsommets], 0, 1);
						while(SDL_PollEvent(&e)){
							switch(e.type){
								case SDL_KEYDOWN:
									if( e.key.keysym.sym == SDLK_p){
										continuer = 0;
									}

									if( e.key.keysym.sym == SDLK_ESCAPE){
										printf("hdscnqkljqsl\n");
										boo = 0;
										return 0;
									} 

								break;
							}
						}
					}
					continuer = 1;

					/*On ajoute sa distance au poids parcourue jusqu'au noeud sur lequel on se trouve*/
					poids[i-courant*g->nbsommets] = poids[courant] + g->matrice[i];
					/*On marque son antécédant*/
					antecedant[i-courant*g->nbsommets] = courant;	
				}
					
			}

			/*On recherche le noeud avec le poids minimale non parcourue*/
			for (i = 0; i < g->nbsommets; i++)
			{
				if (parcourue[i] == 0 && poids[i] != 999999)
				{
					for (j = 0; j < g->nbsommets; j++)
					{
						if (parcourue[j] == 0 && poids[j] <= poidsmin && poids[j] != 999999)
						{
							poidsmin = poids[j];
							min = j;

						}
					}
				}
			}

			parcourue[min] = 1;
			courant = min;
			poidsmin = 999999;
			continuer = 1;

			while(continuer == 1){

				printf("3\n");
				drawColor(position[min], position[antecedant[min]], 1,1);
				circleColor(position[min], 1, 1);
				circleColor(position[antecedant[min]], 1, 1);
				while(SDL_PollEvent(&e)){
					switch(e.type){
						case SDL_KEYDOWN:
							if( e.key.keysym.sym == SDLK_p){
								continuer = 0;
							}

							if( e.key.keysym.sym == SDLK_ESCAPE){
								printf("hdscnqkljqsl\n");
								boo = 0;
								return 0;
							} 
						break;
					}
				}
			}
			continuer = 1;
		}

		i = 0;
		while(antecedant[min] != -1){
			chemin[i] = antecedant[min];
			min = antecedant[min];
			i++;
		}




		printf("%d Le chemin est: \n", i);
		for (i = i-1; i >= 0; i--)
		{
			printf("%d\t",chemin[i] );
			circleColor(position[chemin[i]], 2, 1);
			drawColor(position[chemin[i]], position[chemin[i-1]], 2, 1);

		}
		printf("%d\t",arrive-1 );
		circleColor(position[arrive-1], 2, 1);
		drawColor(position[chemin[i]], position[arrive-1], 2, 1);
		printf("final\n");


		while(SDL_PollEvent(&e)){
			if( e.key.keysym.sym == SDLK_SPACE){
				printf("hdscnqkljqsl\n");
				boo = 0;
				return 0;
			} 
		}
	}
	return 1;								
}


void drawColor(Point2D p1, Point2D p2, int color, int boo){

	if (boo == 1)
	{
		glMatrixMode(GL_MODELVIEW);                
			glLoadIdentity(); 
			glPushMatrix();
			glScalef(0.1, 0.1, 1);

			glBegin(GL_LINES);
			if (color == 0)/*rouge*/
				glColor3ub(255, 0, 0);

			if (color == 1)/*blue*/
				glColor3ub(0,0,255);

			if (color == 2)/*dorée*/
				glColor3ub(240, 195, 0);
								
			glVertex2f(p1.x,p1.y);glVertex2f(p2.x,p2.y);
			glEnd();
		glPopMatrix();
	}
	
}

void circleColor(Point2D p1, int color, int boo){

	if (boo == 1)
	{
		glMatrixMode(GL_MODELVIEW);                
	    glLoadIdentity(); 
		glPushMatrix();
		glScalef(0.1, 0.1, 1);
		glTranslatef(p1.x, p1.y, 0);
		glBegin(GL_TRIANGLE_FAN);
			if (color == 0)/*rouge*/
				glColor3ub(255, 0, 0);

			if (color == 1)/*blue*/
				glColor3ub(0,0,255);

			if (color == 2)/*dorée*/
				glColor3ub(240, 195, 0);

			for (int j = 0; j <= SEGMENTS; j++){
		      glVertex2f(cos(j*(M_PI/(SEGMENTS/2))), sin(j*(M_PI/(SEGMENTS/2))));
		 	}
		glEnd();
	glPopMatrix();
	}
}

void poids(Graphe *g, Point2D *position){
	void *font = malloc(sizeof(void));
	char *txt = malloc(sizeof(char));
	font = GLUT_BITMAP_TIMES_ROMAN_24;
	txt = malloc(sizeof(char));

	for (int i = 0; i < g->nbsommets; i++)
	{
		for (int j = 0; j < g->nbsommets; j++)
		{
			if (g->matrice[i*g->nbsommets + j] > 0)
			{	
				sprintf(txt, "%d", g->matrice[i*g->nbsommets + j]); 
				strcat(txt, " ");
				ecrire( ( position[i].x+position[i].x )/2, ( position[i].y+position[i].y )/2,txt ,font);
			}
		}
	}
}