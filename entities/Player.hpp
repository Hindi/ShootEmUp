#pragma once
#include "../stdafx.h"

#include "Movable.hpp"
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

class Player: public Movable
{
public:
	Player(sf::Texture& texture, ProjectileManager& projManager);
	~Player();
	void fireLaser(sf::Vector2i mousePos);
private:
	ProjectileManager& m_projectileManager;
	int m_fireRate;
	sf::Clock m_fireRateClock;
};

Player::Player(sf::Texture& texture, ProjectileManager& projManager):
	Movable(texture),
		m_projectileManager(projManager),
		m_fireRate(50)
{
	m_maxSpeed = 150;
	m_maxAcceleration = 10;
	m_deceleration = 4;

}

Player::~Player()
{

}


void Player::fireLaser(sf::Vector2i mousePos)
{
	if(m_fireRateClock.getElapsedTime().asMilliseconds() > m_fireRate)
	{
		//Caculate the direction
		sf::Vector2f direction;
		sf::Vector2f playerPos = m_sprite.getPosition();
		direction.x = (mousePos.x - playerPos.x);
		direction.y = (mousePos.y - playerPos.y);
		int norm = sqrt(direction.x*direction.x + direction.y*direction.y);
            if(norm==0)
                norm=1;
		direction.x = direction.x/norm;
		direction.y = direction.y/norm;
		//Create the projectile
		m_projectileManager.createProjectile(playerPos,direction);
		m_fireRateClock.restart();
	}
}