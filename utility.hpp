#pragma once
#include "stdafx.h"

const float pi = 3.141592653589793238462643383279502884197169399375105820974944;

sf::Vector2f directionToPosition(sf::Vector2f position, sf::Vector2f direction)
{
	direction.x = (direction.x - position.x);
	direction.y = (direction.y - position.y);
	int norm = sqrt(direction.x*direction.x + direction.y*direction.y);
        if(norm==0)
            norm=1;
	direction.x = direction.x/norm;
	direction.y = direction.y/norm;
	return direction;
}

float directionToAngle(sf::Vector2f direction)
{
	return atan2(direction.y, direction.x)*180/pi; 
}

float normalize(sf::Vector2f vec)
{
	return  pow((double)pow(vec.x,2) + pow(vec.y,2), 0.5);
}


int dotProduct(sf::Vector2f vect1, sf::Vector2f vect2)
{
	return vect1.x*vect2.x + vect1.y*vect2.y;
}