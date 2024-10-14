#include "CBackground.h"

CBackground::CBackground()
{
}

CBackground::CBackground(sf::Vector2f _Size, sf::Vector2f _Position) : CObject(_Size, _Position)
{

}

CBackground::~CBackground()
{
}

int CBackground::GetPath()
{
	return m_Path;
}

void CBackground::SetPath(int _pathNum)
{
	m_Path = _pathNum;
}
