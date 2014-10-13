/***********************************************
 *                                             *
 * Implementacao das funcoes de alocacao de    *
 * memoria em um vetor estatico                *
 *                                             *
 ***********************************************/


// tamanho maximo da memoria
#define MAX_MEM 1024576

// a memoria em si
extern unsigned char MEM[MAX_MEM];

struct bloco *inicioBlocos;

// funcoes de configuracao da memoria
void inicializa_gerencia(void);
void finaliza_gerencia(void);
void imprime_status_memoria(void);

// funcoes de alocacao
void *valloc(size_t size);
void  vfree(void *p);
void *vcalloc(size_t nitems, size_t size);
void *vrealloc(void *p, size_t size);