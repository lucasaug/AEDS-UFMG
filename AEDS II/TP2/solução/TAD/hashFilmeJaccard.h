
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 16/11/2014                            *
 *                                                        *
 * Tabela hash que armazena os registros de filme-usuário *
 *                                                        *
 **********************************************************/

typedef struct {
    FilmeJaccard* lista;
    int tamanhoLista;
} HashFilmeJaccard;

HashFilmeJaccard geraRelacaoRegistros(Usuarios usuarios, Filmes filmes, Usuario recomendar, int tamanhoHash);
void inicializaHash(HashFilmeJaccard *table, int tamanhoHash);
int calculaHashRegistro(FilmeJaccard registro, int tamanhoHash);
void finalizaTabelaHashRegistro(HashFilmeJaccard *table);

void insereRegistroArvore(FilmeJaccard* raiz, FilmeJaccard* novo);
void incluiRegistroHash(HashFilmeJaccard *lista, FilmeJaccard* novo);