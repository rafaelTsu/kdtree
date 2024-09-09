//Aluno Rafael Tsutomu Jyoboji

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

//Alocação dos vetores de struct
muni *aloca_muni(int cod_ibge, char *nome, double coord0, double coord1, int capital, int codigo_uf, char *siafi_id, int ddd, char *fuso_horario){
	int x = 0;
	muni *municipios;
	municipios = malloc(sizeof(muni));

	municipios->cod_ibge = cod_ibge;
	strcpy(municipios->nome ,nome);
	municipios->coord[0] = coord0;
	municipios->coord[1] = coord1; 
	municipios->capital = capital;
	municipios->codigo_uf = codigo_uf;
	strcpy(municipios->siafi_id, siafi_id);
	municipios->ddd = ddd;
	strcpy(municipios->fuso_horario, fuso_horario);

	if(municipios->codigo_uf == 11){
		strcpy(municipios->uf,"RO");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 12){
		strcpy(municipios->uf,"AC");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 13){
		strcpy(municipios->uf,"AM");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 14){
		strcpy(municipios->uf,"RR");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 15){
		strcpy(municipios->uf,"PA");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 16){
		strcpy(municipios->uf,"AP");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 17){
		strcpy(municipios->uf,"TO");
		strcpy(municipios->regiao,"Norte");
	}
	else if(municipios->codigo_uf == 21){
		strcpy(municipios->uf,"MA");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 22){
		strcpy(municipios->uf,"PI");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 23){
		strcpy(municipios->uf,"CE");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 24){
		strcpy(municipios->uf,"RN");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 25){
		strcpy(municipios->uf,"PB");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 26){
		strcpy(municipios->uf,"PE");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 27){
		strcpy(municipios->uf,"AL");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 28){
		strcpy(municipios->uf,"SE");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 29){
		strcpy(municipios->uf,"BA");
		strcpy(municipios->regiao,"Nordeste");
	}
	else if(municipios->codigo_uf == 31){
		strcpy(municipios->uf,"MG");
		strcpy(municipios->regiao,"Sudeste");
	}
	else if(municipios->codigo_uf == 32){
		strcpy(municipios->uf,"ES");
		strcpy(municipios->regiao,"Sudeste");
	}
	else if(municipios->codigo_uf == 33){
		strcpy(municipios->uf,"RJ");
		strcpy(municipios->regiao,"Sudeste");
	}
	else if(municipios->codigo_uf == 35){
		strcpy(municipios->uf,"SP");
		strcpy(municipios->regiao,"Sudeste");
	}
	else if(municipios->codigo_uf == 41){
		strcpy(municipios->uf,"PR");
		strcpy(municipios->regiao,"Sul");
	}
	else if(municipios->codigo_uf == 42){
		strcpy(municipios->uf,"SC");
		strcpy(municipios->regiao,"Sul");
	}
	else if(municipios->codigo_uf == 43){
		strcpy(municipios->uf,"RS");
		strcpy(municipios->regiao,"Sul");
	}
	else if(municipios->codigo_uf == 50){
		strcpy(municipios->uf,"MS");
		strcpy(municipios->regiao,"Centro-Oeste");
	}
	else if(municipios->codigo_uf == 51){
		strcpy(municipios->uf,"MT");
		strcpy(municipios->regiao,"Centro-Oeste");
	}
	else if(municipios->codigo_uf == 52){
		strcpy(municipios->uf,"GO");
		strcpy(municipios->regiao,"Centro-Oeste");
	}
	else if(municipios->codigo_uf == 53){
		strcpy(municipios->uf,"DF");
		strcpy(municipios->regiao,"Centro-Oeste");
	}

	return municipios;
}

tfast *aloca_fast(char *endereco, char *categoria, char *cidade, char *pais, double coord0, double coord1, char *nome, int cod_postal, char *prov, char *site){
	tfast *fastfood;
	fastfood = malloc(sizeof(tfast));

	strcpy(fastfood->endereco, endereco);
	strcpy(fastfood->categoria, categoria);
	strcpy(fastfood->cidade, cidade);
	strcpy(fastfood->pais, pais);
	fastfood->coord[0] = coord0;
	fastfood->coord[1] = coord1;
	strcpy(fastfood->nome, nome);
	fastfood->cod_postal = cod_postal;
	strcpy(fastfood->prov, prov);
	strcpy(fastfood->site, site);

	return fastfood;
}

//Inicia árvores
void initialize(tarv *arv, double (*compara_x)(const void *a, const void *b), double (*compara_y)(const void *a, const void *b), double (*distancia)(const void *a, const void *b)){
	arv->raiz = NULL;
	arv->compara_x = compara_x;
	arv->compara_y = compara_y;
	arv->distancia = distancia;
}

//Função para inserir o nó na árvore
void inserir(tarv *arv, void *new_reg, int nivel){
	tnode **ppnode;
	tnode *pnode;
	tnode *ppai = NULL;
	ppnode = &(arv->raiz);
	pnode = *ppnode;
	int index;

	while(pnode != NULL){
		index = nivel%2;

		if(index == 0){
			if(arv->compara_x(pnode->reg, new_reg) < 0){
				ppai = *ppnode;
				ppnode = &(pnode->dir);
				pnode = *ppnode;
			}
			else{
				ppai = *ppnode;
				ppnode = &(pnode->esq);
				pnode = *ppnode;
			}
		}

		else{
			if(arv->compara_y(pnode->reg, new_reg) < 0){
				ppai = *ppnode;
				ppnode = &(pnode->dir);
				pnode = *ppnode;
			}
			else{
				ppai = *ppnode;
				ppnode = &(pnode->esq);
				pnode = *ppnode;
			}
		}
		nivel++;
	}

	if(*ppnode == NULL){
		(*ppnode) = malloc(sizeof(tnode));
		(*ppnode)->reg = new_reg;
		(*ppnode)->dir = NULL;
		(*ppnode)->esq = NULL;
		(*ppnode)->pai = ppai;
	}
}

