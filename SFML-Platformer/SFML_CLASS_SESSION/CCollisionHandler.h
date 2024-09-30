#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CObject.h"
static class CCollisionHandler
{
public:
	static void ResolveXCollisions(sf::Shape* _ObjA, sf::FloatRect* _ObjB)// Horizontal movement AFTER already knowing there IS a collision
	{
		sf::Vector2f EntityACentre = 
		{ 
			(_ObjA->getGlobalBounds().left + _ObjA->getGlobalBounds().width / 2.0f),
			(_ObjA->getGlobalBounds().top + _ObjA->getGlobalBounds().height / 2.0f) 
		};

		sf::Vector2f EntityBCentre = 
		{ 
			(_ObjB->left + _ObjB->width / 2.0f),
			(_ObjB->top + _ObjB->height / 2.0f) 
		};

		if (EntityACentre.x <= EntityBCentre.x)//If left
		{
			float offset = -(_ObjA->getGlobalBounds().left + _ObjA->getGlobalBounds().width - _ObjB->left);
			_ObjA->move(offset, 0);
		}

		if (EntityACentre.x >= EntityBCentre.x)//if Right
		{
			float offset = (_ObjB->left + _ObjB->width - _ObjA->getGlobalBounds().left);
			_ObjA->move(offset, 0);
		}
	}

	static void ResolveYCollisions(sf::Shape* _ObjA, sf::FloatRect* _ObjB) //Vertical Movement AFTER already knowing there IS a collision
	{
		sf::Vector2f EntityACentre = 
		{ 
			(_ObjA->getGlobalBounds().left + _ObjA->getGlobalBounds().width / 2.0f),
			(_ObjA->getGlobalBounds().top + _ObjA->getGlobalBounds().height / 2.0f) 
		};

		sf::Vector2f EntityBCentre = 
		{ 
			(_ObjB->left + _ObjB->width / 2.0f),
			(_ObjB->top + _ObjB->height / 2.0f) 
		};

		if (EntityACentre.y <= EntityBCentre.y)//if above
		{
			float offset = -(_ObjA->getGlobalBounds().top + _ObjA->getGlobalBounds().height - _ObjB->top);
			_ObjA->move(0, offset);
		}
		if (EntityACentre.y >= EntityBCentre.y)//if below
		{
			float offset = (_ObjB->top + _ObjB->height - _ObjA->getGlobalBounds().top);
			_ObjA->move(0, offset);
		}
	}
};