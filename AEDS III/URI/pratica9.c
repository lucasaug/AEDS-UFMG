#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct {
    int idProd;
    float preco;
} Produto;

int main() {

    int M, N, i, j;

    Produto *lista;
    Produto *mercado;
    float **precos;
    float preco;
    float aux;
    scanf("%d %d", &M, &N);

    while(M && N) {
        lista   = (Produto*) malloc(M * sizeof(Produto));
        mercado = (Produto*) malloc(N * sizeof(Produto));
        precos = (float**) calloc(M, sizeof(float*));

        i = 0;
        while(i < M) {
            precos[i] = (float*) calloc(N, sizeof(float));
            scanf("%d", &lista[i].idProd);
            lista[i].preco = FLT_MAX;
            i++;
        }

        i = 0;
        while(i < N) {
            scanf("%d %f", &mercado[i].idProd, &mercado[i].preco);
            i++;
        }

        for(i = 0; i < M; i++) {
            for(j = 0; j < N; j++) {
                if(lista[i].idProd == mercado[j].idProd &&
                   (i == 0 || precos[i-1][j] != 0) &&
                   (j == 0 || (precos[i][j-1] == 0 || precos[i][j-1] > mercado[j].preco) ) ) {

                        if((i != 0 && lista[i-1].idProd == lista[i].idProd && precos[i-1][j] != precos[i-1][j-1])) {
                            precos[i][j] = precos[i-1][j-1];
                            /*if(precos[i][j] > precos[i-1][j]) {
                                aux = precos[i][j];
                                precos[i][j] = precos[i-1][j];
                                precos[i-1][j] = aux;
                            }*/
                        } else {
                            precos[i][j] = mercado[j].preco;
                        }
                } else if(j != 0){
                    precos[i][j] = precos[i][j-1];
                }
            }
        }

        if(precos[M-1][N-1] == 0) printf("Impossible\n");
        else {
            float preco = 0;
            i = M - 1; 
            for(j = N - 1; j >= 0 && i >= 0; j--) {
                if(j == 0 || precos[i][j] != precos[i][j-1]) {
                    preco += precos[i][j];
                    i--;
                    while(i >= 0 && lista[i+1].idProd == lista[i].idProd) {
                        preco += precos[i][j];
                        i--;
                    }
                }
            }
            printf("%.2f\n", preco);
        }

        free(lista);
        free(mercado);

        i = 0;
        while(i < M) {
            free(precos[i]);
            i++;
        }
        free(precos);
        scanf("%d %d", &M, &N);
    }

    return 0;
}