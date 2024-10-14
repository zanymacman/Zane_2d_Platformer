#pragma once
#include "CObject.h"

enum EnemyType
{
	Walker,
	Runner,
	Tank
};

class CEnemy : public CObject
{
public:
	
	CEnemy();
	CEnemy(sf::Vector2f _Size, sf::Vector2f _Position, float _Speed, int _Hp);
	~CEnemy();

	void Update(sf::RenderWindow* _Window) override;

	float GetSpeed();
	void SetSpeed(float _Speed);
	int GetHp();
	void SetHp(int _Hp);
	sf::Vector2f GetTargetPos();
	void SetTargetPos(sf::Vector2f _TargetPos);

protected:
	float m_MoveSpeed = 5.0f;
	int m_Hp = 10;

	sf::Vector2f m_TargetPosition;
};
