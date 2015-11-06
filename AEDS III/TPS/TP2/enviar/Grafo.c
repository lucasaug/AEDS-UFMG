#include <stdlib.h>
#include "grafo.h"

// Inicialização e liberação da memória de grafos

void inicializaGrafo(Grafo* grafo, int num){
    grafo->arestas = (double**) malloc(num * sizeof(double*));
    int i;
    for(i = 0; i < num; i++) {
        grafo->arestas[i] = (double*) calloc(num, sizeof(double));
    }
    grafo->numVertices = num;
}

void limpaGrafo(Grafo* grafo){
    int i;
    for(i = 0; i < grafo->numVertices; i++) {
        free(grafo->arestas[i]);
    }    
    free(grafo->arestas);
    grafo->numVertices = 0;
}

// Inserção de aresta bidirecional

void insereAresta(Grafo* grafo, int vertice1, int vertice2, double peso){
    grafo->arestas[vertice1][vertice2] = peso;
    grafo->arestas[vertice2][vertice1] = peso;
}