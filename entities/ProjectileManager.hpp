#pragma once
#include "../stdafx.h"

#include "Projectile.hpp"
#include "../ImageManager.hpp"

/*! 
 *  \brief     The projectile manager class
 *  \details   Stores projectiles and update their positions
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class ProjectileManager
{
public:
	ProjectileManager(ImageManager& imageMan, sf::RenderWindow& window);
	//! Draw all the projectiles on screen
	void draw();
	//! Update all the projectiles
	void update();
	//! Return m_projectiles
	std::vector< std::shared_ptr<Projectile> >& getProjectiles();
	//! Create a simple projectile
	void createProjectile(sf::Vector2f position, sf::Vector2f direction);
private:
	std::vector< std::shared_ptr<Projectile> > m_projectiles;
	ImageManager& m_imageManager;
	//! This clock is used to keep the movement speed from changing when framrate changes
	sf::Clock m_clock;
	//! The RenderWindow
	sf::RenderWindow& m_window;
	sf::Texture m_projectileTexture;
};

ProjectileManager::ProjectileManager(ImageManager& imageMan, sf::RenderWindow& window):
		m_imageManager(imageMan),
		m_window(window)
{
	m_projectileTexture.loadFromImage(m_imageManager.getImage("images/projectile.png"));
}
	
void ProjectileManager::draw()
{
	for(int e(0); e < m_projectiles.size(); ++e)
		m_projectiles[e]->draw(m_window);
}

std::vector< std::shared_ptr<Projectile> >& ProjectileManager::getProjectiles()
{
	return m_projectiles;
}

void ProjectileManager::update()
{
	std::vector< std::shared_ptr<Projectile> >::iterator lit(m_projectiles.begin());
	float elapsedTime = m_clock.getElapsedTime().asSeconds();
	for(; lit != m_projectiles.end();)
		if((*lit)->dead)
			lit = m_projectiles.erase(lit);
		else
		{
			(*lit)->move(elapsedTime);
			lit++;
		}
	m_clock.restart();
}


void ProjectileManager::createProjectile(sf::Vector2f position, sf::Vector2f direction)
{
	std::cout << m_projectiles.size() << std::endl;
	std::shared_ptr<Projectile> proj(new Projectile(m_projectileTexture, position, direction));
	m_projectiles.push_back(proj);
}