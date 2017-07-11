#include"EventManager.h"
#include<iostream>


bool EventManager::AddBinding(std::unique_ptr<Binding> bind) {
	bool success = true;
	success=m_bindings.emplace(bind->m_name, std::move(bind)).second;
	return success;
}

bool EventManager::RemoveBinding(const std::string & l_name) {

	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end())return false; 
	m_bindings.erase(itr);
	return true;

}

void EventManager::setFocus(const bool & focus) {
	m_Focus = focus;
}

void EventManager::Update() {
	if (!m_Focus) { return; }
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second.get();
		for (auto &e_itr : bind->m_events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
							
				break;
			}
		}

		if (bind->m_events.size() == bind->c) {

			auto callItr = m_callbacks.find(bind->m_name);
			if (callItr != m_callbacks.end()) {			
				callItr->second(&bind->m_details);
			}
		}

		bind->c = 0;

	}
}




void EventManager::HandleEvent(sf::Event& l_event) {
	// Handling SFML events.
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second.get();
		for (auto &e_itr : bind->m_events) {
			EventType sfmlEvent = (EventType)l_event.type;
			if (e_itr.first != sfmlEvent) { continue; }
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (e_itr.second.m_code == l_event.key.code) {
					// Matching event/keystroke.
					// Increase count.
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (e_itr.second.m_code == l_event.mouseButton.button) {
					// Matching event/keystroke.
					// Increase count.
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_details.m_textEntered = l_event.text.unicode;
				}

				++(bind->c);

				//std::cout << "Binding Name is  : " << bind->m_name << " counter is ! : " << bind->c << std::endl;

			}
		}
	}
}

