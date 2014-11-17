#include "../TAD/filme.h"
#include "../TAD/usuario.h"
#include "../TAD/filmes.h"
#include "../TAD/usuarios.h"
#include "../TAD/registroFilmeJaccard.h"
#include "../TAD/hashFilmeJaccard.h"

#include "funcoesUsuariosFilmes.h"

#include <stdlib.h>

// Função auxiliar de filmesMaisPopulares
// Insere o filme em uma lista de filmes, na posição dada por index
// Insere no mesmo index, em uma lista de inteiros, o número de vezes que esse filme foi assistido
// int tamanho dá o tamanho de ambas as listas
void inserePosicao(Filme elemento, int vezesAssistido, Filme *lista, int *listaVezes, int index, int tamanho) {
    int i;
    for(i = index + 1; i < tamanho; i++) {
        lista[i] = lista[i-1];
    }
    lista[index] = elemento;

    for(i = index + 1; i < tamanho; i++) {
        listaVezes[i] = listaVezes[i-1];
    }
    listaVezes[index] = vezesAssistido;
}

// Função que calcula a popularidade dos filmes, somando em cada filme
// na lista de filmes cada uma das vezes que foi assistido
void calculaPopularidadeFilmes(Filmes* filmes, Usuarios usuarios) {
    int i;
    for(i = 0; i < filmes->tamanhoLista; i++) {
        int id = filmes->lista[i].id;
        int j;
        for(j = 0; j < usuarios.tamanhoLista; j++) {
            filmes->lista[i].popularidade += usuarios.lista[j].filmes[id];
        }
    }
}

// transforma a árvore de filmes em uma lista linear na ordem de impressão
void listaFilmesArvore(Filmes* resultado, Filme* raiz, Usuario usuario) {
    if(raiz == NULL) {
        return;
    }
    listaFilmesArvore(resultado, raiz->esquerda, usuario);
    // se o usuário não viu o filme raiz, inserimos ele no resultado
    if (!usuario.filmes[raiz->id]) {
        incluiFilmeFinal(resultado, *raiz);
    }
    listaFilmesArvore(resultado, raiz->direita, usuario);
}

// descobre os filmes mais populares e retorna o número pedido
// funciona para a lista em hash table
Filmes filmesMaisPopulares(Filmes filmes, Usuario usuario, int numRecomendacoes) {
    // caminhamento central pra achar o filme certo
    Filmes resultado;
    inicializaFilmes(&resultado);
    // passamos por toda a tabela hash em ordem decrescente,
    // para conseguir uma lista linear de filmes na ordem de visualização
    int i;
    for (i = filmes.tamanhoLista - 1; i >= 0; i--) {
        listaFilmesArvore(&resultado, &filmes.lista[i], usuario);
    }
    // caso a lista tenha mais elementos que o número de recomendações
    // que devem ser feitas, limitamos ao número desejado
    if(resultado.tamanhoLista > numRecomendacoes) {
        resultado.tamanhoLista = numRecomendacoes;
    }
    return resultado;
}

// transforma a árvore de registros filme-usuário em uma lista linear na ordem de impressão
void listaRegistrosArvore(Filmes* resultado, FilmeJaccard* raiz, Usuario usuario) {
    if(raiz == NULL) {
        return;
    }
    listaRegistrosArvore(resultado, raiz->esquerda, usuario);
    // se o usuário não viu o filme raiz, inserimos ele no resultado
    if (!usuario.filmes[raiz->idFilme]) {
        incluiFilmeFinal(resultado, raiz->filme);
    }
    listaRegistrosArvore(resultado, raiz->direita, usuario);
}

Filmes recomendacaoPersonalizada(Usuario recomendar, Usuarios lista, Filmes filmes, int numRecomendacoes,
                                 int tamanhoHash) {
    HashFilmeJaccard tabelaFilmes = geraRelacaoRegistros(lista, filmes, recomendar, tamanhoHash);

    // caminhamento central pra achar o filme certo
    Filmes resultado;
    inicializaFilmes(&resultado);
    // passamos por toda a tabela hash em ordem decrescente,
    // para conseguir uma lista linear de filmes na ordem de visualização
    int i;
    for (i = tabelaFilmes.tamanhoLista - 1; i >= 0; i--) {
        listaRegistrosArvore(&resultado, &tabelaFilmes.lista[i], recomendar);
    }
    // caso a lista tenha mais elementos que o número de recomendações
    // que devem ser feitas, limitamos ao número desejado
    if(resultado.tamanhoLista > numRecomendacoes) {
        resultado.tamanhoLista = numRecomendacoes;
    }

    finalizaTabelaHashRegistro(&tabelaFilmes);

    return resultado;
}