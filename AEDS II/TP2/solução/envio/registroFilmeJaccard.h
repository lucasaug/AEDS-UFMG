
/**********************************************************
 *                                                        *
 * Autor: Lucas Augusto                                   *
 * Data de criacao: 16/11/2014                            *
 *                                                        *
 * Registro que armazena um filme, o usuário que assistiu *
 * esse filme, e o número de Jaccard que esse usuário tem *
 * em comparação com o usuário para o qual desejamos      *
 * recomendar                                             *
 *                                                        *
 **********************************************************/

typedef struct FilmeJaccard FilmeJaccard;

struct FilmeJaccard {
    char nomeFilme[500];
    int idFilme;
    int anoFilme;
    int idUsuario;
    Filme filme;
    float jaccard;
    FilmeJaccard* direita;
    FilmeJaccard* esquerda;
};

void criaFilmeJaccard(FilmeJaccard* registro, Filme filme, Usuario usuario, float jaccard);