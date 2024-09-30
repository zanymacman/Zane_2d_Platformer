#include "CTile.h"

CTile::CTile(sf::Vector2f _Size, sf::Vector2f _Position, ObjType _Type, bool _Dynamic) : CObject(_Size, _Position, _Type, _Dynamic)
{
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
	}
}

void CTile::SetTexture(std::string _FilePath)
{
	m_ObjectTexture.loadFromFile(_FilePath);
	m_ObjectTexture.setSmooth(false);
	m_ObjectShape.setTexture(&m_ObjectTexture);
	m_ObjectShape.setTextureRect(sf::IntRect(m_ObjectShape.getLocalBounds().left, m_ObjectShape.getLocalBounds().top,
		m_ObjectShape.getLocalBounds().width, m_ObjectShape.getLocalBounds().height));
}
