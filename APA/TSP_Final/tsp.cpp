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
#include <time.h>

using namespace std;

//Calcula o valor do caminho presente no ciclo presente em resultados
int calcularValorCaminho(std::vector<pair<int, int>> p[], vector<int> caminho, int size){
    int soma = 0;

    for(int i = 0, j = 1; j < caminho.size(); i++, j++){
        soma += p[caminho[i]][caminho[j]].first;
    }

    soma += p[caminho[0]][caminho[size - 1]].first;

    return soma;
}

//movimentaçao de vizinhança utilizando swap
int swapVizinhanca(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int mudou = 0;

    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor = caminho;
    int menor = calcularValorCaminho(p, caminho, size);

    for(int i = 0; i < caminho.size(); i++){
    for(int j = i + 1; j < caminho.size(); j++){
        caminhoaux = caminho;
        swap(caminhoaux[i], caminhoaux[j]);

        if(calcularValorCaminho(p, caminhoaux, size) < menor){
            menor = calcularValorCaminho(p, caminhoaux, size);
            caminhomenor = caminhoaux;
            mudou++;
        }
    }
    }

    caminho = caminhomenor;
    return mudou;
    }

//movimentaçao de vizinhança utilizando 2-opt
int reInsertion(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int mudou = 0;

    vector<int> caminhoaux = caminho;
    vector<int> caminhomenor = caminho;
    int menor = calcularValorCaminho(p, caminho, size);

    int n1;
    int n2;

    for(int i = 0; i < caminho.size(); i++){
        for(int j = 0; j < caminho.size(); j++){
            n1 = i;
            n2 = j;

            caminhoaux = caminho;

            if(n1 != n2){
                if(n1 < n2){
                    while(n1+1 != n2){
                        swap(caminhoaux[n1], caminhoaux[n1 +1]);
                        n1++;
                    }
                }else{
                    while(n2+1 != n1){
                    swap(caminhoaux[n2], caminhoaux[n2 +1]);
                    n2++;   
                    }
                }
            }

            if(calcularValorCaminho(p, caminhoaux, size) < menor){
                menor = calcularValorCaminho(p, caminhoaux, size);
                caminhomenor = caminhoaux;
                mudou++;
            }
        }
    }

    caminho = caminhomenor;
    return mudou;
}

vector<int> vnd(std::vector<pair<int, int>> p[], vector<int> &caminho, int size){
    int select = 0;
    vector<int> caminhoaux = caminho;

    while(select < 2){
        switch(select){
            case 0:
                if(swapVizinhanca(p, caminho, size) != 0){
                        select = 0;
                }else{
                    select++;
                }
                break;
            case 1:
                if(reInsertion(p, caminho, size) != 0){
                        select = 0;
                }else{
                    select++;
                }
                break;
            default:
                break;  
        }
    }        
    return caminho;
}

//verifica se um dado vertice esta contido na atual soluçao
int estaContido(int a, vector<int> &caminho){
    for(int i = 0; i < caminho.size(); i++){
        if(a == caminho[i])
            return 1;
    }
    return 0;
}

//Metodo do vizinho mais proximo
void construir(std::vector<pair<int, int>> p[], int size, vector<int> &caminho, int alfa){
    caminho.clear();
    std::vector<pair<int, int>>* paux = p;

    srand((int)time(0));

    int vertice = rand()%size;
    caminho.push_back(vertice);

    while(1){
        vector <int> LCR;

        sort(paux[vertice].begin(), paux[vertice].begin() + size);

        for(int i = 0; i < paux[vertice].size(); i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second, caminho) && LCR.size() < (alfa * size)){
                LCR.push_back(p[vertice][i].second);
            }
        }

        srand((int)time(0));
        vertice = LCR[rand()%(LCR.size())];
        caminho.push_back(vertice);

        if(caminho.size() == size)
            break;
    }
}

