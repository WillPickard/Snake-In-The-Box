#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <array>
#include <queue>
#include "math.h"

#ifndef DIMENSIONS 
#define DIMENSIONS 7
const int NUM_VERT = pow(2, DIMENSIONS);
int CURRENT_ID = 0;
#endif

#include "worm.h"
#include "vertex.h"
#include "weight.h"

struct Worm;
struct Vertex;

/*
*Cube
*/
typedef struct Cube
{
	
	int dimensions = DIMENSIONS;
	int id = CURRENT_ID++;
	Worm *worm;
	std::array<Vertex *, NUM_VERT> vertices;
	bool valid[NUM_VERT] = {true};	

	std::vector<Vertex *> getChoices(Vertex *v){
		std::vector<Vertex *> neighbors = v->getNeighbors();
		std::vector<Vertex *> choices;
		//prune neighbors to only allow valid ones
		for(int i=0; i<neighbors.size(); i++){
			if(valid[neighbors.at(i)->id]){
				//if it is valid then add it to the choice vector
				choices.push_back(neighbors.at(i));
			}
		}
		return choices;
	};

	/*
	*
	*calculate the weights for a set of choices
	*	depth is how far it will traverse down in making a decision
	*	this function will return an array of ints corresponding with the position of the vertex
	*	each weight will represent the number of available neighbors to that vertex
	*/
	Weights * calculateWeights(std::vector<Vertex *> *choices, int depth){
		Weights *weights = new Weights;
	
		for(int i=0; i<choices->size(); i++){
			weights->addWeight(calculateWeight(choices->at(i)));
		}

		return  weights;
	};

	/**
	*
	*calculate the weight for one vertex
	*/
	Weight * calculateWeight(Vertex *v){
		int weight = 0;
		std::vector<Vertex *> neighbors = v->neighbors;
		
		for(int i=0; i<neighbors.size(); i++){
			if(valid[neighbors.at(i) -> id])
				weight++;
		}
		return new Weight(weight, v);
	};

	//set neighbors of v to false
	void invalidateNeighbors(Vertex *v){
		for(int i=0; i<v->neighbors.size(); i++){
			valid[v->neighbors.at(i)->id] = false;
		}
	}

	void print(){
		for(int i=0; i<vertices.size(); i++){
			vertices.at(i)->print();
		}
	}

	Cube * clone(){
		return new Cube( (*this) );
	}

	~Cube(){
		
		delete  worm;
		
		//delete  &valid;
		
		for(int i=0; i<vertices.size(); i++)
			delete vertices.at(i);

		//delete &vertices;
	}
	

}(Cube);



#endif