#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/Treap.h"
#define TAM 1000000

int main() {
    // gerando várias chaves
    int i;
    int chaves[TAM];
    for(i = 0; i < TAM; i++) {
        chaves[i] = i;
    }
    srand(time(NULL));

    for (i = TAM - 1; i > 0; i--)
    {
        int n = rand() % (i + 1);

        int temp = chaves[n];
        chaves[n] = chaves[i];
        chaves[i] = temp;
    }

    // gerando várias prioridades
    int prioridades[TAM];
    for(i = 0; i < TAM; i++) {
        prioridades[i] = i;
    }

    for (i = TAM - 1; i > 0; i--)
    {
        int n = rand() % (i + 1);

        int temp = prioridades[n];
        prioridades[n] = prioridades[i];
        prioridades[i] = temp;
    }

    Treap *dados = NULL;

    // agora inserimos dados no treap utilizando as chaves e prioridades
    // criadas acima
    for(i = 0; i < TAM; i++) {
        inserir(&dados, chaves[i], prioridades[i]);
    }

    // sorteamos uma chave para localizar, remover e inserir
    int posicao = rand() % (TAM + 1);

    char *caminho = (char*)malloc(sizeof(char) * 1000);
    caminho[0] = '\0';
    float inicio = (float)clock();
    encontrar(dados, chaves[posicao], caminho, 0);
    free(caminho);
    float fim = (float)clock();
    float tempoPassado = (fim - inicio)/CLOCKS_PER_SEC;
    printf("\n\nTempo de Localizacao: %f\n", tempoPassado);
    inicio = (float)clock();
    remover(&dados, chaves[posicao]);
    fim = (float)clock();
    tempoPassado = (fim - inicio)/CLOCKS_PER_SEC;
    printf("\n\nTempo de Remocao: %f\n", tempoPassado);
    inicio = (float)clock();
    inserir(&dados, chaves[posicao], prioridades[posicao]);
    fim = (float)clock();
    tempoPassado = (fim - inicio)/CLOCKS_PER_SEC;
    printf("\n\nTempo de Insercao: %f\n", tempoPassado);

    limpaTreap(dados);

    return 0;
}