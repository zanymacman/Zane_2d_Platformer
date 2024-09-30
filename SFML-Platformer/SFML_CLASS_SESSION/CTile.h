#pragma once
#include "SFML/Graphics.hpp"
#include "CObject.h"

class CTile : public CObject
{
public:
	sf::RectangleShape m_Tileshape;
	sf::FloatRect* m_TileCollider;

	CTile(sf::Vector2f _size, sf::Vector2f _position, ObjType _Type, bool _Dynamic);
	~CTile();

	void Render(sf::RenderWindow* _Window);
	void Update(sf::RenderWindow* _Window) override;

	void SetTexture(std::string _FilePath) override;
};

