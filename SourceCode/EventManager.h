#pragma once

#include<vector>
#include<unordered_map>
#include<string>
#include<functional>
#include<memory> 
#include<SFML\Graphics.hpp>

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo {

	EventInfo(int code=-1) :m_code(code) {

	}
	union {
		int m_code;
	};
	
};

struct EventDetails {
	EventDetails(const std::string& l_bindName)
		: m_name(l_bindName) {
		Clear();
	}
	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode; // Single key code.

	void Clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;



struct Binding {

	Binding(const std::string & bindName):m_name(bindName), m_details(bindName),c(0){
	}

	void bindEvent(EventType evType,int code=-1){
		m_events.emplace_back(evType, EventInfo(code));
		
	}

	std::string m_name;
	Events m_events;
	int c;
	EventDetails m_details;


};

using Callbacks = std::unordered_map < std::string, std::function<void(EventDetails *)>>;

using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;


class EventManager {

public:
	
	bool AddBinding(std::unique_ptr<Binding> bind);
	bool RemoveBinding(const std::string & bindingName);
	void setFocus(const bool & focus);
	void HandleEvent(sf::Event & ev);
	void Update();

	
	template<class T>
	bool AddCallback(const std::string & l_name,void (T::*fncPtr)(EventDetails *),T * l_instance) {

		auto temp = std::bind(fncPtr, l_instance, std::placeholders::_1);
		return m_callbacks.emplace(l_name, temp).second;

	}

	bool RemoveCallback(const std::string & l_name) {

		auto found = m_callbacks.find(l_name);
		if (found == m_callbacks.end())return false;
		m_callbacks.erase(found);
		return true;
	
	}


	EventManager() :m_Focus(true) {

	}


	sf::Vector2i GetMousePos(sf::RenderWindow * win = nullptr) {
		return win == nullptr ? sf::Mouse::getPosition() : sf::Mouse::getPosition(*win);
	}

private:
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_Focus;

};
