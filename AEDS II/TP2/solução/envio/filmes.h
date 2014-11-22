
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 24/08/2014                            *
 *                                                        *
 * Armazena os filmes em um vetor, não implementa         *
 * alocação dinâmica                                      *
 *                                                        *
 **********************************************************/

typedef struct {
    Filme* lista;
    int tamanhoLista;
} Filmes;

void inicializaFilmes(Filmes *lista, int tamanhoMaximo);
int calculaHash(Filme filme, int numUsuarios, int tamanhoHash);
void montaTabelaHash(Filmes *lista, int numUsuarios, int tamanhoHash);
void finalizaTabelaHash(Filmes *lista);

void incluiFilmeFinal(Filmes *lista, Filme novo);
void insereArvore(Filme* raiz, Filme novo);
void incluiFilmeHash(Filmes *lista, Filme novo, int numUsuarios);

void recebeFilmesArquivo(Filmes *lista, char* nomeArquivo);