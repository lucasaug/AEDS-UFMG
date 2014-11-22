
/***********************************************************
 *                                                         *
 * Autor: Lucas Augusto                                    *
 * Data de criacao: 20/08/2014                             *
 *                                                         *
 * Usuario do sistema, armazena apenas o id do usuario     *
 * e uma lista dos filmes que ja assistiu. Os filmes sao   *
 * armazenados no vetor de acordo com seu id no banco.     *
 * Se o usuario ja viu esse filme, inserimos o             *
 * valor 1, do contrario, inserimos 0. O campo             *
 * tamanhoListaFilmes guarda a quantidade de filmes        *
 * registrados nesse usuário, tendo sido assistidos ou não *
 *                                                         *
 ***********************************************************/

#define MAX_FILMES 500

typedef struct {
    int id;
    int filmes[MAX_FILMES];
    int tamanhoListaFilmes;
    int numeroAssistidos;
} Usuario;

void incluiFilmeAssistido(Usuario *user, int indexFilme, int assistido);
int getFilmeAssistido(Usuario user, int indexFilme);
void inicializaUsuario(Usuario *user, int id);

float similaridadeJaccard(Usuario user1, Usuario user2);