#pragma once
#include "stdafx.h"
#include "entities/Player.hpp"
#include "entities\EntityManager.hpp"

class InputManager
{
public:
	InputManager(EntityManager& entMan, sf::RenderWindow& window, sf::Event& event);
	~InputManager();

	//!Check the inputs
	void update();

private:
	//! The entityManager
	EntityManager& m_entityManager;
	//! The player
	Player& m_player;
	//! The RenderWindow events
	sf::Event& m_event;
	//! The RenderWindow
	sf::RenderWindow& m_window;
};

InputManager::InputManager(EntityManager& entMan, sf::RenderWindow& window, sf::Event& event):
		m_entityManager(entMan),
		m_player(m_entityManager.getPlayer()),
		m_event(event),
		m_window(window)
{

}

InputManager::~InputManager()
{

}

void InputManager::update()
{
	while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_window.close();
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_window.close();

	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		int acceleration(15);
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		if(x < 100 && x > -100)
			x =0;
		else if(x > 0)
			x = acceleration;
		else
			x = -acceleration;
		if(y < 100 && y > -100)
			y =0;
		else if(y > 0)
			y = acceleration;
		else
			y = -acceleration;
		m_player.setAcceleration(sf::Vector2f(x,y));
		if(x == 0 && y == 0)
			m_player.decelerate();
	}
	else
	{
		int up(0), down(0), left(0), right(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			left = -100;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			right = 100;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			up = -100;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			down = 100;
		m_player.setVelocity(sf::Vector2f(left + right,up + down));
	}
}