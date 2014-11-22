#include "usuario.h"

// funcao para definir um filme como assistido ou nao
//
// indexFilme: posição do filme no vetor de filmes
// assistido: 0 caso o filme nao tenha sido assistido,
//            do contário, entende-se que foi assistido

void incluiFilmeAssistido(Usuario *user, int indexFilme, int assistido) {
    // se recebermos um valor diferente de 0 para assistido,
    // inserimos o valor 1, independentemente da entrada 
    user->filmes[indexFilme] = assistido ? 1 : 0;
    if(assistido) user->numeroAssistidos++;
}

// encontra o filme na posição indexFilme
int getFilmeAssistido(Usuario user, int indexFilme) {
    return indexFilme < user.tamanhoListaFilmes ? user.filmes[indexFilme] : -1;
}

// inicializa o usuário com seu devido id, e inicializando
// o número de filmes assistidos em 0, além disso, zera todas
// as posições no vetor de filmes
void inicializaUsuario(Usuario *user, int id) {
    user->id = id;
    user->tamanhoListaFilmes = 0;
    user->numeroAssistidos = 0;
    int i;
    for(i = 0; i < MAX_FILMES; i++) {
        user->filmes[i] = 0;
    }
}

// função que calcula a similaridade de Jaccard para dois usuários
float similaridadeJaccard(Usuario user1, Usuario user2) {
    // número de filmes que ambos assistiram
    int numFilmesComuns = 0;
    int i;
    for(i = 0; i < user1.tamanhoListaFilmes; i++) {
        if(user1.filmes[i] && user2.filmes[i]) {
            numFilmesComuns++;
        }
    }

    // número de filmes que pelo menos um deles assistiu
    int numFilmesTotal = 0;
    for(i = 0; i < user1.tamanhoListaFilmes; i++) {
        if(user1.filmes[i] || user2.filmes[i]) {
            numFilmesTotal++;
        }
    }

    return ((float)numFilmesComuns)/((float)numFilmesTotal);
}