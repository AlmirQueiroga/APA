#include <stdio.h>

void insertionsort(int array[], int MAX_ELEM){
	int  aux, sort, i, j;
	

		for(i = 1; i < MAX_ELEM ; i++){
			
			sort = array[i];
			j = i - 1;
			

			while(j >= 0 && sort < array[j]){

				aux = array[j];
				array[j+1] = aux;
				//array[j] = aux;
           		j = j-1;

			}

			//array[j+1] = min;
			array[j+1] = sort;
		}


		for (i=0; i < MAX_ELEM; i++)
       	printf("%d ", array[i]);
   		printf("\n");


}


int main(){

	 int arrayteste[] = {12, 2, 24, 32, 16};

	 insertionsort(arrayteste, 5);
}