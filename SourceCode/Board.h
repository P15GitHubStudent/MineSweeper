#ifndef _BOARD_H
#define _BOARD_H

#include<SFML\Graphics.hpp>
#include"Tile.h"
#include"StateManager.h"
#include<vector>


class Board
{
public:
	Board() = default;
	~Board() = default;
	void Draw();
	void Update(const float & dt);
	void Create(const sf::Vector2u & dimensionBoard, unsigned int numOfBombs,StateManager * StateMgrPtr);
	void rClick(EventDetails * evDetails);
	void lClick(EventDetails * evDetails);
	void initCallBacksBindings();
	void setDimensions(unsigned int width, unsigned int height);
	void setNumOfBombs(unsigned int numBombs);
	int getNumberOfBombs()const { return m_numOfBombs; }
	sf::Vector2u getDimensions()const { return sf::Vector2u(m_width, m_height); }
	void deleteCallBacksBindings();

private:


	StateManager * m_stateMgrPtr;
	unsigned int GetCorrectTileSizeNoBombs();
	unsigned int m_victoryCounter;
	unsigned int m_rClickCounter;
	void reveal(int x,int y);
	int getNumberOfNeightboors(const sf::Vector2i & pos);
	unsigned int  m_numOfBombs; 
	sf::Vector2i  getTile2dCoords();
	unsigned int  m_width;
	unsigned int  m_height;
	std::vector<std::vector<Tile>> m_tile;
};


#endif // !_BOARD_H
