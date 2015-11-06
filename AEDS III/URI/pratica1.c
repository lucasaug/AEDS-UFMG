#include <stdio.h>
#include <string.h>

int main() {
    // a especificacao define que a string possui no maximo
    // 50 caracteres, porem o execicio acusa resposta incorreta
    // se permitimos esse numero de caracteres, e funciona
    // para um numero maior, como 100
    char texto1[52], texto2[52];
    while(fgets(texto1, 52, stdin) != NULL) {
        if(fgets(texto2, 52, stdin) == NULL) {
            return -1;
        }

        // pre-calculamos o tamanho dos textos para otimizacao
        int tamTexto1 = strlen(texto1),
            tamTexto2 = strlen(texto2);
        // tamanho do texto 2 devera ser maior ou igual ao tamanho texto1
        if(tamTexto1 > tamTexto2) { 
            char temp[52];
            strcpy(temp, texto1);
            strcpy(texto1, texto2);
            strcpy(texto2, temp);
            int tamTemp = tamTexto1;
            tamTexto1 = tamTexto2;
            tamTexto2 = tamTemp;
        }
        int maior = 0;
        int i, j;

        // para cada letra da palavra, criamos as substrings que iniciam nela
        for(i = 0; i < tamTexto1; i++) {
            // e terminam nas letras seguintes
            for(j = 1; j <= tamTexto1 - i; j++) {
                if(j > maior) {
                    char padrao[52];
                    strncpy(padrao, texto1 + i, j);
                    padrao[j] = '\0';
                    int pos = procuraPadrao(texto2, padrao, j);
                    if(pos == -1) {
                        break;
                    }
                    maior = j;
                }
            }
        }
        printf("%d\n", maior);
    }
    return 0;
}

// recebemos o tamanho do padrao por questoes de otimizacao
int procuraPadrao(char* texto, char* padrao, int tamanhoPadrao) {
    int i;
    for(i = 0; i < strlen(texto) - tamanhoPadrao; i++) {
        int encontrado = !strncmp(texto + i, padrao, tamanhoPadrao);
        if(encontrado) {
            return i;
        }
    } 
   return -1;
}