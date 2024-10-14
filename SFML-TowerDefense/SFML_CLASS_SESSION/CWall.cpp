#include "CWall.h"

CWall::CWall()
{
}

CWall::CWall(sf::Vector2f _Size, sf::Vector2f _Position) : CObject(_Size, _Position)
{
}

CWall::~CWall()
{
}

bool CWall::IsWall()
{
	return true;
}
