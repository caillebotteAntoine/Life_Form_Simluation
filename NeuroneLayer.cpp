#include "stdafx.h"

#include <stdlib.h>   
#include <cmath>

#include "NeuroneLayer.h"
#include <assert.h> //gestion des erreur mais que pour le debug

NeuroneLayer::NeuroneLayer() :rows(1), cols(1) { allocSpace(); }

NeuroneLayer::~NeuroneLayer()
{
	for (unsigned int i = 0; i < rows; ++i)
		delete[] weight[i];

	delete[] weight;
	delete[] bias;

}

NeuroneLayer::NeuroneLayer(unsigned int ligne, unsigned int colonne) :rows(ligne), cols(colonne)
{
	allocSpace();
	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
			weight[i][j] = float(rand() % 20) - 10.0f;

		bias[i] = float(rand() % 20) - 10.0f;
	}
}

NeuroneLayer::NeuroneLayer(float w[], unsigned int colonne) : rows(colonne), cols(1)
{
	allocSpace();
	
	for (unsigned int i = 0; i < rows; ++i)
	{
		weight[i][0] = w[i];
		bias[i] = 1;
	}
}

NeuroneLayer::NeuroneLayer(const NeuroneLayer& nl) : rows(nl.rows), cols(nl.cols)
{
	allocSpace();
	for (unsigned int i = 0; i < rows; ++i) 
	{
		for (unsigned int j = 0; j < cols; ++j) 
			weight[i][j] = nl.weight[i][j];

		bias[i] = nl.bias[i];
	}
	
}

void NeuroneLayer::Activation()
{
	assert(cols == 1);

	for (unsigned int i = 0; i < rows; ++i)
	{
		weight[i][0] = 1 / (1 + exp(weight[i][0] - bias[i]));
		bias[i] = 1;
	}
}

void NeuroneLayer::Mutation(float mutationRate)
{
	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
			if (rand() % 100 < mutationRate * 100)
				weight[i][j] += 1 - 2 * rand() % 2;

		if (rand() % 100 < mutationRate * 100)
			bias[i] += 1 - 2 * rand() % 2;
	}
}

void NeuroneLayer::Mutation(unsigned int nbrMutation)
{
	int x(0), y(0);

	for (unsigned int i(0); i < nbrMutation; i++)
	{
		x = rand() % rows;
		y = rand() % cols;

		if (rand()%(cols+1) == 0)
			bias[x] += 1 - 2 * rand() % 2;
		else
			weight[x][y] += 1 - 2 * rand() % 2;
	}
}

void NeuroneLayer::Mutation( )
{
	int x = rand() % rows;
	int y = rand() % cols;

	if (rand() % (cols + 1) == 0)
		bias[x] += 1 - 2 * rand() % 2;
	else
		weight[x][y] += 1 - 2 * rand() % 2;
}

float* NeuroneLayer::ToArray()
{
	float *v;
	v = new float[rows * cols];

	for (unsigned int i = 0; i < rows; ++i)
		for (unsigned int j = 0; j < cols; ++j)
			v[i + j * rows] = weight[i][j];
	return v;
}

NeuroneLayer& NeuroneLayer::operator=(const NeuroneLayer& nl)
{
	if (this == &nl)
		return *this;

	if (rows != nl.rows || cols != nl.cols)
	{
		for (unsigned int i = 0; i < rows; ++i)
			delete[] weight[i];

		delete[] weight;
		delete[] bias;

		rows = nl.rows;
		cols = nl.cols;
		allocSpace();
	}

	for (unsigned int i = 0; i < rows; ++i)
	{
		for (unsigned int j = 0; j < cols; ++j)
			weight[i][j] = nl.weight[i][j];

		bias[i] = nl.bias[i];
	}

	return *this;
}

NeuroneLayer& NeuroneLayer::operator*=(const NeuroneLayer& nl)
{
	assert(cols == nl.rows);

	NeuroneLayer temp(rows, nl.cols);
	for (unsigned int i = 0; i < temp.rows; ++i) 
	{
		for (unsigned int j = 0; j < temp.cols; ++j)
		{
			temp.weight[i][j] = 0;
			for (unsigned int k = 0; k < cols; ++k) {
				temp.weight[i][j] += (weight[i][k] * nl.weight[k][j]);
			}
		}
		temp.bias[i] = bias[i] * nl.bias[i];
	}
	return (*this = temp);
}

/*
NeuroneLayer& NeuroneLayer::CrossOver(const NeuroneLayer& A, const NeuroneLayer& B)
{
	assert(A.cols == B.cols && A.rows == B.rows);

	NeuroneLayer temp(A.rows, A.cols);

	int x = rand() % temp.rows;
	int y = rand() % temp.rows;

	float d = x + (float)(y - x) / rows;

	for (int i = 0; i < temp.rows; ++i)
		for (int j = 0; j < temp.cols; ++j)
		{

			if( j <= d * i )
				 weight[i][j] = nl.weight[i][j];
		}
	
	return *this;
}
*/
NeuroneLayer operator*(const NeuroneLayer& nl1, const NeuroneLayer& nl2)
{
	NeuroneLayer temp(nl1);
	return (temp *= nl2);
}

std::ostream& operator<<(std::ostream& os, const NeuroneLayer& nl)
{
	for (unsigned int i = 0; i < nl.rows; ++i)
	{
		os << "w = "<< nl.weight[i][0];
		for (unsigned int j = 1; j < nl.cols; ++j)
			os << " " << nl.weight[i][j];
		
		os << " b = " << nl.bias[i];
		os << std::endl;
	}
	return os;
}

void NeuroneLayer::allocSpace()
{
	bias = new float[rows];
	weight = new float*[rows];
	for (unsigned int i = 0; i < rows; ++i) {
		weight[i] = new float[cols];
	}
}