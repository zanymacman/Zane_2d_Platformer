#include "CEnemy.h"

CEnemy::CEnemy()
{
	m_MoveSpeed = 5;
	m_Hp = 5;
}

CEnemy::CEnemy(sf::Vector2f _Size, sf::Vector2f _Position, float _Speed, int _Hp) : CObject (_Size, _Position)
{
	m_MoveSpeed = _Speed;
	m_Hp = _Hp;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(sf::RenderWindow* _Window)
{
	//calculate movement vector
	sf::Vector2f MoveVector = m_TargetPosition - m_ObjectShape.getPosition();

	float x = MoveVector.x;
	float y = MoveVector.y;
	sf::Vector2f NormalizedMoveVector = sf::Vector2f(x/sqrt((x*x)+(y*y)), y/(sqrt((x*x)+(y*y))));

	//actually do the move move
	//X Axis first
	m_ObjectShape.move(NormalizedMoveVector.x * m_MoveSpeed * CTimeKeeper::getInstance().m_DeltaTme, 0);
	//Then Y Axis
	m_ObjectShape.move(0, NormalizedMoveVector.y * m_MoveSpeed * CTimeKeeper::getInstance().m_DeltaTme);

	//get distance to target location
	float a = abs(m_ObjectShape.getPosition().x) - m_TargetPosition.x;
	float b = abs(m_ObjectShape.getPosition().y) - m_TargetPosition.y;
	float Distance = sqrt((a * a) + (b * b));

	if (Distance <= m_MoveSpeed)
	{

	}
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

sf::Vector2f CEnemy::GetTargetPos()
{
	return m_TargetPosition;
}

void CEnemy::SetTargetPos(sf::Vector2f _TargetPos)
{
	m_TargetPosition = _TargetPos;
}
