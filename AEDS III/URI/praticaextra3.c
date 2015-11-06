#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int N, E, X, Y, H, K, i, j;
    int grafo[501][501];

    scanf("%d %d", &N, &E);
    while(N || E) {
        N++;


        // resetando o grafo    
        for(i = 0; i < 501; i++) {
            for(j = 0; j < 501; j++) {
                grafo[i][j] = -1;
            }
        }

        while(E) {
            scanf("%d %d %d", &X, &Y, &H);
            if(grafo[Y][X] != -1) {
                grafo[X][Y] = grafo[Y][X] = 0;
            } else {
                grafo[X][Y] = H;
            }

            E--;
        }

        scanf("%d", &K);

        while(K) {
            scanf("%d %d", &X, &Y);

            // calculamos o caminho mínimo
            int *d           = malloc(N * sizeof(int)),
                *fechado     = calloc(N, sizeof(int));

            for(i = 0; i < N; i++) {
                d[i] = INT_MAX;
            }

            d[X] = 0;

            // rodar dijsktra
            int verticeAtual = X;
            while(verticeAtual != -1) {
                fechado[verticeAtual] = 1;
                for(i = 1; i < N; i++) {
                    if(grafo[verticeAtual][i] != -1 && !fechado[i] &&
                       d[i] > d[verticeAtual] + grafo[verticeAtual][i]) {
                        d[i] = d[verticeAtual] + grafo[verticeAtual][i];
                    }
                }

                int menor = -1;
                for(i = 1; i < N; i++) {
                    if(!fechado[i] && d[i] != INT_MAX && (menor == -1 || d[i] < d[menor])) {
                        menor = i;
                    }
                }    

                verticeAtual = menor;

            }

            if(d[Y] != INT_MAX) {
                printf("%d\n", d[Y]);
            } else {
                printf("Nao e possivel entregar a carta\n");
            }

            free(d);
            free(fechado);
            K--;
        }

        printf("\n");
        scanf("%d %d", &N, &E);
    }

    return 0;
}