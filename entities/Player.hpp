#pragma once
#include "../stdafx.h"

#include "Armed.hpp"
#include "ProjectileManager.hpp"

/*! 
 *  \brief     The player
 *  \details   Stores player characteristics
 *  \author    Vincent Studer
 *  \date      2013
 *  \pre       None
 *  \bug       None
 *  \warning   None
 *  \copyright GNU Public License.
 */

class Player: public Armed
{
public:
	Player(sf::Texture& texture, ProjectileManager& projManager);
	~Player();
	void draw(sf::RenderWindow &window);


private:
	sf::Shader m_shader;
};

Player::Player(sf::Texture& texture, ProjectileManager& projManager):
	Armed(texture, projManager)
{
	m_fireRate = 100;
	m_maxSpeed = 150;
	m_maxAcceleration = 5;
	m_deceleration = 4;

	updateFocusDirection(sf::Vector2f(100,0));

	if (sf::Shader::isAvailable())
	{
		m_shader.setParameter("texture", sf::Shader::CurrentTexture);
		if (m_shader.loadFromFile("images/shaders/wave.vert", "images/shaders/blur.frag"))
		{
			m_shader.setParameter("wave_phase", 0.1);
			m_shader.setParameter("wave_amplitude", 1, 1);
			m_shader.setParameter("blur_radius", (2 + 2) * 0.008f);
		}
	}
}

Player::~Player()
{

}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite, &m_shader);
}