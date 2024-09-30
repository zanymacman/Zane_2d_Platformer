#include "CTile.h"

CTile::CTile(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic) : CObject(_Size, _Position, _Type, _Dynamic)
{
	m_Tileshape.setSize(_Size);
	m_Tileshape.setOrigin(sf::Vector2f(0, 0));
	m_Tileshape.setPosition(_Position);

	m_Tileshape.setFillColor(sf::Color::Transparent);
	m_Tileshape.setOutlineThickness(-5);
	m_Tileshape.setOutlineColor(sf::Color::Transparent);

	m_TileCollider = new sf::FloatRect();
	m_TileCollider->left = m_Tileshape.getGlobalBounds().left;
	m_TileCollider->top = m_Tileshape.getGlobalBounds().top;
	m_TileCollider->width = m_Tileshape.getGlobalBounds().width;
	m_TileCollider->height = m_Tileshape.getGlobalBounds().height;
}

CTile::~CTile()
{
}


void CTile::Render(sf::RenderWindow* _Window)
{
	_Window->draw(m_Tileshape);
}

void CTile::Update(sf::RenderWindow* _Window)
{
	if (GetMoving())
	{
		Move();
		m_Tileshape.setPosition(m_ObjectShape.getPosition());
	}
}

void CTile::SetTexture(std::string _FilePath)
{
	m_ObjectTexture.loadFromFile(_FilePath);
	m_ObjectTexture.setSmooth(false);
	m_Tileshape.setTexture(&m_ObjectTexture);
	m_Tileshape.setTextureRect(sf::IntRect(m_Tileshape.getLocalBounds().left, m_Tileshape.getLocalBounds().top,
		m_Tileshape.getLocalBounds().width, m_Tileshape.getLocalBounds().height));
}
