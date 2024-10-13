#pragma once
#include "CObject.h"
class CEnemy : public CObject
{
public:
	
	CEnemy();
	CEnemy(sf::Vector2f _Size, sf::Vector2f _Position);
	~CEnemy();
};

