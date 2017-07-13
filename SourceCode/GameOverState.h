
#ifndef  _GAMEOVERSTATE_H
#define _GAMEOVERSTATE_H

#include"BaseState.h"
#include<SFML\Graphics.hpp>


class GameOver_State:public BaseState{

public:
	GameOver_State(StateManager * mStateMgr);
	~GameOver_State() = default;

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

private:
	sf::RectangleShape m_Rect;
	sf::Text m_text;
	sf::Font m_font;
	sf::RectangleShape m_OptionsRect[2];
	sf::Text m_optionsText[2];

	const sf::Color BACKGOUND_COLOR;

};


#endif // ! _GAMEOVERSTATE_H


