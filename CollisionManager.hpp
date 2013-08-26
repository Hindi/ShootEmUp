#pragma once
#include "stdafx.h"
#include "entities\EntityManager.hpp"
#include "entities\Player.hpp"
#include "entities\Entity.hpp"
#include "entities\Ennemy.hpp"
#include "entities\Projectile.hpp"
#include "entities\ProjectileManager.hpp"

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
	CollisionManager(EntityManager& entMan, ProjectileManager& ProjectileManager, sf::Vector2i resolution);
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
	//!Check the projectile/ennemy collisions
	void projectileCollisions();
	//! A reference to the EntityManager
	EntityManager& m_entityManager;
	ProjectileManager& m_projectileManager;
	//! The resolution of the screen
	sf::Vector2i m_resolution;
	//! The player
	Player& m_player;

};

CollisionManager::CollisionManager(EntityManager& entMan, ProjectileManager& projectileManager, sf::Vector2i resolution):
			m_entityManager(entMan),
			m_resolution(resolution),
			m_player(m_entityManager.getPlayer()),
			m_projectileManager(projectileManager)
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::update()
{
	borderCollisions();
	projectileCollisions();
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

	std::vector< std::shared_ptr<Projectile> >& projectiles = m_projectileManager.getProjectiles();
	std::vector< std::shared_ptr<Projectile> >::iterator lit(projectiles.begin());
	int deltaProj(50);
	for(; lit != projectiles.end();lit++)
	{
		sf::Vector2f position((*lit)->getPosition());
		if(position.x > m_resolution.x + deltaProj || position.x < -deltaProj 
			|| position.y > m_resolution.y +deltaProj || position.y < -deltaProj)
			(*lit)->dead = true;
	}
}

void CollisionManager::projectileCollisions()
{
	std::vector< std::shared_ptr<Projectile> >& projectiles = m_projectileManager.getProjectiles();
	std::vector< std::shared_ptr<Ennemy> > enemies;

	std::vector< std::shared_ptr<Projectile> >::iterator lit(projectiles.begin());
	std::vector< std::shared_ptr<Ennemy> >::iterator enemyIT;
		
	for(; lit != projectiles.end();lit++)
	{
		sf::Rect<float> projectileBox((*lit)->getBoundingBox());
		enemies = m_entityManager.canCollide(projectileBox);
		enemyIT = enemies.begin();
		for(; enemyIT != enemies.end(); enemyIT++)
		{
			sf::Rect<float> enemyBox((*enemyIT)->getBoundingBox());
			if(projectileBox.left > enemyBox.left && projectileBox.left < enemyBox.left + enemyBox.width &&
				projectileBox.top > enemyBox.top && projectileBox.top < enemyBox.top + enemyBox.height)
			{
				(*enemyIT)->takeDamage((*lit)->getDamage());
				(*lit)->dead = true;
			}
		}
	}
}