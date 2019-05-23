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

int main()
{
	sf::RenderWindow window(
		sf::VideoMode(screen_width, screen_height),"xPONG 2D"
	);
	IGracz *gracz1 = nullptr;
	IGracz *gracz2 = nullptr;
	IMenu* current_menu = new MainMenu(gracz1, gracz2);

	Sterowanie sterowanie(dynamic_cast<Gracz*>(gracz1),
						  dynamic_cast<Gracz*>(gracz2),
						  current_menu);

	sf::Event event{};
	//sf::Clock time;
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
					case STATE::MENU: sterowanie.menus(event); break;
					case STATE::GRA: sterowanie.games(event); break;
				}
			}
		}
		window.clear(sf::Color::Black);
		switch(stan_gry)
		{
			case STATE::MENU:
				current_menu = sterowanie.getMenu();
				if(auto menu = dynamic_cast<MainMenu*>(current_menu))
				{
					window.draw(*menu);
				}
				else if(auto menu = dynamic_cast<PauseMenu*> (current_menu))
				{
					window.draw(*menu);
				}
				break;
			case STATE::GRA:
				break;
		}

		window.display();
	}
	return 0;
}
