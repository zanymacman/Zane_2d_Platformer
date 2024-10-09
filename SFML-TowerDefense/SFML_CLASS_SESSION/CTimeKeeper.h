#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class CTimeKeeper
{
private:
	//this stuff makes it singlton
	CTimeKeeper() = default;
	CTimeKeeper(const CTimeKeeper&) = delete;
	CTimeKeeper& operator =(const CTimeKeeper&) = delete;

public:
	//this also helps it be singleton
	static CTimeKeeper& getInstance() { static CTimeKeeper instance; return instance; }

	float m_GravityValue = 9.81f;
	sf::Clock GlobalClock;
	float m_DeltaTme = 0.0f;

	void CTimeKeeperUpdate()
	{
		m_DeltaTme = GlobalClock.getElapsedTime().asSeconds();
		GlobalClock.restart();
	}
};