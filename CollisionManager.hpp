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
	void update();

private:
	int dotProduct(Entity& ent1, Entity& ent2);
	int dotProduct(sf::Vector2f vect1, sf::Vector2f vect2);
	EntityManager& m_entityManager;
	sf::Vector2i m_resolution;

};

CollisionManager::CollisionManager(EntityManager& entMan, sf::Vector2i resolution):
			m_entityManager(entMan),
			m_resolution(resolution)
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::update()
{
	
}

int CollisionManager::dotProduct(Entity& ent1, Entity& ent2)
{
	return ent1.getPosition().x*ent2.getPosition().x + ent1.getPosition().y*ent2.getPosition().y;
}

int CollisionManager::dotProduct(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return vect1.x*vect2.x + vect1.y*vect2.y;
}