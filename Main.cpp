// SFML_Modèle.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include <time.h>

#include "Loop.h"

#include "Cerveau.h"
#include "NeuroneLayer.h"

#define FPS 60.0f

int main()
{
	Loop loop;
	loop.Init("SFML works!", 10, 10, 500, 500);
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	
	/*
	unsigned int pattern[3]{ 2,1 };
	Cerveau cerveau(pattern, 2);

	std::cout << cerveau << std::endl;

	float *i = new float[3];
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;

	std::cout << *cerveau.Activation(i, 2) << std::endl;
	std::cout << *cerveau.Activation(i, 2) << std::endl;
	std::cout << *cerveau.Activation(i, 2) << std::endl;
	std::cout << *cerveau.Activation(i, 2) << " fini"<< std::endl;
	
	NeuroneLayer n(1u,2u);

	std::cout << n << std::endl;

	float *w = new float[2]{ 1,2 };
	float *b = new float[2]{ 1,1 };
	NeuroneLayer m(w, b, 2);

	std::cout << m << std::endl;

	std::cout << n*m << std::endl;
	*/



	const float fps(1/FPS);
	int nbrUpdate(0);
	clock_t lastRender(clock());
	int nbrFrame(0);
	clock_t lastTick(clock());

	//TODO activation cerveau n'a pas besoin de len si le prgmer n'est pas con ! 

	while (loop.Running())
	{
		loop.ManageEvent();
		loop.UpDate();
		nbrUpdate++;

		//std::cout << tRender - lastRender << " "<< (float)clock() << std::endl;
		if ( fps < ((float)(clock() - lastRender))/CLOCKS_PER_SEC)
		{
			loop.Render();
			nbrFrame++;
			lastRender = clock();
		}

		if ( 10 < (float)(clock() - lastTick)/ CLOCKS_PER_SEC)
		{
			std::cout << "fps = " << float(nbrFrame)/10 << " ups = " << float(nbrUpdate) / 10 << std::endl;
			nbrFrame = 0;
			nbrUpdate = 0;
			lastTick = clock();
		}
	}

	return 0;
}