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
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");
			}
			if (levelArray[x][y] == 'o')//Wall Tile
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Wall, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile);
				newTile->SetTexture("Sprites/WallV1.png");
			}
			if (levelArray[x][y] == '-')//Platform Tile
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), Platform, false);
				newTile1->m_Tileshape.setFillColor(sf::Color::White);
				newTile1->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");

			}
			if (levelArray[x][y] == 'A')//Arrow Pickup
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64)), ArrowPickup, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineThickness(-5);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Black);
				m_LevelCollisionTiles.push_back(newTile1);
			}
			if (levelArray[x][y] == '^')//FloorSpikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64) + 32), FloorSpike, false);
				newTile1->m_Tileshape.setFillColor(sf::Color::White);
				newTile1->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile1);
				newTile1->SetTexture("Sprites/FloorSpikeV1.png");
			}
			if (levelArray[x][y] == '>')//Left Wall Spikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64)), LWallSpike, false);
				newTile1->m_Tileshape.setFillColor(sf::Color::White);
				newTile1->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile1);
				newTile1->SetTexture("Sprites/LeftSpikeV1.png");
			}
			if (levelArray[x][y] == '<')//Right Wall Spikes
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64) + 32, (y * 64)), RWallSpike, false);
				newTile1->m_Tileshape.setFillColor(sf::Color::White);
				newTile1->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile1);
				newTile1->SetTexture("Sprites/RightSpikeV1.png");
			}
			if (levelArray[x][y] == '_')//Moving Platform
			{
				CTile* newTile = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Background, false);
				newTile->m_Tileshape.setFillColor(sf::Color::White);
				newTile->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelBackgroundTiles.push_back(newTile);
				newTile->SetTexture("Sprites/SkyV1.png");

				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_Tileshape.setFillColor(sf::Color::White);
				newTile1->m_Tileshape.setOutlineColor(sf::Color::Transparent);
				m_LevelCollisionTiles.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(0, 10, 2, 300, 300);
			}
		}
	}
}

void CLevel::RenderBackground(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_LevelBackgroundTiles.size(); i++)
	{
		_Window->draw(m_LevelBackgroundTiles[i]->m_Tileshape);
	}
}

void CLevel::RenderForground(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_LevelCollisionTiles.size(); i++)
	{
		_Window->draw(m_LevelCollisionTiles[i]->m_ObjectShape);
		_Window->draw(m_LevelCollisionTiles[i]->m_Tileshape);
	}
}

void CLevel::UnloadLevel()
{
	CTile* tempTilePtr;
	CObject* tempObjectPtr;

	for (int i = 0; i < g_Objects.size(); i++)
	{
		tempObjectPtr = g_Objects[i];
		g_Objects[i] = nullptr;
		delete tempObjectPtr;
	}
	g_Objects.clear();

	for (int i = 0; i < m_LevelBackgroundTiles.size(); i++)
	{
		tempTilePtr = m_LevelBackgroundTiles[i];
		m_LevelBackgroundTiles[i] = nullptr;
		delete tempTilePtr;
	}
	m_LevelBackgroundTiles.clear();
	
	for (int i = 0; i < m_LevelCollisionTiles.size(); i++)
	{
		tempTilePtr = m_LevelCollisionTiles[i];
		m_LevelCollisionTiles[i] = nullptr;
		delete tempTilePtr;
	}
	m_LevelCollisionTiles.clear();

	for (int i = 0; i < g_Tile.size(); i++)
	{
		tempTilePtr = g_Tile[i];
		g_Tile[i] = nullptr;
		delete tempTilePtr;
	}
	g_Tile.clear();
}