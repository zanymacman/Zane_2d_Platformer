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
	m_PlayerRef->ToggleDynamic();
	for (int y = 0; y < levelHeight; y++)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			if (levelArray[x][y] == ' ')
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
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), Platform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");

			}
			if (levelArray[x][y] == 'A')//Arrow Pickup
			{
				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64)), ArrowPickup, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/ArrowPickupV1.png");
			}
			if (levelArray[x][y] == '^')//FloorSpikes
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64) + 32), FloorSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/FloorSpikeV1.png");
			}
			if (levelArray[x][y] == '>')//Left Wall Spikes
			{
				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64), (y * 64) + 1), LWallSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/LeftSpikeV1.png");
			}
			if (levelArray[x][y] == '<')//Right Wall Spikes
			{
				CTile* newTile1 = new CTile(sf::Vector2f(32, 64), sf::Vector2f((x * 64) + 32, (y * 64) + 1), RWallSpike, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/RightSpikeV1.png");
			}
			if (levelArray[x][y] == '(')//Horizotal Moving Platform Starting on the Left
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(15, 0, 2, 300, 300);
			}
			if (levelArray[x][y] == ')')//Horizotal Moving Platform Starting on the Right
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(-15, 0, 2, 300, 300);
			}
			if (levelArray[x][y] == ']')//Vertical Moving Platform Starting At the Top
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(0, 10, 2, 300, 300);
			}
			if (levelArray[x][y] == '[')//Vertical Moving Platform Starting At the Bottom
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 32), sf::Vector2f((x * 64), (y * 64)), MovingPlatform, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/PlatformV4.png");
				newTile1->BecomeMovingPlatform(0, -10, 2, 300, 300);
			}
			if (levelArray[x][y] == 'S')//Player Spawn
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), Spawn, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/SpawnV1.png");
				m_PlayerRef->SetSpawn(sf::Vector2f((x * 64), (y * 64)));
			}

			if (levelArray[x][y] == 'E')//Level Exit
			{
				CTile* newTile1 = new CTile(sf::Vector2f(64, 64), sf::Vector2f((x * 64), (y * 64)), LevelEnd, false);
				newTile1->m_ObjectShape.setFillColor(sf::Color::White);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Transparent);
				m_Objects.push_back(newTile1);
				newTile1->SetTexture("Sprites/LevelEndV1.png");
			}
			if (levelArray[x][y] == '1')//Enemy Type Walker
			{
				CEnemy* newEnemy = new CEnemy(sf::Vector2f(32, 32), sf::Vector2f(x * 64, y * 64), EWalker, true);
				newEnemy->SetTrackedPlayer(m_PlayerRef);
				m_Objects.push_back(newEnemy);
			}
			if (levelArray[x][y] == 'B')//Enemy Type Walker
			{
				CTile* newTile1 = new CTile(sf::Vector2f(54, 54), sf::Vector2f((x * 64), (y * 64)), Box, true);
				newTile1->m_ObjectShape.setFillColor(sf::Color::Magenta);
				newTile1->m_ObjectShape.setOutlineColor(sf::Color::Black);
				newTile1->m_ObjectShape.setOutlineThickness(-5);
				m_Objects.push_back(newTile1);
			}
		}
	}
	m_PlayerRef->ReSpawn();
	m_PlayerRef->ToggleDynamic();
}

void CLevel::ResetLevel()//reset the current level
{
	UnloadLevel();
	switch (GetCurrentLevel())
	{
	case 1:
		Loadlevel("Levels/Level1.txt");
		break;
	case 2:
		Loadlevel("Levels/Level2.txt");
		break;
	case 3:
		Loadlevel("Levels/Level3.txt");
		break;
	case 4:
		Loadlevel("Levels/Level4.txt");
		break;
	case 5:
		Loadlevel("Levels/Level5.txt");
		break;
	case 6:
		Loadlevel("Levels/Level6.txt");
		break;
	case 7:
		Loadlevel("Levels/Level7.txt");
		break;
	case 8:
		Loadlevel("Levels/Level8.txt");
		break;
	case 9:
		Loadlevel("Levels/Level9.txt");
		break;
	case 10:
		Loadlevel("Levels/Level10.txt");
		break;
	case 11:
		Loadlevel("Levels/Level11.txt");
		break;
	case 12:
		Loadlevel("Levels/Level12.txt");
		break;
	case 13:
		Loadlevel("Levels/Level13.txt");
		break;
	case 14:
		Loadlevel("Levels/Level14.txt");
		break;
	case 15:
		Loadlevel("Levels/Level15.txt");
		break;
	}
}

