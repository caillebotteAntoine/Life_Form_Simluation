#pragma once

#include "Manager.h"
#include "Cerveau.h"
#include "Component.h"

class RayCast;

class Bestiole : public Component
{
public:
	Bestiole(unsigned int pattern[], unsigned int len, int k );
	~Bestiole();

	void Init() override;
	void Update() override;
	void GetBack();

	void UpdateAff();
	void Affichage() override;

	void Naissance(Bestiole *a, unsigned int nbrMutation);
	void Naissance(Bestiole *a, float mutationRate);
	Cerveau* GetCerveau() { return &cerveau; }

	void SwitchAffichage( bool a) { affichage = a; }

	int i;
	
private :
	Position *position;
	BestioleShape *shape;
	PeutManger *manger;

	bool affichage;
	
	Cerveau cerveau;
	int age;

	RayCast *capteur;
	float *input;
	unsigned int lenInput;
};

void Bestiole_Selection_Naturel(std::vector<Entity*>liste);
void BestioleResetFaim(std::vector<Entity*>liste);
