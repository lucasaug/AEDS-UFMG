
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 20/08/2014                            *
 *                                                        *
 * Filme no sistema. O nome pode ter ate 500 caracteres   *
 * Possui apontadores de filmes para a direita e          *
 * da esquerda, que podem estar vazios enquanto os filmes *
 * estiverem sendo listados de forma convencional, sem    *
 * hash/árvores                                           *
 *                                                        *
 **********************************************************/

typedef struct Filme Filme;

struct Filme{
    int id;
    char nome[500];
    int id_imdb;
    int ano;
    int popularidade;
    Filme* direita;
    Filme* esquerda;
};

void inicializaFilme(Filme *inicializar, int id, char nome[500], int id_imdb, int ano);