#pragma once
#include "CTile.h"
#include "CPlayer.h"
#include "CArrow.h"
#include "CEnemy.h"
#include "CPhysics.h"
#include <fstream>

class CLevel
{
public:
	int currentLevelID = 1;

	static const int levelWidth = 20;
	static const int levelHeight = 10;

	std::vector<CObject*> m_Objects; // All objects

	//physics and collision vectors
	CPhysics g_PhysicsHandler;

	char levelArray[levelWidth][levelHeight];

	CPlayer* m_PlayerRef;

	CLevel();
	~CLevel();

	void Loadlevel(std::string _FilePath);
	void UnloadLevel();
	void CreateLevel();

	void RenderBackground(sf::RenderWindow* _Window);
	void RenderForground(sf::RenderWindow* _Window);
};