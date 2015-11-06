#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

#define MAX_COL 250
#define MAX_LIN 250

#define MAX_BITMAPS 20

struct bitmap{
    char nome[13];
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    int padding;
    RGBTRIPLE **dados;
};
typedef struct bitmap bitmap;

bitmap inicializar_bitmap(int linhas, int colunas){
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    bitmap bmp;


    bi.biSize = 40; 
    bi.biWidth = colunas;
    bi.biHeight = linhas;
    bi.biPlanes = 1; 
    bi.biBitCount = 24;
    bi.biCompression = 0;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    bi.biXPelsPerMeter = 0x130B; 
    bi.biYPelsPerMeter = 0x130B; 
    bi.biClrUsed = 0; 
    bi.biClrImportant = 0;

    bf.bfType = 0x4d42;
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
    bf.bfReserved1 = 0; // Reserved; must be zero.
    bf.bfReserved2 = 0; // Reserved; must be zero.
    bf.bfOffBits = 54;

    bmp.bi = bi;
    bmp.bf = bf;
    bmp.padding = padding;

    bmp.dados = (RGBTRIPLE **)malloc(bmp.bi.biHeight * sizeof(RGBTRIPLE *));
    int i;
    for(i = 0; i < bmp.bi.biHeight; i++)
        bmp.dados[i] = (RGBTRIPLE *)malloc(bmp.bi.biWidth * sizeof(RGBTRIPLE));

    return bmp;
}

RGBTRIPLE cor(BYTE blue, BYTE green, BYTE red){
    RGBTRIPLE triple;
    triple.rgbtBlue = blue;
    triple.rgbtGreen = green;
    triple.rgbtRed = red;
    return triple;

}

void colorir(bitmap *bmp, int x, int y, RGBTRIPLE triple){
    if(x <= bmp->bi.biWidth && y <= bmp->bi.biHeight)
        bmp->dados[y-1][x-1] = triple;
}

void zero(bitmap *bmp){
    int i, j, biHeight;
    for (i = 1, biHeight = abs(bmp->bi.biHeight); i <= biHeight; i++){
        // iterate over pixels in scanline
        for (j = 1; j <= bmp->bi.biWidth; j++){
            colorir(bmp, i, j, cor(0xFF, 0xFF, 0xFF));
        }
    }

}

void colorir_linha_vertical(bitmap *bmp, int x, int y1, int y2, char c){
    int j;
    // corrigindo linhas com coordenadas invertidas (y2 < y1)
    if(y1 > y2){
        int aux = y2;
        y2 = y1;
        y1 = aux;
    }
    RGBTRIPLE triple = cor((BYTE)c, (BYTE)c, (BYTE)c);
    for(j = y1; j <= y2; j++)
        colorir(bmp, x, j, triple);
}

void colorir_linha_horizontal(bitmap *bmp, int x1, int x2, int y, char c){
    int i;
    // corrigindo linhas com coordenadas invertidas (x2 < x1)
    if(x1 > x2){
        int aux = x2;
        x2 = x1;
        x1 = aux;
    }
    RGBTRIPLE triple = cor((BYTE)c, (BYTE)c, (BYTE)c);
    for(i = x1; i <= x2; i++)
        colorir(bmp, i, y, triple);
}

void desenhar_retangulo(bitmap *bmp, int x1, int x2, int y1, int y2, char c){
    int i;
    // corrigindo retangulos com coordenadas invertidas (y2 < y1)
    // x2 < x1 é corrigido na funcao colorir_linha_horizontal
    if(y1 > y2){
        int aux = y2;
        y2 = y1;
        y1 = aux;
    }
    for(i = y1; i <= y2; i++)
        colorir_linha_horizontal(bmp, x1,x2, i, c);
}

void salvar_bitmap(bitmap bmp){
    FILE *outptr;

    outptr = fopen(bmp.nome, "wb");
    if(outptr == NULL){
        perror("Nao foi possivel salvar a imagem.\n");
        return;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bmp.bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bmp.bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    int i, j, k, biHeight;
    for (i = 0, biHeight = abs(bmp.bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (j = 0; j < bmp.bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple = bmp.dados[i][j];

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // then add it back (to demonstrate how)
        for (k = 0; k < bmp.padding; k++)
            fputc(0x00, outptr);
    }

    fclose(outptr);
}

int main(){
    bitmap bitmapAtual;
    bitmapAtual.nome[0] = '\0';

    bitmap bitmapsSalvos[MAX_BITMAPS];
    int numBitmaps = 0;

    int linhas, colunas;
    int x1, x2, y1, y2;
    char c;
    char command;

    int primeiro_comando = 1;

    do{
        scanf(" %c", &command);
        if(command == 'I' || command == 'F')
            primeiro_comando = 0;

        if(!primeiro_comando){
            switch(command){
                case 'I':
                    
                    scanf("%d %d ", &colunas, &linhas);
                    bitmapAtual = inicializar_bitmap(linhas, colunas);
                    zero(&bitmapAtual);
                    break;
                case 'Z':
                    zero(&bitmapAtual);
                    break;
                case 'C':
                    scanf("%d %d %c", &x1, &y1, &c);
                    colorir(&bitmapAtual, x1, y1, cor((BYTE)c,(BYTE)c,(BYTE)c) );
                    break;
                case 'V':
                    scanf("%d %d %d %c", &x1, &y1, &y2, &c);
                    colorir_linha_vertical(&bitmapAtual, x1, y1, y2, c);
                    break;
                case 'H':
                    scanf("%d %d %d %c", &x1, &x2, &y1, &c);
                    colorir_linha_horizontal(&bitmapAtual, x1, x2, y1, c);
                    break;
                case 'R':
                    scanf("%d %d %d %d %c", &x1, &y1, &x2, &y2, &c);
                    desenhar_retangulo(&bitmapAtual, x1, x2, y1, y2, c);
                    break;
                case 'S':
                    scanf("%12s", bitmapAtual.nome);
                    salvar_bitmap(bitmapAtual);
                    bitmapsSalvos[numBitmaps] = bitmapAtual;
                    numBitmaps++;
                    bitmapAtual.nome[0] = '\0';
                    break;
                case 'F':
                    break;
                default:
                    for(;getchar()!='\n';);
            }
        }
    }
    while( command != 'F');
    return 0;
}
