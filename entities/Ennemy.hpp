#pragma once
#include "../stdafx.h"

#include "Movable.hpp"
#include "ProjectileManager.hpp"
#include "../utility.hpp"

/*! 
 *  \brief     An ennmy class
 *  \details   Stores an ennemy characteristics
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Ennemy: public Killable
{
public:
	Ennemy(sf::Texture& texture, sf::Vector2f position);
	~Ennemy();
	void accelerateToTarget(sf::Vector2f targetPos);

private:

};

Ennemy::Ennemy(sf::Texture& texture, sf::Vector2f position):
	Killable(texture)
{
	m_maxSpeed = 500;
	m_maxAcceleration = 6;
	m_deceleration = 4;
	m_sprite.setPosition(position);
}

Ennemy::~Ennemy()
{

}

void Ennemy::accelerateToTarget(sf::Vector2f targetPos)
{
	sf::Vector2f direction;
	direction = directionToPosition(m_sprite.getPosition(), targetPos);
	this->setAcceleration(direction);
}