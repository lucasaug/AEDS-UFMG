#include <stdio.h>
#include <string.h>

int main() {
    char linha[52];
    fgets(linha, 51, stdin);

    while(!feof(stdin)) {
        int tamLinha = strlen(linha);
        if(linha[tamLinha - 1] == '\n') {
            linha[tamLinha - 1] = '\0';
            tamLinha--;
        }

        char mascaraLetras[27];
        int i;
        for(i = 0; i < 27; i++) {
            mascaraLetras[i] = 0;
        }

        for(i = 0; i < tamLinha; i++) {
            int posicaoLetra = linha[i] - 97;
            if(posicaoLetra >= 0) {
                mascaraLetras[posicaoLetra] = linha[i];
            }
        }

        int primeiro = 1;
        for(i = 0; i < 26; i++) {
            if(mascaraLetras[i]) {
                if(primeiro) {
                    primeiro = 0;
                } else {
                    printf(", ");
                }
                printf("%c:", mascaraLetras[i]);
                while(mascaraLetras[i]) i++;
                i--;
                printf("%c", mascaraLetras[i]);
            }
        }

        printf("\n");

        fgets(linha, 51, stdin);
    }

    return 0;
}