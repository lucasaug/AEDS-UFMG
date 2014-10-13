#include <stdlib.h>
#include <string.h>

#include "bloco.h"

// Gera o primeiro bloco da lista
Bloco *inicializaLista(size_t tamanhoMemoria){
    Bloco *primeiro = (Bloco*) malloc(sizeof(Bloco));
    primeiro->posicao  = 0;
    primeiro->tamanho  = tamanhoMemoria;
    primeiro->ocupado  = 0;
    primeiro->proximo  = NULL;
    return primeiro;
}

// Procura um bloco na lista de acordo com seu endereco e o retorna
Bloco *recebeBloco(Bloco *inicio, unsigned char *endereco) {
    Bloco *procura = inicio;
    while(procura != NULL) {
        if(procura->endereco == endereco)
            return procura;
        procura = procura->proximo;
    }

    // Nao encontramos o bloco na lista
    return NULL;
}

// Insere os dados de um bloco novo na lista caso haja espaco
// e retorna o bloco onde eles foram inseridos
Bloco *insereBloco(Bloco *inicio, Bloco novo) {
    Bloco *atual = inicio;
    int encontrado = 0;
    while(atual != NULL && !encontrado) {
        if(!atual->ocupado && atual->tamanho >= novo.tamanho)
            encontrado = 1;
        else
            atual = atual->proximo;
    }

    if(!encontrado) return NULL; // nao encontramos espaco para insercao de novo bloco

    size_t espacoVazio = atual->tamanho - novo.tamanho;

    atual->tamanho = novo.tamanho;
    atual->ocupado = 1;

    if(espacoVazio) {
        // se houver espaco restante no bloco, dividimos o bloco em dois
        Bloco *vazio = (Bloco*)malloc(sizeof(Bloco));

        vazio->endereco = atual->endereco + atual->tamanho;
        vazio->posicao  = atual->posicao + atual->tamanho;
        vazio->tamanho  = espacoVazio;
        vazio->ocupado  = 0;
        vazio->proximo  = atual->proximo;
        atual->proximo = vazio;
    }

    return atual;
}

// insere um bloco depois do outro
// o novo bloco nao e necessariamente ocupado
void insereDepois(Bloco *local, Bloco *novo) {
    if(local == NULL) return;
    novo->endereco = local->endereco + local->tamanho;
    novo->posicao  = local->posicao  + local->tamanho;
    novo->proximo = local->proximo;
    local->proximo = novo;
}

int removeBloco(Bloco *inicio, unsigned char *enderecoRemover) {
    Bloco *atual = inicio;
    Bloco *anterior = (Bloco*)malloc(sizeof(Bloco));
    anterior->proximo = NULL;
    int encontrado = 0;
    while(atual != NULL && !encontrado) {
        if(atual->endereco == enderecoRemover)
            encontrado = 1;
        else {
            // liberamos a memória usada para o pseudo-bloco anterior
            // ao início
            if(anterior->proximo == NULL) {
                free(anterior);
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }

    if(!encontrado) return -1; // foi passado um bloco nao existente na lista

    atual->ocupado = 0;

    // se o bloco anterior esta vazio, juntamos os dois
    if(anterior->proximo != NULL && !anterior->ocupado) {
        anterior->tamanho += atual->tamanho;
        anterior->proximo = atual->proximo;
        free(atual);
        atual = anterior;
    }

    Bloco *proximo = atual->proximo;
    // se o proximo bloco esta vazio, juntamos os dois
    if(proximo != NULL && !proximo->ocupado) {
        atual->tamanho += proximo->tamanho;
        atual->proximo = proximo->proximo;
        free(proximo);
    }

    if(anterior->proximo == NULL  && anterior != atual) free(anterior);

    return 0;
}