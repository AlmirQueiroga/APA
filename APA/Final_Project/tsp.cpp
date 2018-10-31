#include "tsp.h"


//Construtor
TSP::TSP(string in, string out){
	iFile = in;
	oFile = out;

	ifstream inStream;
	inStream.open(iFile.c_str(), ios::in);

	if(!inStream){
		cerr << "Can't open input file " << iFile << endl;
		exit(1);
	}
	
	//READ DATA
	int c, x, y;
	int count = 0;
	while(!inStream.eof()){
		inStream >> c >> x >> y;
		count++;
		struct City newCity = {x,y};
		cities.push_back(newCity);
	}
	count--;
	//cidades criadas
	inStream.close();

	//aplica no grafo
	n = count;
	graph = new int*[n];
	for(int i = 0; i < n; i++){
		graph[i] = new int[n];
		for(int j = 0; j < n; j++){
			graph[i][j] = 0;
		}
	}

	cost = new int*[n];
	for(int i = 0; i < n; i++){
		cost[i] = new int[n];
	}

	path_vals = new int*[n];
	for(int i = 0; i < n; i++){
		path_vals[i] = new int[n];
	}

	adjlist = new vector<int>[n];
	for(int i = 0; i < cities.size(); i++){
		struct City cur = cities[i];
	}
}

//Destructor
TSP::~TSP(){
	for(int i = 0; i < n; i++){
		delete [] graph[i];
		delete [] cost[i];
		delete [] path_vals[i];
	}
	delete [] path_vals;
	delete [] graph;
	delete [] cost;
	delete [] adjlist;
}



void TSP::fillMatrix(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			graph[i][j] = graph[j][i] = floor((float)(sqrt(pow((float)(cities[i].x - cities[j].x),2)) + pow((float)(cities[i].y - cities[j].y),2) + .5));
			//(cities[i],cities[j]);
		}
	}
}


// findMST vai encontrar uma árvore minima usando algoritmo de prim

void TSP::findMST() {

  int key[n];
  bool included[n];
  int parent[n];

  for (int i = 0; i < n; i++) {

    // key para infinito para enquandrar as distancias
    key[i] = std::numeric_limits<int>::max();

    // setando nao colocadas na MST
    included[i] = false;

  }

  // no inicial n tem pai nem chave
  key[0] = 0;
  parent[0] = -1;

  for (int i = 0; i < n - 1; i++) {

    // encontra vertice com a menor distancia não encontrado na arvore
    int k = getMinIndex(key, included);

    // incluso na mst
    included[k] = true;

    // examina cada vertice adjacente ao vertice adicionado recentemente
    for (int j = 0; j < n; j++) {

      // se o no existe, não fi examinado e apresenta um caminho menor do que o apresentado no
    	// grafo, realiza modificação
      if (graph[k][j] && included[j] == false && graph[k][j] < key[j]) {

          // atualiza pai
          parent[j] = k;

          // atualiza chave
          key[j] = graph[k][j];

      }
    }

  }

  // constroi a arvore pelas adjacencias encontradas 
  for (int i = 0; i < n; i++) {

    int j = parent[i];

    if (j != -1) {

      adjlist[i].push_back(j);
      adjlist[j].push_back(i);

    }

  }

}


//encontra vertice mais próximo não incluso
int TSP::getMinIndex(int key[], bool mst[]) {

  int min = std::numeric_limits<int>::max();
  int min_index;

  // em cada vertice
  for (int i = 0; i < n; i++) {

    // se o vertice n foi visitado e apresenta chave menos custosa do que o vertice anterior
    if (mst[i] == false && key[i] < min) {

      //troca valores
      min = key[i];
      min_index = i;

    }

  }

  return min_index;

}



void TSP::findOdds() { // faz subgrafo com os vertices faltosos

  for (int i = 0; i < n; i++) {

    if ((adjlist[i].size() % 2) != 0) {

      //adiciona ao subgrafo
      odds.push_back(i);

    }

  }

}


void TSP::perfectMatching() {

	// encontra a melhor combinação para os vertices no subgrafo utilizando um algoritmo guloso

  int closest, length; //int d;
  std::vector<int>::iterator tmp, first;

  // return odds
  findOdds();

  while (!odds.empty()) {
    first = odds.begin();
    vector<int>::iterator it = odds.begin() + 1;
    vector<int>::iterator end = odds.end();
    length = std::numeric_limits<int>::max();
    for (; it != end; ++it) {
      // se esse no está mais próximo do que o atual, atualiza closest e length
      if (graph[*first][*it] < length) {
        length = graph[*first][*it];
        closest = *it;
        tmp = it;
      }
    }
    adjlist[*first].push_back(closest);
    adjlist[closest].push_back(*first);
    odds.erase(tmp);
    odds.erase(first);
    //lista de odds encerrada
  }
}


//find an euler circuit
void TSP::euler_tour(int start, vector<int> &path){
	//Create copy of adj. list
	vector<int> *tempList = new vector<int>[n];
	for(int i = 0; i < n; i++){
		tempList[i].resize(adjlist[i].size());
		tempList[i] = adjlist[i];
	}

	stack<int> stack;
	int pos = start;
	path.push_back(start);
	while(!stack.empty() || tempList[pos].size() > 0){
		//Current node has no neighbors
		if(tempList[pos].empty()){
			//add to circuit
			path.push_back(pos);
			//remove last vertex from stack and set it to current
			pos = stack.top();
			stack.pop();
		}
		//If current node has neighbors
		else{
			//Add vertex to stack
			stack.push(pos);
			//Take a neighbor
			int neighbor = tempList[pos].back();
			//Remove edge between neighbor and current vertex
			tempList[pos].pop_back();
			for(int i = 0; i < tempList[neighbor].size(); i++){
				if(tempList[neighbor][i] == pos){
					tempList[neighbor].erase(tempList[neighbor].begin()+i);
				}
			}
			//Set neighbor as current vertex
			pos = neighbor;
		}
	}
	path.push_back(pos);
}


