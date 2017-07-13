#include "Tile.h"



Tile::Tile()
{
	create();
}


void Tile::setVisited(const bool & flag) {
	m_visited = flag;
}

void Tile::setBomb(const bool & bomb) {
	m_Bomb = bomb;
}



bool Tile::isVisited()const {
	return m_visited;
}

bool Tile::isRClicked()const {
	return m_rCliked;
}


void Tile::setRClick(const bool & flag) {
	m_rCliked = flag;
}


void Tile::reverseRClicked() {
	m_rCliked = !m_rCliked;
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
	m_rCliked = false;

	m_font.loadFromFile("arial.ttf");

	m_text.setFont(m_font);

	m_text.setCharacterSize(TEXTSIZE);

	m_text.setFillColor(sf::Color::Red);

	m_text.setString("");

}


void Tile::Draw(sf::RenderWindow * winPtr) {
	winPtr->draw(m_tileRect);

	std::string str("");

	if (m_adjcBombs > 0) {
		 str = std::to_string(m_adjcBombs);
	}
	if (m_rCliked) {
		str = "X";
	}

	m_text.setString(str);

	winPtr->draw(m_text);
}


int Tile::SIZE = 35;
int Tile::TEXTSIZE = 11;


