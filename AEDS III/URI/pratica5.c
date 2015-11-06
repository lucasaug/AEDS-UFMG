#include <stdio.h>
#include <math.h>

// definimos as instruções
#define STA 0
#define LDA 1
#define BEQ 2
#define NOP 3
#define DEC 4
#define INC 5
#define JMP 6
#define HLT 7

unsigned char converteBin(char *string);
void printBin(unsigned char byte);

int main() {
    unsigned char memoria[32];
    unsigned char accu, pc;

    char entrada[10];
    fgets(entrada, 10, stdin);
    while(!feof(stdin) && entrada != NULL) {
        accu = 0;
        pc   = 0;

        memoria[0] = converteBin(entrada);

        int i;
        for(i = 1; i < 32; i++) {
            fgets(entrada, 10, stdin);
            memoria[i] = converteBin(entrada);
        }

        int halt = 0;
        while(!halt) {
            // pegamos a instrucao e o endereço especificados através de
            // máscaras de bit e bitshifts
            unsigned char instrucao = memoria[pc] >> 5,
                          endereco  = memoria[pc] & (16 + 8 + 4 + 2 + 1);

            ++pc;
            pc &= (16 + 8 + 4 + 2 + 1);

            switch (instrucao) {
                case STA:
                    memoria[endereco] = accu;
                    break;

                case LDA:
                    accu = memoria[endereco];
                    break;

                case BEQ:
                    if(accu == 0) pc = endereco;
                    break;

                case NOP:
                    break;

                case DEC:
                    accu--;
                    break;

                case INC:
                    accu++;
                    break;

                case JMP:
                    pc = endereco;
                    break;

                case HLT:
                    halt = 1;
                    break;
            }

        }

        printBin(accu);
        printf("\n");   

        fgets(entrada, 10, stdin);
    }

    return 0;
}

unsigned char converteBin(char *string) {
    unsigned char resultado = 0;

    int i;
    for(i = 0; i < 8; i++) {
        if(string[i] == '1')
            resultado += pow(2, 7 - i);
    }

    return resultado;
}

void printBin(unsigned char byte) {

    int i;
    for(i = 0; i < 8; i++) {
        if(byte & (int)pow(2, 7 - i))
            printf("1");
        else
            printf("0");
    }

}