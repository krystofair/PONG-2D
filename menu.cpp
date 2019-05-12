//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <cassert>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "menu.h"


MainMenu::MainMenu(std::list<void(*)()> callback_list)
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	std::list<void(*)()>::iterator f = callback_list.begin();
	opcje.emplace_back("Start", font, *f);
	f = std::next(f);
	opcje.emplace_back("Zmieñ sterowanie", font, *f);
	f = std::next(f);
	opcje.emplace_back("Poka¿ wyniki", font, *f);
	f = std::next(f);
	opcje.emplace_back("Wyjœcie", font, *f);
	f = std::next(f);
	assert(f == callback_list.end());
    int i=200;
    for(auto& item : opcje)
    {
        item.setPosition(300, i);
        i+=item.getCharacterSize()+5;
    }
	zaznaczona = opcje.begin();
	zaznaczona->setFillColor(sf::Color::Blue);
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
	t->uruchom();
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

void MainMenu::setCallback(std::list<OptionType>::iterator ito,
						   void(*f)())
{
	//ito->callback = f;
}

PauseMenu::PauseMenu(void(*f)())
{
	opcje.pop_front();
	//opcje.emplace_front("Resume", font, f);
}
