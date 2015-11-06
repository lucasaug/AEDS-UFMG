// Funções: Leitura de ponto e ordenação externa dos pontos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Operacoes.h"

// Função auxiliadora que encontra o índice do maior elemento
// de um vetor de pontos

int maiorPonto(Ponto *lista, int tamanho) {
    if(tamanho == 0) return -1;

    int i;
    int indiceMaior = 0;
    for(i = 0; i < tamanho; i++) {
        if(lista[i].numAtaques > lista[indiceMaior].numAtaques) {
            indiceMaior = i;
        } else if(lista[i].numAtaques == lista[indiceMaior].numAtaques) {
            if(lista[i].distanciaQuad < lista[indiceMaior].distanciaQuad) {
                indiceMaior = i;
            } else if(lista[i].distanciaQuad == lista[indiceMaior].distanciaQuad) {
                if(lista[i].chegada < lista[indiceMaior].chegada) {
                    indiceMaior = i;
                }
            }
        }
    }

    return indiceMaior;
}

// Função que lê um ataque recebido

int lePonto(long long *num, char *x, char *y) {

    char c = '\0';
    scanf("%c", &c);

    // procuramos o caractere 'p' para iniciar um ataque
    while(c != 'p' && !feof(stdin))
        scanf("%c", &c);

    *num = 0;

    // procuramos ocorrências do caracter 'o'
    scanf("%c", &c);
    while((c != 'i' || (*num) == 0) && !feof(stdin)) {
        if(c == 'o')
            (*num)++;

        if((*num) > SEQUENCIAMAX)
            return 0;
        
        scanf("%c", &c);
    }

    // encontramos 'i', procuramos 'n' e 't' e o parêntese
    // de abertura das coordenadas
    while(c != 'n' && !feof(stdin))
        scanf("%c", &c);

    while(c != 't' && !feof(stdin))
        scanf("%c", &c);

    while(c != '(' && !feof(stdin))
        scanf("%c", &c);

    // lemos a coordenada x
    x[0] = '0';
    x[1] = '\0';

    // se torna 1 quando lermos algum valor para X
    int Xvalido = 0;

    scanf("%c", &c);
    while(c != ',' && !feof(stdin)) {
        if(isdigit(c)) {
            Xvalido = 1;

            int posInserir = strlen(x);
            if(posInserir == 1 && x[0] == '0')
                posInserir--;

            // caso o próximo dígito exceda o limite
            // a função retorna
            if(posInserir > MAXDIGITOS)
                return 0;

            x[posInserir] = c;
            x[posInserir + 1] = '\0';


        } else if(c == '(')
            return 0;

        scanf("%c", &c);
    }

    // checa se a coordenada x foi passada
    if(!Xvalido) return 0;

    // lemos a coordenada y
    y[0] = '0';
    y[1] = '\0';

    // se torna 1 quando lermos algum valor para Y
    int Yvalido = 0;

    scanf("%c", &c);
    while(c != ')' && !feof(stdin)) {
        if(isdigit(c)) {
            Yvalido = 1;

            int posInserir = strlen(y);
            if(posInserir == 1 && y[0] == '0')
                posInserir--;

            // caso o próximo dígito exceda o limite
            // a função retorna
            if(posInserir > MAXDIGITOS)
                return 0;

            y[posInserir] = c;
            y[posInserir + 1] = '\0';


        } else if(c == ',')
            return 0;

        scanf("%c", &c);
    }

    // checa se a coordenada y foi passada, e se foi lida
    // totalmente
    if(!Yvalido || c != ')') return 0;


    // se chegou aqui, um ataque foi lido corretamente
    return 1;
}

// Função que ordena os pontos recebidos externamente

