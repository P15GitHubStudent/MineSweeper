#include "Game.h"



Game::Game(const sf::Vector2u & winDimensions):window(sf::Vector2u(winDimensions),"MineSweeper",false),m_stateMgr(&m_sharedContext)
{
	srand(time(NULL));
	m_clock.restart();
	m_elapsed = 0.0f;
	m_sharedContext.win = &window;
	m_sharedContext.evMgr = window.GetEventManager();
	m_stateMgr.SwitchTo(StateType::Game);
}


void Game::run() {


	while (window.isOpen()) {

		window.Update();

		m_stateMgr.Update(m_time);

		window.beginDraw();

		m_stateMgr.Draw();


		window.endDraw();

	}

}

void Game::draw() {


}

void Game::Update() {

}

