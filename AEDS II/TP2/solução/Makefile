all: principal

principal:
	gcc -g -c -o TAD/filme.o TAD/filme.c
	gcc -g -c -o TAD/filmes.o TAD/filmes.c
	gcc -g -c -o TAD/usuario.o TAD/usuario.c
	gcc -g -c -o TAD/usuarios.o TAD/usuarios.c
	gcc -g -c -o TAD/registroFilmeJaccard.o TAD/registroFilmeJaccard.c
	gcc -g -c -o TAD/hashFilmeJaccard.o TAD/hashFilmeJaccard.c

	gcc -g -c -o Utils/funcoesUsuariosFilmes.o Utils/funcoesUsuariosFilmes.c

	gcc -g -o TP2.out TP2.c TAD/filme.o TAD/filmes.o TAD/usuario.o TAD/usuarios.o TAD/registroFilmeJaccard.o TAD/hashFilmeJaccard.o Utils/funcoesUsuariosFilmes.o