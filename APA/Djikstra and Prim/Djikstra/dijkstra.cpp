

#include<stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <limits>



using namespace std;
const int MAX = 1000;
const int infinito = 9999;




void Dijkstra(std::vector<std::vector <int> > adj, int n, int init){
    //n = numero de nós
    //distancia = distancia vista do nó inicial
    //init = no inicial
	bool VisNod[n]; // quando true o no já esta no caminho minimo
	int distancia[n];
	int min = infinito; // <-- minimo dos nós ae 
	//int key = init; // no que vai visitar
	int min_index;
	int i, j, k;


	for(i = 0; i < n ; i++){
		distancia[i] = infinito;
		VisNod[i] = false;
		}
	distancia[init] = 0;
	VisNod[init] =true;

	for(i = 0; i < n -1; i++){
   			for (j = 0; j < n; j++) {
     			if (VisNod[j] == false && distancia[j] <= min){
         			min = distancia[j];
         			min_index = j; 
     				}
   				}	

   		VisNod[min_index] = true;
   			for(k = 0; k < n; k++){
   				if(!VisNod[k] && adj[min_index][k] && distancia[min_index] != infinito && distancia[min_index]+adj[min_index][k] < distancia[k]){

   					distancia[k] = distancia[min_index] + adj[min_index][k]; 
   					}
   			}

		}
	
		for (i = 0; i < n; i++) 
      	printf("%d ---> %d\n", i, distancia[i]); 
 	
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

	std::vector<std::vector<int> > adj(size, vector<int>(size));
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
            //adj[qLines].push_back(index, a[qLines][index]); 
			adj[index][qLines] = a[qLines][index]; 
            
            token = strtok(NULL, "\t");
        }
        qLines++;
    }
    fclose(fp);//fim da leitura


    Dijkstra(adj, size, 0);
}



