#pragma once

#include<SFML\Graphics.hpp>
#include"StateManager.h"
#include"BaseState.h"
#include"Board.h"




class Play_State : public BaseState
{
public:
	Play_State(StateManager * l_stateMgr);
	~Play_State();

	void OnCreate();
	void OnDestroy();
	void Activate();
	void Deactivate();

	virtual void Update(const sf::Time& l_time);
	virtual void Draw();

private:
	Board m_board;

};

