#pragma once

class Entity;
class RayCast;
class Collider;
class PolyCollider;
class CircleCollider;
class PointCollider;

namespace Collision
{
	/*bool RayCollision(RayCast *ray, Collider collider);
	bool RayCollision(RayCast *ray, CircleCollider collider);*/

	bool RayCollision(RayCast *ray, PolyCollider *collider);
	void Impact(Entity* e, Entity* c);

	bool ColliderCollision(Entity* e, Entity* c);
	bool ColliderCollision(CircleCollider a, PointCollider b);
	bool ColliderCollision(PolyCollider a, PointCollider b);
	
};

