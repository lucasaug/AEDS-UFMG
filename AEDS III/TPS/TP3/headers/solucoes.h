#ifndef SOLUCOES
#define SOLUCOES

#define NUMTHREADS 15

/******************************************************
 * Struct que permite passagem de parâmetros para as  *
 * threads                                            *
 ******************************************************/

typedef struct {
    int inicio;
    int fim;
    int limite;
    int *linha;
    int *sequencia;
    int **memorizacao;
} Parametros;

/******************************************************
 * Definimos aqui as três soluções do problema dado:  *
 *                                                    *
 * - Solução brute force (BF)                         *
 * - Solução com Programação Dinâmica (PD)            *
 * - Solução paralelizada                             *
 *                                                    *
 ******************************************************/

int resolveJogoBF     (int *sequencia, int tamSequencia, int inicial, int limite);
int resolveJogoPD     (int *sequencia, int tamSequencia, int inicial, int limite);
int resolveJogoThreads(int *sequencia, int tamSequencia, int inicial, int limite);

#endif