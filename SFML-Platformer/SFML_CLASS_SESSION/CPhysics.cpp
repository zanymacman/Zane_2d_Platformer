#include "CPhysics.h"
//if float rect
bool operator==(const sf::FloatRect _lhs, const sf::FloatRect* _rhs)
{
	if (_lhs.left == _rhs->left && _lhs.top == _rhs->top && _lhs.width == _rhs->width && _lhs.height == _rhs->height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=(const sf::FloatRect _lhs, const sf::FloatRect* _rhs)
{
	return !(_lhs == _rhs);
}

CPhysics::CPhysics()
{
}

CPhysics::~CPhysics()
{
}

void CPhysics::SetTrackedPlayer(CPlayer* _Player)
{
	m_TrackedPlayer = _Player;
}

CPlayer* CPhysics::GetTrackedPlayer()
{
	return m_TrackedPlayer;
}

void CPhysics::CollisionIntergration(std::vector<CObject*> _Objects)//detect if there IS a collision
{
	sf::FloatRect BoundsA;//will be collider 1
	sf::FloatRect BoundsB;//will be collider 2

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
								if (EntityACentre.x >= EntityBCentre.x) { _Objects[i]->SetGrounded(true); } //if the player is on the ground, set it to be on the ground
								CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
							}
						}
						else if (_Objects[j]->m_ObjectType == EWalker)
						{
							if (!m_TrackedPlayer->GetInvul())
							{
								//insert damage and slight knock code
								m_TrackedPlayer->SetPlayerLives(m_TrackedPlayer->GetPlayerLives() - 1);
								m_TrackedPlayer->SetInvul();
							}
						}
						else if (_Objects[j]->m_ObjectType == FloorSpike or _Objects[j]->m_ObjectType == LWallSpike or _Objects[j]->m_ObjectType == RWallSpike)
						{
							if (!m_TrackedPlayer->GetInvul())
							{
								//insert damage and slight knock code
								m_TrackedPlayer->SetPlayerLives(m_TrackedPlayer->GetPlayerLives() - 1);
								m_TrackedPlayer->SetInvul();
							}
						}
						else if (_Objects[j]->m_ObjectType == Platform or _Objects[j]->m_ObjectType == MovingPlatform)//platgforms have no x collision
						{
							if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))//collide if not holding S
							{
								if (fabs(EntityACentre.x - EntityBCentre.x) <= fabs(EntityACentre.y - EntityBCentre.y))//is a collision on the Y Axis
								{
									if (EntityACentre.y <= EntityBCentre.y)//if below platform, do not collide
									{
										_Objects[i]->m_YVelocity = 0;
										_Objects[i]->m_ObjectVelocity.y = 0;
										CCollisionHandler::ResolveYCollisions(&_Objects[i]->m_ObjectShape, &BoundsB);
									}
								}
								//No X collision on Platforms
								m_TrackedPlayer->m_ObjectShape.move(sf::Vector2f(_Objects[j]->m_ObjectVelocity.x * 1.7,0));//player moves with platform
							}
						}
						else if (_Objects[j]->m_ObjectType == ArrowPickup)
						{
							if (m_TrackedPlayer->GetArrowCount() > 2)
							{
								_Objects[j]->m_ObjectShape.setFillColor(sf::Color::Red);
							}
							else
							{
								m_TrackedPlayer->SetArrowCount(m_TrackedPlayer->GetArrowCount() + 1);
								std::cout << "+1 ARROW WOO\n";
								_Objects[j]->m_ObjectShape.move(0, 500);//teleport below the level
							}
						}
						else if (_Objects[j]->m_ObjectType == LifePickup)
						{
							if (m_TrackedPlayer->GetPlayerLives() > 2)
							{
								_Objects[j]->m_ObjectShape.setFillColor(sf::Color::Red);
							}
							else
							{
								m_TrackedPlayer->SetPlayerLives(m_TrackedPlayer->GetPlayerLives() + 1);
								std::cout << "+1 Life WOO\n";
								_Objects[j]->m_ObjectShape.move(0, 500);//teleport below the level
							}
						}
						else if (_Objects[j]->m_ObjectType == LevelEnd)
						{
							//unload level
							//load new level
							//respawn player
						}
						break;

					case Arrow:
						if (_Objects[j]->m_ObjectType == Wall or _Objects[j]->m_ObjectType == Platform)//if the arrow hits a wall
						{
							//insert arrow stopping and sticking against the wall
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
						break;
					case EWalker:
						if (_Objects[j]->m_ObjectType == Wall or _Objects[j]->m_ObjectType == Platform)
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
						else if (_Objects[j]->m_ObjectType == FloorSpike)
						{
							//Insert Enemy dying to spike
						}
						//(WALL, PLATFORM, SPIKE) -- these should have been dealt with above, and so will do nothing
					default:
						break;
					}
				}
			}
		}
	}
}

void CPhysics::MovementIntergration(std::vector<CObject*> _Objects)
{
	for (int i = 0; i < _Objects.size(); i++)
	{
		//ACTUALLY Move on the x
		_Objects[i]->m_ObjectShape.move(_Objects[i]->m_ObjectVelocity.x * _Objects[i]->m_SpeedScalar * CHelper::getInstance().m_DeltaTme, 0);

		//ACTUALLY move on the Y
		_Objects[i]->m_ObjectShape.move(0, _Objects[i]->m_ObjectVelocity.y * _Objects[i]->m_SpeedScalar * CHelper::getInstance().m_DeltaTme);

	}
}