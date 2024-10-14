#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include "CMovementIntergration.h"
#include "CTower.h"
#include "CBackground.h"
#include "CWall.h"

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Loadlevel(std::string _FilePath);
	void UnloadLevel();
	void CreateLevel();
	void ResetLevel();

	int GetCurrentLevel();
	void SetCurrentLevel(int _LevelID);

	sf::Vector2f GetLevelSpawn();
	void SetLevelSpawn(sf::Vector2f _NewSpawn);

	void DrawLevel(sf::RenderWindow* _Window);

	void SpawnEnemy(EnemyType _Type);

	//vectors to use for collisions, pathing, and level loading
	std::vector<CWall*> m_Walls;
	std::vector<CTower*> m_Towers;
	std::vector<CEnemy*> m_Enemies;
	std::vector<CBackground*> m_Paths;

protected:
	static const int LevelWidth = 20;
	static const int LevelHeight = 20;

	sf::Vector2f m_LevelSpawn;

	char levelArray[LevelWidth][LevelHeight];

	int m_PathNum = 0;

	int m_CurrentLevelID = 0;
};