#include <stdio.h>	// fopen, fclose, fgets, feof
#include <stdlib.h>	// malloc, free, exit
#include <string.h>	// strtok, strcmp
#include "valloc.h"	// valloc_initialize, valloc, vcalloc, vrealloc, vfree, print_valloc

#define	MAXLINE	256	// tamanho do buffer da linha
#define SEP	" \n"	// separador de instrucoes
#define SEPVAR	"V"	// separador do id da variavel

// instrucoes
#define MEM		"MEM"
#define VAR		"VAR"
#define VALLOC		"VALLOC"
#define VCALLOC		"VCALLOC"
#define VREALLOC	"VREALLOC"
#define VFREE		"VFREE"
#define PRINT		"PRINT"

int main(int argc, char * argv[])
{
	FILE	*pIn	= NULL;	// Arquivo de entrada

	char	*token = NULL,	// token de instrucao
		line[MAXLINE];	// buffer de linha

	char	**Var;		// vetor de variaveis alocadas com valloc

	int	nVars=0,	// numero de variaveis a serem criadas
		id=0,		// identificador de variavel
		allZero=0;	// flag de verificacao do vcalloc
	
	size_t	tamBloco=0,	// tamanho do bloco a ser alocado
		nItens=0,	// numero de itens alocados pelo vcalloc
		tamItem,	// tamanho de cada item alocado pelo vcalloc
		i=0;


	// Verifica o numero de argumentos
	if( argc < 2 )
	{
		printf("Utilização: ./tp1 <entrada> <saida>");
		exit(EXIT_FAILURE);
	}

	// Abre arquivo de entrada e saida
	pIn = fopen(argv[1],"r");

	// Verifica se o arquivo de entrada existe
	if( pIn == NULL )
	{
		printf("Erro arquivo de entrada %s não encontrado.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	// inicializa o gerenciamento do vetor da memoria
	inicializa_gerencia();

	// executa todos os comandos do arquivo de entrada
	while( 1 ){

		// linha por linha
		fgets(line, MAXLINE, pIn);	// tamanho do bloco
		
		// verifica se encontrou um final de arquivo
		if( feof(pIn) )break;

		// obtem comando
		token = strtok(line, SEP);


		// reconhece os comandos
		
		// VAR: Define numero de variaveis
		if ( strcmp(VAR, token) == 0 ){
			token = strtok(NULL, SEP);
			nVars = atoi(token);
			Var = (char **)malloc(sizeof(char*)*nVars);
			printf("VAR %d\n",nVars);
		}

		// VALLOC: Aloca espaco da memoria
		if ( strcmp(VALLOC,token) == 0 ){
			// tamanho do bloco
			token = strtok(NULL, SEP);
			tamBloco = atoi(token);

			// id da variavel
			token = strtok(NULL, SEP);	// V[id]
			token = strtok(token, SEPVAR);	// id
			id = atoi(token);
			
			// aloca espaco e armazena no vetor
			Var[id] = (char*)valloc(tamBloco);
			printf("\n");
			if(Var[id]!=NULL)printf("VALLOC %zu V%d\tOK\n",tamBloco, id);
			else printf("VALLOC %zu V%d\tNULL\n",tamBloco, id);
		}
		
		// VCALLOC: aloca espaco da memoria e preenche com zeros
		if ( strcmp(VCALLOC, token) == 0 ){
			// numero de itens alocados
			token = strtok(NULL, SEP);
			nItens = atoi(token);

			// tamanho do bloco
			token = strtok(NULL, SEP);
			tamItem = atoi(token);

			// id da variavel
			token = strtok(NULL, SEP);	// V[id]
			token = strtok(token, SEPVAR);	// id
			id = atoi(token);
			
			// aloca espaco e armazena no vetor
			Var[id] = (char*)vcalloc(nItens, tamItem);
			printf("\n");
			if(Var[id]!=NULL){
				allZero = 0;
				for(i=0;i<nItens*(tamItem/sizeof(char));i++){
					if(Var[id][i]!=0)allZero = 1;
				}
				printf("VCALLOC %zu %zu V%d\t%s\n",nItens, tamItem, id, allZero==0 ? "OK" : "NOT ZERO");
			}
			else printf("VCALLOC %zu V%d\tNULL\n",tamBloco, id);
		}

		// VREALLOC: realoca espaco da memoria
		if ( strcmp(VREALLOC, token) == 0 ){
			// tamanho do bloco
			token = strtok(NULL, SEP);
			tamBloco = atoi(token);

			// id da variavel
			token = strtok(NULL, SEP);	// V[id]
			token = strtok(token, SEPVAR);	// id
			id = atoi(token);
			
			Var[id] = (char*)vrealloc(Var[id], tamBloco);
			printf("\n");
			if(Var[id]!=NULL)printf("VREALLOC %zu V%d\tOK\n",tamBloco, id);
			else printf("VREALLOC %zu V%d\tNULL\n",tamBloco, id);
		}

		// VFREE: libera espacos de memoria
		if ( strcmp(VFREE, token) == 0 ){
			// id da variavel
			token = strtok(NULL, SEP);	// V[id]
			token = strtok(token, SEPVAR);	// id
			id = atoi(token);

			vfree(Var[id]);
			printf("\n");
			printf("VFREE %d\n", id);
		}
		// PRINT: Imprime o estado da memoria
		if ( strcmp(PRINT, token) == 0){
			imprime_status_memoria();
		}
	}

	// Fecha arquivos de entrada e saida
	fclose(pIn);
	
	// Libera o espaco de memoria alocado para as variaveis
	free(Var);

	// finaliza gerencia da memoria
	finaliza_gerencia();
	return 0;
}
