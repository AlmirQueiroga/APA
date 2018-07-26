#include <stdio.h>


void SelectionSort (int array[],int MAX_ELEM) {
  int i, j, min, aux;

   for(i = 0; i < MAX_ELEM - 1; i++){
   		for(j = i + 1; j < MAX_ELEM; j++){
   			if(array[j]<array[i]){
   				min = j;
   				aux = array[min];
    			array[min] = array[i];
    			array[i] = aux;
   			}
   		}
   }
 
 for (i = 0; i < MAX_ELEM; i++) {
    printf ("%d ", array[i]);
  }
  printf ("\n");
}

  


 int main () {
  int arrayteste[] = {12, 2, 24, 32, 16};
  
  
  SelectionSort(arrayteste, 5);
  
}


