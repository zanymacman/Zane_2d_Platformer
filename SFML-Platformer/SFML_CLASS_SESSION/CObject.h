#pragma once
#include "CCollisionHandler.h"
#include "CHelper.h"


enum ObjType
{
	Spawn,
	Wall,
	Platform,
	MovingPlatform,
	FloorSpike,
	LWallSpike,
	RWallSpike,
	Background,
	Player,
	EWalker,
	Arrow,
	ArrowPickup,
	LifePickup
};

class CObject
{
public:
	sf::RectangleShape m_ObjectShape;
	sf::Vector2f m_ObjectVelocity;

	sf::Texture m_ObjectTexture;
	sf::Sprite m_ObjectSprite;

	ObjType m_ObjectType;

	float m_YVelocity = 0; // Use this for gravity
	bool m_Dynamic = false;
	float m_SpeedScalar = 100.0f; // scale movespeed

	CObject(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic);
	~CObject();

	virtual void Render(sf::RenderWindow* _Window);
	virtual void Update(sf::RenderWindow* _Window);
	virtual void ApplyGravity();

	virtual void SetTexture(std::string _FilePath);

	void ToggleDynamic();

	bool GetGrounded();
	void SetGrounded(bool _IsGrounded);

	//getters and setters for moving platforms
	float GetYMove();
	void SetYMove(float _YMove);
	float GetXMove();
	void SetXMove(float _YMove);
	float GetMoveSpeed();
	void SetMoveSpeed(float _MoveSpeed);
	sf::Vector2f GetStartPos();
	void SetStartPos(sf::Vector2f _StartPos);
	bool GetMovingOut();
	void SetMovingOut(bool _MovingOut);
	bool GetMoving();
	void SetMoving(bool _Moving);
	int GetMovingTimer();
	void SetMovingTimer(int _MovingTimer);
	int GetMovingTimerMax();
	void SetMovingTimerMax(int _TimerMax);

	void BecomeMovingPlatform(float _XMove, float _YMove, float _MoveSpeed, int _MovingTimer, int _TimerMax);
	void Move();

private:
	bool m_Grounded = true;

	//moving platform requirements
	float m_XMove;
	float m_YMove;
	float m_Movespeed;
	sf::Vector2f m_StartPos;
	bool m_MovingOut;
	bool m_Moving;
	int m_MovingTimer;
	int m_MovingTimerMax;

};