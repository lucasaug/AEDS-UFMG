
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 20/08/2014                            *
 *                                                        *
 * Filme no sistema. O nome pode ter ate 500 caracteres   *
 *                                                        *
 **********************************************************/

typedef struct {
    int id;
    char nome[500];
    int id_imdb;
    int ano;
} Filme;

void inicializaFilme(Filme *inicializar, int id, char nome[500], int id_imdb, int ano);