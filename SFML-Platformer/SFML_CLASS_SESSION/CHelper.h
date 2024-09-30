#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class FontHelper
{
public:
	sf::Font* mainFont = new sf::Font();
	void LoadFont() { mainFont->loadFromFile("");}
};

class CHelper
{
private:
	//this stuff makes it singlton
	CHelper() = default;
	CHelper(const CHelper&) = delete;
	CHelper& operator =(const CHelper&) = delete;

public:
	//this also helps it be singleton
	static CHelper& getInstance() { static CHelper instance; return instance;}

	float m_GravityValue = 9.81f;
	sf::Clock GlobalClock;
	float m_DeltaTme = 0.0f;

	void CHelperUpdate()
	{
		m_DeltaTme = GlobalClock.getElapsedTime().asSeconds();
		GlobalClock.restart();
	}
};