#pragma once
#include <fstream>
#include "CTile.h"
#include "CPlayer.h"
#include "CArrow.h"
#include "CEnemy.h"

class CLevel
{
public:
	static const int levelWidth = 58;
	static const int levelHeight = 9;

	std::vector<CObject*> m_Objects; // All objects are stored here for collisions, physics, and other misc fun things woo!

	char levelArray[levelWidth][levelHeight];

	CPlayer* m_PlayerRef;

	CLevel();
	~CLevel();

	void Loadlevel(std::string _FilePath);
	void UnloadLevel();
	void CreateLevel();
	void ResetLevel();

	int GetCurrentLevel();
	void SetCurrentLevel(int _LevelID); 

	void RenderBackground(sf::RenderWindow* _Window);
	void RenderForground(sf::RenderWindow* _Window);

	void CollisionIntergration(std::vector<CObject*> _Objects);
	void MovementIntergration(std::vector<CObject*> _Objects);

private:
	int m_CurrentLevelID = 1;
};