#include "CObject.h"

CObject::CObject(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic)
{
	m_ObjectShape.setSize(_Size);
	m_ObjectShape.setFillColor(sf::Color::Transparent);
	m_ObjectShape.setPosition(_Position);
	m_Dynamic = _Dynamic;
	m_ObjectType = _Type;

	m_XMove = 0;
	m_YMove = 0;
	m_Movespeed = 0;
	m_StartPos = _Position;
	m_MovingOut = false;
	m_Moving = false;
	m_MovingTimer = 0;
	m_MovingTimerMax = 0;
}

CObject::~CObject()
{
}

void CObject::Render(sf::RenderWindow* _Window)
{
	_Window->draw(m_ObjectShape);
	_Window->draw(m_ObjectSprite);
}

void CObject::Update(sf::RenderWindow* _Window)
{
	if (m_ObjectType == MovingPlatform)
	{
		Move();
	}
}

void CObject::ApplyGravity() // gravtiy intergration
{
	if (m_Dynamic) 
	{
		if (m_YVelocity < 8.0f) 
		{
			m_YVelocity += CHelper::getInstance().m_GravityValue * CHelper::getInstance().m_DeltaTme;
		}
		if (m_ObjectType != MovingPlatform and m_ObjectType != Arrow and m_ObjectType != Platform)
		{
			m_ObjectShape.move(0, m_YVelocity);
		}
	}
}

void CObject::SetTexture(std::string _FilePath)
{
	m_ObjectTexture.loadFromFile(_FilePath);
	m_ObjectShape.setTexture(&m_ObjectTexture);
	m_ObjectShape.setTextureRect(sf::IntRect(m_ObjectShape.getGlobalBounds().left, m_ObjectShape.getGlobalBounds().top, 
											 m_ObjectShape.getGlobalBounds().width, m_ObjectShape.getGlobalBounds().height));
}

void CObject::ToggleDynamic()
{
	m_Dynamic = !m_Dynamic;
}

bool CObject::GetGrounded()
{
	return m_Grounded;
}

void CObject::SetGrounded(bool _IsGrounded)
{
	m_Grounded = _IsGrounded;
}

float CObject::GetYMove()
{
	return m_YMove;
}

void CObject::SetYMove(float _YMove)
{
	m_YMove = _YMove;
}

float CObject::GetXMove()
{
	return m_XMove;
}

void CObject::SetXMove(float _XMove)
{
	m_XMove = _XMove;
}

float CObject::GetMoveSpeed()
{
	return m_Movespeed;
}

void CObject::SetMoveSpeed(float _MoveSpeed)
{
	m_Movespeed = _MoveSpeed;
}

sf::Vector2f CObject::GetStartPos()
{
	return m_StartPos;
}

void CObject::SetStartPos(sf::Vector2f _StartPos)
{
	m_StartPos = _StartPos;
}

bool CObject::GetMovingOut()
{
	return m_MovingOut;
}

void CObject::SetMovingOut(bool _MovingOut)
{
	m_MovingOut = _MovingOut;
}

bool CObject::GetMoving()
{
	return m_Moving;
}

void CObject::SetMoving(bool _Moving)
{
	m_Moving = _Moving;
}

int CObject::GetMovingTimer()
{
	return m_MovingTimer;
}

void CObject::SetMovingTimer(int _MovingTimer)
{
	m_MovingTimer = _MovingTimer;
}

int CObject::GetMovingTimerMax()
{
	return m_MovingTimerMax;
}

void CObject::SetMovingTimerMax(int _TimerMax)
{
	m_MovingTimerMax = _TimerMax;
}

void CObject::BecomeMovingPlatform(float _XMove, float _YMove, float _MoveSpeed, int _MovingTimer, int _TimerMax)
{
	m_XMove = _XMove;
	m_YMove = _YMove;
	m_Movespeed = _MoveSpeed;
	m_MovingOut = true;
	m_Moving = true;
	m_MovingTimer = _MovingTimer;
	m_MovingTimerMax = _TimerMax;
	m_Dynamic = true;
}

void CObject::Move()
{
	if (m_Moving)
	{
		if (m_MovingOut)
		{
			if (m_MovingTimer == 0)
			{
				m_MovingOut = !m_MovingOut;//swap move direction
				m_ObjectVelocity.x = 0;
				m_ObjectVelocity.y = 0;
				m_MovingTimer = m_MovingTimerMax;
			}
			else
			{
				m_MovingTimer--;
				m_ObjectVelocity.x = m_XMove * m_Movespeed * CHelper::getInstance().m_DeltaTme;
				m_ObjectVelocity.y = m_YMove * (m_Movespeed) * CHelper::getInstance().m_DeltaTme;
			}
		}
		else
		{
			if (m_MovingTimer == 0)
			{
				m_MovingOut = !m_MovingOut;//swap move direction
				m_ObjectVelocity.x = 0;
				m_ObjectVelocity.y = 0;
				m_MovingTimer = m_MovingTimerMax;
			}
			else
			{
				m_MovingTimer--;
				m_ObjectVelocity.x = m_XMove * m_Movespeed * CHelper::getInstance().m_DeltaTme * -1;
				m_ObjectVelocity.y = m_YMove * (m_Movespeed) * CHelper::getInstance().m_DeltaTme * -1;
			}
		}
	}
}