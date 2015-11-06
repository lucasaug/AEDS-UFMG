all:
	gcc -g -c -o Treap.o Treap.c
	gcc -g -o bin/TP0 TP0.c Treap.o
	rm Treap.o

test:
	gcc -g -c -o Treap.o Treap.c
	gcc -g -o teste experimental.c Treap.o
	rm Treap.o

cleantest:
	rm teste

clean:
	rm bin/TP0