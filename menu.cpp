//
// Created by Christofair on 23.04.2019.
//

#include <list>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "menu.h"



Menu::Menu()
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf")) throw("najlepiej wyrzuciæ wyj¹tek z tej okazji");
    opcje.emplace_back("Start", font);
    opcje.emplace_back("Ustaw sterowanie", font);
    opcje.emplace_back("Wyjscie", font);
    zaznaczona = opcje.begin();
    zaznaczona->setFillColor(sf::Color::Blue);
    int i=200;
    for(auto& item : opcje)
    {
        item.setPosition(300, i);
        i+=item.getCharacterSize()+5;
    }
}

bool Menu::zaznaczOpcje(Menu::Kontener<OptionType>::iterator t)
{
    t->setFillColor(sf::Color::Blue);
    zaznaczona = t;
	return true;
}

bool Menu::odznaczOpcje()
{
	zaznaczona->setFillColor(sf::Color::White);
	zaznaczona = opcje.end();
	return true;
}

void Menu::uruchomOpcje(Menu::Kontener<OptionType>::iterator t)
{
	if (std::string(t->getString()) == "Wyjscie") exit(0);
	else if (std::string(t->getString()) == "Start") throw("uruchamiam gre XD");
    //callback(t);
}

Menu::Kontener<Menu::OptionType>::iterator Menu::getZaz()
{
    return zaznaczona;
}

Menu::Kontener<Menu::OptionType>& Menu::getKontOpcji()
{
    return opcje;
}

void Menu::draw(sf::RenderTarget &target,
        sf::RenderStates states = sf::RenderStates::Default) const
{
    for(auto& item : opcje)
        target.draw(item, states);
}
