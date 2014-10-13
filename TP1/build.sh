rm solucao/*

cp TAD/bloco.c solucao/bloco.c
cp TAD/bloco.h solucao/bloco.h
cp valloc.c solucao/valloc.c
cp valloc.h solucao/valloc.h

sed -i 's/TAD\/bloco.h/bloco.h/g' solucao/valloc.c