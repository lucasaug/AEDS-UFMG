
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 24/08/2014                            *
 *                                                        *
 * Armazena os usuários em um vetor, com alocação         *
 * dinâmica                                               *
 *                                                        *
 **********************************************************/

typedef struct {
    Usuario* lista;
    int tamanhoLista;
} Usuarios;

void inicializaUsuarios(Usuarios *lista, int tamanhoListaUsuarios);

void incluiUsuario(Usuarios *lista, Usuario novo);
Usuario getUsuario(Usuarios lista, int indexUsuario);
Usuario getUsuarioId(Usuarios lista, int id);

void recebeUsuariosArquivo(Usuarios *lista, char* nomeArquivo, int numFilmes);