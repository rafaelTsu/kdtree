#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

//Funções de comparação
double comparaMuni_x(const void *a, const void *b){
	return (*(muni *)a).coord[0] - (*(muni *)b).coord[0];
}

double comparaMuni_y(const void *a, const void *b){
	return (*(muni *)a).coord[1] - (*(muni *)b).coord[1];
}

double comparaFast_x(const void *a, const void *b){
	return (*(tfast *)a).coord[0] - (*(tfast *)b).coord[0];
}

double comparaFast_y(const void *a, const void *b){
	return (*(tfast *)a).coord[1] - (*(tfast *)b).coord[1];
}

//Calcula distância entre dois pontos
double distancia_muni(const void *a, const void *b){
	double dx = (*(muni *)a).coord[0] - (*(muni *)b).coord[0];
	double dy = (*(muni *)a).coord[1] - (*(muni *)b).coord[1];

	return sqrt(dx*dx + dy*dy);
}

double distancia_fast(const void *a, const void *b){
	double dx = (*(tfast *)a).coord[0] - (*(tfast *)b).coord[0];
	double dy = (*(tfast *)a).coord[1] - (*(tfast *)b).coord[1];

	return sqrt(dx*dx + dy*dy);
}

int main(){
	vizinho *neighbors;
	char descarta;
	muni *municipios, aux1;
	muni temp;
	tfast temp1;
	tfast *fastfood, aux2;
	tarv arvMuni, arvFast;
	tnode *bestNode;
	FILE *arq;
	int size;
	int option;

	arq = fopen("csv/municipios.csv","r");

	if(arq == NULL){
		printf("\nErro ao abrir o arquivo municipios.\n\n");
		exit(1);
	}
	else{
		initialize(&arvMuni, comparaMuni_x, comparaMuni_y, distancia_muni);
		while(feof(arq) == 0){
			fscanf(arq, "%d, %[^,],%lf,%lf,%d,%d, %[^,],%d, %[^\n]", 
				&temp.cod_ibge, temp.nome, &temp.coord[0], &temp.coord[1], 
				&temp.capital, &temp.codigo_uf, temp.siafi_id, &temp.ddd,
				temp.fuso_horario);

			inserir(&arvMuni, aloca_muni(temp.cod_ibge, temp.nome, temp.coord[0], temp.coord[1], 
			temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd,
			temp.fuso_horario), 0);
		}
	}
	fclose(arq);	

	arq = fopen("csv/Fast_Food_Restaurants_US.csv","r");

	if(arq == NULL){
		printf("\nErro ao abrir o arquivo fastfood.\n\n");
		exit(1);
	}
	else{
		initialize(&arvFast, comparaFast_x, comparaFast_y, distancia_fast);
		while(feof(arq) == 0){
			fscanf(arq, " %[^,]", temp.regiao);
            fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^,]", temp1.endereco);
            fscanf(arq, "%c", &descarta);
            fscanf(arq, " %[^,]", temp1.categoria);
            fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^,]", temp1.cidade);
            fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^,]", temp1.pais);
            fscanf(arq, "%c", &descarta);
			fscanf(arq, " %lf", &temp1.coord[0]);
			fscanf(arq, "%c", &descarta);
			fscanf(arq, " %lf", &temp1.coord[1]);
			fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^,]", temp1.nome);
			fscanf(arq, "%c", &descarta);
			fscanf(arq, " %d", &temp1.cod_postal);
			fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^,]", temp1.prov);
			fscanf(arq, "%c", &descarta);
			fscanf(arq, " %[^\n]", temp1.site);

			inserir(&arvFast, aloca_fast(temp1.endereco, temp1.categoria, temp1.cidade, temp1.pais, temp1.coord[0], temp1.coord[1], 
			temp1.nome, temp1.cod_postal, temp1.prov, temp1.site), 0);
		}
	}
	fclose(arq);

	do{
		printf("0 - Sair\n1 - Procurar pelos municípios mais próximos do Brasil\n2 - Procurar pelos fastfoods mais próximos\nDigite a opção: ");
		scanf("%d",&option);

		if(option == 1){
			printf("\nDigite quantos municípios mais próximos deseja buscar:\n");
			scanf("%d", &size);
			printf("\nDigite as coordenadas: (Latitude Longitude)\n");
			scanf("%lf %lf", &aux1.coord[0], &aux1.coord[1]);

			neighbors = malloc(size * sizeof(vizinho));
			initialize_neighbors(neighbors, size);

			bestNode = findNearestNeighbor(&arvMuni, arvMuni.raiz, &aux1, 0);
			neighbors[0].vizin = bestNode;
			neighbors[0].distance = (arvMuni.distancia(bestNode->reg, &aux1));
			searchNeighbors(&arvMuni, bestNode, neighbors, size);

			for(int i = 0; i<size; i++){
				municipios = (muni *)((neighbors[i].vizin)->reg);
				printf("\n%d° cidade mais perto:\n", i+1);
				printf("Código IBGE: %d\nNome do município: %s\nLatitude: %f\nLongitude: %f\nCapital: %d\nCódigo UF: %d\nSiafi ID: %s\nDDD: %d\nFuso horário: %s\nRegião: %s\nUF: %s\n\n", 
					municipios->cod_ibge, municipios->nome, municipios->coord[0], municipios->coord[1], 
					municipios->capital, municipios->codigo_uf, municipios->siafi_id, municipios->ddd,
					municipios->fuso_horario, municipios->regiao, municipios->uf);
			}
			free(neighbors);
		}

		else if(option == 2){
			printf("\nDigite quantos fastfoods mais próximos deseja buscar:\n");
			scanf("%d", &size);
			printf("\nDigite as coordenadas: (Latitude Longitude)\n");
			scanf("%lf %lf", &aux2.coord[0], &aux2.coord[1]);

			neighbors = malloc(size * sizeof(vizinho));
			initialize_neighbors(neighbors, size);

			bestNode = findNearestNeighbor(&arvFast, arvFast.raiz, &aux2, 0);
			neighbors[0].vizin = bestNode;
			neighbors[0].distance = (arvFast.distancia(bestNode->reg, &aux2));
			searchNeighbors(&arvFast, bestNode, neighbors, size);

			for(int i = 0; i<size; i++){
				fastfood = (tfast *)((neighbors[i].vizin)->reg);
				printf("\n%d° fastfood mais perto:\n", i+1);
				printf("Adress: %s\nCategories: %s\nCity: %s\nLatitude: %f\nLongitude: %f\nName: %s\nPostal code: %d\nProvince: %s\nWebsites: %s\n\n", 
					fastfood->endereco, fastfood->categoria, fastfood->cidade, fastfood->coord[0],
					fastfood->coord[1], fastfood->nome, fastfood->cod_postal,
					fastfood->prov, fastfood->site);
			}
			free(neighbors);
		}

		printf("\n");
	}while(option!=0);

	freeNode(arvMuni.raiz);
	freeNode(arvFast.raiz);

	return EXIT_SUCCESS;
}