#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct Point2D
{
	float x, y;
} Point2D;

typedef struct
{
    int nbsommets;
    int * matrice;
} Graphe;

void initGraphe(Graphe * g, int * m, int nbsommets);
void afficheGraphe(const Graphe * G);

void initTab(int* tab,Point2D *position);
void drawLines(Point2D p1, Point2D p2); 

void ecrire(int x, int y, char *string, void *font);

void Dijkstra(Graphe *g, int depart, int arrive, Point2D *position, int boo);
void drawColor(Point2D p1, Point2D p2, int color, int boo);
void circleColor(Point2D p1, int color, int boo);
void drawGraphe(Graphe *g, Point2D *position, int boo );

#endif