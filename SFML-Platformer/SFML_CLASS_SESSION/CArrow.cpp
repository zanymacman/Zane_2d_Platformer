#include "CArrow.h"

CArrow::CArrow(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic, bool _FacingRight) : CObject (_Size, _Position, _Type, _Dynamic)
{
	m_ArrowShape.setSize(_Size);
	m_ArrowShape.setPosition(_Position);

	m_ObjectShape.setFillColor(sf::Color::White);
	//SetTexture("Sprites/ArrowV1.png");

	m_ArrowCollider = new sf::FloatRect();
	m_ArrowCollider->left = m_ArrowShape.getGlobalBounds().left;
	m_ArrowCollider->top = m_ArrowShape.getGlobalBounds().top;
	m_ArrowCollider->width = m_ArrowShape.getGlobalBounds().width;
	m_ArrowCollider->height = m_ArrowShape.getGlobalBounds().height;

	m_ObjectType = Arrow;

	if (_FacingRight) //facing right
	{
		m_ObjectVelocity.x = m_ArrowSpeed;
		m_ArrowShape.setOrigin(sf::Vector2f(0, 0));
	}
	else //facing left
	{
		m_ObjectVelocity.x = -m_ArrowSpeed;
		m_ArrowShape.setOrigin(sf::Vector2f(m_ArrowCollider->left + m_ArrowCollider->width, 0));
	}
}

CArrow::~CArrow()
{
}

void CArrow::Render(sf::RenderWindow* _Window)
{
	_Window->draw(m_ObjectShape);
}
