#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Treap.h"

// Funções básicas

// inicializa o Treap
void inicializa(Treap *dados) {
    dados->chave = -1;
    dados->prioridade = -1;
    dados->direita = NULL;
    dados->esquerda = NULL;
}

// limpeza de memória após a utilização do Treap
void limpaTreap(Treap *dados) {
    if(dados == NULL) return;
    limpaTreap(dados->direita);
    limpaTreap(dados->esquerda);
    free(dados);
}

// Funções da especificação

// retorna 0 caso a inserção seja feita com sucesso
// do contrário retorna -1
int inserir (Treap **dados, int chave, int prioridade) {
    if(*dados == NULL) {
        *dados = malloc(sizeof(Treap));
        inicializa(*dados);
        (*dados)->chave      = chave;
        (*dados)->prioridade = prioridade;    

        return 0;
    }

    Treap *menor, *maior;
    corte(*dados, chave, &menor, &maior);

    Treap *inserir = NULL;
    char caminho[1000];

    if(menor == NULL || encontrar(menor, chave, caminho, 0) == NULL) {
        // inserimos um novo par apenas se a chave dada ainda não
        // existir no treap
        // se ela já existir, o par inserir fica nulo e portanto
        // será descartado durante a fusão

        inserir = malloc(sizeof(Treap));
        inicializa(inserir);
        inserir->chave = chave;
        inserir->prioridade = prioridade;
    }

    Treap *resultado;
    resultado = fusao(menor, inserir);
    *dados    = fusao(resultado, maior);

    if(inserir == NULL) return -1;

    return 0;
}

// retorna 0 caso a remoção seja feita com sucesso
// do contrário retorna -1
int remover (Treap **dados, int chave) {
    if(*dados == NULL) return -1;

    // menor = chaves menores que a chave passada
    // intermediario = chaves menores ou iguais à chave passada
    // procurado = par de chave igual à chave passada
    // maior = chaves maiores que a chave passada
    Treap *menor, *intermediario, *procurado, *maior;
    corte(*dados        , chave    , &intermediario, &maior);
    corte( intermediario, chave - 1, &menor        , &procurado);

    *dados = fusao(menor, maior);

    if(procurado == NULL) return -1;

    free(procurado);
    return 0;

}

// o argumento printaResultados determina se a função deve fazer chamadas
// à função printf ou não
Treap* encontrar(Treap *dados, int chave, char *caminho, int printaResultados) {
    if(dados == NULL) {

        caminho[0] = '\0';
        if(printaResultados) printf("-1");

        return NULL;

    } else if(chave > dados->chave && dados->direita != NULL) {

        int tamCaminho = strlen(caminho);
        caminho[tamCaminho] = 'R';
        caminho[tamCaminho + 1] = '\0';

        return encontrar(dados->direita, chave, caminho, printaResultados);

    } else if(chave < dados->chave && dados->esquerda != NULL) {

        int tamCaminho = strlen(caminho);
        caminho[tamCaminho] = 'L';
        caminho[tamCaminho + 1] = '\0';

        return encontrar(dados->esquerda, chave, caminho, printaResultados);

    } else if(chave != dados->chave) {

        caminho[0] = '\0';
        if(printaResultados)    printf("-1");

        return NULL;
    }

    // se chegou aqui, chave == dados.chave
    return dados;

}

Treap* fusao(Treap *A, Treap *B) {
    if(A == NULL) return B;
    if(B == NULL) return A;

    // a raiz do treap A deve ter prioridade superior
    // à prioridade da raiz do treap B
    if(B->prioridade > A->prioridade) {
        Treap *swap;
        swap = B;
        B = A;
        A = swap;
    }

    Treap *atual = B;

    while(A != NULL) {
        // procuramos uma prioridade maior que
        // a da raiz de A no treap B, seguindo o
        // posicionamento definido pela árvore binária

        if(A->chave < atual->chave) {
            // seguimos à esquerda

            if(atual->esquerda == NULL) {
                // não encontramos prioridade maior que a da raiz de A
                // portanto inserimos A à esquerda do par atual e a
                // fusão está completa

                atual->esquerda = A;
                A = NULL;

            } else if(atual->esquerda->prioridade > A->prioridade) {
                // achamos uma prioridade maior
                // esse par de maior prioridade se torna o novo A,
                // e colocamos o A antigo no lugar desse par

                Treap *swap;
                swap = A;
                A = atual->esquerda;
                atual->esquerda = swap;
                atual = swap;
            } else {
                // continuamos caminhando para a esquerda

                atual = atual->esquerda;
            }

        } else {
            // seguimos à direita

            if(atual->direita == NULL) {
                // não encontramos prioridade maior que a da raiz de A
                // portanto inserimos A à direita do par atual e a
                // fusão está completa

                atual->direita = A;
                A = NULL;

            } else if(atual->direita->prioridade > A->prioridade) {
                // achamos uma prioridade maior
                // esse par de maior prioridade se torna o novo A,
                // e colocamos o A antigo no lugar desse par

                Treap *swap;
                swap = A;
                A = atual->direita;
                atual->direita = swap;
                atual = swap;
            } else {
                // continuamos caminhando para a direita

                atual = atual->direita;
            }
        
        }
    }

    return B;
}

