#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "headers/solucoes.h"


int main() {

    struct timeval start, end;
    int tmili;
    gettimeofday(&start, NULL);

    int  numInstancias, tamSequencia, inicial, limite, minimo, resultado, i;
    int *sequencia;

    scanf("%d", &numInstancias);

    while(numInstancias) {

        scanf("%d %d %d %d", &tamSequencia, &inicial, &limite, &minimo);
        sequencia = (int*) malloc(sizeof(int) * tamSequencia);

        for(i = 0; i < tamSequencia; i++) {
            scanf("%d", sequencia + i);
        }

        resultado = resolveJogoThreads(sequencia, tamSequencia, inicial, limite);

        if(resultado >= minimo && resultado <= limite) {
            printf("S,%d\n", resultado);
        } else {
            printf("N,%d\n", (resultado <= limite && resultado >= 0) ? resultado : -1);
        }

        numInstancias--;
        free(sequencia);

    }

    gettimeofday(&end, NULL);
    tmili = (int) (1000 * (end.tv_sec - start.tv_sec) +
            (end.tv_usec - start.tv_usec) / 1000);
    printf("tempo decorrido: %d ms\n", tmili);
    printf("Threads: %d\n", NUMTHREADS);

    return 0;
}