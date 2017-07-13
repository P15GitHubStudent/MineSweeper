#include"GameOverState.h"
#include"StateManager.h"



GameOver_State::GameOver_State(StateManager * mStateMgr):BaseState(mStateMgr),BACKGOUND_COLOR(sf::Color(144,23,23)){

}


void GameOver_State::OnCreate() {

	sf::Vector2u winSize = m_stateMgr->GetContext()->win->getWinSize();
	SetTransparent(true);
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("GAME OVER ! ");
	m_Rect.setSize(sf::Vector2f(m_text.getCharacterSize() * sizeof("епамаййимисг"), 150));
	//m_Rect.setOrigin(winSize.x / 2 - m_Rect.getPosition().x, winSize.y / 2 - m_Rect.getPosition().y);
	m_Rect.setFillColor(BACKGOUND_COLOR);
	m_text.setFillColor(sf::Color::White);	
	m_text.setPosition(sf::Vector2f(winSize.x / 2-100, winSize.y / 2));
	m_Rect.setPosition(sf::Vector2f(winSize.x / 2-150, winSize.y / 2));
	m_optionsText[0].setString(L"епамаййимгсг");
	m_optionsText[1].setString(L"енодос");


	for (int c = 0; c < 2; c++) {
		m_optionsText[c].setCharacterSize(20);
		m_optionsText[c].setFont(m_font);
		m_optionsText[c].setPosition(sf::Vector2f(m_Rect.getPosition().x + (250 * c), m_Rect.getPosition().y+m_Rect.getSize().y- 50));
	}
}

void GameOver_State::Activate() {


}


void GameOver_State::Deactivate() {

}

void GameOver_State::Draw() {

	sf::RenderWindow * win = m_stateMgr->GetContext()->win->getWindow();

	win->draw(m_Rect);
	win->draw(m_text);
	for (int c = 0; c < 2; c++) {
		win->draw(m_optionsText[c]);
	}

}

void GameOver_State::Update(const sf::Time& l_time) {

}

void GameOver_State::OnDestroy() {

}
