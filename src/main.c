#include <SDL/SDL.h>       
#include <GL/gl.h>                       
#include <GL/glu.h>    
#include <GL/glut.h>               
#include <stdlib.h>      
#include <stdio.h>  
#include <math.h>                       
#include "graphe.c"         
   
#define MYSCALE 0.05        

 

/* Dimensions de la fenêtre */    
static unsigned int WINDOW_WIDTH = 800;          
static unsigned int WINDOW_HEIGHT = 800; 
 
/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;                   
  
/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;   

int main(int argc, char** argv) {          
  // initialisation de GLUT             
  glutInit(&argc, argv);                                  
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {              
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");        
    return EXIT_FAILURE;                         
  }                    
   
  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;                        
  }               
  
  /*Booleen pour fonction Dijkstra et DrawGraphe*/
  int boo = 1;
  int step = 0;
  Graphe *graphe;        
  graphe = malloc(sizeof(Graphe));   
  /*Tableau pour la matrice */
  int tab[25]; 
  /*Conversion des paramètres mis en arguments*/
  int arg1 = atoi(argv[1]);
  int arg2 = atoi(argv[2]);
  /*Tableau de points pour les noeuds du graphe*/
  Point2D position[5];
  /*Initialisation de la matrice du graphe ainsi que les positions des noeuds (valeur fixe)*/
  initTab(tab, position);  
  /*Initialisation du graphe*/   
  initGraphe(graphe, tab, 5); 
  /*Affichage de la matice sur le terminal*/              
  afficheGraphe(graphe);                  
         
              
  /* Titre de la fenêtre */         
  SDL_WM_SetCaption("Shall we begin this Dijkstra algorithm ?!", NULL);  

  /* Boucle d'affichage */   
  int loop = 1;    
  while(loop) {  
    /* Récupération du temps au début de la boucle */        
    Uint32 startTime = SDL_GetTicks();                             
       
    /* Placer ici le code de dessin */             
    glClear(GL_COLOR_BUFFER_BIT); 
 
    /*Dessin du graphe*/
    drawGraphe(graphe,position,boo ); 

    Dijkstra(graphe,arg1,arg2,position,step,boo);

    /*Si on appuie sur escape*/
    if ( Dijkstra(graphe, arg1, arg2,position, step,boo) == 0)
    {
       SDL_Quit();
    }

    /*Fonction affichage ne marche pas car buffer overflow -> Problème à résoudre*/
    /*poids(graphe, position); */

    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    SDL_GL_SwapBuffers();                           
        
    /* Boucle traitant les evenements */  
    SDL_Event e;                 
    while(SDL_PollEvent(&e)) {      
      /* L'utilisateur ferme la fenêtre : */       
      if(e.type == SDL_QUIT) {                
        loop = 0;     
        break; 
      }     
       
      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {      
      
        /* Touche clavier */
        case SDL_KEYDOWN: 
 
          if( e.key.keysym.sym == SDLK_s){    
            printf("Commençons!\n");
            boo = 0;/*Avec boo = 0; C'est la fonction Dijkstra qui s'occupe d'afficher le graphe*/
            step = 0;
          }   

          if( e.key.keysym.sym == SDLK_ESCAPE){
            printf("Fin d'animation\n");
            SDL_Quit();
          } 

          if( e.key.keysym.sym == SDLK_p){
            step++;
            printf("step == %d\n",step );

            if (boo == 0)
            {
              if(step == 5){
              boo = 1;
              step = 0;
            }
            }
            
               
          } 
             
          break; 

          
   
        default:
          break; 
      } 
    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  /* Liberation des ressources associées à la SDL */ 
  SDL_Quit();

  return EXIT_SUCCESS;
}