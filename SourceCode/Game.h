#pragma once

#include<SFML/Graphics.hpp>
#include "window.h" 
//#include"Board.h"
#include "EventManager.h"
#include "SharedContext.h"
#include "StateManager.h"

class Game
{
public:
	Game(const sf::Vector2u & ScreenDimensions);
	~Game()=default;
	void run();

private:
	StateManager m_stateMgr;
	SharedContext m_sharedContext;
	//Board m_Board;
	sf::Clock m_clock;
	sf::Time m_time;
	float m_elapsed;
	void draw();
	void Update();
	window window;

 
};

