#include "CPlayer.h"


CPlayer::CPlayer(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic) : CObject(_Size, _Position, _Type, _Dynamic)
{
	m_ObjectShape.setFillColor(sf::Color::White);
	m_ObjectTexture.loadFromFile("Sprites/SpriteSheet.png");
	m_ObjectShape.setTexture(&m_ObjectTexture);
	m_ObjectShape.setTextureRect(sf::IntRect(84, 0, 39, 65));

	m_AnimationRect.top = 0;
	m_AnimationRect.left = 84;
	m_AnimationRect.width = 39;
	m_AnimationRect.height = 65;

	m_ObjectType = Player;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Input()
{
	m_ObjectVelocity = sf::Vector2f(0, 0);
	m_CurrentPlayerAnimationState = Idle;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_ObjectVelocity.y = -m_PlayerSpeed;
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))   ---   player down move discabled. may return if needed
	{
		m_ObjectVelocity.y = m_PlayerSpeed;
	}*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_FacingRight = false;
		m_CurrentPlayerAnimationState = Moving_L;
		m_ObjectVelocity.x = -m_PlayerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_FacingRight = true;
		m_CurrentPlayerAnimationState = Moving_R;
		m_ObjectVelocity.x = m_PlayerSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (m_Grounded)
		{
			Jump();
			SetGrounded(false);
		}
		else
		{
			std::cout << " NOT GROUNDED!!!\n";
		}
	}
}

void CPlayer::Jump()
{
	m_ObjectShape.move(0, -0.2);
	m_YVelocity = -m_PlayerJumpheight;
}

CArrow* CPlayer::Shoot()
{
	CArrow* newArrow = new CArrow(sf::Vector2f(64, 12), m_ObjectShape.getPosition(), Arrow, true, m_FacingRight);
	return newArrow;
}

int CPlayer::GetArrowCount()
{
	return m_ArrowCount;
}

void CPlayer::SetArrowCount(int _NewCount)
{
	m_ArrowCount = _NewCount;
}

int CPlayer::GetPlayerLives()
{
	return m_PlayerLives;
}

void CPlayer::SetPlayerLives(int _Lives)
{
	m_PlayerLives = _Lives;
}

void CPlayer::SetInvul()
{
	if (m_IFrames == m_IFramesMax)
	{
		m_IFrames = 0;
		m_Invul = true;
		m_ObjectShape.setFillColor(sf::Color::Red);
	}
}

bool CPlayer::GetInvul()
{
	return m_Invul;
}

void CPlayer::Render(sf::RenderWindow* _Window)
{
	_Window->draw(m_ObjectShape);
}

void CPlayer::Update(sf::RenderWindow* _Window)
{
	Input();
	AnimateCharacter();

	if (m_YVelocity > 0.0f && m_YVelocity < 13.0f)// max gravity
	{
		m_YVelocity *= 1 + m_FallScaler * CHelper::getInstance().m_DeltaTme;
	}

	if (m_IFrames < m_IFramesMax)
	{
		m_IFrames++;
	}
	else//reset color with iframe end
	{
		m_ObjectShape.setFillColor(sf::Color::White);
		m_Invul = false;
	}
}

void CPlayer::AnimateCharacter()
{
	switch (m_CurrentPlayerAnimationState)
	{
	case Moving_R:
		if (m_AnimationClock.getElapsedTime().asSeconds() > 0.125f)
		{
			if (m_AnimationRect.left < 502)
			{
				m_AnimationRect.left += 70;
			}
			else if (m_AnimationRect.left >= 502)
			{
				m_AnimationRect.left = 82;
			}
			m_ObjectShape.setTextureRect(m_AnimationRect);
			m_AnimationClock.restart();
		}
		break;
	case Moving_L:
		m_ObjectShape.setTextureRect(sf::IntRect(m_AnimationRect.left + m_AnimationRect.width, 
											     m_AnimationRect.top, -m_AnimationRect.width, m_AnimationRect.height));
		if (m_AnimationClock.getElapsedTime().asSeconds() > 0.125f)
		{
			if (m_AnimationRect.left < 502)
			{
				m_AnimationRect.left += 70;
			}
			else if (m_AnimationRect.left >= 502)
			{
				m_AnimationRect.left = 82;
			}
			m_AnimationClock.restart();
		}
		break;
	case Idle:

		break;
	case Jumping_Up:
		break;

	case Jumping_Down:
		break;
	}
}
