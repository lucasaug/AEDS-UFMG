#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main() {
    int N, D, indiceAtual, i, posPilha;
    long long int numero;
    char* numeroStr, *resultado;
 
    scanf("%d %d", &N, &D);
    while(N || D) {
        numeroStr = (char*) malloc(N * sizeof(char));
        resultado = (char*) calloc(N , sizeof(char));
 
        scanf("%lld", &numero);
        sprintf(numeroStr, "%lld", numero);
        indiceAtual = 0;
 
        posPilha = 0;
        while(indiceAtual <= N && posPilha < N - D) {

            if(numeroStr[indiceAtual] > resultado[posPilha]) {
                resultado[posPilha] = numeroStr[indiceAtual];
            } else {
                posPilha++;
                resultado[posPilha] = numeroStr[indiceAtual];
            }
            indiceAtual++;
        }

        for(i = 0; i < N; i++) {
            printf("%c", resultado[i]);
        }
        printf("\n");
 
        scanf("%d %d", &N, &D);

        free(numeroStr);
        free(resultado);
    }
 
    return 0;
}