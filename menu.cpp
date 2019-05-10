//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <Windows.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "menu.h"

void f() {
}
MainMenu::MainMenu()
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf")) throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back("Start", font, f);
	opcje.emplace_back("Ustaw sterowanie", font, f);
	opcje.emplace_back("Wyniki", font, f);
	opcje.emplace_back("Wyjscie", font, f);
    zaznaczona = opcje.begin();
    zaznaczona->setFillColor(sf::Color::Blue);
    int i=200;
    for(auto& item : opcje)
    {
        item.setPosition(300, i);
        i+=item.getCharacterSize()+5;
    }
}

bool MainMenu::zaznaczOpcje(std::list<OptionType>::iterator t)
{
    t->setFillColor(sf::Color::Blue);
    zaznaczona = t;
	return true;
}

bool MainMenu::odznaczOpcje()
{
	zaznaczona->setFillColor(sf::Color::White);
	zaznaczona = opcje.end();
	return true;
}

void MainMenu::uruchomOpcje(std::list<OptionType>::iterator t)
{
	if(t->getString() == "Wyjscie") exit(0);
	else t->uruchom();
}

std::list<OptionType>::iterator MainMenu::getZaz()
{
    return zaznaczona;
}

std::list<OptionType>& MainMenu::getKontOpcji()
{
    return opcje;
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const
{
	for (auto& item : opcje)
		target.draw(item, states);
}
