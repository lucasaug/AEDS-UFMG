#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "filmes.h"

// inicializa o tamanho do vetor de filmes
void inicializaFilmes(Filmes *lista, int tamanhoMaximo){
    lista->lista = malloc(sizeof(Filme) * tamanhoMaximo);
    lista->tamanhoLista = 0;
}

// função que calcula a posição de um filme na tabela hash
int calculaHash(Filme filme, int numUsuarios, int tamanhoHash) {
    return (int) (((float)filme.popularidade/numUsuarios) * (tamanhoHash-1));
}

// transformamos a lista de filmes em uma tabela hash
void montaTabelaHash(Filmes *lista, int numUsuarios, int tamanhoHash) {
    // armazenamos a lista de filmes na forma atual,
    // para passá-los para a forma de uma tabela hash
    Filme* listaAntiga = lista->lista;
    int tamanhoListaAntiga = lista->tamanhoLista;

    lista->lista = malloc(sizeof(Filme) * tamanhoHash);
    lista->tamanhoLista = tamanhoHash;

    int i;
    // primeiro fazemos com que todos os filmes da lista tenham o id igual
    // a -1, indicando que nenhum filme foi inserido na posição na hash table
    for(i = 0; i < tamanhoHash; i++) {
        lista->lista[i].id = -1;
    }

    for(i = 0; i < tamanhoListaAntiga; i++) {
        incluiFilmeHash(lista, listaAntiga[i], numUsuarios);
    }
    free(listaAntiga);
}

// desaloca uma árvore de filmes
void finalizaArvore(Filme* raiz) {
    if(raiz == NULL) {
        return;
    }
    
    finalizaArvore(raiz->direita);
    finalizaArvore(raiz->esquerda);
    free(raiz);
}

// desaloca as entradas na tabela hash e as árvores
void finalizaTabelaHash(Filmes *lista) {
    int i;
    for(i = 0; i < lista->tamanhoLista; i++) {
        finalizaArvore(&lista->lista[i]);
    }
}

// inclui um filme no fim da lista (quando os filmes estão listados da forma comum)
void incluiFilmeFinal(Filmes *lista, Filme novo) {
    int posicao = lista->tamanhoLista;
    novo.direita = NULL;
    novo.esquerda = NULL;
    lista->lista[posicao] = novo;
    lista->tamanhoLista++;
}

// insere um filme em uma árvore, usando os critérios dados
void insereArvore(Filme* raiz, Filme novo) {
    if (novo.popularidade < raiz->popularidade) {
        if (raiz->direita == NULL) {
            raiz->direita = malloc(sizeof(Filme));
            *raiz->direita = novo;
        } else {
            insereArvore(raiz->direita, novo);
        }
    } else if (novo.popularidade > raiz->popularidade){
        if (raiz->esquerda == NULL) {
            raiz->esquerda = malloc(sizeof(Filme));
            *raiz->esquerda = novo;
        } else {
            insereArvore(raiz->esquerda, novo);
        }
    } else {
        // caso tenham a mesma popularidade, avaliamos pela data de lançamento
        if (novo.ano < raiz->ano) {
            if (raiz->direita == NULL) {
                raiz->direita = malloc(sizeof(Filme));
                *raiz->direita = novo;
            } else {
                insereArvore(raiz->direita, novo);
            }
        } else if (novo.ano > raiz->ano){
            if (raiz->esquerda == NULL) {
                raiz->esquerda = malloc(sizeof(Filme));
                *raiz->esquerda = novo;
            } else {
                insereArvore(raiz->esquerda, novo);
            }
        } else {
            // por fim, avaliamos o id do filme
            if (novo.id < raiz->id) {
                if (raiz->direita == NULL) {
                    raiz->direita = malloc(sizeof(Filme));
                    *raiz->direita = novo;
                } else {
                    insereArvore(raiz->direita, novo);
                }
            } else if (novo.id > raiz->id){
                if (raiz->esquerda == NULL) {
                    raiz->esquerda = malloc(sizeof(Filme));
                    *raiz->esquerda = novo;
                } else {
                    insereArvore(raiz->esquerda, novo);
                }
            }
        }
    }
}

// inclui um filme na hash table (quando os filmes estão listados na tabela hash)
void incluiFilmeHash(Filmes *lista, Filme novo, int numUsuarios){
    int posicao = calculaHash(novo, numUsuarios, lista->tamanhoLista);
    novo.direita = NULL;
    novo.esquerda = NULL;
    // checamos se houve colisão
    if(lista->lista[posicao].id == -1) {
        // não houve colisão
        lista->lista[posicao] = novo;
    } else {
        // houve colisão, inserimos na árvore na posição dada
        insereArvore(&lista->lista[posicao], novo);
    }
}

// le o arquivo dado por nomeArquivo e procura os filmes conforme
// a especificação, colocando-os na coleção de filmes passada
void recebeFilmesArquivo(Filmes *lista, char* nomeArquivo) {
    FILE* arq;
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL) {
        // erro na abertura do arquivo
        return;
    }

    Filme adicionar;
    char* token;
    char linha[150];

    // usa a função strtok para separar cada linha do arquivo em tokens
    // usando \t (tab) como separador
    fgets(linha, 150, arq);
    while(!feof(arq)) {
        token = strtok(linha, "\t");
        int id = atoi(token);
        token = strtok(NULL, "\t");
        char nome[500];
        strcpy(nome, token);
        token = strtok(NULL, "\t");
        int id_imdb = atoi(token);
        token = strtok(NULL, "\t");
        int ano = atoi(token);

        inicializaFilme(&adicionar, id, nome, id_imdb, ano);

        incluiFilmeFinal(lista, adicionar);

        fgets(linha, 150, arq);
    }

    fclose(arq);
}