#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

int main(){
	vizinho *neighbors;
	muni *municipios;
	tnode *node;
	muni temp;
	FILE *arq;
	point aux;
	int size;
	int option;
	int character;

	do{
		printf("0 - Sair\n1 - Procurar pelos municípios mais próximos do Brasil\n2 - Procurar pelos fastfoods mais próximos\nDigite a opção: ");
		scanf("%d",&option);

		if(option == 1){
			arq = fopen("csv/municipios.csv","r");

			if(arq == NULL){
				printf("\nErro ao abrir o arquivo.\n\n");
			}
			else{
				initialize(&node);

				while(feof(arq) == 0){
					fscanf(arq, "%d, %[^,],%lf,%lf,%d,%d, %[^,],%d, %[^\n]", 
						&temp.cod_ibge, temp.nome, &temp.coord[0], &temp.coord[1], 
						&temp.capital, &temp.codigo_uf, temp.siafi_id, &temp.ddd,
						temp.fuso_horario);

					inserir(&node, aloca_muni(temp.cod_ibge, temp.nome, temp.coord[0], temp.coord[1], 
					temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd,
					temp.fuso_horario), 0);
				}
			}
			printf("\nDigite quantos municípios mais próximos deseja buscar:\n");
			scanf("%d", &size);
			printf("\nDigite as coordenadas: \n");
			scanf("%lf %lf", &aux.coord[0], &aux.coord[1]);

			neighbors = malloc(size * sizeof(vizinho));
			initialize_neighbors(neighbors, size);

			searchNeighbors(node, aux, neighbors, size, 0);

			for(int i = 0; i<size; i++){
				municipios = (muni *)neighbors[i].vizin;
				printf("\n%d° cidade mais perto:\n", i+1);
				printf("Código IBGE: %d\nNome do município: %s\nLatitude: %f\nLongitude: %f\nCapital: %d\nCódigo UF: %d\nSiafi ID: %s\nDDD: %d\nFuso horário: %s\nRegião: %s\nUF: %s\n\n", 
					municipios->cod_ibge, municipios->nome, municipios->coord[0], municipios->coord[1], 
					municipios->capital, municipios->codigo_uf, municipios->siafi_id, municipios->ddd,
					municipios->fuso_horario, municipios->regiao, municipios->uf);
			}
		}

		else if(option == 2){
			arq = fopen("csv/Fast_Food_Restaurants_US.csv","r");

			if(arq == NULL){
				printf("\nErro ao abrir o arquivo.\n\n");
			}
			else{
				initialize(&node);

				while(feof(arq) == 0){
					fscanf(arq, "%[^,], %[^,],",
						temp.regiao, temp.endereco);

					character = getchar();

					if(character == '\"'){
						fscanf(arq, " %[^\"], %[^,], %[^,],%lf,%lf, %[^,],%d, %[^,], %[^\n]",
							temp.categoria, temp.cidade, temp.pais, &temp.coord[0], &temp.coord[1], temp.nome, &temp.cod_postal, temp.prov, temp.site);
					}
					else{
						fscanf(arq, " %[^,], %[^,], %[^,],%lf,%lf, %[^,],%d, %[^,], %[^\n]",
							temp.categoria, temp.cidade, temp.pais, &temp.coord[0], &temp.coord[1], temp.nome, &temp.cod_postal, temp.prov, temp.site);
					}

					inserir(&node, aloca_fast(temp.endereco, temp.categoria, temp.cidade, temp.pais, temp.coord[0], temp.coord[1], 
					temp.nome, temp.cod_postal, temp.prov, temp.site), 0);

					municipios = aloca_fast(temp.endereco, temp.categoria, temp.cidade, temp.pais, temp.coord[0], temp.coord[1], 
					temp.nome, temp.cod_postal, temp.prov, temp.site);

					printf("Address: %s\nCategories: %s\nCity: %s\nCountry: %s\nLatitude: %f\nLongitude: %f\nName: %s\nPostal code: %d\nProvince: %s\nWebsites: %s\n\n", 
						municipios->endereco, municipios->categoria, municipios->cidade, municipios->pais, municipios->coord[0],
						municipios->coord[1], municipios->nome, municipios->cod_postal,
						municipios->prov, municipios->site);
				}
			}
			printf("\nDigite quantos fastfoods mais próximos deseja buscar:\n");
			scanf("%d", &size);
			printf("\nDigite as coordenadas: \n");
			scanf("%lf %lf", &aux.coord[0], &aux.coord[1]);

			neighbors = malloc(size * sizeof(vizinho));
			initialize_neighbors(neighbors, size);

			searchNeighbors(node, aux, neighbors, size, 0);

			for(int i = 0; i<size; i++){
				municipios = (muni *)neighbors[i].vizin;
				printf("\n%d° fastfood mais perto:\n", i+1);
				printf("Adress: %s\nCategories: %s\nCity: %s\nLatitude: %f\nLongitude: %f\nName: %s\nPostal code: %d\nProvince: %s\nWebsites: %s\n\n", 
					municipios->endereco, municipios->categoria, municipios->cidade, municipios->coord[0],
					municipios->coord[1], municipios->nome, municipios->cod_postal,
					municipios->prov, municipios->site);
			}
		}

		printf("\n\n");
		free(neighbors);
		freeNode(node);
		fclose(arq);	
	}while(option!=0);


	return EXIT_SUCCESS;
}