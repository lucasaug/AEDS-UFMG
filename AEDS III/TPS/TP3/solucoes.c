#include <stdlib.h>
#include <pthread.h>
#include "headers/solucoes.h"

/****
 * Solução por força bruta:
 *
   Tenta cada combinação diferente de somas e subtrações. *
                                                          *
                                                       ****/

int resolveJogoBF(int *sequencia, int tamSequencia, int inicial, int limite) {
    if(inicial > limite || inicial < 0) return -1;
    if(tamSequencia == 0)               return inicial;

    int soma      = inicial + sequencia[0],
        subtracao = inicial - sequencia[0];

    if(tamSequencia == 1) {

        if(soma > subtracao) {
            if(soma <= limite) return soma;
            else               return subtracao;
        } else {
            if(subtracao <= limite) return subtracao;
            else                    return soma;
        }

    } else {

        int jogoSoma = resolveJogoBF(sequencia + 1, tamSequencia - 1, soma,      limite),
            jogoSub  = resolveJogoBF(sequencia + 1, tamSequencia - 1, subtracao, limite);

        if(jogoSoma > jogoSub) {
            if(jogoSoma <= limite) return jogoSoma;
            else                   return jogoSub;
        } else {
            if(jogoSub <= limite) return jogoSub;
            else                  return jogoSoma;
        }

    }

}

/****
 * Solução com programação dinâmica:
 *
   Salva em uma matriz quais os valores alcançáveis
   por cada carta do baralho considerando os valores
   das cartas anteriores e o valor inicial. Cada
   linha da matriz representa uma carta e cada
   coluna um valor alcançado (ou não) pela carta        *
   Mais detalhes na documentação.                       *
                                                     ****/

int resolveJogoPD(int *sequencia, int tamSequencia, int inicial, int limite) {
    if(tamSequencia == 0) return inicial;

    int **memorizacao = (int**) calloc((tamSequencia + 1), sizeof(int*));
    int i, j, soma, subtracao;
    for(i = 0; i <= tamSequencia; i++) {
        memorizacao[i] = (int*) calloc((limite + 1), sizeof(int));
    }

    memorizacao[0][inicial] = 1;
    for(i = 1; i <= tamSequencia; i++) {
        for(j = 0; j <= limite; j++) {
            if(memorizacao[i - 1][j]) {
                soma      = j + sequencia[i - 1];
                subtracao = j - sequencia[i - 1];

                if(soma >= 0      && soma <= limite)      memorizacao[i][soma] = 1;
                if(subtracao >= 0 && subtracao <= limite) memorizacao[i][subtracao] = 1;
            }
        }
    }

    int melhorValor = -1;
    for(i = limite; i >= 0 && melhorValor == -1; i--) {
        if(memorizacao[tamSequencia][i]) {
            melhorValor = i;
        }
    }


    for(i = 0; i <= tamSequencia; i++) {
        free(memorizacao[i]);
    }
    free(memorizacao);

    return melhorValor;
}

/****
 * Solução paralelizada:
 *
   Executa o algoritmo de programação dinâmica, porém
   paraleliza o processo. Cada thread recebe um conjunto
   de colunas da matriz para calcular os montantes possíveis
   para cada linha considerando os valores anteriores.
   As threads são sincronizadas para que estejam sempre
   operando na mesma linha, para que não surjam hazards.     *
                                                             *
                                                          ****/

void *processoThread(void *parametros) {
    int j, soma, subtracao, inicio, fim, linha, limite;
    int *sequencia;
    int **memorizacao;
    Parametros param = *((Parametros*) parametros);

    inicio       =  param.inicio;
    fim          =  param.fim;
    sequencia    =  param.sequencia;
    memorizacao  =  param.memorizacao;
    linha        = *param.linha;
    limite       =  param.limite;

    for(j = inicio; j < fim; j++) {
        if(memorizacao[linha - 1][j]) {
            soma      = j + sequencia[linha - 1];
            subtracao = j - sequencia[linha - 1];

            if(soma >= 0      && soma <= limite)      memorizacao[linha][soma] = 1;
            if(subtracao >= 0 && subtracao <= limite) memorizacao[linha][subtracao] = 1;
        }
    }

    pthread_exit(NULL);
}

int resolveJogoThreads(int *sequencia, int tamSequencia, int inicial, int limite) {
    if(tamSequencia == 0) return inicial;

    int **memorizacao = (int**) calloc((tamSequencia + 1), sizeof(int*));
    int i, j, capacidadeThread;
    for(i = 0; i <= tamSequencia; i++) {
        memorizacao[i] = (int*) calloc((limite + 1), sizeof(int));
    }

    capacidadeThread = limite/NUMTHREADS;
    
    pthread_t  *threads = (pthread_t*)  malloc(NUMTHREADS * sizeof(pthread_t));
    Parametros *param   = (Parametros*) malloc(NUMTHREADS * sizeof(Parametros));

    for(i = 0; i < NUMTHREADS; i++) {
        param[i].inicio       = i       * capacidadeThread;
        param[i].fim          = (i + 1) * capacidadeThread;
        param[i].sequencia    = sequencia;
        param[i].memorizacao  = memorizacao;
        param[i].linha        = &i;
        param[i].limite       = limite;
    }

    param[NUMTHREADS - 1].fim = limite + 1;

    memorizacao[0][inicial] = 1;
    for(i = 1; i <= tamSequencia; i++) {
        for(j = 0; j < NUMTHREADS; j++) {
            pthread_create(&threads[j], NULL, processoThread, (void*) &param[j]);
        }
        for(j = 0; j < NUMTHREADS; j++) {
            pthread_join(threads[j], NULL);
        }
    }

    int melhorValor = -1;
    for(i = limite; i >= 0 && melhorValor == -1; i--) {
        if(memorizacao[tamSequencia][i]) {
            melhorValor = i;
        }
    }


    for(i = 0; i <= tamSequencia; i++) {
        free(memorizacao[i]);
    }
    free(memorizacao);
    free(threads);
    free(param);

    return melhorValor;
}