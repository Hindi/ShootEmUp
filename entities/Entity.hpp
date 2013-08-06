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
	Entity(sf::Texture texture);
	~Entity();

	void draw(sf::RenderWindow &window);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

protected:
	sf::Texture& m_texture;
	sf::Sprite m_sprite;
};

Entity::Entity(sf::Texture texture):
	m_texture(texture)
{
	m_sprite.setTexture(m_texture);
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