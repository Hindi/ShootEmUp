#pragma once
#include "../stdafx.h"

#include "Armed.hpp"
#include "ProjectileManager.hpp"

/*! 
 *  \brief     The player
 *  \details   Stores player characteristics
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Player: public Armed
{
public:
	Player(sf::Texture& texture, ProjectileManager& projManager);
	~Player();

private:

};

Player::Player(sf::Texture& texture, ProjectileManager& projManager):
	Armed(texture, projManager)
{
	m_fireRate = 50;
	m_maxSpeed = 150;
	m_maxAcceleration = 5;
	m_deceleration = 4;

	updateFocusDirection(sf::Vector2f(100,0));
}

Player::~Player()
{

}