#include <stdio.h>
#include <stdlib.h>

#include "usuario.h"
#include "usuarios.h"
#include "filme.h"
#include "filmes.h"

#include "funcoesUsuariosFilmes.h"

int main(int argc, char *argv[]){

    // Caso o usuário não tenha passado parâmetros suficientes,
    // abortamos a execução do programa
    if(argc != 3) {
        return -1;
    }

    // Primeiro lemos os dados do arquivo de entrada
    FILE *arquivoEntrada = fopen(argv[1], "r");

    char *nomeArqFilmes = malloc(sizeof(char) * 255);
    char *nomeArqUsuarios = malloc(sizeof(char) * 255);
    int numRecomendacoes, tamanhoHash;

    fscanf(arquivoEntrada, "%s\t%s\t%d\t%d", nomeArqFilmes, nomeArqUsuarios,
                                             &numRecomendacoes, &tamanhoHash);

    // contamos o número de filmes no arquivo dado
    int numFilmes = 0;
    FILE *arqFilmes = fopen(nomeArqFilmes, "r");
    while(!feof(arqFilmes)) {
        char ch = fgetc(arqFilmes);
        if(ch == '\n')
        {
            numFilmes++;
        }
    }
    numFilmes++;
    fclose(arqFilmes);

    // e agora o número de usuários
    int numUsuarios = 0;
    FILE *arqUsuarios = fopen(nomeArqUsuarios, "r");
    while(!feof(arqUsuarios)) {
        char ch = fgetc(arqUsuarios);
        if(ch == '\n')
        {
            numUsuarios++;
        }
    }
    numUsuarios++;
    fclose(arqUsuarios);

    // Carregamos os filmes e usuários do sistema usando os nomes de arquivo encontrados
    Filmes filmes;
    Usuarios usuarios;

    inicializaFilmes(&filmes, numFilmes);
    inicializaUsuarios(&usuarios, numUsuarios);

    // recebemos os filmes e os colocamos em uma lista comum
    recebeFilmesArquivo(&filmes, nomeArqFilmes);
    recebeUsuariosArquivo(&usuarios, nomeArqUsuarios, numFilmes);

    // calculamos a popularidade dos filmes
    calculaPopularidadeFilmes(&filmes, usuarios);
    // agora organizamos os filmes, transformando a lista de filmes em uma tabela hash
    montaTabelaHash(&filmes, usuarios.tamanhoLista, tamanhoHash);

    // Agora lemos do arquivo os usuários para os quais teremos que fazer recomendações
    int *usuariosRecomendar = malloc(sizeof(int) * usuarios.tamanhoLista);
    int numeroRecomendar; // Número de usuários para o qual teremos que fazer recomendações
    fscanf(arquivoEntrada, "%d", &usuariosRecomendar[0]);
    for(numeroRecomendar = 1; !feof(arquivoEntrada); numeroRecomendar++) {
        fscanf(arquivoEntrada, "%d", &usuariosRecomendar[numeroRecomendar]);
    }
    numeroRecomendar--;

    FILE *arquivoSaida = fopen(argv[2], "w");

    fprintf(arquivoSaida, "%s\t%s\t%d\t%d\n", nomeArqFilmes, nomeArqUsuarios, numRecomendacoes, tamanhoHash);
    int i;
    for(i = 0; i < numeroRecomendar; i++) {
        Usuario recomendar = getUsuarioId(usuarios, usuariosRecomendar[i]);
        fprintf(arquivoSaida, "\n%d:\n", usuariosRecomendar[i]);
        fprintf(arquivoSaida, "Most popular\n");
        Filmes recomendacao = filmesMaisPopulares(filmes, recomendar, numRecomendacoes, numFilmes);
        int j;
        for(j = 0; j < recomendacao.tamanhoLista; j++) {
            fprintf(arquivoSaida, "%s\t", recomendacao.lista[j].nome);
        }
        free(recomendacao.lista);
        fprintf(arquivoSaida, "\n\nPersonalizada\n");
        recomendacao = recomendacaoPersonalizada(recomendar, usuarios, filmes, numRecomendacoes, tamanhoHash,
                                                 numFilmes * usuarios.tamanhoLista);
        for(j = 0; j < recomendacao.tamanhoLista; j++) {
            fprintf(arquivoSaida, "%s\t", recomendacao.lista[j].nome);
        }
        fprintf(arquivoSaida, "\n");
        free(recomendacao.lista);
    }

    // desalocamos a árvore de filmes
    finalizaTabelaHash(&filmes);

    // Fechamos os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    // Liberamos a memória usada
    free(usuarios.lista);
    free(usuariosRecomendar);
    free(nomeArqUsuarios);
    free(nomeArqFilmes);

    return 0;
}