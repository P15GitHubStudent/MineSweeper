#pragma once

#include"BaseState.h"
#include<SFML\Graphics.hpp>
#include"EventManager.h"
#include"StateManager.h"
#include"Board.h"


class Play_State:public BaseState{

public:
	Play_State(StateManager * mStateMgr);
	~Play_State() = default;

	 void OnCreate();
	 void OnDestroy();

	 void Activate();
	 void Deactivate();

	 void Update(const sf::Time& l_time);
	 void Draw();

private:
	Board *  m_board;
	


};