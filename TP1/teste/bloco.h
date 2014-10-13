/***************************************
 *                                     *
 * Estrutura que representa um bloco   *
 * de memoria, e funcoes para          *
 * coordenar uma lista de blocos       *
 *                                     *
 * Bloco.ocupado = 0: bloco livre      *
 * Bloco.ocupado = 1: bloco ocupado    *
 *                                     *
 ***************************************/

typedef struct bloco {
    unsigned char *endereco;
    int    posicao;
    size_t tamanho;
    int    ocupado;
    struct bloco *proximo;
} Bloco;

Bloco *inicializaLista(size_t tamanhoMemoria);
Bloco *recebeBloco(Bloco *inicio, unsigned char *endereco);
Bloco *insereBloco(Bloco *inicio, Bloco novo);
void   insereDepois(Bloco *local, Bloco *novo);
int    removeBloco(Bloco *inicio, unsigned char *endereco);