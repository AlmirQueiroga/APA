

#include<stdio.h>
#include<conio.h>
#include<vector>



using namespace std;
const int MAX = 1000
const int infinito = 9999

	
	/*C[][]
	aresta[][]
	visitados[]
	distancia[]
	*/



void Dijkstra(std::vector<int , int> C, int n, int init){

 	std::vector<int, int> AUX, anterior[n], visitado[n], distancia[MAX], novisit, prox, minim;

 	// Faz a matriz de distancias
 	for(i = 0; i < n; i++){
 		for(int j = 0; j < n; j++){
 			if(C[][] == 0){
 				AUX[i][j] = infinito; //se os vertices não tem conexão então a distancia é infinita 
 				}
 			if(C[][] != 0){
 				AUX[i][j] = C[i][j];
 				}
 			}

 		}

 	 for(int i=0; i<n; i++){
        visitado[i]= 0; 
        distancia[i] = AUX[init][i];
        anterior[i] = init
    	}
    distancia[init] = 0;
    visitado[init] = 1;
    novisit = 1;

     while(novisit < n-1)
    {
        minim =infinito;
        
        for(i=0; i<n; i++)
            if(distancia[i]<minim && !visitado[i])
            {
                minim = distancia[i];
                prox = i;
            }
                       
            visitado[prox]= 1;
            for(i=0; i < n; i++)
                if(!visitado[i])
                    if(minim + AUX[prox][i] < distancia[i])
                    {
                        distancia[i]=minim + AUX[prox][i];
                        anterior[i] = prox;
                    }
        novisit++;
    }


    printresultado(init, anterior[], n);

}


printresultado(init, anterior[], n){

	for(int i = 0; i < n; i++){
		if(i != init){
			printf("\np/no =%d", i);
            
            int j = i;
            do{
                j = anterior[j];

                printf("<-%d", j);

            }while(j != init);
            	continue;
		}
	}


}


int main(){

	/*
	 //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/dij10.txt", "r");
    
    int qLines = 0;
    int size;
    int tamanho;
    char line[999];
    char *token;

    fgets(line, 999,fp);

    size = atoi(line);

    int a[size][size] = {0};

	std::vector<int, int> adj[size][size];
    std::vector<int> v[size];

    while(1){
        int  i = qLines;
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }
        token = strtok(line, "\t");
        while(token!=NULL){
        	int index = ++i;
            a[qLines][index] = atoi(token);
            adj[qLines].push_back(index, a[qLines][index]); 
			adj[index].push_back(qLines, a[qLines][index]); 
            
            token = strtok(NULL, "\t");
        }
        qLines++;
    }
    fclose(fp);//fim da leitura
    //erro de leitura
    */


    Dijkstra(adj, size, 0);
}



