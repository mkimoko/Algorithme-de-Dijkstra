#include <SDL/SDL.h>       
/*#include <SDL/SDL_image.h>*/   
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

  int boo = 1;
  Graphe *graphe;        
  graphe = malloc(sizeof(Graphe));
  int tab[25];   
  Point2D position[5];
  initTab(tab, position);
     
  initGraphe(graphe, tab, 5);           
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
  
    drawGraphe(graphe,position,boo ); 
    Dijkstra(graphe, 1, 5,position,boo); 
  
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
        /* Clic souris */
        case SDL_MOUSEBUTTONUP:  
          
          break;

          case SDL_MOUSEMOTION: 
          
          break;       
  
 
        /* Touche clavier */
        case SDL_KEYDOWN:
 
          if( e.key.keysym.sym == SDLK_s){ 
            printf("c'est appuyé!\n");
            boo = 0;
            printf("boo = %d\n", boo);
        
          } 

          if( e.key.keysym.sym == SDLK_q) 
            SDL_Quit(); 
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
