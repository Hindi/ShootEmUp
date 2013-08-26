#pragma once

#include "../stdafx.h"
#include "Ennemy.hpp"
#include "Player.hpp"

template <typename T>
class Quadtree 
{
public:
	Quadtree(int pLevel, sf::Rect<int> pBounds);
	void clear();
	void split();
	void insert(std::shared_ptr<T> ent);
	void update();
	std::vector< std::shared_ptr<T> > canCollide(sf::Rect<float> pRect);
	void draw(sf::RenderWindow& window);

private:
	int getIndex(sf::Rect<float> pRect);
	int MAX_OBJECTS;
	int MAX_LEVELS;
 
	int level;
	std::vector< std::shared_ptr<T> > m_entities;
	sf::Rect<int> bounds;
	std::vector<std::shared_ptr<Quadtree> > m_nodes;
};

template <typename T>
Quadtree<T>::Quadtree(int pLevel, sf::Rect<int> pBounds) 
{
	MAX_LEVELS = 5;
	MAX_OBJECTS = 5;
	level = pLevel;
	bounds = pBounds;
}

template <typename T>
void Quadtree<T>::clear()
{
	m_entities.clear();
	std::vector<std::shared_ptr<Quadtree> >::iterator it(m_nodes.begin());
	for(; it != m_nodes.end();)
	{
		(*it)->clear();
		it = m_nodes.erase(it);
	}
}

template <typename T>
void Quadtree<T>::split() 
{
   int subWidth = bounds.width / 2;
   int subHeight = bounds.height / 2;
   int x = bounds.left;
   int y = bounds.top;
   
   m_nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(level+1, sf::Rect<int>(x + subWidth, y, subWidth, subHeight))));
   m_nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(level+1, sf::Rect<int>(x, y, subWidth, subHeight))));
   m_nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(level+1, sf::Rect<int>(x, y + subHeight, subWidth, subHeight))));
   m_nodes.push_back(std::shared_ptr<Quadtree>(new Quadtree(level+1, sf::Rect<int>(x + subWidth, y + subHeight, subWidth, subHeight))));
 }

template <typename T>
int Quadtree<T>::getIndex(sf::Rect<float> pRect) 
{
   int index = -1;
   double verticalMidpoint = bounds.left + (bounds.width / 2);
   double horizontalMidpoint = bounds.top + (bounds.height / 2);
 
   // Object can completely fit within the top quadrants
   bool topQuadrant = (pRect.top < horizontalMidpoint && pRect.top + pRect.height < horizontalMidpoint);
   // Object can completely fit within the bottom quadrants
   bool bottomQuadrant = (pRect.top > horizontalMidpoint);
 
   // Object can completely fit within the left quadrants
   if (pRect.left < verticalMidpoint && pRect.left + pRect.width < verticalMidpoint) {
      if (topQuadrant) {
        index = 1;
      }
      else if (bottomQuadrant) {
        index = 2;
      }
    }
    // Object can completely fit within the right quadrants
    else if (pRect.left > verticalMidpoint) {
     if (topQuadrant) {
       index = 0;
     }
     else if (bottomQuadrant) {
       index = 3;
     }
   }
 
   return index;
 }

template <typename T>
void Quadtree<T>::insert(std::shared_ptr<T> ent) 
{
	if (m_nodes.size()>0) 
	{
		int index = getIndex(ent->getBoundingBox());
     if (index != -1) {
       m_nodes[index]->insert(ent);
 
       return;
     }
   }
 
   m_entities.push_back(ent);
 
   if (m_entities.size() > MAX_OBJECTS && level < MAX_LEVELS) 
   {
	   if (m_nodes.size() == 0) 
	   { 
         split(); 
      }
	
	 std::vector< std::shared_ptr<T> >::iterator it(m_entities.begin());
     for(; it != m_entities.end();)
	 {
		int index = getIndex((*it)->getBoundingBox());
		if (index != -1) 
		{
			m_nodes[index]->insert((*it));
			it = m_entities.erase(it);
		}
		else
			it++;
     }
   }
 }

template <typename T>
void Quadtree<T>::update() 
{
	for(int n(0); n < m_nodes.size(); ++n)
		m_nodes[n]->update();
	std::vector< std::shared_ptr<T> >::iterator it(m_entities.begin());
     for(; it != m_entities.end();)
	 {
		if (!(*it)->isAlive()) 
			it = m_entities.erase(it);
		else
			it++;
     }
}

template <typename T>
std::vector< std::shared_ptr<T> > Quadtree<T>::canCollide(sf::Rect<float> pRect) 
{
	std::vector< std::shared_ptr<T> > result;
	int index = getIndex(pRect);
	if (index != -1 && m_nodes.size() > 0) 
		result = m_nodes[index]->canCollide(pRect);

	for(int e(0); e < m_entities.size(); ++e)
		result.push_back(m_entities[e]);
 
	return result;
 }

template <typename T>
void Quadtree<T>::draw(sf::RenderWindow& window)
{
	std::vector< std::shared_ptr<T> >::iterator it(m_entities.begin());
	for(int n(0); n < m_nodes.size(); ++n)
		m_nodes[n]->draw(window);
    for(; it != m_entities.end();++it)
	{
		(*it)->draw(window);
    }
}