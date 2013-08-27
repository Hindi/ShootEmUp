#pragma once
#include "../stdafx.h"

/*! 
 *  \brief     All the drawable objetcs are entities
 *  \details   
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Entity
{
public:
	Entity(sf::Texture& texture);
	~Entity();

	//! Draw the entity on screen
	virtual void draw(sf::RenderWindow &window);
	//! Set the absolute position of the entity
	void setPosition(sf::Vector2f position);
	//! Return the absolute position of the entity
	sf::Vector2f getPosition();
	//! Return the bounding box
	sf::Rect<float> getBoundingBox();
	sf::Sprite& getSprite();
protected:
	//! The sprite of the entity
	sf::Sprite m_sprite;
};

Entity::Entity(sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width/2, m_sprite.getLocalBounds().height/2);
}

Entity::~Entity()
{

}

void Entity::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
 }

void Entity::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

sf::Vector2f Entity::getPosition()
{
	return m_sprite.getPosition();
}

sf::Rect<float> Entity::getBoundingBox()
{
	return m_sprite.getGlobalBounds();
}

sf::Sprite& Entity::getSprite()
{
	return m_sprite;
}