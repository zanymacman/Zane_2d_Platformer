#include "CObject.h"

CObject::CObject()
{
	m_ObjectShape.setSize(sf::Vector2f(64,64));
	m_ObjectShape.setPosition(sf::Vector2f(1,1));
	m_ObjectShape.setFillColor(sf::Color::Transparent);
	m_ObjectShape.setOutlineThickness(-5);
	m_ObjectShape.setOutlineColor(sf::Color::Transparent);
}

CObject::CObject(sf::Vector2f _Size, sf::Vector2f _Position)
{
	m_ObjectShape.setSize(_Size);
	m_ObjectShape.setPosition(_Position);
	m_ObjectShape.setFillColor(sf::Color::White);
	m_ObjectShape.setOutlineThickness(-5);
	m_ObjectShape.setOutlineColor(sf::Color::Transparent);
}

CObject::~CObject()
{
}

void CObject::Render(sf::RenderWindow* _Window)
{
	_Window->draw(m_ObjectShape);
	_Window->draw(m_ObjectSprite);
}

void CObject::Update(sf::RenderWindow* _Window)
{
}

void CObject::SetTexture(std::string _FilePath)
{
	m_ObjectTexture.loadFromFile(_FilePath);
	m_ObjectTexture.setSmooth(false);
	m_ObjectShape.setTexture(&m_ObjectTexture);
	m_ObjectShape.setTextureRect(sf::IntRect(	m_ObjectShape.getLocalBounds().left, 
												m_ObjectShape.getLocalBounds().top,
												m_ObjectShape.getLocalBounds().width,
												m_ObjectShape.getLocalBounds().height));//this is the best layout of this i could find lmao
}

sf::RectangleShape CObject::GetShape()
{
	return m_ObjectShape;
}

sf::Vector2f CObject::GetVelocity()
{
	return m_ObjectVelocity;
}

void CObject::SetVelocity(sf::Vector2f _Velocity)
{
	m_ObjectVelocity = _Velocity;
}

bool CObject::IsWall()
{
	return false;
}
