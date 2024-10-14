#pragma once
#include "CObject.h"
class CEnemy : public CObject
{
public:
	
	CEnemy();
	CEnemy(sf::Vector2f _Size, sf::Vector2f _Position, float _Speed, int _Hp);
	~CEnemy();

	float GetSpeed();
	void SetSpeed(float _Speed);
	int GetHp();
	void SetHp(int _Hp);

protected:
	float m_MoveSpeed = 5.0f;
	int m_Hp = 10;
};