void GRASP(vector<pair<int, int>> p[], vector<pair<int, int>> paux[], int size, vector<int> &caminho, int GraspMax, int alfa){
    clock_t c2, c1;
    float tempo;
    c1= clock();
    construir(p, size, caminho, alfa);
    vector<int> caminhomenor = caminho;
    int f = calcularValorCaminho(paux, caminho, size);

    for(int i = 0; GraspMax > i; i++){
        construir(p, size, caminho, alfa);

        vnd(paux, caminho, size);

        if(calcularValorCaminho(paux, caminho, size) < f){
            caminhomenor = caminho;
            f = calcularValorCaminho(paux, caminho, size);
        }
    }
   

    caminho = caminhomenor;
     c2 = clock();
     tempo = (c2- c1)*1000/CLOCKS_PER_SEC;

    cout << "\nCaminho final:" << endl;
    for(int j = 0; j < caminho.size(); j++){
        cout << caminho[j] << " ";
    }
    cout << endl;
    cout << "\nCusto final:" << endl;
    cout << calcularValorCaminho(paux, caminho, size) << endl;
    cout << "tempo =" << tempo << "ms" << endl;
}

int DistanciaEuclidiana(float x1, float x2, float y1, float y2){
    float d = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
    return round(sqrt(d));
}

int main(){

    int escolha;
    float alfa;
    int GraspMax;

    //cout << "Escolha o tipo de leitura:" << endl;
    //cout << "1 - TSP teste \n 2 - TSP Cup" << endl;
    //cin >> escolha;


        cout << "digite o alfa" << endl;
    cin >> alfa; // de preferência mesmo número de iterações
    cout << "digite o numero de iteracoes" << endl;
    cin >> GraspMax;

    //leitura do arquivo
    FILE *fp;

    //if(escolha == 1){
    fp = fopen("instancias/instancias_teste/bayg29.txt", "r");
      // }
    //if(escolha == 2){
    //fp = fopen("instancias/instancias_tsp_cup/tsp1.txt", "r");
    //}

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    int qLines = 0;
    int size;
    int tamanho;
    char line[99999];
    char *token;
    char *tokenS;

    fgets(line, 99999,fp);

    tokenS = strtok(line, " ");
    tamanho = atoi(tokenS);

    int X[tamanho];
    int Y[tamanho];

    size = atoi(line);

    std::vector<pair<int, int>> p[size];


    while(1){

        fgets(line, 99999, fp);

        if (feof(fp))
            break;

        int index = 0;

        token = strtok(line, " ");
        while(token!=NULL){
           
          // cout << "teste" << endl;
           p[qLines].push_back(make_pair(atoi(token), index));
            token = strtok(NULL, " ");
            index++;
        }
        qLines++;
        // cout << "teste2" << endl;
    }


    fclose(fp);//fim da leitura

/*
    std::vector<pair<int, int>> pCUP[size];

    if(escolha == 2){

    for (int n = 0; n < tamanho; n++){
            X[n] = p[n][1].first;
    }
    
     for (int n = 0; n < tamanho; n++){
            Y[n] = p[n][2].first;
    }

    int init = 0;
    for (int i = 0; i < tamanho - 1 ; i++) {
        for (int j = init; j < tamanho ; j++){
            if (i == j){
                pCUP[i][j].first = pCUP[j][j].first = 0;
                continue;
            }
             pCUP[p[0][init].second].push_back(make_pair(DistanciaEuclidiana(X[i], X[j], Y[i], Y[j]), p[0][init].second)); 
        }
        init++;
        }

   }

   std::vector<pair <int, int>> pCUPaux[size] = pCUP;*/
    std::vector<pair <int, int>> paux[size] = p;
    vector<int> caminho;



/*
    for(int n = 0; n < tamanho; n++){
        for(int m = 0; m < tamanho; m++){

            float d = ((X[m] - X[n])*(X[m] - X[n]) + (Y[m] - Y[n])*(Y[m] - Y[n]));

                paux.[].push_back(make_pair(round(sqrt(d)), p[0][m].second))

        }
    }
*/


   GRASP(p, paux, size, caminho, GraspMax, alfa);

    

    return 0;
}
