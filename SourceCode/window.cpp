#include "window.h"
#include<memory>
#include<iostream>
#include"Board.h"

window::window(const sf::Vector2u & winSize, const sf::String & winTitle,const bool & fullScreenFlag):m_isOpen(true),m_fullScreen(fullScreenFlag),m_winSize(winSize),m_gameTitle(winTitle)
{
	Binding * bindclose=new Binding("winCloseX");
	bindclose->BindEvent(EventType::Closed);
	m_evManager.AddCallback(StateType(0),"winCloseX", &window::close, this);
	m_evManager.AddBinding(bindclose);
	create();
}


void window::Update() {


	sf::Event ev;


	while (win.pollEvent(ev)) {
		m_evManager.HandleEvent(ev);
	}


	m_evManager.Update();

}


void window::create() {

	win.close();

	win.create(sf::VideoMode(m_winSize.x, m_winSize.y), m_gameTitle, m_fullScreen ? sf::Style::Fullscreen :sf::Style::Default ) ;

}

void window::setFullScreen(const bool & FullScreenFlag) {
	if (m_fullScreen != FullScreenFlag) {
		m_fullScreen = FullScreenFlag;
		create();
	}
}

void window::setFocus(const bool & focusFlag) {
	m_focus = focusFlag;
}

void window::close(EventDetails * evinfo ) {
	m_isOpen = false;
}


void window::setWindowSize(const sf::Vector2u & winSize) {
	if (winSize != m_winSize) {
		m_winSize = winSize;
		create();
	}
}


void window::beginDraw(const sf::Color & color) {
	win.clear(color);
}

void window::endDraw() {
	win.display();
}



window::~window()
{
}
