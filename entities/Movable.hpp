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
	Movable(sf::Texture& texture);
	~Movable();
	void move();

	sf::Vector2f m_velocity;

protected:
	int m_mass;

};

Movable::Movable(sf::Texture& texture):
	Entity(texture),
		m_velocity(0,0)
{

}

void Movable::move()
{
	m_sprite.move(m_velocity);
}