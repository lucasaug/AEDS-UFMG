// Representação de uma cidade, função que calcula distâncias entre elas

#ifndef TP2_CIDADE
#define TP2_CIDADE

typedef struct Cidade {
    int x;
    int y;
} Cidade;

double distancia(Cidade A, Cidade B);

#endif