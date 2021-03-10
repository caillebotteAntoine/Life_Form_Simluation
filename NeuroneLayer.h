	#pragma once

#include <iostream>

class NeuroneLayer
{
public:
	NeuroneLayer();
	NeuroneLayer(unsigned int ligne, unsigned int colonne);
	NeuroneLayer(float w[], unsigned int colonne);
	NeuroneLayer(const NeuroneLayer& nl);
	~NeuroneLayer();

	void Activation();
	void Mutation( float mutationRate);
	void Mutation(unsigned int nbrMutation);
	void Mutation();
	//void CrossOver(const NeuroneLayer& A, const NeuroneLayer& B)

	float* ToArray();
	//NeuroneLayer& operator=(const Matrix&);

	inline float& operator()(int x, int y) { return weight[x][y]; }

	NeuroneLayer& operator=(const NeuroneLayer&);
	NeuroneLayer& operator*=(const NeuroneLayer&);

	friend std::ostream& operator<<(std::ostream&, const NeuroneLayer&);

private :
	unsigned int rows, cols;

	float **weight;
	float *bias;


	void allocSpace();
};

NeuroneLayer operator*(const NeuroneLayer&, const NeuroneLayer&);
