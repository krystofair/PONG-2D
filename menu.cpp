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
    if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf")) exit(10);
    opcje.emplace_back("Uruchom gre", font);
    opcje.emplace_back("Zmien sterowanie", font);
    opcje.emplace_back("Wyjscie", font);
    zaznaczona = opcje.begin();
    zaznaczona->setFillColor(sf::Color::Blue);
    int i=0;
    for(auto& item : opcje)
    {
        item.setPosition(200, i);
        i+=item.getCharacterSize()+5;
    }
}

bool Menu::zaznaczOpcje(Menu::Kontener<OptionType>::iterator t)
{
    //for(auto item = opcje.begin(); item != opcje.end(); item++)
    {
        //if(item == t)
        {
            t->setFillColor(sf::Color::Blue);
            zaznaczona = t;
            return true;
        }
    }
    return false;
}

bool Menu::odznaczOpcje()
{
    //for(auto item = opcje.begin(); item != opcje.end(); item++)
    {
        //if(item == zaznaczona)
        {
            zaznaczona->setFillColor(sf::Color::White);
            zaznaczona = opcje.end();
            return true;
        }
    }
    return false;
}

void Menu::uruchomOpcje(Menu::Kontener<OptionType>::iterator t)
{
    if(std::string(t->getString()) == "Wyjscie") exit(0);
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
