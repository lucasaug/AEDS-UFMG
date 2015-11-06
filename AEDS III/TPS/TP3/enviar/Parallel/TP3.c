#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solucoes.h"

/*
   Todas as soluções estão inclusas em solucoes.h
   O programa principal escolhe a solução apropriada

   Todos os códigos são iguais, apenas a linha que chama
   a função que resolve o jogo muda

   Esse código utiliza programação paralela
*/

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

        // Resolve utilizando programação paralela
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