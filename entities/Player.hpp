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
	void fireLaser();
	void updateFocusDirection(sf::Vector2f mousePosition);

private:
	ProjectileManager& m_projectileManager;
	int m_fireRate;
	sf::Vector2f m_focusDirection;
	sf::Clock m_fireRateClock;
};

Player::Player(sf::Texture& texture, ProjectileManager& projManager):
	Movable(texture),
		m_projectileManager(projManager),
		m_fireRate(50)
{
	m_maxSpeed = 150;
	m_maxAcceleration = 5;
	m_deceleration = 4;

	updateFocusDirection(sf::Vector2f(100,0));
}

Player::~Player()
{

}

void Player::updateFocusDirection(sf::Vector2f mousePosition)
{
	sf::Vector2f direction;
	sf::Vector2f playerPos = m_sprite.getPosition();
	direction.x = (mousePosition.x - playerPos.x);
	direction.y = (mousePosition.y - playerPos.y);
	int norm = sqrt(direction.x*direction.x + direction.y*direction.y);
        if(norm==0)
            norm=1;
	m_focusDirection.x = direction.x/norm;
	m_focusDirection.y = direction.y/norm;
}

void Player::fireLaser()
{
	if(m_fireRateClock.getElapsedTime().asMilliseconds() > m_fireRate)
	{
		sf::Vector2f playerPos = m_sprite.getPosition();
		
		//Create the projectile
		m_projectileManager.createProjectile(playerPos,m_focusDirection);
		m_fireRateClock.restart();
	}
}