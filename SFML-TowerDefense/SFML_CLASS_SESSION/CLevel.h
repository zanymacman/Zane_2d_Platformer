#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "CEnemy.h"
#include "CTower.h"
#include "CBackground.h"

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

	void DrawLevel(sf::RenderWindow* _Window);

	std::vector<CTower*> m_Towers;
	std::vector<CEnemy*> m_Enemies;
	std::vector<CBackground*> m_Backgrounds;

protected:
	static const int LevelWidth = 20;
	static const int LevelHeight = 20;

	char levelArray[LevelWidth][LevelHeight];

	int m_CurrentLevelID = 0;
};