#include <cassert>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "sterowanie.h"
#include "globals.h"

using namespace std;

int screen_width = 800;
int screen_height = 600;

STAN stan_gry = STATE::MENU;
Sterowanie stery;

int main()
{
	sf::RenderWindow window(
		sf::VideoMode(screen_width, screen_height), "xPONG 2D"
	);
	IGracz* gracz1{nullptr};
	IGracz* gracz2{nullptr};
	// wskazniki do wyswietlania
	Rakieta *r1, *r2;
	IMenu* current_menu;

	sf::Event event{};
	//sf::Clock time;

	stan_gry = STAN::MENU;
	stery.setMenu(new MainMenu(gracz1, gracz2));
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				switch(stan_gry)
				{
					case STATE::PAUZA:
					case STATE::MENU:
						stery.menus(event);
						break;
					case STATE::GRA:
						stery.games(event);
						break;
				}
			}
		}


		//drawing
		window.clear(sf::Color::Black);
		current_menu = stery.getMenu();
		r1 = gracz1->getRakieta();
		r2 = gracz2->getRakieta();
		switch(stan_gry)
		{
			case STATE::PAUZA:
			case STATE::MENU:
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::GRA:
			{
				stery.zwolnijMenu();
				if(r1) window.draw(*r1);
				if(r2) window.draw(*r2);
				break;
			}
		}

		window.display();
	}
	return 0;
}
