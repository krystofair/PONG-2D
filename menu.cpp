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
	if (!font.loadFromFile("Font/calibri.ttf")) exit(10);
	opcje.emplace_back("Uruchom gre", font);
	opcje.emplace_back("Zmien sterowanie", font);
	opcje.emplace_back("Wyjscie", font);
	zaznaczona = &opcje.front();
	zaznaczona->setFillColor(sf::Color::Blue);

	int i = 0;
	for (auto& item : opcje)
	{
		item.setPosition(200, i);
		i += item.getCharacterSize() + 5;
	}
}

void Menu::zaznaczOpcje(OptionType* t)
{
	if (t == nullptr) return;
	t->setFillColor(sf::Color::Blue);
	zaznaczona = t;
}

void Menu::odznaczOpcje()
{
	if (zaznaczona == nullptr) return;
	zaznaczona->setFillColor(sf::Color::White);
	zaznaczona = nullptr;

}

void Menu::uruchomOpcje(OptionType *t)
{

}

IMenu::OptionType* Menu::getZaz()
{
	return zaznaczona;
}

IMenu::Kontener<IMenu::OptionType>& Menu::getKontOpcji()
{
	return opcje;
}

void Menu::draw(sf::RenderTarget &target,
	sf::RenderStates states = sf::RenderStates::Default) const
{
	for (auto& item : opcje)
		target.draw(item, states);
}
