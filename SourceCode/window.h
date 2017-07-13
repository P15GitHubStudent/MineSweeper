#pragma once

#include<SFML\Graphics.hpp>
#include"EventManager.h"


class window
{
public:
	window(const sf::Vector2u & winSize,const sf::String & winTitle,const bool & FullScreenFlag);
	~window();
	void setFullScreen(const bool & FullScreenFlag);
	void setWindowSize(const sf::Vector2u & size);
	const sf::Vector2u & getWinSize()const { return m_winSize; }
	bool isOpen() { return m_isOpen; }
	sf::RenderWindow * getWindow() { return &win; }
	void setFocus(const bool & focusFlag);
	void close(EventDetails  * evinfo);
	void beginDraw(const sf::Color & color=sf::Color::Black);
	void endDraw();
	EventManager * GetEventManager() { return &m_evManager; }
	void Update();
private:
	EventManager m_evManager;
	sf::String m_gameTitle;
	sf::RenderWindow win;
	bool m_fullScreen;
	bool m_focus;
	bool m_isOpen;
	sf::Vector2u m_winSize;
	void create();
};

