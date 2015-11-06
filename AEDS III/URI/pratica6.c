#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Pessoa {
    double x;
    double y;
} Pessoa;

typedef struct Aresta {
    int origem;
    int destino;
    double peso;
} Aresta;

double distancia(Pessoa a, Pessoa b) {
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

int compara (const void * a, const void * b) {
    double diferenca = ((Aresta*)a)->peso - ((Aresta*)b)->peso;
    return diferenca > 0 ? 1 : (diferenca ? 0 : -1); 
}

int main() {
    int N;
    scanf("%d", &N);

    while(N) {
        Pessoa listaPessoas[500];

        int numPessoas;
        scanf("%d", &numPessoas);

        int i, j;
        int numArestas = 0;
        Aresta arestas[500*500];
        for(i = 0; i < numPessoas; i++) {
            scanf("%lf %lf", &listaPessoas[i].x, &listaPessoas[i].y);
            for(j = 0; j < i; j++) {
                arestas[numArestas].origem = i;
                arestas[numArestas].destino = j;
                arestas[numArestas].peso = distancia(listaPessoas[i], listaPessoas[j]);
                numArestas++;
            }
        }

        qsort((void*)arestas, numArestas, sizeof(Aresta), compara);

        int verticeIncluso[500];
        for(i = 0; i < numPessoas; i++) {
            verticeIncluso[i] = 0;
        }

        double tamTeia = 0;
        int grupoAtual = 1;
        for(i = 0; i < numArestas; i++) {
            Aresta atual = arestas[i];

            int origem = verticeIncluso[atual.origem],
                destino = verticeIncluso[atual.destino];

            if(!origem || !destino) {
                tamTeia += atual.peso;
                int grupoInserir = (origem || destino) ? (origem ? origem : destino)
                                                       :  grupoAtual;
                if(grupoInserir == grupoAtual) {
                    grupoAtual++;
                }

                verticeIncluso[atual.origem] = verticeIncluso[atual.destino] = grupoInserir;
            } else if(origem != destino){
                tamTeia += atual.peso;
                for(j = 0; j < numPessoas; j++) {
                    if(verticeIncluso[j] == destino)
                        verticeIncluso[j] = origem;
                }
            }

        }

        printf("%.2lf\n", tamTeia/100.0);

        N--;
    }

    return 0;
}