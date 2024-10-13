#pragma once
#include <SFML/Graphics.hpp>


class CObject
{
public:
	CObject();
	CObject(sf::Vector2f _Size, sf::Vector2f _Position);
	~CObject();

	virtual void Render(sf::RenderWindow* _Window);
	virtual void Update(sf::RenderWindow* _Window);

	virtual void SetTexture(std::string _FilePath);//set texture override to load and then apply texture properly

	//getters and setters
	sf::RectangleShape GetShape();//shape is set at compile time, no need for setter
	sf::Vector2f GetVelocity();
	void SetVelocity(sf::Vector2f _Velocity);

protected:
	sf::RectangleShape m_ObjectShape;
	sf::Vector2f m_ObjectVelocity;

	sf::Texture m_ObjectTexture;
	sf::Sprite m_ObjectSprite;
};

