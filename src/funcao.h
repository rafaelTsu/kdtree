#ifndef _VIZINHO_
#define  _VIZINHO_

#define TAM 2000
#define MAX 100
#define MIN 50

typedef struct municipios{
    int cod_ibge;
    char nome[MIN];
    double coord[2];
    int capital;
    int codigo_uf;
    char siafi_id[5];
    int ddd;
    char fuso_horario[MIN];
    char regiao[15];
    char uf[3];
}muni;

typedef struct fastfood{
    char endereco[MIN];
    char categoria[MAX];
    char cidade[25];
    char pais[3];
    double coord[2];
    char nome[MIN];
    int cod_postal;
    char prov[3];
    char site[TAM];
}fast;

typedef void treg;

typedef struct node{
    treg *reg;
    struct node *dir;
    struct node *esq;
}tnode;

typedef struct arvore{
    tnode *raiz;
    int (*compara)(const void *a, const void *b, int index);
}tarv;

muni *aloca_muni(int cod_ibge, char *nome, double coord0, double coord1, int capital, int codigo_uf, char *siafi_id, int ddd, char *fuso_horario);

fast *aloca_fast(char *endereco, char *categoria, char *cidade, char *pais, double coord0, double coord1, char *nome, int cod_postal, char *prov, char *site);

void construir_arvore(tarv *arv, int (*compara)(const void *a, const void *b, int index));

void inserir(tarv *arv, treg *new_reg);

void search(tarv *arv, int *coord);

#endif