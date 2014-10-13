
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 24/08/2014                            *
 *                                                        *
 * Armazena os filmes em um vetor, não implementa         *
 * alocação dinâmica                                      *
 *                                                        *
 **********************************************************/

#define MAX_FILMES 500

typedef struct {
    Filme lista[MAX_FILMES];
    int tamanhoLista;
} Filmes;

void inicializaFilmes(Filmes *lista);

void incluiFilme(Filmes *lista, Filme novo);
Filme getFilme(Filmes lista, int index);

void recebeFilmesArquivo(Filmes *lista, char* nomeArquivo);