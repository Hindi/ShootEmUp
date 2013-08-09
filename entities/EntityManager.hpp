#pragma once
#include "../stdafx.h"
#include "Entity.hpp"
#include "Player.hpp"
#include "../ImageManager.hpp"

/*! 
 *  \brief     Manage the entities
 *  \details   
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class EntityManager
{
public:
	EntityManager(ImageManager &imageManager, sf::RenderWindow &window, Player &player);
	~EntityManager();

	//! Create a border that'll occupy the rectange in parameter
	void createBorder(sf::Rect<int> rectangle);
	//! Draw all the entities on screen
	void draw();
	//! Update all the entities
	void update();
	//! Return m_entities
	std::vector< std::shared_ptr<Entity> > getEntities();
	//! Return a reference to the player
	Player& getPlayer();

private:
	//! The ImageManager
	ImageManager &m_imageManager;
	//! The RenderWindow
	sf::RenderWindow& m_window;
	//! Where all the entities are stored
	std::vector< std::shared_ptr<Entity> > m_entities;
	//! The player
	Player& m_player;
	//! This clock is used to keep the movement speed from changing when framrate changes
	sf::Clock m_clock;
};

EntityManager::EntityManager(ImageManager &imageManager, sf::RenderWindow &window, Player &player):
			m_imageManager(imageManager),
			m_window(window),
			m_player(player)
{
	
}

EntityManager::~EntityManager()
{

}

void EntityManager::createBorder(sf::Rect<int> rectangle)
{
	sf::Rect<int> textRect(0, 0, rectangle.width, rectangle.height);
	std::shared_ptr<Entity> ent( new Entity(m_imageManager.getTexture("images/border template.png", textRect)));
	ent->setPosition(sf::Vector2f(rectangle.left, rectangle.top));
	m_entities.push_back(ent);
}

void EntityManager::draw()
{
	for(int e(0); e < m_entities.size(); ++e)
		m_entities[e]->draw(m_window);
	m_player.draw(m_window);
}

std::vector< std::shared_ptr<Entity> > EntityManager::getEntities()
{
	return m_entities;
}

Player& EntityManager::getPlayer()
{
	return m_player;
}

void EntityManager::update()
{
	m_player.move(m_clock.getElapsedTime().asSeconds());
	m_clock.restart();
}