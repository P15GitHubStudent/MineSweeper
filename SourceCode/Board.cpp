#include "Board.h"
#include<iostream>



Board::Board(unsigned int  width, unsigned int height,unsigned int numOfBombs ):m_width(width),m_height(height),m_sharedContextPtr(nullptr),m_numOfBombs(numOfBombs)
, m_victoryCounter(0){

}

sf::Vector2i Board::getTile2dCoords() {

	sf::Vector2i mPos = m_sharedContextPtr->evMgr->GetMousePos(m_sharedContextPtr->win->getWindow());

	sf::Vector2i TileIds;

	TileIds.x = mPos.x / Tile::SIZE;

	TileIds.y = mPos.y / Tile::SIZE;

	return TileIds;

}


void Board::rClick(EventDetails * evDetails) {

	sf::Vector2i tileCoords =getTile2dCoords();
	


}

//bad neighboor code ? s
int Board::getNumberOfNeightboors(const sf::Vector2i & posTile) {

	int neighboors = 0;

	int boundX = m_width / Tile::SIZE;
	int boundY = m_height / Tile::SIZE;

	std::vector<sf::Vector2i> data{ {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

	for (auto & itr : data) {

		sf::Vector2i pos;

		pos.x = itr.x + posTile.x;
		pos.y = itr.y + posTile.y;

		if (pos.x >= boundX || pos.x < 0 || pos.y >= boundY || pos.y < 0)continue;

		if (m_tile[pos.y][pos.x].isBomb()) {
			neighboors++;
		}
	}


	return neighboors;
}



unsigned int Board::GetCorrectTileSizeNoBombs() {

	int numX = m_width / Tile::SIZE; 
	int numY = m_height / Tile::SIZE;

	return numX + numY - m_numOfBombs;

}


void Board::lClick(EventDetails * evDetails) {


	sf::Vector2i tileCoords = getTile2dCoords();

	sf::Vector2i Mpos = m_sharedContextPtr->evMgr->GetMousePos();

	//m_tile[tileCoords.y][tileCoords.x].m_visited = true;

	if (m_tile[tileCoords.y][tileCoords.x].isBomb()) {
		std::cout << "You Lost!" << std::endl;
		//StateManager.SwitchTo(State::GameOver);
		return;
	}

	reveal(tileCoords.x,tileCoords.y);


	
	if (m_victoryCounter >= GetCorrectTileSizeNoBombs()) {
		std::cout << "We Won !! \n";
	}
	



}

void Board::reveal(int x,int y) {


	//out of bounds base case 
	if (x >=m_width / Tile::SIZE  || x < 0 || y >= m_height/Tile::SIZE || y < 0)return;

	//visited 

	if (m_tile[y][x].m_visited)return;

	m_tile[y][x].m_visited = true;

	++m_victoryCounter;
	
	//153 - 255 - 51
	m_tile[y][x].m_tileRect.setFillColor(sf::Color(190, 255, 95));


	m_tile[y][x].m_adjcBombs = getNumberOfNeightboors(sf::Vector2i(x,y));

	if (m_tile[y][x].m_adjcBombs > 0) {
		return;
	}

	std::vector<sf::Vector2i> neighboors{ { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 },{ 1,1 },{ 1,-1 },{ -1,1 },{ -1,-1 } };

	for (auto & itr : neighboors)
		reveal(x + itr.x, y + itr.y);

}


void Board::initCallBacksBindings() {

	std::unique_ptr<Binding> rClickBind(new Binding("rClick"));
	rClickBind->bindEvent(EventType::MButtonUp, sf::Mouse::Right);
	m_sharedContextPtr->evMgr->AddBinding(std::move(rClickBind));
	m_sharedContextPtr->evMgr->AddCallback("rClick", &Board::rClick, this);
	std::unique_ptr<Binding> lClickBind(new Binding("lClick"));
	lClickBind->bindEvent(EventType::MButtonUp, sf::Mouse::Left);
	m_sharedContextPtr->evMgr->AddBinding(std::move(lClickBind));
	m_sharedContextPtr->evMgr->AddCallback("lClick", &Board::lClick, this);
	std::unique_ptr<Binding> bind(new Binding("reset"));
	bind.get()->bindEvent(EventType::KeyUp, sf::Keyboard::Escape);
	m_sharedContextPtr->evMgr->AddBinding(std::move(bind));
	m_sharedContextPtr->evMgr->AddCallback("reset", &Board::CreateBoard, this);

}

void Board::setDimensions(unsigned int width, unsigned int height) {
	m_width = width;
	m_height = height;
}

void Board::setNumOfBombs(unsigned int numOfBombs) {
	m_numOfBombs = numOfBombs;
}


void Board::CreateBoard(EventDetails * evDetails) {


	int xRange = m_width / Tile::SIZE;
	int yRangle = m_height / Tile::SIZE;

	m_tile.resize(yRangle);
	//m_visible.resize(yRangle);


	for (int c = 0; c < xRange; c++) {
		m_tile[c].resize(xRange);
		//m_visible[c].resize(xRange);
	}
	

	for (int x = 0; x < xRange; ++x) {

		for (int y = 0; y < yRangle ; ++y) {

			m_tile[y][x].m_tileRect.setFillColor(sf::Color::Green);
			m_tile[y][x].m_tileRect.setOutlineThickness(1.5f);
			m_tile[y][x].m_tileRect.setOutlineColor(sf::Color::Black);
			m_tile[y][x].m_tileRect.setSize(sf::Vector2f(Tile::SIZE, Tile::SIZE));
			m_tile[y][x].m_tileRect.setPosition(sf::Vector2f(x * Tile::SIZE, y * Tile::SIZE));
			m_tile[y][x].m_text.setPosition(sf::Vector2f(x * Tile::SIZE + Tile::SIZE - 0.5 * Tile::SIZE, y * Tile::SIZE + Tile::SIZE - 0.5 * Tile::SIZE));
			m_tile[y][x].m_text.setString("");
			m_tile[y][x].create();
		}
	}

	for (int c = 0; c < m_numOfBombs; c++) {

		int randx = rand() % xRange;

		int randY = rand() % yRangle;
		
		m_tile[randY][randx].m_tileRect.setFillColor(sf::Color(255, 0, 255));

		m_tile[randY][randx].m_Bomb = true;

	}

}


void Board::setSharedContext(SharedContext * sharedContextptr) {
	m_sharedContextPtr = sharedContextptr;
}


void Board::Update(const float & dt) {

}

void Board::Draw() {

	sf::RenderWindow * win = m_sharedContextPtr->win->getWindow();
	
	if (!win) {
		std::cout << "WIN - > NULLPTR\n ";
		return;
	}

	std::cout << m_width / Tile::SIZE << std::endl;
	std::cout << m_height / Tile::SIZE << std::endl;


	for (int x = 0; x <  m_width/ Tile::SIZE; ++x) {

		for (int y = 0; y < m_height / Tile::SIZE; ++y) {

			m_tile[y][x].Draw(win);


		}
	}

}


Board::~Board()
{

}
