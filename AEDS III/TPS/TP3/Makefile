all:
	gcc -g -c -o solucoes.o solucoes.c
	gcc -g -o bin/TP3 TP3.c solucoes.o -lm -lpthread
	rm solucoes.o

clean:
	rm bin/TP3