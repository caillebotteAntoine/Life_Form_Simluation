#pragma once

#include "Component.h"
#include "Collider.h"

class SeMange: public Component
{
public:
	SeMange(float a) : apport(a)  {}

	float GetApport() const { return apport; }
	
private:
	const float apport;
};

class PeutManger : public Component
{
public:
	PeutManger( float m): energie(0.0f), max(m), eff(1.0f) {}

	void AddApport(float a) 
	{
		//std::cout << eff << std::endl;
		energie += eff*a;
		if (energie < 0)
			energie = 0;
		else if (energie > max)
			energie = max;
	}

	void SetEff(float e) { eff = e; }
	float GetEnergie() const { return energie; }
	void ResetFaim() { energie = 0.0f; }

private:
	float energie;
	float eff;

	const float max;
};