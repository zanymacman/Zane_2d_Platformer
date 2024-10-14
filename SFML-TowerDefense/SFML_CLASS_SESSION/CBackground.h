#pragma once
#include "CObject.h"

class CBackground : public CObject
{
public:
	CBackground();
	CBackground(sf::Vector2f _Size, sf::Vector2f _Position);
	~CBackground();

	int GetPath();
	void SetPath(int _pathNum);
protected:
	int m_Path = 0;
};
