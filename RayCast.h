#pragma once

#include "Component.h"
#include <SFML/Graphics.hpp>

class RayCast : public Component
{
public:
	RayCast() : tag(0), longueur(0), rotation(0), direction(1, 0), intersection(0) {}
	RayCast(size_t t, float l, float r) : tag(t), longueur(l), rotation(r), direction(1,0), intersection(1) {}

	~RayCast() {};
	
	bool Hit() const { return res; }
	bool IsTag(size_t t) const { return t == tag; }

	sf::Vector2f  Segment() const { return longueur * direction; }
	sf::Vector2f  GetOrigine() const { return position->position; }
	//Vec2 SetOrigine(Vec2 o) { origine = o; }

	void Affichage() override
	{
		UpdateAff();
		Loop::window->draw(line, 2, sf::Lines);
	}

	void Init() override
	{
		if (!entity->HasComponent<Position>())
		{
			entity->AddComponent<Position>();
		}

		position = &entity->GetComponent<Position>();
	}

	void UpdateAff();
	void Update() override;

	void SetIntersection(float i) { intersection = i; }

	const float longueur;
	
private:
	Position *position;
	sf::Vector2f direction;

	const float rotation;

	bool res = false;

	size_t tag;

	float intersection;
	sf::Vertex line[2];


};

