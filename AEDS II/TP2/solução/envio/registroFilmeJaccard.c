#include <string.h>
#include "filme.h"
#include "usuario.h"
#include "registroFilmeJaccard.h"

void criaFilmeJaccard(FilmeJaccard* registro, Filme filme, Usuario usuario, float jaccard) {
    strcpy(registro->nomeFilme, filme.nome);
    registro->idFilme = filme.id;
    registro->anoFilme = filme.ano;
    registro->filme = filme;
    registro->idUsuario = usuario.id;
    registro->jaccard = jaccard;
    registro->direita = NULL;
    registro->esquerda = NULL;
}