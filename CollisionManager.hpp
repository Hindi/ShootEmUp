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

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox (const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
	{
		sf::Transform trans = Object.getTransform();
		sf::IntRect local = Object.getTextureRect();
		Points[0] = trans.transformPoint(0.f, 0.f);
		Points[1] = trans.transformPoint(local.width, 0.f);
		Points[2] = trans.transformPoint(local.width, local.height);
		Points[3] = trans.transformPoint(0.f, local.height);
	}

	sf::Vector2f Points[4];

	void ProjectOntoAxis (const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
	{
		Min = (Points[0].x*Axis.x+Points[0].y*Axis.y);
		Max = Min;
		for (int j = 1; j<4; j++)
		{
			float Projection = (Points[j].x*Axis.x+Points[j].y*Axis.y);

			if (Projection<Min)
				Min=Projection;
			if (Projection>Max)
				Max=Projection;
		}
	}
};

class CollisionManager
{
public:
	CollisionManager(EntityManager& entMan, ProjectileManager& ProjectileManager, sf::Vector2i resolution);
	~CollisionManager();
	//! Use the other methods to check all the collisions
	void update();
	bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

private:
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
	std::vector< std::shared_ptr<Ennemy> > enemies = m_entityManager.getEnemies();

	std::vector< std::shared_ptr<Projectile> >::iterator lit(projectiles.begin());
	std::vector< std::shared_ptr<Ennemy> >::iterator enemyIT = enemies.begin();
		
	for(; lit != projectiles.end();lit++)
	{
		sf::Rect<float> projectileBox((*lit)->getBoundingBox());

		for(; enemyIT != enemies.end(); enemyIT++)
		{
			sf::Rect<float> enemyBox((*enemyIT)->getBoundingBox());
			if(BoundingBoxTest((*lit)->getSprite(), (*enemyIT)->getSprite()))
			{
				(*enemyIT)->takeDamage((*lit)->getDamage());
				(*lit)->dead = true;
			}
		}
		enemyIT = enemies.begin();
	}
}

bool CollisionManager::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
		OrientedBoundingBox OBB1 (Object1);
		OrientedBoundingBox OBB2 (Object2);

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
			OBB1.Points[1].y-OBB1.Points[0].y),
			sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
			OBB1.Points[1].y-OBB1.Points[2].y),
			sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
			OBB2.Points[0].y-OBB2.Points[3].y),
			sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
			OBB2.Points[0].y-OBB2.Points[1].y)
		};

		for (int i = 0; i<4; i++) // For each axis...
		{
			float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

			// ... project the points of both OBBs onto the axis ...
			OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
			OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Seperating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOBB2<=MaxOBB1)&&(MaxOBB2>=MinOBB1)))
				return false;
		}
		return true;
	}

	