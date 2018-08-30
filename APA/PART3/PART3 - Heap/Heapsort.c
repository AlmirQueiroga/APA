#include <stdio.h>

int TamanhoEx = NULL; 

void HeapSort(int array[],int tamanho){
    BuildMaxHeap(array, tamanho); //Constroi heap

    for(int i = tamanho - 1; i > 0; i--){
        int aux = array[0];
        array[0] = array[i]; //trocar a raiz com a folha
        array[i] = aux;
        TamanhoEx--; // remover o nó 
        MaxHeapify(array, 0);
    }
}

void BuildMaxHeap(int array[],int tamanho){ // fazer as propriedades do MaxHeap
    TamanhoEx = tamanho;
	int p = Pai(tamanho);
    for(int i = p; i >= 0; i--){
        MaxHeapify(array, i);
    }
}

void MaxHeapify(int array[], int i){
    int E = FilhoEsquerdo(i);
    int D = FilhoDireito(i);

    int maior = i; //raiz atual - Pai

    //ultimo ramo maior que a raiz? 
    if(E < TamanhoEx && array[E] > array[maior]){
        maior = E;
    }
    
    if(D < TamanhoEx && array[D] > array[maior]){
        maior = D;
    }
    
    //filhos maiores que o pai
    //trocar numero maior nos filhos pelo pai
    //até filho for menor e vai para o for do heapsort
    if(maior != i){
        int aux = array[i];
        array[i] = array[maior];
        array[maior] = aux;
        MaxHeapify(array, maior); 
    }
}

int Pai(int i){ 
    //if(i = 0)
      //  return 0;

    return (i - 1)/2;
}

int FilhoEsquerdo(int i){
    return 2*i + 1;
}

int FilhoDireito(int i){
    return 2*i + 2;
}

int main(int argc, char const *argv[])
{
    int array[] ={8, 23, 12, 2, 8, 41, 13, 2, 3, 2, 31};

   	int tamanho = sizeof(array)/sizeof(int);

    HeapSort(array, tamanho);

    for(int i = 0; i < tamanho; i++){
    	printf("%d\n", array[i]);
    }
  
    return 0;
}
