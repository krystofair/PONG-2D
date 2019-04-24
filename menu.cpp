//
// Created by Christofair on 23.04.2019.
//

#include <list>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "IMenu.h"


template <typename T>
class MainMenu: public IMenu<T>, public sf::Drawable
{
private:
    sf::Font font;
    std::list<sf::Text> opcje;
public:
    sf::Text* zaz_opcja{nullptr};
    MainMenu()
    {
        font.loadFromFile("Font/calibri.ttf");
        opcje.emplace_back("Uruchom gre", font);
        opcje.emplace_back("Zmien sterowanie", font);
        opcje.emplace_back("Wyjscie", font);
        zaz_opcja = &opcje.front();
        int i=0;
        for(auto& item : opcje)
        {
            item.setPosition(100, i);
            i+=item.getCharacterSize()+5;
        }

    }



    void zaznaczOpcje(sf::Text* t) override
    {
        t->setFillColor(sf::Color::Blue);
        zaz_opcja = t;

    }

    void odznaczOpcje(sf::Text* t) override
    {
        t->setFillColor(sf::Color::Black);
        zaz_opcja = nullptr;
    }
    void uruchomOpcje(sf::Text* t) override {}
    ~MainMenu(){}

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const
    {
        for(auto& opcja : opcje)
            target.draw(opcja, states);
    }
};

