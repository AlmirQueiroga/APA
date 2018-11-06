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



int calc(vector<vector<int>> matrix, vector<int> path, int size){

	 int soma = 0;

    for(int i = 0, j = 1; j < size; i++, j++){
        soma += matrix[path[i]][path[j]];
    }

    soma += matrix[path[0]][path[size - 1]];

return soma;

}



vector<int> SwapVizinhanca(vector<vector<int>> matrix, int size, vector<int> path){

	vector<int> temp = path;

	int PLength = calc(matrix, path, size);
	int TempLength;

	for(int i = 1; i < size; i++){

		temp = path; ///////////// voltar ao estado inicial

		for(int j = i +1; j< size; j++){
			int aux = temp[i];
			temp[i] = temp[j];
			temp[j] = aux;

			TempLength = calc(matrix, temp, size);

			if(TempLength < PLength){
				PLength = TempLength;
				path = temp;
				TempLength = calc(matrix, path, size);
			}
		}
	}



	return path;

}


std::vector<int> opt(vector<vector<int>> matrix, int size, vector<int> path){

	vector<int> nPath = path;
	vector<int> aux;


	int Length = calc(matrix, path, size);
	int nLength;

	for(int i = 1; i < size; i++){
		for(int j = i + 1; j < size; j++){
			aux = nPath;

			for(int k = i; k <= j; k++){
				for(int f = j; k <= j; f--){
					nPath[k] = aux[f];
				}
			}


			nLength = calc(matrix, nPath, size);
			if(nLength < Length){
				Length = nLength;
				path = nPath;
			}
		}
	}

	return path;
}

vector<int> VND(vector<vector<int>> matrix, vector<int> path, int size){
    
int numStrucs = 2;
int i = 1;

int Length;
int nLength;

vector<int> nPath = path;
	
	while( i <= numStrucs){
		if(i ==1){
			nPath = SwapVizinhanca(matrix, size, path);
			nLength = calc(matrix, nPath, size);
		}else if(i == 2){
			nPath = opt(matrix, size, path);
			nLength = calc(matrix, nPath, size);
		}
		Length = calc(matrix, path, size);
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





int main(){ 
	int size = 0;
	//Leitura do arquivo
	
	ifstream grafo_matrix("si535.txt", ios::in);

	//valores otimos:
	//brasil58 = 25395
	//gr120 = 6942
	//bturma14 = 3323
	//gr96 = 55209
	//bays29 = 2020
	//gr17 = 2085
	//si535 = 48450
	//gr229 = 134602
	
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

	int k = calc(matrix, InitPath, size);
//	for(int i = 0; i < size; i++){
//		cout<< InitPath[i] << endl;
//	}
	//GRASP(matrix, size, InitPath, InterGrasp, alfa, Init);
	FPath = VND(matrix, InitPath, size); //Busca Local

	printf("VND Length:\n");

	cout << calc(matrix, FPath, size) << endl;

	return 0;
}
