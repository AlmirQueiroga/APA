#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


vector<int> ContrucaoInit(vector<vector<int>> matrix, int size, int Init){

	int cidades[size] = {};
	vector<int> path;
	path.push_back(Init);

	cidades[Init] = 1;


	for(int i = 0; i < size; i++){
		int Length = std::numeric_limits<int>::max();
		int Index = 0;
		for(int j = 0; j < size; j++){
			if(!cidades[j] && Length > matrix[i][j]){
				Index = j;
				Length = matrix[i][j];
			}
		}

		path.push_back(Index);
		cidades[Index] = 1;
	
	}
	path.push_back(Init);
	


	return path;
}



int make_halmitonian(vector<vector<int>> matrix, vector<int> path, int size){

	 int soma = 0;

    for(int i = 0, j = 1; j < size; i++, j++){
        soma += matrix[path[i]][path[j]];
    }

    soma += matrix[path[0]][path[size - 1]];

return soma;

}


/*void Rand(){

	int rand = (float) rand()/(float)RAND_MAX;
	std::vector<int> solut;

	solut.push_back((int)(rand()%size));

	while(solut.size() != size){

	}



}*/

vector<int> SwapVizinhanca(vector<vector<int>> matrix, int size, vector<int> path){

	vector<int> temp = path;

	int PLength = make_halmitonian(matrix, path, size);
	int TempLength;

	for(int i = 1; i < size; i++){

		temp = path;

		for(int j = i +1; j< size; j++){
			int aux = temp[i];
			temp[i] = temp[j];
			temp[j] = aux;

			TempLength = make_halmitonian(matrix, temp, size);

			if(TempLength < PLength){
				PLength = TempLength;
				path = temp;
				TempLength = make_halmitonian(matrix, path, size);
			}
		}
	}

	return path;

}


std::vector<int> Construtor(vector<vector<int>> matrix, int size, vector<int> path){

	vector<int> nPath = path;
	vector<int> aux;


	int Length = make_halmitonian(matrix, path, size);
	int nLength;

	for(int i = 1; i < size; i++){
		for(int j = i + 1; j < size; j++){
			aux = nPath;

			for(int k = i; k <= j; k++){
				for(int f = j; k <= j; f--){
					nPath[k] = aux[f];
				}
			}


			nLength = make_halmitonian(matrix, nPath, size);
			if(nLength < Length){
				Length = nLength;
				path = nPath;
			}
		}
	}

	return path;
}

std::vector<int> VND(vector<vector<int>> matrix, vector<int> path, int size){
    
int numStrucs = 2;
int i = 1;

int Length;
int nLength;

vector<int> nPath = path;
	
	while( i <= numStrucs){
		if(i ==1){
			nPath = SwapVizinhanca(matrix, size, path);
			nLength = make_halmitonian(matrix, nPath, size);
		}else if(i == 2){
			nPath = Construtor(matrix, size, path);
			nLength = make_halmitonian(matrix, nPath, size);
		}
		Length = make_halmitonian(matrix, path, size);
		if(nLength < Length){
			path = nPath;
			i = 1;
		}else{
			i++;
		break;
		}
	}
	


	return path;

}









/*int GRC(vector<vector<int>> matrix, int a, int tamanho){
	vector<int> solucao;
	int decisao;
	solucao.push_back((int)(rand()%tamanho));
	while(solucao.size() != tamanho){
		vector<int> custoRecurso;
		for(int i = 0; i < tamanho; i++){

			int ch;
			for(int i = 0; i < solucao.size();i++)
			if(i == solucao[i]) ch = true;
			 ch =false;

			 int pb = make_halmitonian(matrix, solucao, tamanho);

			if(!ch)
				custoRecurso.push_back(pb);
		}

		vector<int> LCR;
		int Fcustominimo = std::numeric_limits<int>::max();
			int Fcustomaximo = 0;
			int L;

		for(int i = 0; i < tamanho; i++){
			vector<int> m = ContrucaoInit(matrix, tamanho, i);
			L = make_halmitonian(matrix, m, tamanho);
			
			if(Fcustominimo < L){
				Fcustominimo = L;
			}
			if(Fcustomaximo > L){
				Fcustomaximo = L;
			}
		}

		decisao = Fcustominimo + a*(Fcustomaximo - Fcustominimo);

		for(int i = 0; i < custoRecurso.size(); i++){
			if(custoRecurso[i] <= decisao)
				LCR.push_back(custoRecurso[i]);
		}
		srand(clock());
		int aleatorio = rand() % (LCR.size());

		solucao.push_back(LCR[aleatorio]);
	}
	solucao.push_back(solucao[0]);
	
	return decisao;

}*/

void GRASP(vector<vector<int>> matrix, int size, std::vector<int> path, int MaxInt, int alfa, int Init){





	vector<vector<int>> nMatrix(size, vector <int>(size));
	nMatrix = matrix;
	vector<int> nPath = path;
	int Length = make_halmitonian(nMatrix, path, size);
	int nLength;

	for (int i = 0; i < MaxInt; i++){
		
		path = ContrucaoInit(matrix, size, Init);
		VND(nMatrix, path, size);
		//alfa = GRC(matrix, alfa, size);
		nLength = make_halmitonian(nMatrix, path, size);

		if(nLength < Length){
			path = nPath;
			Length = nLength;
		}
	}

	path = nPath;


	//printf("Caminho:\n");

	//for (int i = 0; i < size; i++){
	//	cout<< path[i]<< " ---->" << endl;
	//}


	printf("GRASP Length:\n");

	cout << make_halmitonian(nMatrix, path, size)<< endl;
	/*int custo_solucao = std::numeric_limits<int>::max();
	int total;

	vector <int> solucao;
	vector <int> melhor_solucao;

	for(int i = 0; i < MaxInt; i++){
		//solucao = GRC( matrix, (float) rand() / (float) RAND_MAX, size);
		solucao = VND(matrix, solucao, size);
		total = make_halmitonian(matrix, solucao, size);
		if(total < custo_solucao){
			custo_solucao = total;
			melhor_solucao = solucao;
		}
	}

cout << "Custo GRASP: " << custo_solucao << endl;*/
}



int main(){ 
	int size = 0;
	//Leitura do arquivo
	
	ifstream grafo_matrix("brasil58.txt", ios::in);

	//valores otimos:
	//brasil58 = 25395
	//gr120 = 6942
	//bturma14 = 3323
	//gr96 = 55209
	
	grafo_matrix >> size; 


	//int**vec = a;	
	vector <vector <int>> matrix (size, vector <int>(size)); 
    // or vec_2d matrix (n, vec_1d(n)); with your typedefs

    for (auto &i: matrix)
        for (auto &j: i)
            grafo_matrix >> j;

	//fim letura do arquivo
	;

	int InterGrasp = 10;
	float alfa = 0;
	int Init = 0;
	vector<int> InitPath = ContrucaoInit(matrix, size, Init);
	vector<int> FPath;

	int k = make_halmitonian(matrix, InitPath, size);
//	for(int i = 0; i < size; i++){
//		cout<< InitPath[i] << endl;
//	}
	//GRASP(matrix, size, InitPath, InterGrasp, alfa, Init);
	FPath = VND(matrix, InitPath, size); //Busca Local

	printf("VND Length:\n");

	cout << make_halmitonian(matrix, FPath, size) << endl;

	return 0;
}