int CLevel::GetCurrentLevel()//get the current levels id
{
	return m_CurrentLevelID;
}

void CLevel::SetCurrentLevel(int _LevelID) // set the current levels id
{
	m_CurrentLevelID = _LevelID;
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
		if (m_Objects[i]->m_ObjectType != Background and m_Objects[i]->m_ObjectType != Spawn and m_Objects[i]->m_ObjectType != Player)//then draw props and such
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType == Wall)//then Finally draw the player
		{
			_Window->draw(m_Objects[i]->m_ObjectShape);
		}
	}
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->m_ObjectType == Player)//then Finally draw the player
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
	m_Objects.push_back(m_PlayerRef);
}

void CLevel::CollisionIntergration(std::vector<CObject*> _Objects)//detect if there IS a collision
{
	sf::FloatRect BoundsA;//will be collider 1
	sf::FloatRect BoundsB;//will be collider 2
	bool LoadLevel = false;
	m_PlayerRef->SetGrounded(false);
	for (int i = 0; i < _Objects.size(); i++)
	{
		BoundsA = _Objects[i]->m_ObjectShape.getGlobalBounds();
		//Overlaps
		for (int j = 0; j < _Objects.size(); j++)
		{
			BoundsB = _Objects[j]->m_ObjectShape.getGlobalBounds();

			if (BoundsA != BoundsB)
			{
				if (BoundsA.intersects(BoundsB))//if they ACTUALLY COLLIDE
				{
					sf::Vector2f EntityACentre =
					{
						(BoundsA.left + BoundsA.width / 2.0f),
						(BoundsA.top + BoundsA.height / 2.0f)
					};

					sf::Vector2f EntityBCentre =
					{
						(BoundsB.left + BoundsB.width / 2.0f),
						(BoundsB.top + BoundsB.height / 2.0f)
					};

					switch (_Objects[i]->m_ObjectType)
					{
					case Player:
						if (_Objects[j]->m_ObjectType == Wall)
						{
							if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
							{
								_Objects[i]->m_ObjectVelocity.x = 0;
								CCollisionHandler::ResolveXCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
							else//is a collision on the Y Axis
							{
								_Objects[i]->m_YVelocity = 0;
								_Objects[i]->m_ObjectVelocity.y = 0;
								if (EntityACentre.y <= EntityBCentre.y) 
								{ 
									m_PlayerRef->SetGrounded(true); 
								} //if the player is on the ground, set it to be on the ground
								CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
						}
						if (_Objects[j]->m_ObjectType == Box)
						{
							if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
							{
								//do nothing, its happening in the box collisions
							}
							else//is a collision on the Y Axis
							{
								_Objects[i]->m_YVelocity = 0;
								_Objects[i]->m_ObjectVelocity.y = 0;
								CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
						}
						else if (_Objects[j]->m_ObjectType == EWalker)
						{
							if (!m_PlayerRef->GetInvul())
							{
								//insert damage and slight knock code
								m_PlayerRef->SetPlayerLives(m_PlayerRef->GetPlayerLives() - 1);
								m_PlayerRef->SetInvul();
								if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
								{
									m_PlayerRef->XHurtReact();
								}
								else
								{
									m_PlayerRef->YHurtReact();
								}
							}
						}
						else if (_Objects[j]->m_ObjectType == FloorSpike or _Objects[j]->m_ObjectType == LWallSpike or _Objects[j]->m_ObjectType == RWallSpike)
						{
							if (!m_PlayerRef->GetInvul())
							{
								//insert damage and slight knock code
								m_PlayerRef->SetPlayerLives(m_PlayerRef->GetPlayerLives() - 1);
								m_PlayerRef->SetInvul();
								if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
								{ 
									m_PlayerRef->XHurtReact();
								}
								else
								{
									m_PlayerRef->YHurtReact();
								}
								
							}
						}
						else if (_Objects[j]->m_ObjectType == Platform)//platgforms have no x collision
						{
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))//collide if not holding S
							{
								if (fabs(EntityACentre.x - EntityBCentre.x) <= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the Y Axis
								{
									if (EntityACentre.y <= EntityBCentre.y - 10)//if below platform, do not collide
									{
										_Objects[i]->m_YVelocity = 0;
										_Objects[i]->m_ObjectVelocity.y = 0;
										if (EntityACentre.y <= EntityBCentre.y) { m_PlayerRef->SetGrounded(true); ; } //if the player is on the ground, set it to be on the ground
										CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
									}
								}
								//No X collisions for Platforms
							}
						}
						else if (_Objects[j]->m_ObjectType == MovingPlatform)//platgforms have no x collision
						{
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))//collide if not holding S
							{
								if (fabs(EntityACentre.x - EntityBCentre.x) <= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the Y Axis
								{
									if (EntityACentre.y <= EntityBCentre.y - 10)//if below platform, do not collide
									{
										_Objects[i]->m_YVelocity = 0;
										_Objects[i]->m_ObjectVelocity.y = 0;
										if (EntityACentre.y <= EntityBCentre.y) { m_PlayerRef->SetGrounded(true); ; } //if the player is on the ground, set it to be on the ground
										CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
									}
								}
								//No X collision on Moving Platforms
								m_PlayerRef->m_ObjectShape.move(sf::Vector2f(_Objects[j]->m_ObjectVelocity.x * 1.7, 0));//player moves with platform
							}
						}
						else if (_Objects[j]->m_ObjectType == ArrowPickup)
						{
							if (m_PlayerRef->GetArrowCount() > 2)
							{
								_Objects[j]->m_ObjectShape.setFillColor(sf::Color::Red);
							}
							else
							{
								m_PlayerRef->SetArrowCount(m_PlayerRef->GetArrowCount() + 1);
								std::cout << "+1 ARROW WOO\n";
								_Objects[j]->m_ObjectShape.move(0, 500);//teleport below the level
							}
						}
						else if (_Objects[j]->m_ObjectType == LifePickup)
						{
							if (m_PlayerRef->GetPlayerLives() > 2)
							{
								_Objects[j]->m_ObjectShape.setFillColor(sf::Color::Red);
							}
							else
							{
								m_PlayerRef->SetPlayerLives(m_PlayerRef->GetPlayerLives() + 1);
								std::cout << "+1 Life WOO\n";
								_Objects[j]->m_ObjectShape.move(0, 500);//teleport below the level
							}
						}
						else if (_Objects[j]->m_ObjectType == LevelEnd)
						{
							LoadLevel = true;
						}
						break;

					case Arrow:
						if (_Objects[j]->m_ObjectType == Wall or _Objects[j]->m_ObjectType == Platform)//if the arrow hits a wall
						{
							//insert arrow stopping and sticking against the wall
							_Objects[i]->m_ObjectVelocity.y = 0;
							_Objects[i]->m_ObjectVelocity.x = 0;
							_Objects[i]->m_ObjectType = Platform;
						}
						else if (_Objects[j]->m_ObjectType == MovingPlatform)
						{
							_Objects[i]->m_ObjectVelocity.x = 0;
							_Objects[i]->m_ObjectType = MovingPlatform;

							//duplicate the moving platform settings, but slightly to the side
							_Objects[i]->SetXMove(_Objects[j]->GetXMove());
							_Objects[i]->SetYMove(_Objects[j]->GetYMove());
							_Objects[i]->SetMoveSpeed(_Objects[j]->GetMoveSpeed());
							_Objects[i]->SetStartPos(_Objects[i]->m_ObjectShape.getPosition());
							_Objects[i]->SetMovingOut(_Objects[j]->GetMovingOut());
							_Objects[i]->SetMoving(true);
							_Objects[i]->SetMovingTimer(_Objects[j]->GetMovingTimer());
							_Objects[i]->SetMovingTimerMax(_Objects[j]->GetMovingTimerMax());
							_Objects[i]->ToggleDynamic();
						}
						else if (_Objects[j]->m_ObjectType == EWalker)
						{
							//insert arrow killing enemy code
						}
						else if (_Objects[j]->m_ObjectType == Box)
						{
							_Objects[i]->m_ObjectVelocity.x = 0;//Arrow stops moving and falls to the ground
							_Objects[i]->m_ObjectVelocity.y = 3;
						}
						break;
					case EWalker:
						if (_Objects[j]->m_ObjectType == Wall or _Objects[j]->m_ObjectType == Platform or _Objects[j]->m_ObjectType == FloorSpike
							or _Objects[j]->m_ObjectType == LWallSpike or _Objects[j]->m_ObjectType == RWallSpike or _Objects[j]->m_ObjectType == Box)
						{
							//insert normal rebound code for Enemy
							if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
							{
								_Objects[i]->m_ObjectVelocity.x = 0;
								CCollisionHandler::ResolveXCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
							else//is a collision on the Y Axis
							{
								_Objects[i]->m_YVelocity = 0;
								_Objects[i]->m_ObjectVelocity.y = 0;
								CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
						}
					case Box:
						if (_Objects[j]->m_ObjectType == Wall or _Objects[j]->m_ObjectType == Platform or _Objects[j]->m_ObjectType == FloorSpike 
							or _Objects[j]->m_ObjectType == LWallSpike or _Objects[j]->m_ObjectType == RWallSpike)
						{
							if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis
							{
								_Objects[i]->m_ObjectVelocity.x = 0;
								CCollisionHandler::ResolveXCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
							else//is a collision on the Y Axis
							{
								_Objects[i]->m_YVelocity = 0;
								_Objects[i]->m_ObjectVelocity.y = 0;
								CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
						}
						if (_Objects[j]->m_ObjectType == Player)
						{
							if (fabs(EntityACentre.x - EntityBCentre.x) >= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the X Axis, get pushed by the player
							{
								_Objects[i]->m_ObjectVelocity.x = 0;
								CCollisionHandler::ResolveXCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
							//in player collision, the player can walk on the box. if the box is pushed against the wall, it is stuck and cannot be pushed.
						}
						break;
						//(WALL, PLATFORM, SPIKE) -- these should have been dealt with above, and so will do nothing
					default:
						break;
					}
				}
			}
		}
	}
	if (LoadLevel)
	{
		UnloadLevel();
		switch (GetCurrentLevel())
		{
		case 1:
			Loadlevel("Levels/Level2.txt");
			SetCurrentLevel(GetCurrentLevel() + 1);
			break;
		case 2:
			Loadlevel("Levels/Level3.txt");
			SetCurrentLevel(GetCurrentLevel() + 1);
			break;
		case 3:
			Loadlevel("Levels/Level4.txt");
			SetCurrentLevel(GetCurrentLevel() + 1);
			break;
		case 4:
			Loadlevel("Levels/Level5.txt");
			SetCurrentLevel(GetCurrentLevel() + 1);
			break;
		}
	}
}

void CLevel::MovementIntergration(std::vector<CObject*> _Objects)
{
	for (int i = 0; i < _Objects.size(); i++)
	{
		//ACTUALLY Move on the x
		_Objects[i]->m_ObjectShape.move(_Objects[i]->m_ObjectVelocity.x * _Objects[i]->m_SpeedScalar * CHelper::getInstance().m_DeltaTme, 0);

		//ACTUALLY move on the Y
		_Objects[i]->m_ObjectShape.move(0, _Objects[i]->m_ObjectVelocity.y * _Objects[i]->m_SpeedScalar * CHelper::getInstance().m_DeltaTme);

	}
}