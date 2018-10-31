#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>

using namespace std;

#ifndef TSP_H
#define TSP_H

class TSP{
private:

	struct City{
		int x;
		int y;
	};

	string iFile;
	string oFile;

	// Lista de odds
	vector<int>odds;

	//matrix minima odds
	int **cost;

	//lista de adjacencia
	vector<int> *adjList;

	void findOdds();


public:
	// Numero de cidades
	int n;

	//path
	int **path_vals;

	//comprimento minimo total
	int pathLength;
	// novo comprimento de vizinhança
	int nLength; 

	//euler circuit
	vector<int> circuit;
	//novo circuito de euler
	vector<int> nCircuit;

	vector<City> cities;

	int **graph;

  vector<int>* adjlist;

	// Construtor
	TSP(string in, string out);

	// Destrutor
	~TSP();

	int get_distance(struct City c1, struct City c2);

	//combinação de odds
	void perfectMatching();

	//volta euler
	void euler_tour(int start, vector<int> &path);

	//caminho hamiltoniano
	void make_hamiltonian(vector<int> &path, int &pathCost);

	// Prim
	void findMST();

	int getMinIndex(int key[], bool mst[]);

	void printResult();
	void printPath();
	void printEuler();
	void printAdjList();
	void printCities();

	int get_size(){return n;};

	void fillMatrix();

	int findBestPath(int start);

	void swapVizinhanca(vector<int> &path, vector<int> &npath, int nLength);

	int Construcao(int tsp);

	//int SimulatedAnnealing(vector <int> &path, vector <int> &fpath, int Length, int fLength);

	int GRASP(int size);

};

#endif
