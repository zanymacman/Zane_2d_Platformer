#pragma once
#include "string.h"
#include <SFML/Graphics.hpp>
class CButton
{
public:
	CButton(sf::Vector2f _Pos, sf::Font* _FontRef, sf::Vector2f _Size, std::string _Text);
	~CButton();

	void Update(sf::RenderWindow* _Window);
	void Draw(sf::RenderWindow* _Window);

	sf::RectangleShape GetShapeElement();
	sf::Text GetTextElement();

private:
	sf::RectangleShape m_ShapeElement;
	sf::Text m_TextElement;
};

