#include <stdio.h>
#include <string.h>

int  procuraPadrao(char* texto, char* padrao, int tamanhoPadrao);
void trocaStr     (char *original, char *substring, int posicao, int tamRemover);

int main() {
    char tag[12], linha[52];
    int numero;
    while(fgets(tag, 11, stdin) != NULL) {
        int tamTag = strlen(tag);
        if(tag[tamTag - 1] == '\n'){
            tag[tamTag - 1] = '\0';
            tamTag--;
        }

        scanf("%d ", &numero);
        // convertemos o numero para uma string
        char numeroStr[4];
        sprintf(numeroStr, "%d", numero);
        int tamNumero = strlen(numeroStr);

        if(fgets(linha, 51, stdin) == NULL) {
            return -1;
        }
        int tamLinha = strlen(linha);
        if(linha[tamLinha - 1] == '\n'){
            linha[tamLinha - 1] = '\0';
            tamLinha--;
        }

        int i, j;
        int posicao = 0;

        // procuramos um caracter < na linha
        for(i = 0; (i < strlen(linha) - 1) && (posicao != -1); i++) {
            if(linha[i] == '<') {
                for(j = i + 1; j < strlen(linha) && linha[j] != '>'; j++) {}

                // encontramos a ocorrencia da tag na linha
                posicao = procuraPadrao(linha + i + 1, tag, tamTag);

                // consideramos apenas ocorrências antes do próximo >
                while(posicao + i < j && posicao != -1) {
                    // encontramos a ocorrencia da tag na linha,
                    // agora trocamos a palavra

                    trocaStr(linha, numeroStr, posicao + i + 1, tamTag);

                    i += tamNumero;
                    j += tamNumero - tamTag;

                    posicao = procuraPadrao(linha + i + posicao + 1, tag, tamTag);
                }

                // posicionamos o cursor no >
                i = j + 1;
            }
        }
        printf("%s\n", linha);
    }
    return 0;
}

// recebemos o tamanho do padrão por questões de otimização
int procuraPadrao(char* texto, char* padrao, int tamanhoPadrao) {
    int i;
    // para que a função seja case insensitive, criamos uma cópia
    // em letras minúsculas das strings
    char textoMin[51], padraoMin[11];
    int tamanhoTexto = strlen(texto);
    for(i = 0; i < tamanhoTexto || i < tamanhoPadrao; i++){
        if(i < tamanhoTexto)
            textoMin[i] = tolower(texto[i]);
        if(i < tamanhoPadrao)
            padraoMin[i] = tolower(padrao[i]);
    }
    textoMin[tamanhoTexto] = '\0';
    padraoMin[tamanhoPadrao] = '\0';

    for(i = 0; i < strlen(textoMin) - tamanhoPadrao; i++) {
        int encontrado = !strncmp(textoMin + i, padraoMin, tamanhoPadrao);
        if(encontrado) {
            return i;
        }
    } 
   return -1;
}

// função que troca um trecho de uma string por outro
void trocaStr(char *original, char *substring, int posicao, int tamRemover) {
    char inicioOriginal[51], fimOriginal[51];
    strncpy(inicioOriginal, original                       , posicao);
    inicioOriginal[posicao] = '\0';
    strncpy(fimOriginal   , original + posicao + tamRemover, strlen(original) - posicao - tamRemover);
    fimOriginal[strlen(original) - posicao - tamRemover] = '\0';
    strcat(inicioOriginal, substring);
    strcat(inicioOriginal, fimOriginal);
    strcpy(original, inicioOriginal);
    return;
}