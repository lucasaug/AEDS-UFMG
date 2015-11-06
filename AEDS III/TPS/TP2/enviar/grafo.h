// Implementação de um grafo não-direcionado

#ifndef TP2_GRAFO
#define TP2_GRAFO

typedef struct Grafo {
    double** arestas;
    int numVertices;
} Grafo;

void inicializaGrafo(Grafo* grafo, int num);
void limpaGrafo(Grafo* grafo);

void insereAresta(Grafo* grafo, int vertice1, int vertice2, double peso);

#endif