#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/solucoes.h"


int main() {

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

    return 0;
}