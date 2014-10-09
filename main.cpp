#include "structs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;
string d7 = "Dimension7Table.txt";
string d3 = "d1Table.txt";

string inputFile = d7;

const int D = 7;
const int N_V = pow(2, D);
const int N_E = (2 * pow(D, 2)) - 2*D;
const int N_S = 1000;

Cube *cube = new Cube;
queue<Cube *> MANAGER;
queue<Cube *> TO_DESTROY;
queue<Worm *> WINNERS;

void initCube(ifstream *, Cube *);
void destroy();

int main(int argc, char* argv[]){
	if(argc > 2){
		cout << "Too many args" << endl;
		exit(1);
	}
	if (argc == 2){
		//input file provided 
		inputFile = argv[1];
	}

	//open file
	ifstream adjTable;
	//adjTable.open(inputFile, ios_base::in);

	//cout << "creating cube..." << endl;
	//create environment from file
	//initCube(&adjTable, cube);
	//Worm *worm = cube->worm;

	//cout << "running..." << endl;
	
	//int best = cube-> worm ->run();	
	//printf("path length: %d\n", best);

/**/
	printf(".............................. .....................testing..........................................................\n");
	int num = 0, best = 0, current, nb = 0;
	Worm *bestWorm = new Worm;
	for(int s=0; s<N_S; s++){

		for(int i=0; i<N_E; i++){
			Cube *c1 = new Cube;

			adjTable.open(inputFile, ios_base::in);

			initCube(&adjTable, c1);

			MANAGER.push(c1);
		}
	
		while(!MANAGER.empty()){

			current = MANAGER.front() -> worm -> run(false, false);

			if(current > ( bestWorm -> traversals )){
				bestWorm = MANAGER.front()->worm;
				WINNERS.push(bestWorm);
			}
			else
				TO_DESTROY.push(MANAGER.front());

			MANAGER.pop();	
			
			num++;
		}
		if ( (s) % 100 == 0 ) {
			cout << "SIMULATION " << s << endl;
			cout << "worms executed: " << num << endl;
			cout << "best: " << bestWorm->traversals << endl;
			cout << ".................................................... done ......................................................" << endl;
		}

		//check if time to delete
		if(s % 100 == 0){
			destroy();
		}
	}

	bestWorm -> print(false);
	printf("winners size: %d\n", WINNERS.size());
}

/*
*make the cube, vertices and worm
*/
void initCube(ifstream * adjTable, Cube * cube){
	string line;
	int id, v=pow(2, cube->dimensions);

	//create the currentVertex and put it in the array
	for(int i=0; i<v; i++)
		cube->vertices.at(i) = new Vertex(i);

	//each iteration for the outer while loop represents 1 vertex
	//currentVertex denotes ^that^ vertex's id
	//the actual line will consist of dimensions number of vertices
	//each vertices will be represented by an int denoting its id
	int currentVertex = 0;
	while(getline(*adjTable, line)){
		//the number of dimensions indicates how many vertices there are
		istringstream iss(line);
		for(int i=0; i<cube->dimensions; i++){
			iss >> id; 
			cube->vertices.at(currentVertex)->add(cube->vertices.at(id));
		}
		cube->valid[currentVertex] = true;
		currentVertex++;
	}
	cube->worm = new Worm();
	//create this cubes worm
	cube->worm->init(cube->vertices.at(0), cube);
	adjTable -> close();
};	

//destroy the global TO_DESTROY queue
void destroy(){
	int size;

	size = TO_DESTROY.size();
	for(int i=0; i<size; i++){
		Cube *c = TO_DESTROY.front();
		delete c;
		TO_DESTROY.pop();
	}
}