#pragma once
#include "CPlayer.h"

class CEnemy : public CObject

{
public:
	CEnemy(sf::Vector2f _size, sf::Vector2f _position, ObjType _Type, bool _Dynamic);
	~CEnemy();

	void SetTrackedPlayer(CPlayer* _trackedPlayer);

	void EnemyJump();

	void Render(sf::RenderWindow* _window) override;
	void Update(sf::RenderWindow* _window) override;

private:
	float m_FallScaler = 2.5f;
	float m_EnemySpeed = 1.0f;
	float m_EnemyJumpheight = 2.5f;

	ObjType m_EnemyType;

	float previousRunDir = 0.0f;
	float fleeTimer = 1.0f;
	float cowerTimer = 1.0f;

	float fleeLength = 1.0f;
	float cowerLength = 0.5f;

	float previousPositionX = 0.0f;

	CPlayer* m_trackedPlayer;
};