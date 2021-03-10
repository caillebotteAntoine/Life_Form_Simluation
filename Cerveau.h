#pragma once

#include "NeuroneLayer.h"

class Cerveau
{
public:
	Cerveau();
	Cerveau(unsigned int pattern[], unsigned int len);
	Cerveau(const Cerveau& c);
	~Cerveau();

	float* Activation(float input[], unsigned len);
	void Mutation(float mutationRate);
	void Mutation(unsigned int nbrMutation);

	Cerveau& operator=(const Cerveau&);

	friend std::ostream& operator<<(std::ostream&, const Cerveau&);

private :
	unsigned int nLayers;
	NeuroneLayer *layers;

	void allocSpace();
};

