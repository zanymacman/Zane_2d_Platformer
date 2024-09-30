#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "CPlayer.h"

class CUIManager
{
private:
	CPlayer* m_TrackedPlayer;

	sf::Texture m_LifeUITexture;
	sf::Sprite m_Life1;
	sf::Sprite m_Life2;
	sf::Sprite m_Life3;

	sf::Texture m_ArrowUITexture;
	sf::Sprite m_Arrow1;
	sf::Sprite m_Arrow2;
	sf::Sprite m_Arrow3;

public:
	CUIManager();
	CUIManager(CPlayer* _TrackedPlayer);
	~CUIManager();

	void SetTrackedPlayer(CPlayer* _Player);

	CPlayer* GetTrackedPlayer();

	void DrawPlayerHealth(sf::RenderWindow* _Window);

	void DrawPlayerArrowStock(sf::RenderWindow* _Window);
};