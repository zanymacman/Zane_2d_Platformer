#pragma once
#include "CObject.h"
#include "CArrow.h"

enum CharAnimationState
{
	Moving_L,
	Moving_R,
	Idle,
	Jumping_Up,
	Jumping_Down
};


class CPlayer : public CObject
{
public:
	//animation stuff
	CharAnimationState m_CurrentPlayerAnimationState = Idle; //Keep track of current animation
	sf::Clock m_AnimationClock; //tick to update the animation
	sf::IntRect m_AnimationRect; //the sprite from current sheet for current frame
	// --------------

	CPlayer(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic);
	~CPlayer();

	void Input();
	void Jump();

	CArrow* Shoot();
	int GetArrowCount();
	void SetArrowCount(int _NewCount);

	int GetPlayerLives();
	void SetPlayerLives(int _Lives);

	void SetInvul();
	bool GetInvul();

	void SetSpawn(sf::Vector2f _SpawnPos);
	sf::Vector2f GetSpawn();
	void ReSpawn();

	void Render(sf::RenderWindow* _Window) override;
	void Update(sf::RenderWindow* _Window) override;

	void AnimateCharacter();

private:
	float m_FallScaler = 2.5f;
	float m_PlayerSpeed = 3;
	float m_PlayerJumpheight = 10;
	bool m_Grounded = false;
	float m_LastYVelocity = 0;
	bool m_FacingRight = true;

	int m_ArrowCount = 3;
	int m_PlayerLives = 3;
	int m_IFrames = 30;
	int m_IFramesMax = 30;
	bool m_Invul = false;
	sf::Vector2f m_PlayerSpawnPos = sf::Vector2f(20, 20);
};