void leOrdenado(char *nomeArquivo, int xBase, int yBase, unsigned long long tamMemoria, unsigned long long numPontos) {

    // calculamos a quantidade de memória que teremos disponível, em bytes
    unsigned long long memDisponivel = tamMemoria * USOMEMORIA * 1000000;

    // tamanho do buffer que poderemos usar
    unsigned long long tamanhoBuffer = memDisponivel / sizeof(Ponto);
    if(numPontos < tamanhoBuffer) {
        tamanhoBuffer = numPontos;
    }

    Ponto *buffer = (Ponto*)malloc(sizeof(Ponto) * tamanhoBuffer);
    if(buffer == NULL) {
        printf("Erro ao criar buffer");
        return;
    }

    FILE *arqOrigem = fopen(nomeArquivo, "r+b");

    // listamos os pontos em ordem decrescente de prioridade
    // enquanto a quantidade restante não couber na memória principal
    while(numPontos > tamanhoBuffer) {
        Ponto maior;
        maior.numAtaques = 0;
        maior.x = 0;
        maior.y = 0;
        long int posicaoArq = 0;
        rewind(arqOrigem);

        long long numAtaques = -1;
        fread(&numAtaques, sizeof(long long), 1, arqOrigem);

        // carregamos os dados do arquivo na memória
        while(!feof(arqOrigem)) {
            unsigned long long i = 0;

            while(!feof(arqOrigem) && i < tamanhoBuffer) {
                if(numAtaques != -1) {
                    buffer[i].numAtaques = numAtaques;
                    buffer[i].posicaoArq = posicaoArq;
                    fread(&buffer[i].x, sizeof(int), 1, arqOrigem);
                    fread(&buffer[i].y, sizeof(int), 1, arqOrigem);
                    fread(&buffer[i].chegada, sizeof(unsigned long long), 1, arqOrigem);
                    fread(&buffer[i].distanciaQuad, sizeof(unsigned long long), 1, arqOrigem);

                    i++;
                } else {
                    int descartaInt;
                    unsigned long long descartaUL;
                    fread(&descartaInt, sizeof(int), 1, arqOrigem);
                    fread(&descartaInt, sizeof(int), 1, arqOrigem);
                    fread(&descartaUL,  sizeof(unsigned long long), 1, arqOrigem);
                    fread(&descartaUL,  sizeof(unsigned long long), 1, arqOrigem);
                }

                posicaoArq = ftell(arqOrigem);
                fread(&numAtaques, sizeof(long long), 1, arqOrigem);
            }

            int posMaior = maiorPonto(buffer, i);

            Ponto listaComp[2];
            listaComp[0] = buffer[posMaior];
            listaComp[1] = maior;
            posMaior = maiorPonto(listaComp, 2);
            maior = listaComp[posMaior];


        }

        printf("%lld;(%d,%d)\n", maior.numAtaques, maior.x, maior.y);
        fseek(arqOrigem, maior.posicaoArq, SEEK_SET);

        long long nulificaPonto = -1;
        // sobrescrevemos o numero de ataques do ponto retirado com -1
        fwrite(&nulificaPonto, sizeof(long long), 1, arqOrigem);

        numPontos--;

    }

    // carregamos os pontos restantes na memória primária
    unsigned long long i = 0;
    long long numAtaques = 0;
    fread(&numAtaques, sizeof(long long), 1, arqOrigem);

    while(!feof(arqOrigem)) {

        if(numAtaques != -1) {
            buffer[i].numAtaques = numAtaques;
            fread(&buffer[i].x, sizeof(int), 1, arqOrigem);
            fread(&buffer[i].y, sizeof(int), 1, arqOrigem);
            fread(&buffer[i].chegada, sizeof(unsigned long long), 1, arqOrigem);
            fread(&buffer[i].distanciaQuad, sizeof(unsigned long long), 1, arqOrigem);
            i++;
        } else {
            int descartaInt[2];
            unsigned long long descartaUL[2];
            fread(&descartaInt, sizeof(int), 2, arqOrigem);
            fread(&descartaUL,  sizeof(unsigned long long), 2, arqOrigem);
        }

        fread(&numAtaques, sizeof(long long), 1, arqOrigem);

    }

    // lemos os pontos restantes
    while(numPontos > 0) {
        int posMaior = maiorPonto(buffer, numPontos);

        printf("%lld;(%d,%d)\n", buffer[posMaior].numAtaques, buffer[posMaior].x, buffer[posMaior].y);

        buffer[posMaior] = buffer[numPontos - 1];

        numPontos--;
    }

    fclose(arqOrigem);

    free(buffer);

}