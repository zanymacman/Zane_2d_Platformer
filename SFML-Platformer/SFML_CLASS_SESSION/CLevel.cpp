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

void CLevel::CreateLevel()
{
	for (int y = 0; y < levelHeight; y++)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			if (levelArray[x][y] == 'x')//background Tile
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");
			}
			if (levelArray[x][y] == 'o')//Wall Tile
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Wall, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/WallV1.png");
			}
			if (levelArray[x][y] == '-')//Platform Tile
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), Platform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");

			}
			if (levelArray[x][y] == 'A')//Arrow Pickup
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64)), ArrowPickup, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineThickness(-5);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Black);
				m_Objects.push_back(newTile1);
			}
			if (levelArray[x][y] == '^')//FloorSpikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64) + 32), FloorSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/FloorSpikeV1.png");
			}
			if (levelArray[x][y] == '>')//Left Wall Spikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64)), LWallSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/LeftSpikeV1.png");
			}
			if (levelArray[x][y] == '<')//Right Wall Spikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64) + 32, (y * 64)), RWallSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/RightSpikeV1.png");
			}
			if (levelArray[x][y] == '_')//Moving Platform
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(0, 10, 2, 300, 300);
			}
			if (levelArray[x][y] == 'S')//Player Spawn
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Spawn, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/SpawnV1.png");
				m_PlayerRef->SetSpawn(newTile1->m_ObjectShape.getPosition());
			}
			if (levelArray[x][y] == 'E')
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), LevelEnd, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/LevelEndV1.png");
			}
			if (levelArray[x][y] == '1')
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_ObjectShape.setFillColor(sf::Color::White);
				newTile->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CEnemy* newEnemy = new CEnemy(sf::Vector2f(32, 32), sf::Vector2f(x * 64, y * 64), EWalker, true);
				newEnemy->SetTrackedPlayer(m_PlayerRef);
				m_Objects.push_back(newEnemy);
			}
		}
	}
}

void CLevel::RenderBackground(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if(m_Objects[i]->m_ObjectType == Background)//draw the background
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType == Spawn)//Then Draw the Spawnpoint
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
}

void CLevel::RenderForground(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType == Arrow)//Draw Arrows in front of walls and other platforms, so they stick in nicely
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType != Background and m_Objects[i]->m_ObjectType != Spawn)//then draw everything else
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
}

void CLevel::UnloadLevel()
{
	CObject* tempObjectPtr;

	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType != Player)
		{
			tempObjectPtr = m_Objects[i];
			m_Objects[i] = nullptr;
			delete tempObjectPtr;
		}
		else
		{
			m_Objects[i]->m_ObjectShape.setPosition(sf::Vector2f(-100, -100));
		}
	}
	m_Objects.clear();
}