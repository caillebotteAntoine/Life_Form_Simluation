#pragma once

//#include "SDL.h"
#include <SFML/Graphics.hpp>
#include "Vecteur2.h"
#include <iostream>

class Loop
{
public:
	Loop();
	~Loop();

	int Init(const char *title, int xpos, int ypos, int width, int height);

	void ManageEvent();
	void UpDate();
	void Render();
	void Clean();

	bool Running();
	
	static sf::Vector2f GetRandomVec2();
	static sf::Vector2f ClampedVec2(sf::Vector2f);

	enum groupLabels : std::size_t
	{
		groupBestiole,
		groupColliders,
		groupNourriture,
		groupObstacle
	};

	static sf::RenderWindow *window;

private :
	
	void CreeBestiole();
	void CreeNourriture();
	void CreePolygone(unsigned int n);
	void CreeCadre();

	float fps;
	
	int cpt;
	bool isRunning;
};
