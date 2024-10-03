#include "CUIManager.h"

CUIManager::CUIManager()
{
	//copy everything from the below constructor when finished
}

CUIManager::CUIManager(CPlayer* _TrackedPlayer)
{
	m_TrackedPlayer = _TrackedPlayer;

	//set life texture
	if (!m_LifeUITexture.loadFromFile("Sprites/UILifeV1.png"))
	{
		std::cout << "Failed to load LifeUI Image\n";
	}

	m_Life1.setOrigin(sf::Vector2f(0, 0));
	m_Life1.setColor(sf::Color::White);
	m_Life1.setPosition(sf::Vector2f(10, 10));
	m_Life1.setTexture(m_LifeUITexture);

	m_Life2.setOrigin(sf::Vector2f(0, 0));
	m_Life2.setColor(sf::Color::White);
	m_Life2.setPosition(sf::Vector2f(42, 10));
	m_Life2.setTexture(m_LifeUITexture);

	m_Life3.setOrigin(sf::Vector2f(0, 0));
	m_Life3.setColor(sf::Color::White);
	m_Life3.setPosition(sf::Vector2f(74, 10));
	m_Life3.setTexture(m_LifeUITexture);

	//set arrow texture
	if (!m_ArrowUITexture.loadFromFile("Sprites/UIArrowV1.png"))
	{
		std::cout << "Failed to load ArrowUI Image\n";
	}

	m_Arrow1.setOrigin(sf::Vector2f(0, 0));
	m_Arrow1.setColor(sf::Color::White);
	m_Arrow1.setPosition(sf::Vector2f(10, 42));
	m_Arrow1.setTexture(m_ArrowUITexture);

	m_Arrow2.setOrigin(sf::Vector2f(0, 0));
	m_Arrow2.setColor(sf::Color::White);
	m_Arrow2.setPosition(sf::Vector2f(42, 42));
	m_Arrow2.setTexture(m_ArrowUITexture);

	m_Arrow3.setOrigin(sf::Vector2f(0, 0));
	m_Arrow3.setColor(sf::Color::White);
	m_Arrow3.setPosition(sf::Vector2f(74, 42));
	m_Arrow3.setTexture(m_ArrowUITexture);
}

CUIManager::~CUIManager()
{
}

void CUIManager::SetTrackedPlayer(CPlayer* _Player)
{
	m_TrackedPlayer = _Player;
}

CPlayer* CUIManager::GetTrackedPlayer()
{
	return m_TrackedPlayer;
}

void CUIManager::DrawPlayerHealth(sf::RenderWindow* _Window)
{
	if (m_TrackedPlayer->GetPlayerLives() > 0) { _Window->draw(m_Life1); }
	if (m_TrackedPlayer->GetPlayerLives() > 1) { _Window->draw(m_Life2); }
	if (m_TrackedPlayer->GetPlayerLives() > 2) { _Window->draw(m_Life3); }
}

void CUIManager::DrawPlayerArrowStock(sf::RenderWindow* _Window)
{
	if (m_TrackedPlayer->GetArrowCount() > 0) { _Window->draw(m_Arrow1); }
	if (m_TrackedPlayer->GetArrowCount() > 1) { _Window->draw(m_Arrow2); }
	if (m_TrackedPlayer->GetArrowCount() > 2) { _Window->draw(m_Arrow3); }
}

void CUIManager::MoveUI(sf::Vector2f _MoveUIVec)
{
	m_Life1.move(_MoveUIVec);
	m_Life2.move(_MoveUIVec);
	m_Life3.move(_MoveUIVec);
	m_Arrow1.move(_MoveUIVec);
	m_Arrow2.move(_MoveUIVec);
	m_Arrow3.move(_MoveUIVec);
}
