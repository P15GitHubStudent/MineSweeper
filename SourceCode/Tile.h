#pragma once

#include<SFML\Graphics.hpp>

class Tile
{
public:
	friend class Board;
	Tile();
	~Tile()=default;
	void create();
	void setVisited(const bool & flag);
	void setBomb(const bool &flag);
	bool isVisited()const;
	bool isBomb() const { return m_Bomb; }
	static int SIZE;
	void Draw(sf::RenderWindow * win);
	bool isRClicked()const;
	void setRClick(const bool & flag);
	void reverseRClicked(); // apla antistrefei to rclicked diladi ama eixe patihei to rclick tote ua bgalei tin simaia kaki eksigisi !!
private:
	static int TEXTSIZE;
	bool m_rCliked;
	sf::Font m_font;
	sf::Text m_text; // text to print when they are adjant number of bombs 
	sf::RectangleShape m_tileRect;
	int m_adjcBombs;
	sf::Vector2f m_size;
	bool m_Bomb;
	bool m_visited;
};

