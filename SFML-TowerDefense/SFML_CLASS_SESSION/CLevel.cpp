#include "CLevel.h"

CLevel::CLevel()
{

}

CLevel::~CLevel()
{

}

void CLevel::Loadlevel(std::string _FilePath)
{
	std::fstream loadFileStream;
	loadFileStream.open(_FilePath, std::ios::in);

	std::string loadFileString;
	int lineCount = 0;

	if (loadFileStream.is_open())
	{
		while (std::getline(loadFileStream, loadFileString))
		{
			for (int i = 0; i < loadFileString.size(); i++)
			{
				levelArray[i][lineCount] = loadFileString[i];
			}

			lineCount++;
		}

		loadFileStream.close();
	}

	CreateLevel();
}

void CLevel::UnloadLevel()//iterate through each array and clear them
{
	CEnemy* tempEnemyPtr;

	for (int i = 0; i < m_Enemies.size(); i++)//clear Enemies Vector
	{
		tempEnemyPtr = m_Enemies[i];
			m_Enemies[i] = nullptr;
			delete tempEnemyPtr;
	}
	m_Enemies.clear();

	CTower* tempTowerPtr;
	for (int i = 0; i < m_Towers.size(); i++)//clear Towers Vector
	{
		tempTowerPtr = m_Towers[i];
		m_Towers[i] = nullptr;
		delete tempTowerPtr;
	}
	m_Towers.clear();

	CBackground* tempBackgroundPtr;
	for (int i = 0; i < m_Backgrounds.size(); i++)//clear Backgrounds Vector
	{
		tempBackgroundPtr = m_Backgrounds[i];
		m_Backgrounds[i] = nullptr;
		delete tempBackgroundPtr;
	}
	m_Backgrounds.clear();
}

void CLevel::CreateLevel()//make the level from x/y grid
{
	for (int y = 0; y < LevelHeight; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (levelArray[x][y] == ' ')
			{
				CBackground* newBackground = new CBackground();
			}
		}
	}
}

void CLevel::ResetLevel()//unload and reload current level
{
	UnloadLevel();
	switch (GetCurrentLevel())
	{
	case 1:
		break;
	case 2:
		break;
	}
}

int CLevel::GetCurrentLevel()//return current level id
{
	return m_CurrentLevelID;
}

void CLevel::SetCurrentLevel(int _LevelID)//set currnet level id
{
	m_CurrentLevelID = _LevelID;
}

void CLevel::DrawLevel(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Backgrounds.size(); i++)//draw background
	{
		m_Backgrounds[i]->Render(_Window);
	}
	for (int i = 0; i < m_Towers.size(); i++)//draw Towers
	{
		m_Towers[i]->Render(_Window);
	}
	for (int i = 0; i < m_Enemies.size(); i++)//draw Enemies
	{
		m_Enemies[i]->Render(_Window);
	}
}
