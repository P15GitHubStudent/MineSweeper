#include<iostream>
#include"Game.h"

int main() {


	try {

		Game Game(sf::Vector2u(500, 500));

		Game.run();
	
	}
	catch (...) {
		std::cout << "Exception! " << std::endl;
	}

	return EXIT_SUCCESS;

}