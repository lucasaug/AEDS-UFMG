/*********************************************
 *                                           *
 * Implementação de uma Treap                *
 * (Árvore binária + Heap)                   *
 *                                           *
 *********************************************/

#ifndef TREAP
#define TREAP

typedef struct Treap {
    int chave;
    int prioridade;
    struct Treap* direita;
    struct Treap* esquerda;
} Treap;

// Funções básicas
void inicializa(Treap *dados);
void limpaTreap(Treap *dados);

// Funções da especificação
int    inserir  (Treap **dados, int chave, int prioridade);
int    remover  (Treap **dados, int chave);
Treap* encontrar(Treap  *dados, int chave, char *caminho, int printaResultados);
Treap* fusao    (Treap  *A, Treap *B);
void   corte    (Treap  *dados, int chave, Treap **menor, Treap **maior);

#endif