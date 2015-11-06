#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PGM{
	char tipo[3];
	int cols;
	int rows;
	int rep;
	int **dados;
} pgm;

pgm ler_imagem(FILE *fp){
	pgm imagem;
	fscanf(fp, " %2s", imagem.tipo);
	imagem.tipo[2]='\0';
	fscanf(fp, " %d %d", &imagem.cols, &imagem.rows);
	fscanf(fp, " %d", &imagem.rep);
	imagem.dados = (int **)malloc((imagem.rows)*sizeof(int *));
	int i, j;
	for(i = 0; i < imagem.rows; i++)
		imagem.dados[i] = (int *)malloc((imagem.cols)*sizeof(int));

	for(i = 0; i < imagem.rows; i++)
		for(j = 0; j < imagem.cols; j++)
			fscanf(fp, " %d", &imagem.dados[i][j]);

	return imagem;
}

void gravar_imagem(pgm imagem, FILE *fp){
	fprintf(fp, "%s\n", imagem.tipo);
	fprintf(fp, "%d %d\n", imagem.cols, imagem.rows);
	fprintf(fp, "%d\n", imagem.rep);

	int i,j;
	for(i = 0; i < imagem.rows; i++){
		for(j = 0; j < imagem.cols; j++)
			fprintf(fp, "%d ", imagem.dados[i][j]);
		fprintf(fp, "\n");
	}
}

pgm limiarizar(pgm imagem, int limiar){
	pgm limiarizada;
	strcpy(limiarizada.tipo, imagem.tipo);
	limiarizada.cols = imagem.cols;
	limiarizada.rows = imagem.rows;
	limiarizada.rep = 255;

	limiarizada.dados = (int **)malloc((limiarizada.rows)*sizeof(int *));
	int i, j;
	for(i = 0; i < limiarizada.rows; i++)
		limiarizada.dados[i] = (int *)malloc((limiarizada.cols)*sizeof(int));

	for(i = 0; i < imagem.rows; i++){
		for(j = 0; j < imagem.cols; j++){
			if(imagem.dados[i][j] < limiar)
				limiarizada.dados[i][j] = 0;
			else
				limiarizada.dados[i][j] = 255;
		}
	}

	return limiarizada;
}

int main(){
	FILE *fp_input, *fp_output;
	pgm input, output;
	char nome_input[256], nome_output[256];
	int limiar;

	// Entrada
	scanf(" %255s", nome_input);
	nome_input[255] = '\0';

	scanf(" %d", &limiar);

	scanf(" %255s", nome_output);
	nome_output[255] = '\0';

	fp_input = fopen(nome_input, "r");
	if(fp_input == NULL){
		printf("Erro na leitura da imagem.\n");
		return -1;
	}

	
	input = ler_imagem(fp_input);
	fclose(fp_input);

	// Processamento
	output = limiarizar(input, limiar);

	// Saida
	fp_output = fopen(nome_output, "w");
	if(fp_output == NULL){
		printf("Erro na gravacao da imagem.\n");
		return -1;
	}

	gravar_imagem(output, fp_output);
	fclose(fp_output);

	return 0;
}