#pragma once
#include "../stdafx.h"

#include "Movable.hpp"

/*! 
 *  \brief     The projectile class
 *  \details   Stores projectiles characteristics
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Projectile: public Movable
{
public:
	Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction);
private:
	int m_speed;
};

Projectile::Projectile(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction):
		Movable(texture),
			m_speed(500)
{
	m_sprite.setPosition(position);
	m_velocity.x = direction.x*m_speed;
	m_velocity.y = direction.y*m_speed;
}