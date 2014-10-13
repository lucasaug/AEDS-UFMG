all: principal

principal:
	gcc -c -o TAD/filme.o TAD/filme.c
	gcc -c -o TAD/filmes.o TAD/filmes.c
	gcc -c -o TAD/usuario.o TAD/usuario.c
	gcc -c -o TAD/usuarios.o TAD/usuarios.c

	gcc -c -o Utils/funcoesUsuariosFilmes.o Utils/funcoesUsuariosFilmes.c

	gcc -o TP0.out TP0.c TAD/filme.o TAD/filmes.o TAD/usuario.o TAD/usuarios.o Utils/funcoesUsuariosFilmes.o