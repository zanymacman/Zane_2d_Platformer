#pragma once
#include "CObject.h"
class CWall : public CObject
{
public:
	CWall();
	CWall(sf::Vector2f _Size, sf::Vector2f _Position);
	~CWall();

	bool IsWall() override;
};
