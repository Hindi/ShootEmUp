#pragma once
#include "../stdafx.h"

#include "Movable.hpp"
#include "Killable.hpp"
#include "ProjectileManager.hpp"

/*! 
 *  \brief     Derivable class for weapons
 *  \details   Manage the shooting action
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Armed: public Killable
{
public:
	Armed(sf::Texture& texture, ProjectileManager& projManager);
	~Armed();
	virtual void fire();
	virtual void updateFocusDirection(sf::Vector2f mousePosition);

protected:
	ProjectileManager& m_projectileManager;
	int m_fireRate;
	sf::Vector2f m_focusDirection;
	sf::Clock m_fireRateClock;
};

Armed::Armed(sf::Texture& texture, ProjectileManager& projManager):
	Killable(texture),
		m_projectileManager(projManager),
		m_fireRate(0)
{

}

Armed::~Armed()
{

}

void Armed::updateFocusDirection(sf::Vector2f mousePosition)
{
	sf::Vector2f direction;
	sf::Vector2f playerPos = m_sprite.getPosition();
	playerPos.x += m_sprite.getLocalBounds().width/2;
	playerPos.y += m_sprite.getLocalBounds().height/2;

	direction.x = (mousePosition.x - playerPos.x);
	direction.y = (mousePosition.y -22 - playerPos.y);
	int norm = sqrt(direction.x*direction.x + direction.y*direction.y);
        if(norm==0)
            norm=1;
	m_focusDirection.x = direction.x/norm;
	m_focusDirection.y = direction.y/norm;
}

void Armed::fire()
{
	if(m_fireRateClock.getElapsedTime().asMilliseconds() > m_fireRate)
	{
		sf::Vector2f playerPos = m_sprite.getPosition();
		
		//Create the projectile
		m_projectileManager.createProjectile(playerPos,m_focusDirection);
		m_fireRateClock.restart();
	}
}