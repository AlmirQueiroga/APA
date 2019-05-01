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
void construir(std::vector<pair<int, int>> p[], std::vector<pair<int, int>> p_cont[], int size, vector<int> &caminho){
    caminho.clear();
    std::vector<pair<int, int>>* paux = p;

    srand((int)time(0));

    int vertice = rand()%size;
    caminho.push_back(vertice);

    while(1){
        vector <int> LCR;

        sort(paux[vertice].begin(), paux[vertice].begin() + size);

        for(int i = 0; i < paux[vertice].size(); i++){
            if(p[vertice][i].first != 0 && !estaContido(p[vertice][i].second, caminho)){
                LCR.push_back(p[vertice][i].second);
            }
        }

        srand((int)time(0));
        vertice = LCR[rand()%(LCR.size())];
        caminho.push_back(vertice);

        if(caminho.size() == size)
            break;
    }

    //cout << "até aqui td bem" << endl;


    cout << calcularValorCaminho(p_cont, caminho, size) << endl;

    for(int i = 0; i < caminho.size(); i++)
        cout << caminho[i] << " ";
    cout << endl;

    cout << "Custo Final: " << calcularValorCaminho(paux, vnd(p_cont, caminho, size), size) << endl;
}

/*void GRASP(vector<pair<int, int>> p[], vector<pair<int, int>> paux[], int size, vector<int> &caminho, int GraspMax, int alfa){
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
    cout << "---------------------------------------\nCaminho final:" << endl;
    for(int j = 0; j < caminho.size(); j++){
        cout << caminho[j] << " ";
    }
    cout << endl;
    cout << "---------------------------------------\nCusto final:" << endl;
    cout << calcularValorCaminho(paux, caminho, size) << endl;
}*/

//leitura do arquivo e chamada de funçoes
int main(){
    //string instancia;
    //float alfa;
    //int GraspMax;

    /*cout << "digite o nome da instancia" << endl;
    cin >> instancia;
    instancia = "instancias/" + instancia + ".txt";*/
   /* cout << "digite o alfa" << endl;
    cin >> alfa;
    cout << "digite o numero de iteracoes" << endl;
    cin >> GraspMax;*/

   // instancia = "instancias/instancias_teste" + instancia + ".txt";
    //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/instancias_teste/bayg29.txt", "r");

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    int qLines = 0;
    int aux = 0;
    int size;
    char line[99999];
    char *token;
z
    size = atoi(line);

    std::vector<pair<int, int>> p[size];

    fgets(line, 99999, fp);

    while(1){
        int  i = qLines;
        fgets(line, 99999, fp);


        int index = 0;

        token = strtok(line, "A");
        while(token!=NULL){
            p[qLines].push_back(make_pair(atoi(token), index));
            token = strtok(NULL, " ");
            index++;
        }
        qLines++;


        index = 0;

        token = strtok(line, " ");
        while(token!=NULL){
            p[qLines].push_back(make_pair(atoi(token), index));
            token = strtok(NULL, " ");
            index++;
        }
        qLines++;

/*
        cout << p[0][0].first << endl;
        cout << p[0][1].first << endl;
        cout << p[0][2].first << endl;
        cout << p[0][3].first << endl;
        cout << p[0][4].first << endl;
        cout << p[0][5].first << endl;
        cout << p[0][6].first << endl;
        cout << p[0][7].first << endl;
        cout << p[0][8].first << endl;
        cout << p[0][9].first << endl;
        cout << p[0][10].first << endl;
        cout << p[0][11].first << endl;
*/

         if (feof(fp))
            break;
    }

    fclose(fp);//fim da leitura

    std::vector<pair<int, int>> p_cont[size] = p;
    vector<int> caminho;

    cout << "teste" << endl;

    construir(p, p_cont, size, caminho);



    //GRASP(p, paux, size, caminho, GraspMax, alfa);

    return 0;
}
