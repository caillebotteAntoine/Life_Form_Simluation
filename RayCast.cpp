#include "stdafx.h"

#include "RayCast.h"
#include "Loop.h"
#include "Collision.h"
#include "Vecteur2.h"

void RayCast::UpdateAff()
{
	sf::Color c = sf::Color::Red;
	if (res)
		c = sf::Color::Green;
	else
		intersection = 1;

	//std::cout <<intersection<<std::endl;
	line[0] = sf::Vertex(GetOrigine(), c);
	line[1] = sf::Vertex(GetOrigine() + intersection * longueur * direction, c);

}

void RayCast::Update()
{
	direction = v2::Rotation(position->direction, rotation);

	Manager *manager = entity->manager;

	auto& colliders = manager->GetGroup(Loop::groupColliders);


	res = false;
	for (auto& e : colliders)
	{
		if (e->HasComponent<PolyCollider>())
		{
			PolyCollider *c = &e->GetComponent<PolyCollider>();

			if (Collision::RayCollision(this, c))
				res = true;
		}
	}
}