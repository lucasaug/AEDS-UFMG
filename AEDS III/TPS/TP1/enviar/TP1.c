#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdint.h>
#include "Operacoes.h"

void SetMemoryLimit(const int64_t limit_mb);

int main() {
    char nomeArquivo[20] = "./pontos.bin";

    unsigned long long tamMemoria;
    int xBase, yBase;
    scanf("%llu", &tamMemoria);
    scanf("%d %d", &xBase, &yBase);

    // limitando a memória
    // SetMemoryLimit(tamMemoria);

    long long num;
    char x[6], y[6];

    FILE *pontos = fopen(nomeArquivo, "wb");
    if(pontos == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    unsigned long long numPontos = 0;
    unsigned long long distanciaQuad;

    while(!feof(stdin)) {
        int sucesso = lePonto(&num, x, y);

        if(sucesso) {
            int coordX = atoi(x);
            int coordY = atoi(y);

            distanciaQuad = (coordX - xBase) * (coordX - xBase) +
                                               (coordY - yBase) * (coordY - yBase);

            // insere o ataque no arquivo
            fwrite(&num, sizeof(long long), 1, pontos);
            fwrite(&coordX, sizeof(int), 1, pontos);
            fwrite(&coordY, sizeof(int), 1, pontos);
            fwrite(&numPontos, sizeof(unsigned long long), 1, pontos);
            fwrite(&distanciaQuad, sizeof(unsigned long long), 1, pontos);

            numPontos++;
        }
    }

    fclose(pontos);

    if(numPontos == 0) return 0;

    // agora lemos o arquivo de maneira ordenada
    leOrdenado(nomeArquivo, xBase, yBase, tamMemoria, numPontos);

    return 0;
}

void SetMemoryLimit(const int64_t limit_mb) {
    struct rlimit limits;
    limits.rlim_cur = limit_mb * 1024ull * 1024ull;
    limits.rlim_max = limit_mb * 1024ull * 1024ull;
    // int error_code = setrlimit(RLIMIT_AS, &limits);
}