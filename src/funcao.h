#ifndef _VIZINHO_
#define  _VIZINHO_

#define TAM 20000
#define MAX 100
#define MIN 50

typedef struct _ponto{
    double coord[2];
}point;

typedef struct _municipios{
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

typedef struct _fastfood{
    char regiao[4];
    char endereco[MAX];
    char categoria[MAX];
    char cidade[MIN];
    char pais[MIN];
    char nome[MAX];
    int cod_postal;
    char prov[MAX];
    char site[TAM];
    double coord[2];
}tfast;

typedef struct _node{
    void *reg;
    struct _node *pai;
    struct _node *dir;
    struct _node *esq;
}tnode;

typedef struct _neighbors{
    tnode *vizin;
    double distance;
}vizinho;

typedef struct _arv{
    tnode *raiz;
    double (*compara_x)(const void *a, const void *b);
    double (*compara_y)(const void *a, const void *b);
    double (*distancia)(const void *a, const void *b);
}tarv;

muni *aloca_muni(int cod_ibge, char *nome, double coord0, double coord1, int capital, int codigo_uf, char *siafi_id, int ddd, char *fuso_horario);

tfast *aloca_fast(char *endereco, char *categoria, char *cidade, char *pais, double coord0, double coord1, char *nome, int cod_postal, char *prov, char *site);

void initialize(tarv *arv, double (*compara_x)(const void *a, const void *b), double (*compara_y)(const void *a, const void *b), double (*distancia)(const void *a, const void *b));

void inserir(tarv *arv, void *new_reg, int nivel);

tnode *tree_minimum(tnode *node);

tnode *tree_maximum(tnode *node);

tnode *sucessor(tnode *node);

tnode *antecessor(tnode *node);

void initialize_neighbors(vizinho *neighbors, int size);

void ordenar_vizinho(vizinho *neighbors, int i);

void searchNeighbors(tarv *arv, tnode *node, vizinho *neighbors, int n);

tnode *closest(tarv *arv, tnode *node, tnode *temp, void *coordenada);

tnode *findNearestNeighbor(tarv *arv, tnode *node, void *coordenada, int nivel);

void freeNode(tnode *node);

#endif