void corte(Treap *dados, int chave, Treap **menor, Treap **maior) {
    *maior = NULL;
    *menor = NULL;

    if(dados == NULL) return;

    if(dados->chave == chave) {
        // o par raiz do treap já tem a chave procurada
        // basta separar a direita da raiz e o resto
        *menor = dados;
        *maior = dados->direita;
        dados->direita = NULL;

        return;
    }

    // a chave não está na raiz, devemos fazer uma busca
    // mais profunda

    if(chave > dados->chave)    *menor = dados;
    else                        *maior = dados; 

    Treap *atual         = dados;
    Treap *insercaoMaior = *maior;
    Treap *insercaoMenor = *menor;

    // varremos o treap fazendo o corte
    while(atual != NULL) {
        if(atual->chave < chave) {
            // caminhamos para a direita

            if( atual->direita == NULL ||
                atual->direita->chave == chave ||
               (atual->direita->chave < chave && atual->direita->direita == NULL) ||
               (atual->direita->chave > chave && atual->direita->esquerda == NULL)) {

                // estamos prestes a encontrar a chave procurada,
                // ou o maior valor menor que a chave

                if(atual->direita != NULL && atual->direita->chave >= chave) {
                    // deslocamos para o par à direita caso a chave da direita
                    // seja a procurada, para que ela seja incluída no treap
                    // menor
                    if(atual->direita->chave == chave) atual = atual->direita;

                    if(*maior == NULL) {
                        *maior = atual->direita;
                        atual->direita = NULL;
                    } else {
                        insercaoMaior->esquerda = atual->direita;
                        atual->direita = NULL;
                    }
                }

                atual = NULL;

            } else if(atual->direita->chave > chave) {
                // logo depois, precisaremos caminhar à esquerda

                // marcamos o atual como ponto de inserção no
                // menor treap
                insercaoMenor = atual;

                // agora inserimos o próximo valor no treap maior
                if(*maior == NULL) {
                    *maior = atual->direita;
                } else {
                    insercaoMaior->esquerda = atual->direita;
                }

                Treap *auxiliar = atual->direita;
                atual->direita = NULL;
                atual = auxiliar;

            } else if(atual->direita->chave < chave) {

                atual = atual->direita;

            }

        } else if(atual->chave > chave) {
            // caminhamos para a esquerda

            if( atual->esquerda == NULL ||
                atual->esquerda->chave == chave ||
               (atual->esquerda->chave > chave && atual->esquerda->esquerda == NULL) ||
               (atual->esquerda->chave < chave && atual->esquerda->direita == NULL)) {
                
                // estamos prestes a encontrar a chave procurada,
                // ou o maior valor menor que a chave

                if(atual->esquerda != NULL && atual->esquerda->chave <= chave) {
                    if(*menor == NULL && atual->esquerda != NULL) {
                        *menor = atual->esquerda;
                        atual->esquerda = atual->esquerda->direita;
                        (*menor)->direita = NULL;
                    } else if(atual->esquerda != NULL){
                        insercaoMenor->direita = atual->esquerda;
                        atual->esquerda = atual->esquerda->direita;
                        insercaoMenor->direita->direita = NULL;
                    }
                }

                atual = NULL;

            } else if(atual->esquerda->chave < chave) {

                // marcamos o atual como ponto de inserção no
                // maior treap
                insercaoMaior = atual;

                // agora inserimos o próximo valor no treap menor
                if(*menor == NULL) {
                    *menor = atual->esquerda;
                } else {
                    insercaoMenor->direita = atual->esquerda;
                }

                Treap *auxiliar = atual->esquerda;
                atual->esquerda = NULL;
                atual = auxiliar;

            } else if(atual->esquerda->chave > chave) {

                atual = atual->esquerda;

            }

        }
    }
}