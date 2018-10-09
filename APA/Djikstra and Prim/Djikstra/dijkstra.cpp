//Dikstra's

/*
1. Create cost matrix C[ ][ ] from adjacency matrix adj[ ][ ]. C[i][j] is the cost of going from vertex i to vertex j. If there is no edge between vertices i and j then C[i][j] is infinity.
 
2. Array visited[ ] is initialized to zero.
               for(i=0;i<n;i++)
                              visited[i]=0;
 
3. If the vertex 0 is the source vertex then visited[0] is marked as 1.
 
4. Create the distance matrix, by storing the cost of vertices from vertex no. 0 to n-1 from the source vertex 0.
               for(i=1;i<n;i++)
                              distance[i]=cost[0][i];
Initially, distance of source vertex is taken as 0. i.e. distance[0]=0;
 
5. for(i=1;i<n;i++)
– Choose a vertex w, such that distance[w] is minimum and visited[w] is 0. Mark visited[w] as 1.
– Recalculate the shortest distance of remaining vertices from the source.
– Only, the vertices not marked as 1 in array visited[ ] should be considered for recalculation of distance. i.e. for each vertex v
               if(visited[v]==0)
                              distance[v]=min(distance[v],
                              distance[w]+cost[w][v])
 */

#include<stdio.h>
#include<conio.h>



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

	 //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/dij10.txt", "r");

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }
    
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


    Dijkstra(adj, size, 0);
}



