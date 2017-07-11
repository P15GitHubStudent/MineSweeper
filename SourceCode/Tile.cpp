#include "Tile.h"



Tile::Tile()
{
	create();
}

Tile::~Tile() {

}



void Tile::setVisited(const bool & flag) {
	m_visited = flag;
}


bool Tile::isVisited()const {
	return m_visited;
}


void Tile::setBomb(const bool & bomb) {
	m_Bomb = bomb;
}


void Tile::create() {
	
	m_adjcBombs = -1;
	m_size.x = Tile::SIZE;
	m_size.y = Tile::SIZE;
	m_visited = false;
	m_tileRect.setSize(m_size);
	m_tileRect.setFillColor(sf::Color::Green);
	m_tileRect.setOutlineThickness(1.5f);
	m_tileRect.setOutlineColor(sf::Color::Black);
	m_Bomb = false;

	m_font.loadFromFile("arial.ttf");

	m_text.setFont(m_font);

	m_text.setCharacterSize(9);

	m_text.setFillColor(sf::Color::Red);

}


void Tile::Draw(sf::RenderWindow * winPtr) {
	winPtr->draw(m_tileRect);
	m_text.setString(m_adjcBombs > 0 ? std::to_string(m_adjcBombs) : "");
	//m_text.setPosition(centerPos.x,centerPos.y);
	winPtr->draw(m_text);
}


int Tile::SIZE = 35;


