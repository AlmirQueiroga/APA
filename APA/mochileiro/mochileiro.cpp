#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#define infinito std::numeric_limits<int>::max()

using namespace std;


int cost=0;
int cidades[999]; //cidades que foram visitadas


int least(int c, std::vector<std::vector<int>> ary, int n)
{
    int i,nc=999;
    int min=999,kmin;
 
    for(i=0;i < n;i++)
    {
        if((ary[c][i]!=0) && (cidades[i]==0))
            if(ary[c][i]+ary[i][c] < min)
            {
                min=ary[i][0]+ary[c][i];
                kmin=ary[c][i];
                nc=i;
            }
    }
 
    if(min!=999)
        cost+=kmin;
 
    return nc;
}

void mincost(int city, std::vector<std::vector<int>> ary, int size){
    int i,ncity;
 
    cidades[city]=1;
 
    cout<<city<<"--->";
    ncity=least(city, ary, size);
 
    if(ncity==999)
    {
        ncity=0;
        cout<<ncity;
        cost+=ary[city][ncity];
 
        return;
    }
 
    mincost(ncity, ary, size);
}


int main() {
  std::ifstream file("instancias/pcv04.txt");
  unsigned size;
  file >> size; 


  if (!file) {
    printf("arquivo não encontrado");
  }

  std::vector<int> matrix;
  matrix.reserve(size*size);
  std::vector<std::vector<int>> adj;

  while (true) {
    double value;
    if (!(file >> value)) {
      break;
    }
    matrix.push_back(value);
  }

  if (matrix.size() != size*size) {
    printf("erro durante leitura");
  }
  
  printf("tamanho = %d \n", size);

  printf("matrix = \n");


  /*int cout = 0;
  for(int i = 0; i < size*size; i++){
    //for(int j = 0; j < size; j++){
    printf("%d\t", matrix[i]);
    cout++;
    if(cout == size){
      printf("\n");
      cout = 0;
      }
    for(int j = 0; j < size; j++){
      for(int k = 0; k < size; k++){
        adj[i][j] = matrix[i];
      }
    }
    }*/
  adj.resize(size, std::vector<int>(size, 0));
  int k = 0;
  for(int i = 0; i < size; i ++){
    for(int j = 0; j < size; j++){
      adj[i][j] = matrix[k];
      k++;
      if(k > size*size){
        break;
      }
    }
  }
  int cout = 0;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      printf("%d\t", adj[i][j]);
      cout++;
      if(cout == size){
      printf("\n");
      cout = 0;
      }
    }
  }
    printf("caminho =\t");
   mincost(0, adj, size);
   printf("\t");
}