//Funções de busca do antecessor e sucessor
tnode *tree_minimum(tnode *node){
	while(node->esq != NULL){
		node = node->esq;
	}
	return node;
}

tnode *tree_maximum(tnode *node){
	while(node->dir != NULL){
		node = node->dir;
	}
	return node;
}

tnode *sucessor(tnode *node){
	if(node->dir != NULL){
		return tree_minimum(node->dir);
	}
	else{
		tnode *ppai = node->pai;
		while(ppai != NULL && node == ppai->dir){
			node = ppai;
			ppai = ppai->pai;
		}
		return ppai;
	}
}

tnode *antecessor(tnode *node){
	if(node->esq != NULL){
		return tree_maximum(node->esq);
	}
	else{
		tnode *ppai = node->pai;
		while(ppai != NULL && node == ppai->esq){
			node = ppai;
			ppai = ppai->pai;
		}
		return ppai;
	}
}


//Função para ordenar lista dos vizinhos mais próximos
void ordenar_vizinho(vizinho *neighbors, int n){
	vizinho aux;

	for(int i = 1; i<n-1; i++){
		aux.vizin = neighbors[i].vizin;
		aux.distance = neighbors[i].distance;
		for(int j = i+1; j<n; j++){
			if(neighbors[j].distance < aux.distance){
				neighbors[i].vizin = neighbors[j].vizin;
				neighbors[i].distance = neighbors[j].distance;
				neighbors[j].vizin = aux.vizin;
				neighbors[j].distance = aux.distance;
				aux.vizin = neighbors[i].vizin;
				aux.distance = neighbors[i].distance;
			}
		}
	}
}

//Funções de busca
void searchNeighbors(tarv *arv, tnode *node, vizinho *neighbors, int n){
	ordenar_vizinho(neighbors, n);
	tnode *antec = antecessor(node);
	tnode *suces = sucessor(node);
	int cont = 1;
	double ant, suc;

	while(cont++ < n){
		if(suces != NULL){
			suc = (arv->distancia(node->reg, suces->reg));
			if(suc < neighbors[n-1].distance){
				neighbors[n-1].distance = suc;
				neighbors[n-1].vizin = suces;
				ordenar_vizinho(neighbors, n);
			}
			suces = sucessor(suces);
		}
		if(antec != NULL){
			ant = (arv->distancia(node->reg, antec->reg));
			if(ant < neighbors[n-1].distance){
				neighbors[n-1].distance = ant;
				neighbors[n-1].vizin = antec;
				ordenar_vizinho(neighbors, n);
			}
			antec = antecessor(antec);
		}
	}
}

tnode *closest(tarv *arv, tnode *node, tnode *temp, void *coordenada){
	if(node == NULL){
		return temp;
	}
	else if(temp == NULL){
		return node;
	}
	else{
		double dist1 = arv->distancia(node->reg, coordenada);
		double dist2 = arv->distancia(temp->reg, coordenada);
		if(dist1 < dist2)
			return node;
		else
			return temp;
	}

}

tnode *findNearestNeighbor(tarv *arv, tnode *node, void *coordenada, int nivel){
	if(node == NULL){
		return NULL;
	}
	else{
		int index = nivel%2;
		double dist;
		tnode *pnode_prox = node;
		tnode *pnode_ant = node;
		if(index == 0){
			if(arv->compara_x(node->reg, coordenada) < 0){
				pnode_prox = node->dir;
				pnode_ant = node->esq;
			}
			else{
				pnode_prox = node->esq;
				pnode_ant = node->dir;
			}
			dist = arv->compara_x(coordenada, node->reg);
		}
		else{
			if(arv->compara_y(node->reg, coordenada) < 0){
				pnode_prox = node->dir;
				pnode_ant = node->esq;
			}
			else{
				pnode_prox = node->esq;
				pnode_ant = node->dir;
			}
			dist = arv->compara_y(coordenada, node->reg);
		}

		tnode *temp = findNearestNeighbor(arv, pnode_prox, coordenada, nivel+1);
		tnode *bestNode = closest(arv, node, temp, coordenada);

		double euclidiana = arv->distancia(coordenada, bestNode->reg);

		if(euclidiana >= dist*dist){
			temp = findNearestNeighbor(arv, pnode_ant, coordenada, nivel+1);
			bestNode = closest(arv, bestNode, temp, coordenada);
		}

		return bestNode;
	}
}

//Função para destruir a árvore
void freeNode(tnode *node){
	if(node != NULL){
		freeNode(node->esq);
		freeNode(node->dir);
		free(node->reg);
		free(node);
	}
}

//Função para inicializar vetor de vizinhos
void initialize_neighbors(vizinho *neighbors, int size){
	for(int i = 0; i<size; i++){
		neighbors[i].vizin = NULL;
		neighbors[i].distance = 10000000;
	}
}
