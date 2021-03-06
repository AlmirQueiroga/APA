#include <iostream>
#include <utility>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

  
int knapSack( int n, int W, int wt[], int val[]) 
{ 
 
   if (n == 0 || W == 0) 
       return 0; 
 
   if (wt[n-1] > W) 
       return knapSack(n-1, W, wt, val); 
  
   else return  (val[n-1] + knapSack( n-1, W-wt[n-1], wt, val) > knapSack(n-1, W, wt, val))? val[n-1] + knapSack( n-1, W-wt[n-1], wt, val) : knapSack(n-1, W, wt, val); 
} 


int main(){
    //leitura do arquivo
    FILE *fp;
    fp = fopen("instancias/mochila01.txt", "r");

    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }

    int qLines = 0;
    int items;
    char line[999];
    char *token;
    int weight;

    //pega tamanho e capacidade da mochila
    while(1){
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }
        if(qLines == 1)
            break;

        token = strtok(line, " ");

        int k = 0;
        while(token!=NULL){
            if(qLines == 0){
                if(k == 0)
                    items = atoi(token);
                else
                    weight = atoi(token);
            }
            token = strtok(NULL, " ");
            k++;
        }
        qLines++;
    }

    int val[items];
    int wt[items];

    while(1){
        fgets(line, 999, fp);
        if (feof(fp)){
            break;
        }

        token = strtok(line, " ");

        int k = 0;
        while(token!=NULL){
            if(!k)
                wt[qLines - 1] = atoi(token);
            else
                val[qLines - 1] = atoi(token);

            token = strtok(NULL, " ");
            k++;
        }
        qLines++;
    }
    fclose(fp);//fim da leitura

    int x = knapSack(items, weight, wt, val);

    cout << "valor : " << x << endl;

    return 0;
}
