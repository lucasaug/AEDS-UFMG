#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "usuarios.h"
#include "filme.h"
#include "filmes.h"
#include "registroFilmeJaccard.h"
#include "hashFilmeJaccard.h"
#include "funcoesUsuariosFilmes.h"

// inicializa a tabela hash
void inicializaHash(HashFilmeJaccard *table, int tamanhoHash) {
    table->lista = malloc(sizeof(FilmeJaccard) * tamanhoHash);
    int i;
    for(i = 0; i < tamanhoHash; i++) {
        strcpy(table->lista[i].nomeFilme, "");
        table->lista[i].idFilme = -1;
        table->lista[i].anoFilme = -1;
        table->lista[i].idUsuario = -1;
        inicializaFilme(&table->lista[i].filme, -1, "", -1, -1);
        table->lista[i].jaccard = -1;
        table->lista[i].direita = NULL;
        table->lista[i].esquerda = NULL;
    }
    table->tamanhoLista = tamanhoHash;
}

// função que calcula a posição de um registro na tabela hash
int calculaHashRegistro(FilmeJaccard registro, int tamanhoHash) {
    return (int) (registro.jaccard * (tamanhoHash-1));
}

// desaloca uma árvore de registros
void finalizaArvoreRegistros(FilmeJaccard* raiz) {
    if(raiz == NULL) {
        return;
    }
    finalizaArvoreRegistros(raiz->direita);
    finalizaArvoreRegistros(raiz->esquerda);
    free(raiz);
}

// desaloca as entradas na tabela hash e as árvores
void finalizaTabelaHashRegistro(HashFilmeJaccard *table) {
    int i;
    for(i = 0; i < table->tamanhoLista; i++) {
        if(table->lista[i].jaccard != -1) {
            finalizaArvoreRegistros(table->lista[i].esquerda);
            finalizaArvoreRegistros(table->lista[i].direita);
        }
    }
    free(table->lista);
    free(table);
}

// insere um registro em uma árvore, usando os critérios dados
void insereRegistroArvore(FilmeJaccard* raiz, FilmeJaccard* novo) {
    if (novo->jaccard < raiz->jaccard) {
        if (raiz->direita == NULL) {
            raiz->direita = novo;
        } else {
            insereRegistroArvore(raiz->direita, novo);
        }
    } else if (novo->jaccard > raiz->jaccard){
        if (raiz->esquerda == NULL) {
            raiz->esquerda = novo;
        } else {
            insereRegistroArvore(raiz->esquerda, novo);
        }
    } else {
        // caso tenham o mesmo valor de Jaccard, avaliamos pelo id de usuário
        if (novo->idUsuario < raiz->idUsuario) {
            if (raiz->direita == NULL) {
                raiz->direita = novo;
            } else {
                insereRegistroArvore(raiz->direita, novo);
            }
        } else if (novo->idUsuario > raiz->idUsuario){
            if (raiz->esquerda == NULL) {
                raiz->esquerda = novo;
            } else {
                insereRegistroArvore(raiz->esquerda, novo);
            }
        } else {
            // senão, avaliamos pela data do filme
            if (novo->anoFilme < raiz->anoFilme) {
                if (raiz->direita == NULL) {
                    raiz->direita = novo;
                } else {
                    insereRegistroArvore(raiz->direita, novo);
                }
            } else if (novo->anoFilme > raiz->anoFilme){
                if (raiz->esquerda == NULL) {
                    raiz->esquerda = novo;
                } else {
                    insereRegistroArvore(raiz->esquerda, novo);
                }
            } else {
                // por fim, avaliamos pelo id do filme
                if (novo->idFilme < raiz->idFilme) {
                    if (raiz->direita == NULL) {
                        raiz->direita = novo;
                    } else {
                        insereRegistroArvore(raiz->direita, novo);
                    }
                } else if (novo->idFilme > raiz->idFilme){
                    if (raiz->esquerda == NULL) {
                        raiz->esquerda = novo;
                    } else {
                        insereRegistroArvore(raiz->esquerda, novo);
                    }
                }
            }
        }
    }
}

// inclui um registro na hash table
void incluiRegistroHash(HashFilmeJaccard *lista, FilmeJaccard *novo) {
    int posicao = calculaHashRegistro(*novo, lista->tamanhoLista);
    novo->direita = NULL;
    novo->esquerda = NULL;
    // checamos se houve colisão
    if(lista->lista[posicao].jaccard == -1) {
        // não houve colisão
        lista->lista[posicao] = *novo;
        free(novo);
    } else {
        // houve colisão, inserimos na árvore na posição dada
        insereRegistroArvore(&lista->lista[posicao], novo);
    }
}

// preenche a tabela usando a lista de usuários e filmes,
// gerando os registros necessários
HashFilmeJaccard* geraRelacaoRegistros(Usuarios usuarios, Filmes filmes, Usuario recomendar, int tamanhoHash,
                                      int tamanhoListaLinear) {
    // recebemos a lista de filmes como uma lista linear
    int i;
    Filmes listaFilmes;
    inicializaFilmes(&listaFilmes, tamanhoListaLinear);
    for (i = filmes.tamanhoLista - 1; i >= 0; i--) {
        listaFilmesArvore(&listaFilmes, &filmes.lista[i], recomendar);
    }

    HashFilmeJaccard* resultado = malloc(sizeof(HashFilmeJaccard));
    inicializaHash(resultado, tamanhoHash);

    for(i = 0; i < usuarios.tamanhoLista; i++) {
        if(usuarios.lista[i].id != recomendar.id) {
            float jaccard = similaridadeJaccard(usuarios.lista[i], recomendar);
            int j;
            for(j = 0; j < listaFilmes.tamanhoLista; j++) {
                int idFilme = listaFilmes.lista[j].id;
                if(usuarios.lista[i].filmes[idFilme]){
                    // se o usuário atual já viu esse filme, ele entra na lista
                    FilmeJaccard* registro = malloc(sizeof(FilmeJaccard));
                    criaFilmeJaccard(registro, listaFilmes.lista[j], usuarios.lista[i], jaccard);
                    incluiRegistroHash(resultado, registro);
                }
            }
        }
    }

    free(listaFilmes.lista);

    return resultado;
}

