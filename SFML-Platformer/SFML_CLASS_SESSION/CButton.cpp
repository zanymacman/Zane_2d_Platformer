#include "CButton.h"

CButton::CButton(sf::Vector2f _Pos, sf::Font* _FontRef, sf::Vector2f _Size, std::string _Text)
{
	m_ShapeElement.setSize(_Size);
	m_ShapeElement.setFillColor(sf::Color::White);
	m_ShapeElement.setOrigin(sf::Vector2f(50, 20));

	m_TextElement.setFont(*_FontRef);
	m_TextElement.setCharacterSize(30);
	m_TextElement.setFillColor(sf::Color::White);
	m_TextElement.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_TextElement.setOrigin(50, 20);
	m_TextElement.setString(_Text);

	m_ShapeElement.setPosition(_Pos);
	m_TextElement.setPosition(_Pos);
}

CButton::~CButton()
{
}

void CButton::Update(sf::RenderWindow* _Window)
{
}

void CButton::Draw(sf::RenderWindow* _Window)
{
	_Window->draw(m_ShapeElement);
	_Window->draw(m_TextElement);
}

sf::RectangleShape CButton::GetShapeElement()
{
	return m_ShapeElement;
}

sf::Text CButton::GetTextElement()
{
	return m_TextElement;
}
