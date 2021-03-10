#include "stdafx.h"
#include "Cerveau.h"

Cerveau::Cerveau() : nLayers(1) { allocSpace(); }

Cerveau::Cerveau(unsigned int pattern[], unsigned int len): nLayers(len-1)
{
	allocSpace();

	for (unsigned int i(1); i < len; ++i)
		layers[i-1] = NeuroneLayer(pattern[i], pattern[i - 1]);
}

Cerveau::~Cerveau()
{
	delete[] layers;
}

Cerveau::Cerveau(const Cerveau& c): nLayers(c.nLayers)
{
	allocSpace();

	for (unsigned int i(0); i < nLayers; ++i)
		layers[i] = c.layers[i];
}

float* Cerveau::Activation(float input[], unsigned len)
{
	NeuroneLayer res(input,  len);

	for (unsigned int i(0); i < nLayers; ++i)
	{
		res = layers[i] * res;
		res.Activation();
	}
	
	return res.ToArray();
}

void Cerveau::Mutation(float mutationRate)
{
	for (unsigned int i(0); i < nLayers; ++i)
		layers[i].Mutation(mutationRate);
}
void Cerveau::Mutation(unsigned int nbrMutation)
{
	unsigned int x(0);

	for (unsigned int i(0); i < nbrMutation; ++i)
	{
		x = rand() % nLayers;
		layers[x].Mutation();
	}
}

Cerveau& Cerveau::operator=(const Cerveau& c)
{
	if (this == &c)
		return *this;

	if (nLayers != c.nLayers)
	{
		delete[] layers;

		nLayers= c.nLayers;
		allocSpace();
	}

	for (unsigned int i = 0; i < nLayers; ++i)
			layers[i] = c.layers[i];

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Cerveau& c)
{
	os << "[";
	for (unsigned int i = 0; i < c.nLayers; ++i) 
	{
		os << c.layers[i];
		os << std::endl;
	}
	os << "]"<<std::endl;
	return os;
}

void Cerveau::allocSpace()
{
	layers = new NeuroneLayer[nLayers];
}