//Make euler tour Hamiltonian
void TSP::make_hamiltonian(vector<int> &path, int &pathCost){
	//remove visited nodes from Euler tour
	bool visited[n];
	for(int i = 0; i < n; i++){
		visited[i] = 0;
	}
	
	pathCost = 0;

	int root = path.front();
	vector<int>::iterator cur = path.begin();
	vector<int>::iterator iter = path.begin()+1;
	visited[root] = 1;

	//iterate through circuit
	while(iter != path.end()){
		if(!visited[*iter]){
			pathCost += graph[*cur][*iter];
			cur = iter;
			visited[*cur] = 1;
			iter = cur + 1;
		}	
		else{
			iter = path.erase(iter);
		}
	}
	
	//Add distance to root
	pathCost += graph[*cur][*iter];
}


	// retorna o melhor caminho hamiltoniano
int TSP::findBestPath(int start){
	vector<int> path;
	euler_tour(start, path);

	int length;
	make_hamiltonian(path, length);

	return length;
}


void TSP::printResult(){
  ofstream outputStream;
  outputStream.open(oFile.c_str(), ios::out);
  outputStream << pathLength << endl;
  for (vector<int>::iterator it = circuit.begin(); it != circuit.end(); ++it) {
    outputStream << *it << endl;
  }
  outputStream.close();
};

void TSP::printPath(){
  cout << endl;
  for (vector<int>::iterator it = circuit.begin(); it != circuit.end()-1; ++it) {
    cout << *it << " to " << *(it+1) << endl;
    //cout << graph[*it][*(it+1)] << endl;
  }
  cout << *(circuit.end()-1) << " to " << circuit.front();
  cout << "\nLength: " << pathLength << endl << endl;
};

void TSP::swapVizinhanca(vector<int> &path, vector<int> &npath, int nLength){
	//Create copy of adj. list

	for(int i = 0; i < circuit.size(); i++)
  srand (time(NULL));
	int Length = pathLength; //comprimrnto com best index
  vector<int> caminhomenor;
  int menor;
  int n1;
  int index;
  //int n2 = start; //Best Index
  int i = 0;

  // calcula novo nó aleatório
  while(i < 999){
    n1 = rand() % circuit.size();
    i++;
    if(n1 == 0)
        n1++;
	}

	for(i =0; i < path.size(); i++){
		if(path[i] == n1){
			index = i;
		}
	}

/*
  cout << endl;
  for (vector<int>::iterator it = path.begin(); it != path.end()-1; ++it) {
    cout << *it << " to " << *(it+1) << endl;
    //cout << graph[*it][*(it+1)] << endl;
  }
  cout << *(path.end()-1) << " to " << path.front();
  cout << "\nLength: " << nLength << endl << endl;*/
	for(vector<int>::iterator it = path.begin(); it != path.end()-1; ++it){
		npath.push_back(*it);
	}

	swap(npath[0], npath[index]);

	bool visited[n];
	for(int i = 0; i < n; i++){
		visited[i] = 0;
	}
	
	nLength = 0;

	int root = npath.front();
	vector<int>::iterator cur = npath.begin();
	vector<int>::iterator iter = npath.begin()+1;
	visited[root] = 1;

	//iterate through circuit
	while(iter != npath.end()){
		if(!visited[*iter]){
			nLength += graph[*cur][*iter];
			cur = iter;
			visited[*cur] = 1;
			iter = cur + 1;
		}	
		else{
			iter = npath.erase(iter);
		}
	}
	nLength += graph[*cur][*iter];

	  cout << endl;
  for (vector<int>::iterator aux = npath.begin(); aux != npath.end()-1; ++aux) {
    cout << *aux << " to " << *(aux+1) << endl;
    //cout << graph[*aux][*(aux+1)] << endl;
  }
  cout << *(npath.end()-1) << " to " << npath.front();

	cout << "\nnó original:" << path[0] << endl;

	cout << "\ncomprimento original:" << Length << endl;

	cout << "\nnovo nó:" << n1 << endl;

	cout << "\nnovo comprimento:" << nLength << endl;

};

int TSP::Construcao(int size){
 int best = std::numeric_limits<int>::max();
	int bestIndex;
	for (long t = 0; t < size; t++) {
		int result = findBestPath(t);

		path_vals[t][0] = t; // determina inicio
		path_vals[t][1] = result; // determina final

		if (path_vals[t][1] < best) {
			bestIndex = path_vals[t][0];
			best = path_vals[t][1];
		}
	}
return bestIndex;
}

/*int TSP::SimulatedAnnealing(vector <int> &path, vector <int> &fpath, int Length, int fLength){

	int auxLength; // s*
	auxLength = Length; // s* <- s
	int ite = 0; // numero de iterações
	int delta;
	bool x;

		while(ite < 10){
			ite++;
			swapVizinhanca(path, fpath, fLength);

			delta = fLength - Length;

			if(delta < 0){
				Length = fLength;
				if(fLength < auxLength){
					auxLength = fLength;
				}
			}else{
			}
		}
		ite = 0;

	return Length;

};*/


int TSP::GRASP(int size){

	int FinalIndex, GlobalIndex;
	int f = std::numeric_limits<int>::max();
	bool a;
	for(int i = 1; i < size; i ++){


		int LocalIndex = Construcao(size);

		int LocalResult = findBestPath(LocalIndex);

		if(LocalResult < f){
			GlobalIndex = LocalIndex;
			f = LocalResult; 
		}
	}

FinalIndex = GlobalIndex;

return FinalIndex;

}
