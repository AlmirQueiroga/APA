#include <stdio.h>

int TamanhoEx = NULL; 


int Pai(int i){
    if(i = 0)
        return 0;

    return (i - 1)/2;
}

int FilhoEsquerdo(int i){
    return 2*i + 1;
}

int FilhoDireito(int i){
    return 2*i + 2;
}

void MaxHeapify(int array[], int i){
    int E = FilhoEsquerdo(i);
    int D = FilhoDireito(i);

    int maior = i;

    if(E < TamanhoEx && array[E] > array[maior])
        maior = E;
    
    if(D < TamanhoEx && array[D] > array[maior])
        maior = D;

    if(maior != i){
        //std::swap(array[i], array[maior]);
        int aux = array[i];
        array[i] = array[maior];
        array[maior] = aux;
        MaxHeapify(array, maior);
    }
}

void BuildMaxHeap(int array[],int tamanho){
    TamanhoEx = tamanho;
    for(int i = (tamanho - 1)/2; i >= 0; i--){
        MaxHeapify(array, i);
    }
}

void HeapSort(int array[],int tamanho){
    BuildMaxHeap(array, tamanho);

    for(int i = tamanho - 1; i > 0; i--){
        //std::swap(array[0], array[i]);
        int aux = array[0];
        array[0] = array[i];
        array[i] = aux;
        TamanhoEx--;
        MaxHeapify(array, 0);
    }
}


int main(int argc, char const *argv[])
{
    int array[] ={1, 16, 5, 30, 27, 17, 20, 2, 57, 3, 90};

   	int tamanho = sizeof(array)/sizeof(int);

    HeapSort(array, tamanho);

    for(int i = 0; i < tamanho; i++){
    	printf("%d\n", array[i]);
    }
  
    return 0;
}
