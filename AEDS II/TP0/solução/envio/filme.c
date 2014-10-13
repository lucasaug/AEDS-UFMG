#include <string.h>
#include "filme.h"

// inicializa os dados do filme
void inicializaFilme(Filme *inicializar, int id, char *nome, int id_imdb, int ano){
    inicializar->id = id;
    strcpy(inicializar->nome, nome);
    inicializar->id_imdb = id_imdb;
    inicializar->ano = ano;
}