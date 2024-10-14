#pragma once
#include "CObject.h"
class CTower : public CObject
{
public:
	
	CTower();
	CTower(sf::Vector2f _Size, sf::Vector2f _Position);
	~CTower();
};
