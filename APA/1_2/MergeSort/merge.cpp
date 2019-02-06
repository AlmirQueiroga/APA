#include <iostream>
#include <vector>
using namespace std;

void PrintVector(vector<int> vector){
    vector<int>::iterator v = vector.begin();

    while( v != vector.end()) {
        cout << *v << ", ";
        v++;
    }
    cout << endl << endl;
}

void Merge(vector <int>* vector, int inicio, int meio, int fim){
    int n1 = meio - inicio + 1, n2 = fim - meio;
    vector <int> esq, dir;

    for(int i = 0; i < n1; i++){
        esq.push_back((*vector)[inicio + i]);
    }
    for(int i = 0; i < n2; i++){
        dir.push_back((*vector)[meio + 1 + i]);
    }

    esq.push_back(INT_MAX);
    dir.push_back(INT_MAX);

    int j = 0, k = 0;

    for(int i= inicio; i <= fim; i++){
        if(esq[j] <= dir[k]){
            (*vector)[i] = esq[j];
            j++;
        }
        else{
            (*vector)[i] = dir[k];
            k++;
        }
    }

    PrintVector(*vector);
}

void MergeSort(vector <int>* vetor, int inicio, int fim){
    int meio;

    if(inicio == fim){
        return;
    }

    meio = (inicio + fim)/2;

    MergeSort(vetor, inicio, meio);
    MergeSort(vetor, meio + 1, fim);
    Merge(vetor, inicio, meio, fim);

    return;
}

int main(){
    vector <int> v {8,7,6,5,4,3,2,1,5,2,3,51,7456,89};

    MergeSort(&v, 0, (v.size() - 1));

    PrintVector(v);
    return 0;
}
