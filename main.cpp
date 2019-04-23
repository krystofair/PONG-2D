
using namespace std;

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main()
{
    //sf::Window window(sf::VideoMode(800, 600), "SFML works!");
    sf::RenderWindow window(sf::VideoMode(1920,1080), "cocoo", sf::Style::Fullscreen);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }

    return 0;
}
