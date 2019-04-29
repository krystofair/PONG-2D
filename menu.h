//
// Created by Christofair on 25.04.2019.
//

#include <SFML/Graphics/Text.hpp>
#include "IMenu.h"

#ifndef PONG_MENU_H
#define PONG_MENU_H

/**
 * Klasa dziedziczy po interfejsie `IMenu` więc znane jest przeznaczenie jej metod.
 * Menu jest próbne
 */
class Menu : public IMenu, public sf::Drawable
{
public:
    using OptionType = IMenu::OptionType;
    Menu();

    virtual ~Menu() = default;

    bool zaznaczOpcje(Menu::Kontener<OptionType>::iterator);

    bool odznaczOpcje();

    void uruchomOpcje(Menu::Kontener<OptionType>::iterator);

    Kontener<OptionType>::iterator getZaz();

    Kontener<OptionType>& getKontOpcji();

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Font font;
};

#endif //PONG_MENU_H
