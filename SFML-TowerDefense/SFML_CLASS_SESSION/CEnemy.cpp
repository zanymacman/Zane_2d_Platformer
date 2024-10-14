#include "CEnemy.h"

CEnemy::CEnemy()
{
}

CEnemy::CEnemy(sf::Vector2f _Size, sf::Vector2f _Position, float _Speed, int _Hp) : CObject (_Size, _Position)
{
	m_MoveSpeed = _Speed;
	m_Hp = _Hp;
}

CEnemy::~CEnemy()
{
}

float CEnemy::GetSpeed()
{
	return m_MoveSpeed;
}

void CEnemy::SetSpeed(float _Speed)
{
	m_MoveSpeed = _Speed;
}

int CEnemy::GetHp()
{
	return m_Hp;
}

void CEnemy::SetHp(int _Hp)
{
	m_Hp = _Hp;
}
