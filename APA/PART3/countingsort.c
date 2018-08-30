#include <stdio.h>



int CountingSort(int array[],int TAM_ARRAY,int maior){
	
	int ArAux[maior+1]; //cria auxiliar
	int ArOrd[TAM_ARRAY]; //cria array de saida

	//Está configurando o auxiliar para 0
	for(int i = 0; i < maior + 1; i++){
	ArAux[i] = 0;
	}


	//acrescentando ao indice
	for(int i = 0; i < TAM_ARRAY; i++){
		ArAux[array[i]]++;
	}

	//etapa de somar com o sucessor
	for(int i = 1; i <= maior; i++){
		ArAux[i] += ArAux[i-1];
	}

	for(int i = TAM_ARRAY - 1; i >= 0; i--){
        ArOrd[--ArAux[array[i]]] = array[i];
    }

    for (int i = 0; array[i]; ++i)
        array[i] = ArOrd[i];

}


int main(){

	int maior = 0;
 	int array[] = {13, 12, 1, 4, 4, 6, 3, 4, 13, 2, 1};
 	int tamanho = sizeof(array)/sizeof(int);

 	for(int i = 0; i < tamanho; i++){
 		if(array[i] > maior){
 			maior = array[i];
 		}
 	}

 	CountingSort(array, tamanho, maior);

 	for(int i = 0; i < tamanho; i++){
 		printf("%d\n", array[i]);
 	}

	
	return 0;
}
