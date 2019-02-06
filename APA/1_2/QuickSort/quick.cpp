#include <iostream>
#include <vector>
using namespace std;

void PrintVector(vector <int> vector){
    vector<int>::iterator v = vector.begin();

    while( v != vector.end()) {
        cout << *v << ", ";
        v++;
    }
    cout << endl << endl;
}

void Swap(vector <int>* a, int i, int j){
    int aux = (*a)[i];
    (*a)[i] = (*a)[j];
    (*a)[j] = aux;
}

int Partition(vector <int>* vector, int l, int r){
    int i = l - 1, j, p = (*vector)[r];

    for(j = l; j < r; j++){
        if((*vector)[j] <= p){
            i++;
            Swap(vector, i, j);
        }
    }
    Swap(vector, i+1, r);
    PrintVector(*vector);

    return i + 1;
}

void QuickSort(vector <int>* vector, int l, int r){
    if (l < r){
        int p = Partition(vector, l, r);
        QuickSort(vector, l, p -1);
        QuickSort(vector, p+1, r);
    }
}

int main(){
    vector <int> v {8,7,6,5,4,3,2,1,5,2,3,51,7456,5};

    QuickSort(&v, 0, (v.size() - 1));
    PrintVector(v);

    return 0;
}
