#pragma once
#include "../stdafx.h"

#include "Movable.hpp"

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

class Player: public Movable
{
public:
	Player(sf::Sprite sprite);
	~Player();
private:

};

Player::Player(sf::Sprite sprite):
	Movable(sprite)
{

}

Player::~Player()
{

}