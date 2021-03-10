#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

class Collider : public Component
{
public:
	Collider(size_t t) : tag(t) {}
	
	size_t GetTag() const { return tag; }
	sf::Vector2f GetPosition() const { return position->position; }

	virtual void Init()
	{
		if (!entity->HasComponent<Position>())
			entity->AddComponent<Position>();
		
		position = &entity->GetComponent<Position>();
	}
	
protected:
	const size_t tag;
	Position *position;
	//rajouter le décalage avec la position de ref
};

class CircleCollider : public Collider
{
public:
	CircleCollider(size_t  t, int r) : Collider(t), rayon(r) {}

	int GetRayon() const { return rayon; }

private:
	int rayon;
};

class PointCollider : public Collider
{
public:
	PointCollider(size_t  t, sf::Vector2f p) : Collider(t), point(p) {}

	sf::Vector2f GetPoint() const { return position->position + point; }

private:
	sf::Vector2f point;
};

class PolyCollider : public Collider
{
public:
	PolyCollider(size_t  t, sf::Vector2f s[], unsigned int l) : Collider(t), len(l), intCext(false)
	{
		segment = new sf::Vector2f[len];

		for (unsigned int i(0); i < len; i++)
			segment[i] = s[i];
	}

	PolyCollider(size_t  t, sf::Vector2f s[], unsigned int l, bool interieurCexterieur) : Collider(t), len(l), intCext(interieurCexterieur)
	{
		segment = new sf::Vector2f[len];

		for (unsigned int i(0); i < len; i++)
			segment[i] = s[i];
	}
	
	PolyCollider(size_t  t, sf::Vector2f c, float l, float L, bool interieurCexterieur) : Collider(t), len(4), intCext(interieurCexterieur)
	{
		segment = new sf::Vector2f[len];

		segment[0] = c - sf::Vector2f(l / 2, L / 2);
		segment[1] = c - sf::Vector2f(-l / 2, L / 2);
		segment[2] = c - sf::Vector2f(-l / 2, -L / 2);
		segment[3] = c - sf::Vector2f(l / 2, -L / 2);

	}

	~PolyCollider()
	{
		//delete[] segment;
	}

	void Affichage() override
	{
		sf::Vertex *line = new sf::Vertex[len+1];

		for (unsigned int i(0); i < len+1; i++)
			line[i] = sf::Vertex(GetPosition() + segment[i], sf::Color::Red);

		line[len] = sf::Vertex(GetPosition() + segment[0], sf::Color::Red);

		Loop::window->draw(line, len+1, sf::LineStrip);

		delete[] line;
	}

	void Init() override
	{
		Collider::Init();
		SetDistanceMax();
	}

	float GetDistanceMax() { return distance_max; }

	sf::Vector2f GetSegment(int i){ return GetPosition() + segment[i]; }

	const unsigned int len;
	const bool intCext;

private:
	void SetDistanceMax()
	{
		distance_max = 0;
		sf::Vector2f d;
		sf::Vector2f o = GetPosition();
		for (unsigned int i(0); i < len; i++)
		{
			d = segment[i];
			d =  o - d;
			if ( distance_max < v2::Abs(d) )
				 distance_max = v2::Abs(d);
		}
	}

	sf::Vector2f *segment;
	float distance_max;
};
