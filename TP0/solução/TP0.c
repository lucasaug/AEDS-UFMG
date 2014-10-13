#include <stdio.h>
#include <stdlib.h>

#include "TAD/usuario.h"
#include "TAD/usuarios.h"
#include "TAD/filme.h"
#include "TAD/filmes.h"

#include "Utils/funcoesUsuariosFilmes.h"

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

    fscanf(arquivoEntrada, "%s\t%s", nomeArqFilmes, nomeArqUsuarios);

    // Carregamos os filmes e usuários do sistema usando os nomes de arquivo encontrados
    Filmes filmes;
    Usuarios usuarios;

    inicializaFilmes(&filmes);
    inicializaUsuarios(&usuarios);

    recebeFilmesArquivo(&filmes, nomeArqFilmes);
    recebeUsuariosArquivo(&usuarios, nomeArqUsuarios);

    // Agora lemos do arquivo os usuários para os quais teremos que fazer recomendações
    int *usuariosRecomendar = malloc(sizeof(int) * usuarios.tamanhoLista);
    int numeroRecomendar; // Número de usuários para o qual teremos que fazer recomendações
    fscanf(arquivoEntrada, "%d", &usuariosRecomendar[0]);
    for(numeroRecomendar = 1; !feof(arquivoEntrada); numeroRecomendar++) {
        fscanf(arquivoEntrada, "%d", &usuariosRecomendar[numeroRecomendar]);
    }
    numeroRecomendar--;

    // Descobrimos os filmes mais populares
    Filmes populares = filmesMaisPopulares(filmes, usuarios);
    // Passamos o resultado para um vetor
    int i;
    Filme resultado[3];
    for(i = 0; i < populares.tamanhoLista; i++) {
        resultado[i] = getFilme(populares, i);
    }

    FILE *arquivoSaida = fopen(argv[2], "w");

    fprintf(arquivoSaida, "%s\t%s\n\n", nomeArqFilmes, nomeArqUsuarios);
    fprintf(arquivoSaida, "Most popular\n");
    fprintf(arquivoSaida, "%s\t%s\t%s\n\n", resultado[0].nome, resultado[1].nome, resultado[2].nome);
    fprintf(arquivoSaida, "Personalizada");
    for(i = 0; i < numeroRecomendar; i++) {
        Usuario recomendar = getUsuarioId(usuarios, usuariosRecomendar[i]);
        Filmes recomendacao = recomendacaoPersonalizada(recomendar, usuarios, filmes);
        fprintf(arquivoSaida, "\n%d:\t%s\t%s\t%s", usuariosRecomendar[i],      recomendacao.lista[0].nome,
                                                   recomendacao.lista[1].nome, recomendacao.lista[2].nome);
    }

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