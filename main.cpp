
using namespace std;


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "sterowanie.h"
#include "gameapp.h"

using STATE = GameApp::STAN;
STATE GameApp::stan_gry = STATE::MENU;

int main()
{
	GameApp game_app;
	sf::RenderWindow window(sf::VideoMode(game_app.screen_width, game_app.screen_height), "xPONG 2D");
	Sterowanie sterowanie;

	game_app.current_menu = new MainMenu(game_app.gracz1, game_app.gracz2);
	sterowanie.setMenu(game_app.current_menu);

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
				switch(game_app.stan_gry)
				{
					case STATE::MENU: sterowanie.menus(event); break;
					case STATE::GRA: sterowanie.games(event); break;
				}
			}
		}
		window.clear(sf::Color::Black);
		switch(game_app.stan_gry)
		{
			case STATE::MENU:
				game_app.menu_instr(window);
				break;
			case STATE::GRA:
				game_app.gameloop(window);
				break;
		}

		window.display();
	}
	return 0;
}
