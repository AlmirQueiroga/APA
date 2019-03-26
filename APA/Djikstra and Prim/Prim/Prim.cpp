#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

#define INFINITO 999999999

typedef pair<int, int> par;

int main()
{
    ifstream arq_matriz("instancias_teste/dij10.txt", ios::in);
    //ifstream arq_matriz("instancias_teste/dij20.txt", ios::in);
    //ifstream arq_matriz("instancias_teste/dij40.txt", ios::in);
    //ifstream arq_matriz("instancias_teste/dij50.txt", ios::in);

    int tam_matriz;
    int num_arestas = 0;
    arq_matriz >> tam_matriz; //Lê a primeira linha da matriz que diz respeito ao tamanho

    int dij[tam_matriz][tam_matriz] = {0}; //Cria matriz adjacência do tamanho certo 
    int n, m;                      // número de vértices e arestas
    int distancia[tam_matriz];           // o array de distâncias à fonte
    int processado[tam_matriz];          // o array que guarda se um vértice foi processado
    vector<par> vizinhos[tam_matriz];    // nossas listas de adjacência. O primeiro elemento do par representa a distância e o segundo representa o vértice
    
    for (int i = 0; i < tam_matriz; i++){
        for (int j = i; j < tam_matriz; j++){
            if (i == j) //Distância entre um vértice em relação a ele mesmo é 0
                continue;
            
            arq_matriz >> dij[i][j];
            dij[j][i] = dij[i][j];
            num_arestas++;
            vizinhos[i].push_back(par(dij[i][j], j));
            vizinhos[j].push_back(par(dij[i][j], i));
        }
    }


    

    for(int i = 2; i <= num_arestas; i++) distancia[i] = INFINITO; // definimos todas as distâncias como infinito, exceto a de S = 1.
	distancia[1] = 0;                                  // Assim, garantimos que o primeiro vértice selecionado será o próprio 1.
	
	priority_queue< par, vector<par>, greater<par> > fila; // Criamos uma fila de prioridade onde o menor fica no topo.
	fila.push( par(distancia[1], 1) );                     // Como se pode ver, colocamos o primeiro elemento como seja a distância do
	                                                       // vértice a Árvore Geradora Mínima e o segundo como sendo o próprio vértice
	
	while(true){ // rodar "infinitamente"
		
		int davez = -1;
		
		// selecionamos o vértice mais próximo
		while(!fila.empty()){
			
			int atual = fila.top().second;
			fila.pop();
			
			if(!processado[atual]){ // podemos usar esse vértice porque ele ainda não foi processado
				davez = atual;
				break;
			}
			
			// se não, continuamos procurando
		}
		
		if(davez == -1) break; // se não achou ninguém, é o fim do algoritmo
		
		processado[davez] = true; // marcamos para não voltar para este vértice
		
		// agora, tentamos atualizar as distâncias
		for(int i = 0;i < (int)vizinhos[davez].size();i++){
			
			int dist  = vizinhos[davez][i].first;
			int atual = vizinhos[davez][i].second;
			
			// A nova possível distância é dist.
			// Comparamos isso com distancia[atual].
			// Porém, é importante checar se o vértice atual não foi processado ainda
			
			if( distancia[atual] > dist && !processado[atual]){  // vemos que vale a pena usar o vértice davez
				distancia[atual] = dist;                         // atualizamos a distância
				fila.push( par(distancia[atual], atual) );       // inserimos na fila de prioridade
			}
		}
	}
	
	int custo_arvore = 0;
	for(int i = 1;i <= tam_matriz;i++) custo_arvore += distancia[i];
    
    cout << "Custo: " << custo_arvore << endl;

    return 0;
}
