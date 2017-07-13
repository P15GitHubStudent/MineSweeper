#include"Play_State.h"
#include"StateManager.h"


Play_State::Play_State(StateManager * stMgr):BaseState(stMgr) {

	m_board = new Board();
}

void Play_State::OnCreate() {

	m_board->Create(sf::Vector2u(500, 500), 50, m_stateMgr);
	m_board->initCallBacksBindings();

}

void Play_State::Update(const sf::Time & dt) {
		m_board->Update(dt.asSeconds());
}

void Play_State::Draw() {
	m_board->Draw();
}


void Play_State::Activate() {

}

void Play_State::Deactivate(){

}

void Play_State::OnDestroy() {

	delete m_board;

}