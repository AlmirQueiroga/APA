#include <fstream>
#include <vector>

int main() {
  std::ifstream file("instancias/pcv04.txt");
  unsigned size;
  file >> size; 

  if (!file) {
    printf("arquivo não encontrado")
  }

  std::vector<int> matrix;
  matrix.reserve(size*size);

  while (true) {
    double value;
    if (!(file >> value)) {
      break;
    }
    matrix.push_back(value);
  }

  if (matrix.size() != size*size) {
    printf("erro durante leitura")
  }
  

  for(int i = 0; i < size){
  printf("%s\n", matrix[i]);
  }
}
