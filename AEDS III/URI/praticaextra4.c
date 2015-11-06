#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int N, nPaineis, numCaminhoes, frete, i, j, k, somaPesos, somaParcial, maiorPeso, pesoParcial, parcialInterno;
    int* pesos;
    int** PD;

    scanf("%d", &N);

    while(N) {
        scanf("%d %d %d", &nPaineis, &numCaminhoes, &frete);

        PD    = (int**) malloc(sizeof(int*) * nPaineis);
        pesos = (int*)  malloc(sizeof(int)  * nPaineis);
        somaPesos = 0;
        for(i = 0; i < nPaineis; i++) {
            scanf("%d", &pesos[i]);
            PD[i] = (int*) malloc(sizeof(int) * (numCaminhoes));
            somaPesos += pesos[i];
        }

        somaParcial = 0;
        for(i = 0; i < nPaineis; i++) {
            somaParcial += pesos[i];
            PD[i][0] = somaParcial;
            for(j = 1; j < numCaminhoes; j++) {
                if(j > i) {
                    PD[i][j] = PD[i][j - 1];
                } else {
                    parcialInterno = 0;
                    maiorPeso = INT_MAX;
                    for(k = i; k > j - 1; k--) {
                        parcialInterno += pesos[k];
                        pesoParcial = parcialInterno > PD[k-1][j - 1] ? parcialInterno : PD[k-1][j - 1];
                        if(pesoParcial < maiorPeso) maiorPeso = pesoParcial;
                    }

                    if(maiorPeso == INT_MAX && i > 0 && j < numCaminhoes - 1) {
                        maiorPeso = pesos[i] > PD[i - 1][j - 1] ? pesos[i] : PD[i - 1][j - 1];
                    }

                    PD[i][j] = maiorPeso;
                }
            }
        }



        somaParcial = 0;
        maiorPeso = PD[nPaineis - 1][numCaminhoes - 1];

        printf("%d $%d\n", maiorPeso, frete * numCaminhoes * maiorPeso);

        for(i = 0; i < nPaineis; i++) {
            free(PD[i]);
        }
        free(PD);
        free(pesos);

        N--;
    }

    return 0;
}