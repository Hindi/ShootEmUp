#pragma once
#include "../stdafx.h"

#include "Entity.hpp"

/*! 
 *  \brief     A movable can be moved on the screen
 *  \details   Movable is a public Entity
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Movable: public Entity
{
public:
	Movable(sf::Sprite sprite);
	~Movable();
	void move(float elapsedTime);
	void setVelocity(sf::Vector2f vel);

protected:
	int m_mass;
	sf::Vector2f m_velocity;
	int m_speed;
};

Movable::Movable(sf::Sprite sprite):
	Entity(sprite),
	m_velocity(0,0),
	m_speed(500)
{

}

Movable::~Movable()
{
}

void Movable::move(float elapsedTime)
{
	m_sprite.move(m_velocity*elapsedTime);
}

void Movable::setVelocity(sf::Vector2f vel)
{
	if(vel.x > m_speed)
		vel.x = m_speed;
	if(vel.y > m_speed)
		vel.y = m_speed;
	if(vel.x < -m_speed)
		vel.x = -m_speed;
	if(vel.y < -m_speed)
		vel.y = -m_speed;
	m_velocity = vel;
}