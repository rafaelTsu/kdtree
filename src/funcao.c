#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

muni *aloca_muni(int cod_ibge, char *nome, double coord0, double coord1, int capital, int codigo_uf, char *siafi_id, int ddd, char *fuso_horario){
	muni *municipios;
	municipios = malloc(sizeof(muni));

	municipios->cod_ibge = cod_ibge;
	strcpy(municipios->nome ,nome);
	municipios->coord.coord[0] = coord0;
	municipios->coord.coord[1] = coord1; 
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

fast *aloca_fast(char *endereco, char *categoria, char *cidade, char *pais, double coord0, double coord1, char *nome, int cod_postal, char *prov, char *site){
	fast *fastfood;
	fastfood = malloc(sizeof(fast));

	strcpy(fastfood->endereco, endereco);
	strcpy(fastfood->categoria, categoria);
	strcpy(fastfood->cidade, cidade);
	strcpy(fastfood->pais, pais);
	fastfood->coord.coord[0] = coord0;
	fastfood->coord.coord[1] = coord1;
	strcpy(fastfood->nome, nome);
	fastfood->cod_postal = cod_postal;
	strcpy(fastfood->prov, prov);
	strcpy(fastfood->site, site);

	return fastfood;
}

double compara(const ponto *a, const ponto *b, int index){
	return (*a).coord[index] - (*b).coord[index];
}

double distancia(const ponto *a, const ponto *b){
	double dx = (*a).coord[0] - (*b).coord[0];
	double dy = (*a).coord[1] - (*b).coord[1];

	return sqrt(dx*dx + dy*dy);
}

void construir_arvore(tarv *arv){
	arv->raiz = NULL;
	arv->compara = compara;
	arv->distancia = distancia;
}

void inserir(tarv *arv, treg *new_reg){
	int nivel = 0, index;
	tnode **ppnode;
	tnode *pnode;
	ppnode = &(arv->raiz);
	pnode = *ppnode;

	while(pnode != NULL){
		index = nivel%2;
		if((arv->compara(pnode->reg, new_reg, index)) < 0){
			ppnode = &(pnode->dir);
			pnode = *ppnode;
		}
		else{
			ppnode = &(pnode->esq);
			pnode = *ppnode;
		}
		nivel++;
	}

	if(*ppnode == NULL){
		(*ppnode) = malloc(sizeof(tnode));
		(*ppnode)->reg = new_reg;
		(*ppnode)->dir = NULL;
		(*ppnode)->esq = NULL;
	}
}

tnode *vizinho(tarv *arv, point ponto){
	int nivel = 0, index;
	tnode **ppnode;
	tnode *pnode;
	ppnode = &(arv->raiz);
	pnode = *ppnode;
}