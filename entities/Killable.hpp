#pragma once
#include "../stdafx.h"

#include "Entity.hpp"
#include "Movable.hpp"

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

class Killable: public Movable
{
public:
	Killable(sf::Texture& texture);
	~Killable();

	bool isAlive();
	void takeDamage(int damage);

protected:
	int m_maxLife;
	int m_life;
};

Killable::Killable(sf::Texture& texture):
	Movable(texture),
		m_maxLife(100),
		m_life(m_maxLife)
{

}

Killable::~Killable()
{
}

bool Killable::isAlive()
{
	return m_life > 0;
}

void Killable::takeDamage(int damage)
{
	m_life -= damage;
	if(m_life < 0)
		m_life = 0;
}