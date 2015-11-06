
// Estrutura que representa um ponto

typedef struct Ponto {
    long long numAtaques;
    int x;
    int y;
    unsigned long long chegada;
    unsigned long long distanciaQuad;
    long int posicaoArq;
} Ponto;

// Funções de leitura de ataque e ordenação

int lePonto(long long *num, char *x, char *y);
void leOrdenado(char *nomeArquivo, int xBase, int yBase, unsigned long long tamMemoria, unsigned long long numPontos);


// CONSTANTES

// máximo de o's em sequencia
#define SEQUENCIAMAX 2147483648
// número máximo de dígitos de x e y
#define MAXDIGITOS 4
// porcentagem de memória que usaremos para
// a ordenação externa
#define USOMEMORIA 0.8