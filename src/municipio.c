#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "funcao.h"

int main(){
	//muni *municipios;
	muni temp;
	FILE *arq;
	tarv arv_municipios;

	arq = fopen("csv/municipios.csv","r");

	if(arq == NULL){
		printf("Erro ao abrir o arquivo.");
		exit(1);
	}
	else{
		construir_arvore(&arv_municipios, compara_muni, distancia_muni);

		while(feof(arq) == 0){
			fscanf(arq, "%d, %[^,],%lf,%lf,%d,%d, %[^,],%d, %[^\n]", 
			&temp.cod_ibge, temp.nome, &temp.coord[0], &temp.coord[1], 
			&temp.capital, &temp.codigo_uf, temp.siafi_id, &temp.ddd,
			temp.fuso_horario);

			inserir(&arv_municipios, aloca_muni(temp.cod_ibge, temp.nome, temp.coord[0], temp.coord[1], 
			temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd,
			temp.fuso_horario));

			/*municipios = aloca_muni(temp.cod_ibge, temp.nome, temp.coord[0], temp.coord[1], 
			temp.capital, temp.codigo_uf, temp.siafi_id, temp.ddd,
			temp.fuso_horario);

			printf("%d, %s, %f, %f, %d, %d, %s, %d, %s, %s, %s\n", municipios->cod_ibge, municipios->nome, municipios->coord[0], municipios->coord[1], 
			municipios->capital, municipios->codigo_uf, municipios->siafi_id, municipios->ddd,
			municipios->fuso_horario, municipios->regiao, municipios->uf);*/
		}
	}
	fclose(arq);



	//imprimir_muni(municipios);
	return EXIT_SUCCESS;
}