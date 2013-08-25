#pragma once
#include "../stdafx.h"

#include "Movable.hpp"
#include "ProjectileManager.hpp"

class Ennemy: public Movable
{
public:
	Ennemy(sf::Texture& texture);
	~Ennemy();

private:

};

Ennemy::Ennemy(sf::Texture& texture):
	Movable(texture)
{

}

Ennemy::~Ennemy()
{

}