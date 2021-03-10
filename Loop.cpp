
#include "stdafx.h"
#include "Loop.h"

#include "Component.h"
#include "Manager.h"

#include "Collision.h"

#include <ctime>

Manager manager;
int i(0);

void Loop::CreeCadre()
{
	auto& e(manager.AddEntity());
	e.AddComponent<Position>(sf::Vector2f(250,250));
	e.AddComponent<PolyCollider>(groupObstacle, sf::Vector2f(0.0f, 0.0f), 490u, 490u, true);

	e.AddGroup(groupColliders);

}

void Loop::CreePolygone( const unsigned int n)
{
	sf::Vector2f *s = new sf::Vector2f[n];

	for (unsigned int i(0); i < n; i++)
		s[i] = (20.0f + rand() % 20)* sf::Vector2f(
			cos(2 * v2::PI * i / n),
			sin(2 * v2::PI * i / n));

	auto& e(manager.AddEntity());
	e.AddComponent<Position>(Loop::GetRandomVec2());
	e.AddComponent<PolyCollider>(groupObstacle, s, n);
	e.AddGroup(groupColliders);
}

void Loop::CreeBestiole()
{
	unsigned int pattern[2]{ 1u,2u };

	auto& bestiole(manager.AddEntity());
	bestiole.AddComponent<Position>(Loop::GetRandomVec2());
	bestiole.AddComponent<Bestiole>(pattern, 2u, i);
	i++;
	bestiole.AddComponent<CircleCollider>(groupBestiole, 10);
	bestiole.AddComponent<PointCollider>(groupBestiole, sf::Vector2f(0.0f, 0.0f));
	
	bestiole.AddGroup(groupBestiole);
}

void Loop::CreeNourriture()
{
	auto& e(manager.AddEntity());
	e.AddComponent<Position>(Loop::GetRandomVec2());
	e.AddComponent<PolyCollider>(groupNourriture, sf::Vector2f(0.0f, 0.0f), 10u, 10u, false);
	e.AddComponent<PointCollider>(groupNourriture, sf::Vector2f(0.0f, 0.0f));
	e.AddComponent<SeMange>(Ebase);

	e.AddGroup(groupColliders);
}

sf::RenderWindow* Loop::window = nullptr;

Loop::Loop() : fps(6000)
{}

Loop::~Loop()
{}

int Loop::Init(const char *title, int xpos, int ypos, int width, int height)
{
	isRunning = false;
	
	Loop::window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	window->setFramerateLimit(fps);
	isRunning = true;
	cpt = 0;

	srand( unsigned int (time(NULL)) );

	int N(40);
	for (int i(0); i < N; i++)
		CreeBestiole();

	N = 15;
	for (int i(0);i < N;i++)
		CreeNourriture();
	//CreeCadre();

	N = 0;
	for (int i(0);i < N;i++)
		CreePolygone(3 + rand() % 10);

	return 0;
}

void Loop::ManageEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			window->setFramerateLimit(30);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			window->setFramerateLimit(6000);
	}
	if (!window->isOpen())
		Clean();
}

void Loop::UpDate()
{
	manager.Update();

	auto& group(manager.GetGroup(groupColliders));
	auto& groupB(manager.GetGroup(groupBestiole));
	
	for(auto& c : group)
		for (auto& b : groupB)
		{
			if (Collision::ColliderCollision(c, b))
				Collision::Impact(b, c);
		}

	if ( cpt % (5000) == 0)
	{
		cout << "cpt = " <<cpt << " energie : " << endl;
		auto& groupB(manager.GetGroup(groupBestiole));
		Bestiole_Selection_Naturel(groupB);

		//BestioleResetFaim(groupB);

		cpt = 0;
	}

	cpt++;	
}

//#include "Bestiole.h"
void Loop::Render()
{
	window->clear();
	
	manager.Affichage();
	/*
	sf::Vector2f p = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	Entity e(&manager);
	e.AddComponent<Position>(p);
	e.AddComponent<PointCollider>(0, sf::Vector2f(0, 0));
	e.AddComponent<PolyCollider>(0, sf::Vector2f(0, 0), 10, 10, false);

	e.Affichage();

	unsigned int n(5);
	sf::Vector2f *s = new sf::Vector2f[n];

	for (unsigned int i(0); i < n; i++)
		s[i] = (20.0f +rand()%20)* sf::Vector2f(
			cos(2 * v2::PI * i / n),
			sin(2 * v2::PI * i / n));

	Entity c(&manager);
	c.AddComponent<Position>(sf::Vector2f(200, 200));
	c.AddComponent<PolyCollider>(0, s, n);

	c.Affichage();
	Collision::ColliderCollision(&c, &e);*/

	window->display();

}

void Loop::Clean()
{
	isRunning = false;
}

bool Loop::Running()
{
	return isRunning;
}

sf::Vector2f Loop::GetRandomVec2()
{
	sf::Vector2u size = window->getSize();

	return sf::Vector2f( (float)(rand() % size.x), (float)(rand() % size.y) );
}

sf::Vector2f Loop::ClampedVec2(sf::Vector2f v)
{
	sf::Vector2u size = window->getSize();
	unsigned int w = size.x;
	unsigned int  h = size.y;

	if (v.x > w)
		v.x = v.x - w;
	else if (v.x < 0)
		v.x = w + v.x;

	if (v.y > h)
		v.y = v.y - h;
	else if (v.y < 0)
		v.y = h + v.y;

	return v;
}
