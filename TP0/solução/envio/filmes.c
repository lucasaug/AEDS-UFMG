#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filme.h"
#include "filmes.h"

// inicializa o tamanho do vetor de filmes
void inicializaFilmes(Filmes *lista){
    lista->tamanhoLista = 0;
}

// inclui um filme no fim da lista
void incluiFilme(Filmes *lista, Filme novo) {
    int posicao = lista->tamanhoLista;
    lista->lista[posicao] = novo;
    lista->tamanhoLista++;
}

// retorna o filme de acordo com o index
// caso o index esteja além do limite do vetor, retorna um filme de id igual a -1
Filme getFilme(Filmes lista, int index) {
    Filme nulo;
    inicializaFilme(&nulo, -1, "", -1, -1);
    return index < lista.tamanhoLista ? lista.lista[index] : nulo;
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

        incluiFilme(lista, adicionar);

        fgets(linha, 150, arq);
    }

    fclose(arq);
}