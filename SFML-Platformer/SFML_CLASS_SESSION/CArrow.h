#pragma once
#include "CObject.h"
class CArrow : public CObject
{
public:
	CArrow(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic, bool _FacingRight);
	~CArrow();

	void Render(sf::RenderWindow* _Window) override;
private:
	float m_ArrowSpeed = 3.0f;

	sf::RectangleShape m_ArrowShape;
	sf::FloatRect* m_ArrowCollider;
};