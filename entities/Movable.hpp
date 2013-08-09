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
	void setAcceleration(sf::Vector2f acceleration);
	void decelerate();

protected:
	void updateVelocity();

	int m_mass;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	const int m_maxSpeed;
	const int m_maxAcceleration;
	const int m_deceleration;
};

Movable::Movable(sf::Sprite sprite):
	Entity(sprite),
	m_velocity(0,0),
	m_maxSpeed(500),
	m_acceleration(0,0),
	m_maxAcceleration(8),
	m_deceleration(7)
{

}

Movable::~Movable()
{
}

void Movable::move(float elapsedTime)
{
	updateVelocity();
	m_sprite.move(m_velocity*elapsedTime);
}

void Movable::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void Movable::setAcceleration(sf::Vector2f acceleration)
{
	m_acceleration = acceleration;
	if(m_velocity.x < 0 && acceleration.x > 0)
		m_acceleration.x = m_maxAcceleration*2.5;
	if(m_velocity.x >0 && acceleration.x < 0)
		m_acceleration.x = -m_maxAcceleration*2.5;
	if(m_velocity.y < 0 && acceleration.y > 0)
		m_acceleration.y = m_maxAcceleration*2.5;
	if(m_velocity.y >0 && acceleration.y < 0)
		m_acceleration.y = -m_maxAcceleration*2.5;

	if(m_acceleration.x > m_maxAcceleration)
		m_acceleration.x = m_maxAcceleration;
	if(m_acceleration.y > m_maxAcceleration)
		m_acceleration.y = m_maxAcceleration;
	if(m_acceleration.x < -m_maxAcceleration)
		m_acceleration.x = -m_maxAcceleration;
	if(m_acceleration.y < -m_maxAcceleration)
		m_acceleration.y = -m_maxAcceleration;
}

void Movable::updateVelocity()
{
	m_velocity.x += m_acceleration.x;
	m_velocity.y += m_acceleration.y;
	if(m_velocity.x > m_maxSpeed)
		m_velocity.x = m_maxSpeed;
	if(m_velocity.y > m_maxSpeed)
		m_velocity.y = m_maxSpeed;
	if(m_velocity.x < -m_maxSpeed)
		m_velocity.x = -m_maxSpeed;
	if(m_velocity.y < -m_maxSpeed)
		m_velocity.y = -m_maxSpeed;
}

void Movable::decelerate()
{
	if(m_velocity.x > 0)
		m_velocity.x -= m_deceleration;
	if(m_velocity.y > 0)
		m_velocity.y -= m_deceleration;
	if(m_velocity.x < 0)
		m_velocity.x += m_deceleration;
	if(m_velocity.y < 0)
		m_velocity.y += m_deceleration;
}