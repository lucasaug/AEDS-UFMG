
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 04/08/2014                            *
 *                                                        *
 * Arquivo que reúne funções que agem tanto em filmes     *
 * como em usuários                                       *
 *                                                        *
 **********************************************************/

Filmes filmesMaisPopulares(Filmes filmes, Usuario usuario, int numRecomendacoes, int numFilmes);
Filmes recomendacaoPersonalizada(Usuario recomendar, Usuarios lista, Filmes filmes,
                                 int numRecomendacoes, int tamanhoHash, int tamanhoListaLinear);
void calculaPopularidadeFilmes(Filmes* filmes, Usuarios usuarios);
void listaFilmesArvore(Filmes* resultado, Filme* raiz, Usuario usuario);