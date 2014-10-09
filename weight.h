#ifndef WEIGHT_H
#define WEIGHT_H

#include <vector>

#include "vertex.h"

struct Vertex;

typedef struct Weight{
	Weight(int k, Vertex *v):
		value(k),
		vertex(v)
		{};

	int value;
	Vertex *vertex;
}(Weight);

typedef struct Weights{

	void addWeight(Weight *w){
		weights.push_back(w);
	};

	std::vector<Weight *> weights;

}(Weights);

#endif