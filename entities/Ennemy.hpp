#pragma once
#include "../stdafx.h"

#include "Movable.hpp"
#include "ProjectileManager.hpp"

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

private:

};

Ennemy::Ennemy(sf::Texture& texture, sf::Vector2f position):
	Killable(texture)
{
	m_sprite.setPosition(position);
}

Ennemy::~Ennemy()
{

}