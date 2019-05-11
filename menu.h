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
	MainMenu() = default;
	MainMenu(std::list<void(*)()>);

    virtual ~MainMenu() = default;
    bool zaznaczOpcje(std::list<OptionType>::iterator);
    bool odznaczOpcje();
    void uruchomOpcje(std::list<OptionType>::iterator);
    std::list<OptionType>::iterator getZaz();
    std::list<OptionType>& getKontOpcji();

	/**
	 * Ustawienie funkcji zwrotnej dla pojedynczej
	 * opcji w menu.
	 */
	void setCallback(std::list<OptionType>::iterator, void (*)());
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Font font;
};

class PauseMenu : public MainMenu
{
    PauseMenu();
	PauseMenu(void(*)());
    virtual ~PauseMenu() = default;
};

#endif //PONG_MENU_H
