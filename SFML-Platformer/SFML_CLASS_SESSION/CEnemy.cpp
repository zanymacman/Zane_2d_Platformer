#include "CEnemy.h"


CEnemy::CEnemy(sf::Vector2f _size, sf::Vector2f _position, ObjType _Type, bool _Dynamic) : CObject(_size, _position, _Type, _Dynamic)
{
	m_ObjectShape.setFillColor(sf::Color(128,128,128));
	m_ObjectVelocity.x = 1.0f;
	m_EnemyType = _Type;
}

CEnemy::~CEnemy()
{
}

void CEnemy::SetTrackedPlayer(CPlayer* _trackedPlayer)
{
	m_trackedPlayer = _trackedPlayer;
}

void CEnemy::EnemyJump()
{
	m_ObjectShape.move(0, -0.2);
	m_YVelocity = -m_EnemyJumpheight;
}

void CEnemy::Render(sf::RenderWindow* _window)
{
	_window->draw(m_ObjectShape);
}

void CEnemy::Update(sf::RenderWindow* _window)
{
	float trackedPlayerX = m_trackedPlayer->m_ObjectVelocity.x;
	float runDir = 1.0f;
	fleeTimer -= 1.0f / 60.0f;
	if (trackedPlayerX > 0.1f || trackedPlayerX < -.1f)
	{
		fleeTimer = fleeLength;
	}

	if (fleeTimer > 0.0f)//if fleeing, run away
	{
		runDir = -2.0f;
		float distanceMoved = previousPositionX - m_ObjectShape.getPosition().x;
		cowerTimer -= CHelper::getInstance().m_DeltaTme;
		if (abs(distanceMoved) > 0.01f)
		{
			cowerTimer = cowerLength;
		}
	}
	previousPositionX = m_ObjectShape.getPosition().x;

	if (runDir == -2.0f && runDir != previousRunDir)
	{
		EnemyJump();
	}
	previousRunDir = runDir;

	//get player position, calculate speed and set it
	float playerX = m_trackedPlayer->m_ObjectShape.getPosition().x ;
	float enemyX = m_ObjectShape.getPosition().x;
	float dirX = playerX - enemyX;
	m_ObjectVelocity.x = dirX / abs(dirX) * m_EnemySpeed * runDir;//set enemy move speed

	if (fleeTimer > 0.0f && cowerTimer < 0.0f)
	{
		float x = ((double)rand() / (RAND_MAX));//randomise the shaking
		x = ((x * 2.0f) - 1.0f) * 3;
		float y = ((double)rand() / (RAND_MAX));//randomise the vertical shaking
		y = ((y * 2.0f) - 1.0f);
		m_ObjectVelocity.x = x;
		m_ObjectVelocity.y = y;
	}

	if (m_YVelocity > 0.0f && m_YVelocity < 13.0f)// max gravity
	{
		m_YVelocity *= 1 + m_FallScaler * CHelper::getInstance().m_DeltaTme;
	}
}