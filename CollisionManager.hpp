#pragma once
#include "stdafx.h"
#include "entities\EntityManager.hpp"
#include "entities\Player.hpp"
#include "entities\Entity.hpp"

/*! 
 *  \brief     Manages collisions between entities
 *  \details   
 *  \author    Vincent Studer
 *  \date      2013
 *  \copyright GNU Public License.
 */

class CollisionManager
{
public:
	CollisionManager(EntityManager& entMan, sf::Vector2i resolution);
	~CollisionManager();
	//! Use the other methods to check all the collisions
	void update();

private:
	//! Calculate the dotproduct between two entities
	int dotProduct(Entity& ent1, Entity& ent2);
	//! Calculate the dotProduct between two sf::Vector
	int dotProduct(sf::Vector2f vect1, sf::Vector2f vect2);
	//! Check the player/border collisions
	void borderCollisions();
	//! A reference to the EntityManager
	EntityManager& m_entityManager;
	//! The resolution of the screen
	sf::Vector2i m_resolution;
	//! The player
	Player& m_player;

};

CollisionManager::CollisionManager(EntityManager& entMan, sf::Vector2i resolution):
			m_entityManager(entMan),
			m_resolution(resolution),
			m_player(m_entityManager.getPlayer())
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::update()
{
	borderCollisions();
}

int CollisionManager::dotProduct(Entity& ent1, Entity& ent2)
{
	return ent1.getPosition().x*ent2.getPosition().x + ent1.getPosition().y*ent2.getPosition().y;
}

int CollisionManager::dotProduct(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return vect1.x*vect2.x + vect1.y*vect2.y;
}

void CollisionManager::borderCollisions()
{
	int delta(70);
	sf::Vector2f playerPosition(m_player.getPosition());
	if(playerPosition.x > m_resolution.x - delta)
		m_player.setAcceleration(sf::Vector2f(-50,0));
	if(playerPosition.x < delta/2)
		m_player.setAcceleration(sf::Vector2f(50,0));
	if(playerPosition.y > m_resolution.y - delta)
		m_player.setAcceleration(sf::Vector2f(0,-50));
	if(playerPosition.y < delta/2)
		m_player.setAcceleration(sf::Vector2f(0,50));
}