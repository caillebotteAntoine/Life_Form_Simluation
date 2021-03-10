
#include "stdafx.h"

#include "Collision.h"
#include "RayCast.h"
#include "Collider.h"
#include "Manager.h"

#include "Loop.h"

#include <SFML/Graphics.hpp>

/*
bool Collision::RayCollision(RayCast *ray, Collider collider)
{
	return false;
}
*/
/*
bool Collision::RayCollision(RayCast *ray, CircleCollider collider)
{
	/*
	if (!ray->IsTag(collider.GetTag()))
		return false;

	Vec2 u = ray->Segment();
	//u.Normalize();

	Vec2 o = ray->GetOrigine();
	Vec2 v = collider.GetPosition() - o;

	double d = abs(Det(u, v));
	double n = u.Abs();
	double c = d / n;

	//std::cout << c << std::endl;
	if (c >= collider.GetRayon())
		return false;

	Vec2 w = collider.GetPosition() - o - u;
	double pscal1 = Dot(u, v);// produit scalaire    
	double pscal2 =  - Dot(u,w);  // produit scalaire    
	if (pscal1>=0 && pscal2>=0)       
		return true;   // I entre A et B, ok.    
					   
	// dernière possibilité, A ou B dans le cercle    
	if (v.Abs() < collider.GetRayon())     
		return true;    
	if (w.Abs() < collider.GetRayon())
		return true;    */
/*
	return false;
}
*/
bool  Collision::RayCollision(RayCast *ray, PolyCollider *collider)
{
	if (!ray->IsTag(collider->GetTag()))
		return false;

	sf::Vector2f o = ray->GetOrigine();
	sf::Vector2f A = collider->GetPosition();

	float d = v2::Abs(o - A);

	if (d > ray->longueur + collider->GetDistanceMax() || d == 0)
		return false;

	unsigned int len = collider->len;

	sf::Vector2f s = o + ray->Segment();
	sf::Vector2f B;
	float t(0);

	for (unsigned int i(0); i < len; i++)
	{
		A = collider->GetSegment(i);

		if( i == len-1)
			B = collider->GetSegment(0);
		else//ie i< len-1
			B = collider->GetSegment(i+1);

		t = v2::IntersectionSegment(o, s, A, B);

		if (t > 0 )
		{
			ray->SetIntersection(t);
			return true;
		}

	}
	return false;
}

void Collision::Impact(Entity* b, Entity* e)
{
	if (e->HasComponent<SeMange>())//Est-ce que l entity peut manger
	{
		if (b->HasComponent<PeutManger>())
		{
			float a = e->GetComponent<SeMange>().GetApport();
			auto& m = b->GetComponent<PeutManger>();
			m.AddApport(a);

			if (e->HasComponent<Position>())
			{
				auto& p = e->GetComponent<Position>();
				p.position = Loop::GetRandomVec2();
			}
		}
	}

	if (b->HasComponent<Bestiole>())
		if (e->HasComponent<PolyCollider>())
		{
			auto& c = e->GetComponent<PolyCollider>();
			if (c.GetTag() == Loop::groupColliders)
				b->GetComponent<Position>().GetBack();
		}
}

bool Collision::ColliderCollision(Entity* e, Entity *b)
{
	if (e->HasComponent<CircleCollider>())
	{
		auto& collider = e->GetComponent<CircleCollider>();
		if (b->HasComponent<PointCollider>())
			return ColliderCollision(collider, b->GetComponent<PointCollider>());
	}
	else if (b->HasComponent<CircleCollider>())
	{
		auto& collider = b->GetComponent<CircleCollider>();
		if (e->HasComponent<PointCollider>())
			return ColliderCollision(collider, e->GetComponent<PointCollider>());
	}

	if (e->HasComponent<PolyCollider>())
	{
		auto& collider = e->GetComponent<PolyCollider>();
		if (b->HasComponent<PointCollider>())
			return ColliderCollision(collider, b->GetComponent<PointCollider>());
	}
	else if (b->HasComponent<PolyCollider>())
	{
		auto& collider = b->GetComponent<PolyCollider>();
		if (e->HasComponent<PointCollider>())
			return ColliderCollision(collider, e->GetComponent<PointCollider>());
	}

	return false;
}

bool Collision::ColliderCollision(CircleCollider a, PointCollider b)
{
	sf::Vector2f x = a.GetPosition();
	sf::Vector2f y = b.GetPoint();

	if (x == y)
		return false;

	sf::Vector2f d = x - y;
	return (v2::Abs(d) < a.GetRayon());
}

bool Collision::ColliderCollision(PolyCollider a, PointCollider b)
{
	int nbp = a.len;

	sf::Vector2f I(10000 + rand()%100, 10000 + rand()%100 );//pour ilimine les cas limites
	sf::Vector2f P = b.GetPoint();

	int nbintersections = 0;
	for (int i(0) ; i < nbp ; i++)
	{
		sf::Vector2f A = a.GetSegment(i);
		sf::Vector2f B(0,0);

		if (i == nbp - 1)  // si c'est le dernier point, on relie au premier
			B = a.GetSegment(0);
		else           // sinon on relie au suivant.
			B = a.GetSegment(i+1);

		float iseg = v2::IntersectionSegment(A, B, I, P);

		if (iseg == -2)
			return ColliderCollision(a, b);  // cas limite, on relance la fonction.
		nbintersections += 1 - (int)(iseg == -1)  ;
	}

	bool res(nbintersections % 2 == 1);  // nbintersections est-il impair ?

	if (a.intCext)
		return !res;
	else
		return res;
}

