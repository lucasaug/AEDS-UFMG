#include <stdio.h>
#include <stdlib.h>

int main() {

    int comprimento = 0, quantidade = 0;
    scanf("%d%d", &comprimento, &quantidade);

    while(!feof(stdin)) {

        getchar();
        int *estacionamento = calloc(comprimento, sizeof(int));

        char op = '\0';
        int placa = 0, tamanho = 0;
        int faturamento = 0;

        for(; quantidade > 0; quantidade--) {
            scanf("%c", &op);
            if(op == 'C') {
                scanf("%d%d", &placa, &tamanho);
                getchar();

                int i;
                int espacoEncontrado = 0;
                for(i = 0; i < comprimento && espacoEncontrado < tamanho; i++) {
                    if(estacionamento[i] == 0) {
                        espacoEncontrado++;
                    } else {
                        espacoEncontrado = 0;
                    }
                }

                if(espacoEncontrado == tamanho) {
                    int posicaoEstacionar = i - espacoEncontrado;
                    for(; posicaoEstacionar < i; posicaoEstacionar++) {
                        estacionamento[posicaoEstacionar] = placa;
                    }

                    faturamento += 10;
                }

            } else if(op == 'S') {
                scanf("%d", &placa);
                getchar();

                int i;
                int encontrado = 0;
                for(i = 0; i < comprimento; i++) {
                    if(estacionamento[i] == placa) {
                        encontrado = 1;
                        estacionamento[i] = 0;
                    } else if(encontrado) {
                        break;
                    }
                }

            }
        }

        printf("%d\n", faturamento);

        free(estacionamento);

        scanf("%d%d", &comprimento, &quantidade);
    }

    return 0;
}