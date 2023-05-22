#ifndef _VIZINHO_
#define  _VIZINHO_

#define TAM 20000
#define MAX 100
#define MIN 50

typedef struct ponto{
    double coord[2];
}point;

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
    char endereco[MIN];
    char categoria[MAX];
    char cidade[25];
    char pais[3];
    int cod_postal;
    char prov[3];
    char site[TAM];
}muni;

typedef void treg;

typedef struct neighbors{
    treg *vizin;
    double distance;
}vizinho;

typedef struct node{
    treg *reg;
    struct node *dir;
    struct node *esq;
}tnode;

muni *aloca_muni(int cod_ibge, char *nome, double coord0, double coord1, int capital, int codigo_uf, char *siafi_id, int ddd, char *fuso_horario);

muni *aloca_fast(char *endereco, char *categoria, char *cidade, char *pais, double coord0, double coord1, char *nome, int cod_postal, char *prov, char *site);

double compara(const double a, const double b);

double distancia(const muni *a, const point *b);

void initialize(tnode **node);

void initialize_neighbors(vizinho *neighbors, int size);

void inserir(tnode **node, treg *new_reg, int nivel);

void ordenar_vizinho(vizinho *neighbors, int i);

void searchNeighbors(tnode *node, point coordenada, vizinho *neighbors, int i, int nivel);

void freeNode(tnode *node);

#endif