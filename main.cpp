
using namespace std;

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "sterowanie.h"
#include "menu.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),
            "PONG");
    Menu moje_menu = Menu();
	//Gracz *player1;
	//Gracz *player2;
    Sterowanie sterowanie(Sterowanie::STAN::MENU);
    sterowanie.setMenu(&moje_menu);
	//sterowanie.setGracz(player1, 1);
    float i =0;

    while (window.isOpen())
    {
        i=0;
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                sterowanie(event);
        }

        window.clear(sf::Color::Black);
        window.draw(moje_menu);

        window.display();

    }

    return 0;
}
