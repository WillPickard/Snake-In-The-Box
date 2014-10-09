#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <array>
#include "math.h"


#include "worm.h"
#include "cube.h"
#include "weight.h"

struct Cube;

/*
*Vertex
*/
typedef struct Vertex
{
	Vertex(int i):
		id(i){};
		
	int id;
	std::vector<Vertex *> neighbors;

	std::vector<Vertex *> getNeighbors(){
		return neighbors;
	}

	void add(Vertex *v){
		this->neighbors.push_back(v);
	}

	void print(){
		printf("vertex %d has neighbors (%d)\n", id, neighbors.size());
		for(int i=0; i<neighbors.size(); i++){
			printf("\t%d (%d)", neighbors.at(i)->id, neighbors.at(i)->neighbors.size());
		}
		printf("\n");
	}

	~Vertex(){
	
	}
}(Vertex);

#endif