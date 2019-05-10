
using namespace std;

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "sterowanie.h"
#include "menu.h"



int main()
{
	sf::RenderWindow window(sf::VideoMode(728,1024), "PONG", sf::Style::Fullscreen);
	MainMenu main_menu = MainMenu();
	//Gracz *player1;
	//Gracz *player2;
	Sterowanie sterowanie(Sterowanie::STAN::MENU);
	sterowanie.setMenu(&main_menu);
	//sterowanie.setGracz(player1, 1);
	//sterowanie.setGracz(player2, 2);
	float i = 0;

	while (window.isOpen())
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
		window.draw(main_menu);

		window.display();

	}

	return 0;
}


/* petelka prototype */
/* tylko dlaczego kursor mi kurwa przys³ania litery???? */
/* nie dzia³a prze³¹czanie okien, a to jest podstawa tego gówna xDDD*/
class Plansza
{
	static void inicjuj() {}
	static void pause(){}
};

/*
int main()
{
	Gracz *player1, *player2;
	Rakieta *r1, *r2;
	Planksza plansza;
	Menu menu;
	while(true)
	{
		if(stan == Sterowanie::STAN::GRA)
		{
			player1 = new Gracz(r1);
			if(!SIoption) player2 = new Gracz(r2);
			else new std::thread();
		}
	}


	return 0;
}
*/