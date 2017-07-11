#include "Game.h"



Game::Game(const sf::Vector2u & winDimensions):window(sf::Vector2u(winDimensions),"MineSweeper",false),m_Board(500,500,30)
{
	srand(time(NULL));
	m_Board.CreateBoard();
	m_clock.restart();
	m_elapsed = 0.0f;
	m_sharedContext.win = &window;
	m_sharedContext.evMgr = window.GetEventManager();
	m_Board.setSharedContext(&m_sharedContext);
	m_Board.initCallBacksBindings();
}


void Game::run() {

	sf::RenderWindow * windowPtr = window.getWindow();

	while (window.isOpen()) {

		window.Update();

		Update();

		window.beginDraw();

		draw();

		window.endDraw();

	}

}

void Game::draw() {

	m_Board.Draw();

}

void Game::Update() {

	m_Board.Update(0);
}

