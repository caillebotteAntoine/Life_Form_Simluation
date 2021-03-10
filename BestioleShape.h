#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>
#include "Header.h"

#include "Vecteur2.h"

class BestioleShape : public Component
{
public:

	BestioleShape() : rayon_corps(10.0f), rayon_coeur(3.0f), corps(0.0f), coeur(0.0f),
		line{ sf::Vertex(sf::Vector2f(0,0),sf::Color::Black),
		sf::Vertex(sf::Vector2f(0,0),sf::Color::Black) }, couleur_corps(sf::Color::Blue), couleur_coeur_ext(sf::Color(150,150,150)), couleur_coeur_int(sf::Color::Red)
	{

		corps.setRadius(rayon_corps);
		corps.setFillColor(sf::Color::White);
		corps.setOutlineThickness(2.0f);
		corps.setOutlineColor(couleur_corps);

		coeur.setRadius(rayon_coeur);
		coeur.setFillColor(couleur_coeur_int);
		coeur.setOutlineThickness(2.0f);
		coeur.setOutlineColor(couleur_coeur_ext);
	}

	void Affichage() override
	{
		UpdateUpdateAff();
		Loop::window->draw(corps);
		Loop::window->draw(line, 2, sf::Lines);
		Loop::window->draw(coeur);

	}

	void UpdateUpdateAff()
	{
		sf::Vector2f p = position->position;
		sf::Vector2f d(1.0f, 1.0f);

		corps.setPosition(p - rayon_corps*d);
		coeur.setPosition(p - rayon_coeur*d);
		coeur.setOutlineColor(couleur_coeur_ext);

		line[0].position = p;

		sf::Vector2f f = p + rayon_corps * position->direction;
		line[1].position = f;

	}

	void Init() override
	{
		if (!entity->HasComponent<Position>())
			entity->AddComponent<Position>();

		position = &entity->GetComponent<Position>();

		position->speed_rot = 1;
		position->speed_trans = 1;
	}

	void SetRayon(float Energie)
	{
		rayon_corps = sqrt(Energie / (2 * v2::PI*rho));
		if (rayon_corps < rayon_coeur + 2)
			rayon_corps = rayon_coeur + 2;

		corps.setRadius(rayon_corps);
	}

	void SetCouleurAge(int age)
	{
		int grey( (1 - (float)age / ageMax) * 255);
		if (age > ageMax)
			grey = 0;

		couleur_coeur_ext = sf::Color(grey, grey, grey);
	}

private :
	Position* position;

	float rayon_corps;
	float rayon_coeur;
	
	sf::CircleShape corps;
	sf::CircleShape coeur;
	sf::Vertex line[2];

	sf::Color couleur_corps;
	sf::Color couleur_coeur_int;
	sf::Color couleur_coeur_ext;

};
