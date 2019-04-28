
using namespace std;

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "sterowanie.h"
#include "menu.h"



int main()
{
	//sf::Window window(sf::VideoMode(800, 600), "SFML works!");
	sf::RenderWindow window(sf::VideoMode(800, 600),"niedzialaLOLZ");
	Menu moje_menu = Menu();
	Sterowanie sterowanie(Sterowanie::STAN::MENU);
	sterowanie.setMenu(&moje_menu);

	float i = 0;

	while (true)
	{
		i = 0;
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				sterowanie(event);
		}

		window.clear(sf::Color::Black);
		window.draw(moje_menu);

		window.display();

	}

	return 0;
}
