#pragma once
#include "CObject.h"

class CBackground : public CObject
{
public:
	CBackground();
	CBackground(sf::Vector2f _Size, sf::Vector2f _Position);
	~CBackground();

protected:
	bool m_Path;
};

