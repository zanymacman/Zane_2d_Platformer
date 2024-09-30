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

	std::vector<CTile*> m_LevelCollisionTiles; // Every tile to be collided with
	std::vector<CTile*> m_LevelBackgroundTiles; // Tiles to not collide with, are for backhground
	std::vector<CObject*> g_Objects; // All objects
	std::vector<CTile*> g_Tile; // All Tiles

	//physics and collision vectors
	CPhysics g_PhysicsHandler;

	char levelArray[levelWidth][levelHeight];

	CPlayer* m_PlayerRef;

	CLevel();
	~CLevel();

	void Loadlevel(std::string _FilePath);
	void CreateLevel();

	void RenderBackground(sf::RenderWindow* _Window);
	void RenderForground(sf::RenderWindow* _Window);
	void UnloadLevel();
};