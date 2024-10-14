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
	for (int i = 0; i < 10; i++)//clear Backgrounds Array
	{
		tempBackgroundPtr = m_Paths[i];
		m_Paths[i] = nullptr;
		delete tempBackgroundPtr;
	};
}

void CLevel::CreateLevel()//make the level from x/y grid
{
	for (int y = 0; y < LevelHeight; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (levelArray[x][y] == 'x')//Create a wall that can't be built on
			{
				CWall* newWall = new CWall(sf::Vector2f(64, 64), sf::Vector2f(x * 64, y * 64));
				newWall->GetShape().setFillColor(sf::Color::White);
				newWall->GetShape().setOutlineColor(sf::Color::Transparent);
				m_Walls.push_back(newWall);
				newWall->SetTexture("Sprites/WallV1.png");
			}
			if (levelArray[x][y] == '1' || levelArray[x][y] == '2' || levelArray[x][y] == '3' || levelArray[x][y] == '4' || levelArray[x][y] == '5' || levelArray[x][y] == '6' || levelArray[x][y] == '7' || levelArray[x][y] == '8' || levelArray[x][y] == '9')
				//create the path and incriment its number, then increase the level path numbers and add it to the path array
			{
				m_PathNum++;
				CBackground* newPath = new CBackground(sf::Vector2f(64, 64), sf::Vector2f(x * 64, y * 64));
				newPath->GetShape().setFillColor(sf::Color::White);
				newPath->GetShape().setOutlineColor(sf::Color::Transparent);
				newPath->SetPath(levelArray[x][y] - '0');//set the path number to be the current read number (char of x/y converted to int by subtracting the vlaye of 0)
				m_Paths.push_back(newPath);//set the path in the correct order, so they can be read sequentially
				newPath->SetTexture("Sprites/FlagV1.png");
				std::cout << newPath->GetPath() << std::endl;

				if (levelArray[x][y] == '1')
				{
					SetLevelSpawn(sf::Vector2f(x * 64, y * 64));
				}
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

sf::Vector2f CLevel::GetLevelSpawn()
{
	return m_LevelSpawn;
}

void CLevel::SetLevelSpawn(sf::Vector2f _NewSpawn)
{
	m_LevelSpawn = _NewSpawn;
}

void CLevel::DrawLevel(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Paths.size(); i++)//draw background
	{
		m_Paths[i]->Render(_Window);
	}
	for (int i = 0; i < m_Towers.size(); i++)//draw Towers
	{
		m_Towers[i]->Render(_Window);
	}
	for (int i = 0; i < m_Enemies.size(); i++)//draw Enemies
	{
		m_Enemies[i]->Render(_Window);
	}
	for (int i = 0; i < m_Walls.size(); i++)//draw Walls
	{
		m_Walls[i]->Render(_Window);
	}
}

void CLevel::SpawnEnemy(float _Speed, int _Hp)
{

}
