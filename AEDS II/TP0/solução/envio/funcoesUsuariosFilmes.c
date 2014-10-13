#include "filme.h"
#include "usuario.h"
#include "filmes.h"
#include "usuarios.h"

#include "funcoesUsuariosFilmes.h"

// Função auxiliar de filmesMaisPopulares
// Insere o filme em uma lista de filmes, na posição dada por index
// Insere no mesmo index, em uma lista de inteiros, o número de vezes que esse filme foi assistido
// int tamanho dá o tamanho de ambas as listas
void inserePosicao(Filme elemento, int vezesAssistido, Filme *lista, int *listaVezes, int index, int tamanho) {
    int i;
    for(i = index + 1; i < tamanho; i++) {
        lista[i] = lista[i-1];
    }
    lista[index] = elemento;

    for(i = index + 1; i < tamanho; i++) {
        listaVezes[i] = listaVezes[i-1];
    }
    listaVezes[index] = vezesAssistido;
}

Filmes filmesMaisPopulares(Filmes filmes, Usuarios usuarios) {
    int i, j;
    int tamanhoUsuarios = usuarios.tamanhoLista;

    // armazenamos o número de vezes que cada filme foi assistido
    // em um vetor, sendo que a posição do filme no vetor é a mesma
    // posição dentro da coleção de Filmes
    int vezesFilmes[MAX_FILMES];
    Filme listaFilmes[MAX_FILMES];

    // primeiro zeramos esse vetor
    for(i = 0; i < MAX_FILMES; i++){
        vezesFilmes[i] = 0;
        listaFilmes[i] = getFilme(filmes, i);
    }

    for(i = 0; i < tamanhoUsuarios; i++) {
        Usuario atual = getUsuario(usuarios, i);
        for(j = 0; j < atual.tamanhoListaFilmes; j++) {
            vezesFilmes[j] += atual.filmes[j];
        }
    }

    // armazenamos os três filmes mais populares, do mais popular
    // para o menos popular, e respectivamente armazenamos o número
    // de vezes que cada um foi assistido
    Filme popular[3];
    popular[0].id = popular[1].id = popular[2].id = -1;
    popular[0].ano = popular[1].ano = popular[2].ano = -1;
    int vezesPopular[3];
    vezesPopular[0] = 0;
    vezesPopular[1] = 0;
    vezesPopular[2] = 0;

    for(i = 0; i < MAX_FILMES; i++) {
        // inserimos os filmes mais populares na lista, considerando também
        // casos em que a quantidade de vezes assistido forem iguais

        // Nessa parte o código fica difícil de seguir
        // Basicamente ele compara com o filme mais popular de todos, caso ele vença
        // em algum dos critérios, ele fica como o mais popular e "empurra" os outros elementos
        // Caso perca do mais popular em algum quesito que não seja popularidade, comparamos com o segundo
        // mais popular, e caso perca dele também em um quesito que não seja popularidade, comparamos com o
        // terceiro mais popular. Porém, ele precisa checar para cada situação envolvendo cada quesito
        // de classificação, o que necessita uma verbosa árvore de ifs 

        if(vezesFilmes[i] > vezesPopular[0]) {
            // caso seja mais popular que o primeiro
            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 0, 3);
        } else if(vezesFilmes[i] == vezesPopular[0]) {
            // caso seja tão popular quanto o primeiro
            if(listaFilmes[i].ano > popular[0].ano) {
                // caso seja mais recente
                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 0, 3);
            } else if(listaFilmes[i].ano == popular[0].ano) {
                // caso seja tão recente quanto
                if(listaFilmes[i].id > popular[0].id) {
                    // caso o id seja maior
                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 0, 3);
                } else {
                    // caso o id seja menor
                    // temos que comparar com o segundo
                    if(vezesFilmes[i] > vezesPopular[1]) {
                        // caso seja mais popular que o segundo
                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                    } else if(vezesFilmes[i] == vezesPopular[1]) {
                        // caso seja tão popular quanto o segundo
                        if(listaFilmes[i].ano > popular[1].ano) {
                            // caso seja mais recente
                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                        } else if(listaFilmes[i].ano == popular[1].ano) {
                            // caso seja tão recente quanto
                            if(listaFilmes[i].id > popular[1].id) {
                                // caso o id seja maior
                                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                            } else {
                                // caso o id seja menor
                                // temos que comparar com o terceiro
                                if(vezesFilmes[i] > vezesPopular[2]) {
                                    // caso seja mais popular que o terceiro
                                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                } else if(vezesFilmes[i] == vezesPopular[2]) {
                                    // caso seja tão popular quanto o terceiro
                                    if(listaFilmes[i].ano > popular[2].ano) {
                                        // caso seja mais recente
                                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                    } else if(listaFilmes[i].ano == popular[2].ano) {
                                        // caso seja tão recente quanto
                                        if(listaFilmes[i].id > popular[2].id) {
                                            // caso o id seja maior
                                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                        }
                                    }
                                }
                            }
                        } else {
                            // caso seja mais velho
                            // temos que comparar com o terceiro
                            if(vezesFilmes[i] > vezesPopular[2]) {
                                // caso seja mais popular que o terceiro
                                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                            } else if(vezesFilmes[i] == vezesPopular[2]) {
                                // caso seja tão popular quanto o terceiro
                                if(listaFilmes[i].ano > popular[2].ano) {
                                    // caso seja mais recente
                                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                } else if(listaFilmes[i].ano == popular[2].ano) {
                                    // caso seja tão recente quanto
                                    if(listaFilmes[i].id > popular[2].id) {
                                        // caso o id seja maior
                                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                // caso seja mais velho
                // temos que comparar com o segundo
                if(vezesFilmes[i] > vezesPopular[1]) {
                    // caso seja mais popular que o segundo
                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                } else if(vezesFilmes[i] == vezesPopular[1]) {
                    // caso seja tão popular quanto o segundo
                    if(listaFilmes[i].ano > popular[1].ano) {
                        // caso seja mais recente
                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                    } else if(listaFilmes[i].ano == popular[1].ano) {
                        // caso seja tão recente quanto
                        if(listaFilmes[i].id > popular[1].id) {
                            // caso o id seja maior
                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                        } else {
                            // caso o id seja menor
                            // temos que comparar com o terceiro
                            if(vezesFilmes[i] > vezesPopular[2]) {
                                // caso seja mais popular que o terceiro
                                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                            } else if(vezesFilmes[i] == vezesPopular[2]) {
                                // caso seja tão popular quanto o terceiro
                                if(listaFilmes[i].ano > popular[2].ano) {
                                    // caso seja mais recente
                                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                } else if(listaFilmes[i].ano == popular[2].ano) {
                                    // caso seja tão recente quanto
                                    if(listaFilmes[i].id > popular[2].id) {
                                        // caso o id seja maior
                                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                    }
                                }
                            }
                        }
                    } else {
                        // caso seja mais velho
                        // temos que comparar com o terceiro
                        if(vezesFilmes[i] > vezesPopular[2]) {
                            // caso seja mais popular que o terceiro
                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                        } else if(vezesFilmes[i] == vezesPopular[2]) {
                            // caso seja tão popular quanto o terceiro
                            if(listaFilmes[i].ano > popular[2].ano) {
                                // caso seja mais recente
                                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                            } else if(listaFilmes[i].ano == popular[2].ano) {
                                // caso seja tão recente quanto
                                if(listaFilmes[i].id > popular[2].id) {
                                    // caso o id seja maior
                                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                                }
                            }
                        }
                    }
                }
            }
        }

        else if(vezesFilmes[i] > vezesPopular[1]) {
            // caso seja mais popular que o segundo
            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
        } else if(vezesFilmes[i] == vezesPopular[1]) {
            // caso seja tão popular quanto o segundo
            if(listaFilmes[i].ano > popular[1].ano) {
                // caso seja mais recente
                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
            } else if(listaFilmes[i].ano == popular[1].ano) {
                // caso seja tão recente quanto
                if(listaFilmes[i].id > popular[1].id) {
                    // caso o id seja maior
                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 1, 3);
                } else {
                    // caso o id seja menor
                    // temos que comparar com o terceiro
                    if(vezesFilmes[i] > vezesPopular[2]) {
                        // caso seja mais popular que o terceiro
                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                    } else if(vezesFilmes[i] == vezesPopular[2]) {
                        // caso seja tão popular quanto o terceiro
                        if(listaFilmes[i].ano > popular[2].ano) {
                            // caso seja mais recente
                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                        } else if(listaFilmes[i].ano == popular[2].ano) {
                            // caso seja tão recente quanto
                            if(listaFilmes[i].id > popular[2].id) {
                                // caso o id seja maior
                                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                            }
                        }
                    }
                }
            } else {
                // caso seja mais velho
                // temos que comparar com o terceiro
                if(vezesFilmes[i] > vezesPopular[2]) {
                    // caso seja mais popular que o terceiro
                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                } else if(vezesFilmes[i] == vezesPopular[2]) {
                    // caso seja tão popular quanto o terceiro
                    if(listaFilmes[i].ano > popular[2].ano) {
                        // caso seja mais recente
                        inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                    } else if(listaFilmes[i].ano == popular[2].ano) {
                        // caso seja tão recente quanto
                        if(listaFilmes[i].id > popular[2].id) {
                            // caso o id seja maior
                            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                        }
                    }
                }
            }
        }

        else if(vezesFilmes[i] > vezesPopular[2]) {
            // caso seja mais popular que o terceiro
            inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
        } else if(vezesFilmes[i] == vezesPopular[2]) {
            // caso seja tão popular quanto o terceiro
            if(listaFilmes[i].ano > popular[2].ano) {
                // caso seja mais recente
                inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
            } else if(listaFilmes[i].ano == popular[2].ano) {
                // caso seja tão recente quanto
                if(listaFilmes[i].id > popular[2].id) {
                    // caso o id seja maior
                    inserePosicao(listaFilmes[i], vezesFilmes[i], popular, vezesPopular, 2, 3);
                }
            }
        }
    }

    Filmes resultado;
    inicializaFilmes(&resultado);
    for(i = 0; i < 3; i++) {
        incluiFilme(&resultado, popular[i]);
    }

    return resultado;
}

Filmes recomendacaoPersonalizada(Usuario recomendar, Usuarios lista, Filmes filmes) {
    // Armazenamos o id e o valor da similaridade de Jaccard para 
    // o usuário mais semelhante na lista
    int idSemelhante = -1;
    float jaccardSemelhante = -1;
    int i;
    for(i = 0; i < lista.tamanhoLista; i++) {
        Usuario atual = getUsuario(lista, i);
        if(atual.id != recomendar.id) {
            float jaccard = similaridadeJaccard(recomendar, atual);
            if(jaccard > jaccardSemelhante) {
                idSemelhante = atual.id;
                jaccardSemelhante = jaccard;
            } else if(jaccard == jaccardSemelhante) {
                if(atual.id < idSemelhante) {
                    idSemelhante = atual.id;
                    jaccardSemelhante = jaccard;
                }
            }
        }
    }

    Usuario semelhante = getUsuarioId(lista, idSemelhante);

    // armazenamos os três filmes mais recentes, do mais recente
    // para o menos recente assistidos por esse usuário
    Filme recomendacao[3];
    inicializaFilme(&recomendacao[0], 0, "", 0, 0);
    inicializaFilme(&recomendacao[1], 0, "", 0, 0);
    inicializaFilme(&recomendacao[2], 0, "", 0, 0);

    for(i = 0; i < semelhante.tamanhoListaFilmes; i++) {
        if(semelhante.filmes[i]) {
            Filme filmeSelecionado = getFilme(filmes, i);

            // decidimos em que posição o filme entrará de acordo
            // com seu ano de lançamento
            if(filmeSelecionado.ano > recomendacao[0].ano) {
                // caso esse filme seja mais recente que o primeiro
                recomendacao[2] = recomendacao[1];
                recomendacao[1] = recomendacao[0];
                recomendacao[0] = getFilme(filmes, i);
            } else if(filmeSelecionado.ano == recomendacao[0].ano) {
                // caso esse filme seja tão recente quanto o primeiro
                if(filmeSelecionado.id > recomendacao[0].id) {
                    // caso o id desse filme seja maior
                    recomendacao[2] = recomendacao[1];
                    recomendacao[1] = recomendacao[0];
                    recomendacao[0] = getFilme(filmes, i);
                } else {
                    // o id é menor, precisamos comparar com o segundo
                    if(filmeSelecionado.ano > recomendacao[1].ano) {
                        // caso esse filme seja mais recente que o segundo
                        recomendacao[2] = recomendacao[1];
                        recomendacao[1] = getFilme(filmes, i);
                    } else if(filmeSelecionado.ano == recomendacao[1].ano) {
                        // caso esse filme seja tão recente quanto o segundo
                        if(filmeSelecionado.id > recomendacao[1].id) {
                            // caso o id desse filme seja maior
                            recomendacao[2] = recomendacao[1];
                            recomendacao[1] = getFilme(filmes, i);
                        } else {
                            // o id é menor, precisamos comparar com o terceiro
                            if(filmeSelecionado.ano > recomendacao[2].ano) {
                                // caso esse filme seja mais recente que o terceiro
                                recomendacao[2] = getFilme(filmes, i);
                            } else if(filmeSelecionado.ano == recomendacao[2].ano) {
                                // caso esse filme seja tão recente quanto o terceiro
                                if(filmeSelecionado.id > recomendacao[2].id) {
                                    // caso o id desse filme seja maior
                                    recomendacao[2] = getFilme(filmes, i);
                                }
                            }
                        }
                    }
                }
            }

            else if(filmeSelecionado.ano > recomendacao[1].ano) {
                // caso esse filme seja mais recente que o segundo
                recomendacao[2] = recomendacao[1];
                recomendacao[1] = getFilme(filmes, i);
            } else if(filmeSelecionado.ano == recomendacao[1].ano) {
                // caso esse filme seja tão recente quanto o segundo
                if(filmeSelecionado.id > recomendacao[1].id) {
                    // caso o id desse filme seja maior
                    recomendacao[2] = recomendacao[1];
                    recomendacao[1] = getFilme(filmes, i);
                } else {
                    // o id é menor, precisamos comparar com o terceiro
                    if(filmeSelecionado.ano > recomendacao[2].ano) {
                        // caso esse filme seja mais recente que o terceiro
                        recomendacao[2] = getFilme(filmes, i);
                    } else if(filmeSelecionado.ano == recomendacao[2].ano) {
                        // caso esse filme seja tão recente quanto o terceiro
                        if(filmeSelecionado.id > recomendacao[2].id) {
                            // caso o id desse filme seja maior
                            recomendacao[2] = getFilme(filmes, i);
                        }
                    }
                }
            }

            else if(filmeSelecionado.ano > recomendacao[2].ano) {
                // caso esse filme seja mais recente que o terceiro
                recomendacao[2] = getFilme(filmes, i);
            } else if(filmeSelecionado.ano == recomendacao[2].ano) {
                // caso esse filme seja tão recente quanto o terceiro
                if(filmeSelecionado.id > recomendacao[2].id) {
                    // caso o id desse filme seja maior
                    recomendacao[2] = getFilme(filmes, i);
                }
            }
        }
    }

    Filmes resultado;
    inicializaFilmes(&resultado);
    for(i = 0; i < 3; i++) {
        incluiFilme(&resultado, recomendacao[i]);
    }

    return resultado;
}