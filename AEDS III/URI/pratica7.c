#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int compara (const void * a, const void * b) {
    return *(char*)a - *(char*)b;
}

void examina(int32_t *grafo, int numVertices, unsigned int *potencias2, int linha, char *vertices, int32_t *visitado) {
    int tamVertices = strlen(vertices);
    vertices[tamVertices]     = (char)(97 + linha);
    vertices[tamVertices + 1] = '\0';

    int i;
    for(i = linha + 1; i < numVertices; i++) {
        if(grafo[linha] & potencias2[i] && !(*visitado & potencias2[i])) {
            *visitado |= potencias2[i];
            examina(grafo, numVertices, potencias2, i, vertices, visitado);
        }
    }

    for(i = 0; i < linha; i++) {
        if(grafo[i] & potencias2[linha] && !(*visitado & potencias2[i])) {
            *visitado |= potencias2[i];
            examina(grafo, numVertices, potencias2, i, vertices, visitado);
        }
    }
}

int main() {

    unsigned int potencias2[26];
    int i, j, k;
    for(i = 0; i < 26; i++) {
        potencias2[i]= pow(2, i);
    }

    int N;
    scanf("%d", &N);

    int atual = 1;
    while(atual <= N) {

        printf("Case #%d:\n", atual);

        int V, E;
        scanf("%d %d", &V, &E);

        int32_t grafo[26];
        for(i = 0; i < V; i++) {
            grafo[i] = 0;
        }

        char origem, destino;
        int numOrigem, numDestino;
        while(E) {
            scanf(" %c %c", &origem, &destino);
            numOrigem = origem % 97;
            numDestino = destino % 97;
            if(numOrigem > numDestino) {
                numOrigem  ^= numDestino;
                numDestino ^= numOrigem;
                numOrigem  ^= numDestino;
            }

            grafo[numOrigem] |= potencias2[numDestino];

            E--;
        }

        int numGrupos = 0;
        char vertices[27];
        int32_t visitado = 0;
        for(i = 0; i < V; i++) {
            vertices[0] = '\0';
            if(grafo[i] && !(visitado & potencias2[i])) {
                visitado |= potencias2[i];
                vertices[0] = (char)(97 + i);
                vertices[1] = '\0';
                for(j = i + 1; j < V; j++) {
                    if((grafo[i] & potencias2[j]) && !(visitado & potencias2[j]) ) {
                        visitado |= potencias2[j];
                        examina(grafo, V, potencias2, j, vertices, &visitado);
                    }
                }

                qsort((void*)vertices, strlen(vertices), sizeof(char), compara);

                for(j = 0; j < strlen(vertices); j++) printf("%c,", vertices[j]);
                printf("\n");

                numGrupos++;
            } else if(!(visitado & potencias2[i])) {
                printf("%c,\n", (char)(97 + i));
                visitado |= potencias2[i];
                numGrupos++;
            }
        }

        printf("%d connected components\n\n", numGrupos);

        atual++;
    }

    return 0;
}