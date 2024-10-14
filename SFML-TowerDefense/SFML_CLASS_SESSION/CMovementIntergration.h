#pragma once
#include <SFML/Graphics.hpp>
#include "CEnemy.h"

class CMovementIntergration
{
private:
	//this stuff makes it singlton
	CMovementIntergration() = default;
	CMovementIntergration(const CMovementIntergration&) = delete;
	CMovementIntergration& operator =(const CMovementIntergration&) = delete;

public:
	//this also helps it be singleton
	static CMovementIntergration& getInstance() { static CMovementIntergration instance; return instance; }

	void Movement(std::vector<CEnemy*> _Enemies);
};

