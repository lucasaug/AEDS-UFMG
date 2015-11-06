#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "headers/grafo.h"
#include "headers/cidade.h"

void constroiGrafoCidades(Grafo* G, Cidade* cidades, int numCidades);
void visita(Grafo G, int numCidade, int** restricoes, int* visitado, double deslocamento, double* minimoGeral);
double geraCaminhoMinimo(Grafo G, int** restricoes);

int main() {
    int N, R, i, a, b, deadlock;
    Cidade *cidades;
    Grafo grafo;
    int** restricoes;
    double minimo;

    // lemos o primeiro N
    scanf("%d", &N);
    while(!feof(stdin) && N) {

        // inicializando o vetor de cidades e matriz
        // de restrições
        cidades    = (Cidade*) malloc(N * sizeof(Cidade));
        restricoes = (int**)   malloc(N * sizeof(int*));

        // lemos todas as cidades e inicializamos cada linha
        // da matriz de restrições
        for(i = 0; i < N; i++) {
            restricoes[i] = (int*) calloc(N, sizeof(int));
            scanf("%d %d", &cidades[i].x, &cidades[i].y);
        }

        // agora lemos as restrições
        scanf("%d", &R);
        deadlock = 0;
        while(R) {
            scanf("%d %d", &a, &b);
            restricoes[b][a] = 1;
            if(restricoes[a][b]) {
                // precisamos visitar a antes de b, e b antes de a?
                // não é possível, deadlock
                deadlock = 1;
            }
            R--;
        }

        if(!deadlock) {
            // construímos o grafo completo
            constroiGrafoCidades(&grafo, cidades, N);
            
            // calculamos o mínimo
            minimo = geraCaminhoMinimo(grafo, restricoes);

            // DBL_MAX representa um valor infinito,
            // simbolizando deadlock
            if(minimo == DBL_MAX)
                printf("Deadlock\n");
            else
                printf("%.2f\n", minimo);

            // liberamos a memória utilizada
            limpaGrafo(&grafo);
        } else {
            printf("Deadlock\n");            
        }


        // liberando a memória
        free(cidades);
        for(i = 0; i < N; i++) {
            free(restricoes[i]);
        }
        free(restricoes);

        // lê próximo N
        scanf("%d", &N);
    }

    return 0;
}

void constroiGrafoCidades(Grafo* G, Cidade* cidades, int numCidades) {
    inicializaGrafo(G, numCidades);
    int i, j;

    // inserimos uma aresta entre quaisquer duas cidades (grafo completo)
    for(i = 0; i < numCidades - 1; i++) {
        for(j = i + 1; j < numCidades; j++) {
            insereAresta(G, i, j, distancia(cidades[i], cidades[j]));
        }
    }
}


void visita(Grafo G, int numCidade, int** restricoes, int* visitado, double deslocamento, double* minimoGeral) {
    int i, j;
    int num = G.numVertices;

    // se essa cidade já foi visitada, não devemos visitá-la
    // novamente, a não ser que essa seja nossa origem e já
    // tenhamos passado por todas as cidades
    if(visitado[numCidade]) {
        if(numCidade == 0) {
            int tudoVisitado = 1;
            for(i = 1; i < num && tudoVisitado; i++) {
                tudoVisitado = visitado[i];
            }

            if(tudoVisitado) {
                *minimoGeral = deslocamento;
                return;
            } else {
                return;
            }
        } else {
            return;
        }
    }

    // marcamos essa cidade como visitada
    visitado[numCidade] = 1;

    int podeVisitar;
    for(i = 0; i < num; i++) {
        // apenas checamos uma cidade se a distância até ela somada com o
        // deslocamento feito até agora for menor que o caminho mais curto já
        // encontrado
        if(i != numCidade && deslocamento + G.arestas[numCidade][i] < *minimoGeral) {
            podeVisitar = 1;
            for(j = 0; j < num; j++) {
                if(restricoes[i][j] && !visitado[j]) {
                    podeVisitar = 0;
                }
            }

            if(podeVisitar) {
                // procuramos o menor caminho continuando por essa cidade
                visita(G, i, restricoes, visitado, deslocamento + G.arestas[numCidade][i], minimoGeral);
            }
        }
    }

    // desmarcamos essa cidade como visitada
    visitado[numCidade] = 0;

}

double geraCaminhoMinimo(Grafo G, int** restricoes) {
    // vetor que utilizaremos para representar
    // se um vértice foi visitado ou não

    int* visitado = calloc(G.numVertices, sizeof(int));

    // variável onde armazenamos o tamanho do menor caminho
    // encontrado até agora (inicialmente setamos como DBL_MAX,
    // representando um valor infinitamente positivo)
    double minimoGeral = DBL_MAX;

    // iniciamos a chamada recursiva a partir da cidade de origem (0)
    visita(G, 0, restricoes, visitado, 0, &minimoGeral);

    free(visitado);

    return minimoGeral;

}