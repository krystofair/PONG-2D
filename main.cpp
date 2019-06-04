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
		sf::VideoMode(screen_width, screen_height),"xPONG 2D"
	);
	IGracz gracz1(nullptr);
	IGracz gracz2{nullptr};
	Rakieta *r1, *r2;
	IMenu* current_menu;

	sf::Event event{};
	//sf::Clock time;

	stan_gry = STAN::MENU;
	current_menu = new MainMenu(&gracz1, &gracz2);
	stery.setMenu(current_menu);
	while(window.isOpen())
	{
		current_menu = stery.getMenu();
		r1 = gracz1.getRakieta();
		r2 = gracz2.getRakieta();
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
		switch(stan_gry)
		{
			case STATE::PAUZA:
				if(!current_menu) current_menu = new PauseMenu(&gracz1, &gracz2);
			case STATE::MENU:
				if(!current_menu) current_menu = new MainMenu(&gracz1, &gracz2);
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::GRA:
			{
				delete current_menu;
				current_menu = nullptr;
				if(r1) window.draw(*r1);
				if(r2) window.draw(*r2);
				break;
			}
		}

		window.display();
	}
	return 0;
}
