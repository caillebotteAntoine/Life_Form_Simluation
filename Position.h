#pragma once

#include "Component.h"
#include "Vecteur2.h"
#include "Loop.h"

class Position : public Component
{
public:
	
	sf::Vector2f position;
	sf::Vector2f direction;
	float speed_trans;
	float speed_rot;

	
	Position():speed_trans(0), speed_rot(0) 
	{
		position = sf::Vector2f(0,0);
		lastPosition = sf::Vector2f(0, 0);
		direction = sf::Vector2f(1, 0);
	}

	Position(sf::Vector2f p) :speed_trans(0), speed_rot(0) { position = p; lastPosition = p; direction = sf::Vector2f(1, 0); }

	Position(float x, float y) :position(x, y), lastPosition(x, y), speed_trans(1), speed_rot(0) { direction = sf::Vector2f(1, 0); }
	
	//#include <iostream>
	void Update() override
	{
		direction = v2::Rotation(direction, speed_rot);

		lastPosition = position;
		position += speed_trans * direction;
		position = Loop::ClampedVec2(position);
	}

	void GetBack()
	{
		position = lastPosition;
	}

private :
	sf::Vector2f lastPosition;
	
};