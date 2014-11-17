#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h"
#include "usuarios.h"

// inicializa o tamanho do vetor de usuários, e aloca a memória para o vetor
void inicializaUsuarios(Usuarios *lista) {
    lista->tamanhoLista = 0;
    lista->lista = malloc(sizeof(Usuario) * MAX_USUARIOS);
}

// inclui um usuario novo na última posição da lista
// caso haja espaço
void incluiUsuario(Usuarios *lista, Usuario novo) {
    int posicao = lista->tamanhoLista;
    lista->lista[posicao] = novo;
    lista->tamanhoLista++;
}

// retorna o usuario por seu index
// caso o index esteja além do limite do vetor, retorna um usuário de id igual a -1
Usuario getUsuario(Usuarios lista, int indexUsuario) {
    Usuario nulo;
    nulo.id = -1;
    return indexUsuario < lista.tamanhoLista ? lista.lista[indexUsuario] : nulo;
}

// retorna o usuário por seu id
// caso o id não exista na lista, retorna um usuário de id igual a -1
Usuario getUsuarioId(Usuarios lista, int id) {
    int i;
    for(i = 0; i < lista.tamanhoLista; i++) {
        if(lista.lista[i].id == id) {
            return lista.lista[i];
        }
    }

    Usuario nulo;
    nulo.id = -1;
    return nulo;
}

// insere na lista os usuário de um arquivo formatado conforme explicado
// na especificação do TP
void recebeUsuariosArquivo(Usuarios *lista, char* nomeArquivo, int numFilmes) {
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL) {
        // erro na abertura do arquivo
        return;
    }

    Usuario adicionar;
    char* token;
    char linha[1100];

    // usa a função strtok para separar cada linha do arquivo em tokens
    // usando \t (tab) como separador
    fgets(linha, 1100, arq);
    while(!feof(arq)) {

        token = strtok(linha, " ");
        inicializaUsuario(&adicionar, atoi(token));

        token = strtok(NULL, " ");
        while(token) {
            incluiFilmeAssistido(&adicionar, atoi(token), 1);
            token = strtok(NULL, " ");
        }

        adicionar.tamanhoListaFilmes = numFilmes;

        incluiUsuario(lista, adicionar);

        fgets(linha, 1100, arq);
    }

    fclose(arq);
}