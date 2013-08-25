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
	int acceleration(15);
	if (sf::Joystick::isConnected(0))
	{
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
		//Update the focus direction if the player moves the pad
		sf::Vector2f focus(sf::Joystick::getAxisPosition(0, sf::Joystick::Z),sf::Joystick::getAxisPosition(0, sf::Joystick::R));
		if(focus.y > 10 || focus.y < -10 || focus.x > 10 || focus.x < -10)
		{
			sf::Vector2f dir(0,0);
			dir.x = focus.x + m_player.getPosition().x;
			dir.y = focus.y + m_player.getPosition().y;
			m_player.updateFocusDirection(dir);
		}

		if(sf::Joystick::isButtonPressed(0,7))//tir en R2
			m_player.fire();

	}
	else
	{
		int x(0), y(0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			x = -acceleration;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			x = acceleration;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			y = -acceleration;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			y = acceleration;
		m_player.setAcceleration(sf::Vector2f(x,y));
		if(x == 0 && y == 0)
			m_player.decelerate();
		//Update the focus direction
		sf::Vector2f mousePos;
		mousePos.x = sf::Mouse::getPosition().x - m_window.getPosition().x;
		mousePos.y = sf::Mouse::getPosition().y - m_window.getPosition().y;
		m_player.updateFocusDirection(mousePos);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_player.fire();
	}
}