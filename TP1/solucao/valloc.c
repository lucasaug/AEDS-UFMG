#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bloco.h"
#include "valloc.h"

unsigned char MEM[MAX_MEM];

void inicializa_gerencia(void) {
    inicioBlocos = inicializaLista(MAX_MEM);
    inicioBlocos->endereco = MEM;
}
void finaliza_gerencia(void) {
    Bloco *atual = inicioBlocos;
    while(atual != NULL) {
        removeBloco(inicioBlocos, atual->endereco);
        atual = atual->proximo;
    }
    free(inicioBlocos);
}
void imprime_status_memoria(void) {
    printf("Status agora:\n");

    Bloco *atual = inicioBlocos;
    while(atual != NULL) {
        printf("Pos: %d, Size: %d, Status: %s\n", (int)atual->posicao, (int)atual->tamanho, 
                                                       atual->ocupado ? "USED" : "FREE");
        atual = atual->proximo;
    }
}


void *valloc(size_t size) {
    Bloco inserir;
    inserir.tamanho = size;
    Bloco *inserido = insereBloco(inicioBlocos, inserir);
    if(inserido == NULL) return NULL;
    inserido->endereco = &MEM[inserido->posicao];
    inserido->tamanho  = size;
    return &MEM[inserido->posicao];
}
void vfree(void *p) {
    if(p == NULL) return;
    removeBloco(inicioBlocos, p);
}
void *vcalloc(size_t nitems, size_t size) {
    size_t tamanho = nitems * size;
    char *ponteiro = valloc(tamanho);
    if(ponteiro == NULL) return NULL;
    int i = 0;
    for(; i < tamanho; i++) {
       *(ponteiro + i) = 0;
    }
    return ponteiro;
}
void *vrealloc(void *p, size_t size) {
    // caso o ponteiro seja nulo, alocamos o tamanho necessario
    if(p == NULL) return valloc(size);
    // caso size seja igual a 0, liberamos esse bloco
    if(size == 0){ vfree(p); return NULL; }

    Bloco *realocar = recebeBloco(inicioBlocos, p);

    size_t tamanho  = realocar->tamanho;

    // caso o novo tamanho seja menor que o atual, apenas
    // diminuimos o tamanho e mudamos o bloco seguinte conforme necessario
    if(size < tamanho) {
        if(realocar->proximo->ocupado) {
            size_t diferencaTamanho = realocar->tamanho - size;
            realocar->tamanho = size;
            Bloco *vazio = (Bloco*)malloc(sizeof(Bloco));
            vazio->tamanho = diferencaTamanho;
            vazio->ocupado = 0;
            insereDepois(realocar, vazio);
        } else {
            size_t tamanhoLivre = realocar->proximo->tamanho + realocar->tamanho - size;
            realocar->tamanho = size;
            realocar->proximo->posicao = realocar->posicao + realocar->tamanho;
            realocar->proximo->tamanho = tamanhoLivre;
        }

        return p;
    } else

    // caso o tamanho novo seja igual ao anterior, nada acontece
    if(size == tamanho) { 
        return p;
    }

    // caso o tamanho novo seja maior que o anterior

    // armazenamos os dados em uma variavel auxiliar para o caso
    // em que tenhamos que mover o conteudo apontado na memoria
    char *dados = malloc(tamanho * sizeof(unsigned char));
    int i = 0;

    for(; i < tamanho; i++) {
        dados[i] = MEM[realocar->posicao + i];
    }


    // encontramos o bloco anterior ao que vai ser realocado
    Bloco *anterior = inicioBlocos;
    int encontrado = 0;
    if(inicioBlocos == realocar) encontrado = 1;
    while(anterior->proximo != NULL && !encontrado) {
        if(anterior->proximo == realocar) encontrado = 1;
        else    anterior = anterior->proximo;
    }
    
    // calculamos para descobrir se as regioes adjacentes a esse bloco somados
    // ao espaco no bloco tem espaco o suficiente para que a realocacao seja feita
    size_t espacoAdjacente = realocar->tamanho;
    espacoAdjacente += (realocar->proximo != NULL && !realocar->proximo->ocupado) ?
                        realocar->proximo->tamanho : 0;
    // caso o espaco na frente ja seja o suficiente para fazer a realocacao,
    // nao utilizamos o bloco anterior, assim podemos manter a variavel no
    // mesmo endereco de memoria
    int usaBlocoAnterior = espacoAdjacente < size;
    // caso nao seja o suficiente ainda, procuramos o bloco anterior
    if(usaBlocoAnterior) {
        espacoAdjacente += (encontrado && !anterior->ocupado) ? anterior->tamanho : 0;
    } else {
        // se o proximo bloco ja tem espaco o suficiente, apenas aumentamos o
        // tamanho do bloco atual e diminuimos o seguinte, removendo-o caso
        // necessario
        size_t espacoVazio = espacoAdjacente - size;

        realocar->tamanho = size;

        if(espacoVazio) {
            // se houver espaco restante adjacente, atualizamos o
            // bloco seguinte de acordo
            realocar->proximo->tamanho = espacoVazio;
            realocar->proximo->posicao = realocar->posicao + realocar->tamanho;
        } else {
            // se nao ha espaco restante adjacente, removemos o
            // bloco seguinte
            Bloco *proximo = realocar->proximo;
            realocar->proximo = proximo->proximo;
            free(proximo);
        }

        free(dados);
        return p;
    }

    if(espacoAdjacente < size) {
        // o espaco adjacente nao e suficiente para o novo tamanho de bloco,
        // fazemos o valloc para alocar o novo bloco, e caso ele funcione, apagamos
        // o bloco antigo, nessa ordem
        unsigned char *endereco = (unsigned char*)valloc(size);
        Bloco *novo = recebeBloco(inicioBlocos, endereco);
        if(novo == NULL) { free(dados); return NULL; }
        novo->endereco = &MEM[novo->posicao];
        vfree(realocar->endereco);

        // por fim copiamos os dados
        int j = 0;
        for(; j < tamanho; j++) {
            (novo->endereco)[j] = dados[j];
        }

        free(dados);
        return novo->endereco;
    }
    
    // o espaco adjacente e suficiente para o novo tamanho de bloco,
    // ou seja, podemos ter certeza que o valloc deve funcionar. Assim,
    // damos free primeiro, e depois o valloc
    vfree(realocar->endereco);
    unsigned char *ponteiro = valloc(size);
    Bloco *novo = recebeBloco(inicioBlocos, ponteiro);
    novo->endereco = &MEM[novo->posicao];

    // por fim copiamos os dados
    int j = 0;
    for(; j < tamanho; j++) {
        (novo->endereco)[j] = dados[j];
    }

    free(dados);

    return novo;
}