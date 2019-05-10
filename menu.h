//
// Created by Christofair on 25.04.2019.
//

#include <SFML/Graphics/Text.hpp>
#include "IMenu.h"

#ifndef PONG_MENU_H
#define PONG_MENU_H

/**
 * Klasa Menu jest implementacją głównego menu, które jest wyświetlane na początku.
 * Klasa dziedziczy po interfejsie `IMenu` więc znane jest przeznaczenie jej metod.
 * Opcje menu są przechowywane w kontenerze z biblioteki standardowej tj. std::list
 */
class MainMenu : public IMenu, public sf::Drawable
{
public:
    MainMenu();

    virtual ~MainMenu() = default;
    bool zaznaczOpcje(std::list<OptionType>::iterator);
    bool odznaczOpcje();
    void uruchomOpcje(std::list<OptionType>::iterator);
    std::list<OptionType>::iterator getZaz();
    std::list<OptionType>& getKontOpcji();
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Font font;
};

#endif //PONG_MENU_H
