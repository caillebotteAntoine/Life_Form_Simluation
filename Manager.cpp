
#include "stdafx.h"
#include "Manager.h"

void Entity::AddGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager->AddToGroup(this, mGroup);
}

void Entity::Affichage()
{
	for (auto& c : components) c->Affichage();
}

void Manager::Affichage()
{
	for (auto& e : entities) e->Affichage();
}