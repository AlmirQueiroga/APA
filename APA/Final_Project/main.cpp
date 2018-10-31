#include <iostream>
#include <climits>
#include "tsp.h"
//#include "twoOpt.h"

int main(int argc, char** argv) {
	if(argc < 2){
		exit(-1);
	}

	//le arquivo
	string input, output;
	input = output = argv[1];
	output.append("bays76.tour");

	// organiza o tsp, determina x, y e n, lista de cidades e grafo
	TSP tsp(input, output);
	int tsp_size = tsp.get_size(); // tsp_size = n

	// cria matriz de adjacencia
	tsp.fillMatrix();

	//pela matriz encontra a arvore minima usando Prim
	tsp.findMST();

	// para vertices que estão fora do ciclo, encontra um subgrafo
	tsp.perfectMatching();

	/*// loop em cada vertice encontrando caminho minimo encontrando o index de inicio
	int best = INT_MAX;
	int bestIndex;
	for (long t = 0; t < tsp_size; t++) {
		int result = tsp.findBestPath(t);

		tsp.path_vals[t][0] = t; // determina inicio
		tsp.path_vals[t][1] = result; // determina final

		if (tsp.path_vals[t][1] < best) {
			bestIndex = tsp.path_vals[t][0];
			best = tsp.path_vals[t][1];
		}
	} */

	clock_t tStart = clock();
	vector<int> CaminhoAt = tsp.VND(tsp.circuit, tsp_size);
	int newlength;
	tsp.make_hamiltonian(CaminhoAt, newlength);
	printf("%d\n", newlength);
	printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	clock_t tStart2 = clock();
	int bestIndex = tsp.GRASP(tsp_size);
	tsp.CalcPath(bestIndex, tsp.circuit, tsp.pathLength);
	printf("%d\n", tsp.pathLength);
	printf("Time taken: %.2fs\n", (double)(clock() - tStart2)/CLOCKS_PER_SEC);

	//cria o caminho com o melhor ciclo
	//tsp.euler_tour(20 ,tsp.circuit);
	//tsp.make_hamiltonian(tsp.circuit,tsp.pathLength);

	//printf("TESTEEEEEEEEEEEEE %d\n", tsp.pathLength);


	// Print
	//tsp.printPath();
	//tsp.printResult();

	//tsp.swapVizinhanca(tsp.tempList, tsp. nCircuit, tsp.nLength);

}
