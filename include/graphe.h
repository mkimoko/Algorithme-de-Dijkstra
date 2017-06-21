#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct
{
    int nbsommets;
    int * matrice;
} Graphe;

void initGraphe(Graphe * g, int * m, int nbsommets);
void afficheGraphe(const Graphe * G);

void initTab(int* tab);

#endif

