#include <stdio.h>
#include <stdlib.h>

void inverteTrecho(int *genes, int inicio, int fim) {
    int aux;

    // decrementa inicio e fim, para fazer a correta
    // indexação no vetor (0-based indexing)
    inicio--;
    fim--;

    while(inicio < fim) {
        aux = genes[inicio];
        genes[inicio] = genes[fim];
        genes[fim] = aux;
        inicio++;
        fim--;
    }
}

int main() {

    int contagemGenoma = 1;

    int numGenes;
    scanf("%d", &numGenes);

    while(numGenes != 0) {
        int *genes = malloc(sizeof(int) * numGenes);
        int i;
        for(i = 0; i < numGenes; i++) {
            genes[i] = i + 1;
        }

        int numInversoes;
        scanf("%d", &numInversoes);

        while(numInversoes) {
            int inicio, fim;
            scanf("%d %d", &inicio, &fim);
            inverteTrecho(genes, inicio, fim);

            numInversoes--;
        }


        int numConsultas;
        scanf("%d", &numConsultas);

        printf("Genome %d\n", contagemGenoma);

        while(numConsultas) {
            int buscar;
            scanf("%d", &buscar);

            for(i = 0; i < numGenes && genes[i] != buscar; i++);

            // comparação para evitar segfault
            if(i <= numGenes) printf("%d\n", ++i);

            numConsultas--;
        }

        free(genes);
        scanf("%d", &numGenes);

        contagemGenoma++;
    }

    return 0;
}