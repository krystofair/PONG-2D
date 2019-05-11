
using namespace std;

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "sterowanie.h"
#include "menu.h"


enum STAN
{
	MENU, GRA
};

static STAN stan_gry = STAN::MENU;
Gracz* gracz1;
Gracz* gracz2;
Rakieta* rakieta1;
Rakieta* rakieta2;

void Exit()
{
	exit(0);
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");

	Sterowanie sterowanie(Sterowanie::STAN::MENU);
	MainMenu main_menu({Exit, Exit, Exit, Exit});
	sterowanie.setMenu(&main_menu);
	//sterowanie.setGracz(gracz1, 1);
	//sterowanie.setGracz(gracz2, 2);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed);
				sterowanie(event);
		}

		window.clear(sf::Color::Black);
		window.draw(main_menu);
		//window.draw(player1->getRakieta());

		window.display();

	}

	return 0;
}
