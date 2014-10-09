#ifndef WORM_H
#define WORM_H

#include <vector>
#include <array>
#include "math.h"
#include <queue>

//remove this when actually doing it:
#include <stdio.h>

#include "cube.h"
#include "vertex.h"
#include "weight.h"


struct Cube;
struct Vertex;


std::queue<Cube *> CUBES;


/*
*Worm
*/
typedef struct Worm
{
	bool running;

	int traversals = 0;

	std::vector<Vertex *> path;
	Vertex *next;
	Vertex *current;
	Vertex *prev;
	Cube *cube;

	void init(Vertex *start, Cube *c){
		CUBES.push(c);

		current = start;
		this->cube = c;
		this->path.push_back(current);
		this->start();
	}

	void start(){
		running = true;
	};

	void stop(){
		running = false;
	};

	bool isRunning(){
		return running;
	};

	std::vector<Vertex *> getPath(){
		return path;
	};


	int run(bool print, bool extra){
		while(!CUBES.empty()){
			Cube *c = CUBES.front(); 
			CUBES.pop();

			while(c->worm->isRunning()){
				c->worm->makeDecision();
			}

			if ( print ) {
				cube -> worm -> print(extra);
				printf("\n");
			}

			return traversals;
		}
	}
	//make a descision for a traversal based on current stuff
	void makeDecision(){
		std::vector<Vertex *> choices = cube->getChoices(current);


		//make the choice
		//when the choice is made, all unchosen choices need to be updated to invalid
		Weights * w = cube->calculateWeights(&choices, 1);

		choose(w);

	};

	//choose the best decision in a set
	void choose(Weights * w){
		
		Weight *best = bestFunction(w);

		if(best->value == 0){
			stop();
			return;
		}
		next = best->vertex;

		move();
	}

	//perform actual traversal updating pointers as necessary
	//also update the valid nodes
	void move(){

		cube->invalidateNeighbors(current);

		prev = current;
		current = next;
		next = 0;
		this->path.push_back(this->current);

		traversals++;
	};

	void print(bool info){
		printf("--------------------- worm %d print -------------------\n", cube->id);
		if(info){
			for(int i=0; i<path.size(); i++){
				path.at(i)->print();
			}
		}
		else{
			for(int i=0; i<path.size(); i++){
				printf("%d -> ", path.at(i)->id);
			}
			printf("\n");
		}
		printf("\ttraversals : %d\n", traversals);
		printf("--------------- end worm print ----------------------\n");
	}

	/*
	*accept weights and return the best one based on some heuristic
	*/
	Weight * bestFunction(Weights *w){
		Weight *best = w->weights.at(0); 
		//assign the default
		for(int i=0; i<w->weights.size(); i++){
			if(w->weights.at(i) -> value > 0){
				best = w->weights.at(i);
				break;
			}
		}

		Weight *current;

		std::vector<Weight *> t;
		for(int i=0; i<w->weights.size(); i++){//iterate through each weight
			current = w->weights.at(i);

			//for this function the lower the value the better the vertex
			if ( ( best->value >= current->value ) && ( current->value > 0 ) ) {
				best = current;

				t.push_back(best);
			}
		}

		
		if ( t.size() > 0 ){
			//choose random one
			int which = rand() % t.size();
			best = t.at( which );
		}
		return best;
	}

	~Worm(){
		delete next;
		delete prev;
		delete current;

		delete  &path;
		delete cube;
	}
}(Worm);

#endif