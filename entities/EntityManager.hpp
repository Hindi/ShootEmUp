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

	void createBorder(sf::Rect<int> rectangle);
	void draw();
	void update();
	std::vector< std::shared_ptr<Entity> > getEntities();
	Player& getPlayer();

private:
	ImageManager &m_imageManager;
	sf::RenderWindow& m_window;
	std::vector< std::shared_ptr<Entity> > m_entities;
	Player& m_player;
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
	sf::Sprite entSprite(m_imageManager.getTexture("images/border template.png", textRect));
	std::shared_ptr<Entity> ent( new Entity(entSprite));
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