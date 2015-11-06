#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/Treap.h"

int main() {

    Treap *dados = NULL;

    int numOp;
    scanf("%d%*c\n", &numOp);

    while(!feof(stdin) && numOp > 0) {

        char entrada[52];
        fgets(entrada, 51, stdin);
        char *operacao;
        operacao = strtok(entrada, " ");
        
        if(strcmp(operacao, "INSERT") == 0) {
            int chave      = atoi(strtok(NULL, " ")),
                prioridade = atoi(strtok(NULL, " "));

            inserir(&dados, chave, prioridade);
            
        } else if(strcmp(operacao, "REMOVE") == 0) {
            int chave      = atoi(strtok(NULL, " "));

            remover(&dados, chave);
            
        } else if(strcmp(operacao, "LOCATE") == 0) {
            int chave      = atoi(strtok(NULL, " "));
            char *caminho = (char*)malloc(sizeof(char) * 1000);
            caminho[0] = '\0';
            encontrar(dados, chave, caminho, 1);
            if(strlen(caminho) > 0) {
                printf("%s", caminho);
            }
            free(caminho);
            printf("\n");
            
        }

        numOp--;
    }

    limpaTreap(dados);

    return 0;
}