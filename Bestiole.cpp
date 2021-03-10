

#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include "bestiole.h"

#include <assert.h> //gestion des erreur mais que pour le debug
#include <iostream>

#define nbrCapeur 1

Bestiole::Bestiole(unsigned int pattern[], unsigned int len, int k) : lenInput(nbrCapeur), age(0), affichage(false), i(k)
{
	capteur = new RayCast[nbrCapeur]{
		RayCast(Loop::groupNourriture, 200, 0)/*,
		RayCast(Loop::groupObstacle, 20, -45),
		RayCast(Loop::groupObstacle, 20, 0),
		RayCast(Loop::groupObstacle, 20, 45)*/
	};
		
	input = new float[nbrCapeur];

	cerveau = Cerveau(pattern,len);
		
	assert(pattern[0] == nbrCapeur);
	assert(pattern[len-1] == 2);
}

Bestiole::~Bestiole()
{
	delete[] capteur;
	delete[] input;
}

void Bestiole::Init()
{
	if (!entity->HasComponent<Position>())
		entity->AddComponent<Position>();

	position = &entity->GetComponent<Position>();

	entity->AddComponent<BestioleShape>();
	shape = &entity->GetComponent<BestioleShape>();

	entity->AddComponent<PeutManger>(Emax);
	manger = &entity->GetComponent<PeutManger>();

	for (unsigned int i(0); i < lenInput; i++)
		capteur[i].entity = entity;

	for (unsigned int i(0); i < lenInput; i++)
		capteur[i].Init();		
}

void Bestiole::UpdateAff()
{
	shape->SetRayon(manger->GetEnergie());
	shape->SetCouleurAge(age);
}

void Bestiole::Update()
{
	age++;
	//std::cout << 3 * (age - ageMax) << std::endl;

	manger->SetEff(1 - exp(3 * (age - ageMax)));

	bool diff = false;

	for (unsigned int i(0); i < lenInput; i++)
	{
		capteur[i].Update();

		if (input[i] != float(capteur[i].Hit()))
		{
			diff = true;
			input[i] = float(capteur[i].Hit());
		}
	}

	if (diff)
	{
		float* output = cerveau.Activation(input, lenInput);

		position->speed_rot = (output[0] - 0.5f) * 12;
		position->speed_trans = output[1];

		delete[] output;
	}
}

void Bestiole::GetBack()
{
	position->speed_rot = -position->speed_rot;
	position->speed_trans = position->speed_trans;

	position->Update();

	position->speed_rot = -position->speed_rot;
	position->speed_trans = position->speed_trans;
}

void Bestiole::Affichage()
{
	UpdateAff();

	if (true || affichage)
	{
		for (unsigned int i(0); i < lenInput; i++)
		{
			if(capteur[i].Hit() || affichage)
				capteur[i].Affichage();
		}
	}
}

void Bestiole::Naissance(Bestiole *a, unsigned int nbrMutation)
{
	Cerveau* c_a = a->GetCerveau();

	cerveau = Cerveau(*c_a);

	cerveau.Mutation(nbrMutation);
}

void Bestiole::Naissance(Bestiole *a, float mutationRate)
{
	Cerveau* c_a = a->GetCerveau();

	cerveau = Cerveau(*c_a);

	cerveau.Mutation(mutationRate);
}

bool SelectionNaturel(Entity*a, Entity *b)
{
	PeutManger faim_a = a->GetComponent<PeutManger>();
	PeutManger faim_b = b->GetComponent<PeutManger>();

	return faim_a.GetEnergie() < faim_b.GetEnergie();
}

void Bestiole_Selection_Naturel(std::vector<Entity*>liste)
{
	std::vector<Entity*> liste_Bestiole;
	for (auto& e : liste)
	{
		if (e->HasComponent<Bestiole>())
		{
			liste_Bestiole.push_back(e);
			e->GetComponent<Bestiole>().SwitchAffichage( false);
		}
	}

	std::cout << "<";
	for (auto& e : liste_Bestiole)
		std::cout << e->GetComponent<PeutManger>().GetEnergie() << ", ";

	std::sort(liste_Bestiole.begin(), liste_Bestiole.end(), SelectionNaturel);

	std::cout << std::endl;
	for (auto& e : liste_Bestiole)
		std::cout << e->GetComponent<PeutManger>().GetEnergie() << ", ";

	std::cout << ">" << std::endl;

	size_t s = liste_Bestiole.size();

	if (s > 2)
	{
		Bestiole* a = &liste_Bestiole[s - 1]->GetComponent<Bestiole>();
		Bestiole* b = &liste_Bestiole[s - 2]->GetComponent<Bestiole>();

		liste_Bestiole[s - 1]->GetComponent<Bestiole>().SwitchAffichage(true);

		liste_Bestiole[0]->GetComponent<Bestiole>().Naissance(a, 2u);
		liste_Bestiole[1]->GetComponent<Bestiole>().Naissance(a, 2u);

		liste_Bestiole[0]->GetComponent<Position>().position = Loop::GetRandomVec2();
		liste_Bestiole[1]->GetComponent<Position>().position = Loop::GetRandomVec2();
	}
}

void BestioleResetFaim(std::vector<Entity*>liste)
{
	for (auto& e : liste)
	{
		if (e->HasComponent<PeutManger>())
			e->GetComponent<PeutManger>().ResetFaim();
	}
}