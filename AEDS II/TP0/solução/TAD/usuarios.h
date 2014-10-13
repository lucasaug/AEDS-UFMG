
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 24/08/2014                            *
 *                                                        *
 * Armazena os usuários em um vetor, com alocação         *
 * dinâmica                                               *
 *                                                        *
 **********************************************************/

#define MAX_USUARIOS 2110

typedef struct {
    Usuario* lista;
    int tamanhoLista;
} Usuarios;

void inicializaUsuarios(Usuarios *lista);

void incluiUsuario(Usuarios *lista, Usuario novo);
Usuario getUsuario(Usuarios lista, int indexUsuario);
Usuario getUsuarioId(Usuarios lista, int id);

void recebeUsuariosArquivo(Usuarios *lista, char* nomeArquivo);