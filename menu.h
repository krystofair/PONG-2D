//
// Created by Christofair on 25.04.2019.
//

#include <SFML/Graphics/Text.hpp>
#include "IMenu.h"
#include "IGracz.h"
#include "sterowanie.h"

#pragma once

#ifndef PONG_MENU_H
#define PONG_MENU_H

/** 
* Klasa MainMenu
* Klasa MainMenu jest implementacją głównego menu, które jest wyświetlane na początku.
* Klasa dziedziczy po interfejsie `IMenu` więc znane jest przeznaczenie jej metod.
* U dokumentowane są metody, które nie zostały nadpisane z interfejsu.
* Opcje menu są przechowywane w kontenerze z biblioteki standardowej tj. std::list
*/
/// Details description
/// Menu zawiera opcje takie jak:
/// Start gry z sztuczną inteligencją,
/// Start gry z drugim człowiekiem,
/// Zmiane ustawień klawiszy,
/// Pokazanie wyników w top10,
/// Wyjście z programu.
class MainMenu : public IMenu, public sf::Drawable
{
public:
	//przyjmuje główny obiekt aplikacji gry, aby móc działać na jej obiektach.
	MainMenu(IGracz* g1, IGracz* g2);

	virtual ~MainMenu();
    bool zaznaczOpcje(std::list<OptionType>::iterator);
    bool odznaczOpcje();
    void uruchomOpcje(std::list<OptionType>::iterator);
    std::list<OptionType>::iterator getZaz();
    std::list<OptionType>& getKontOpcji();

	/**
	 * Ustawienie polecenia do wykonania dla pojedynczej
	 * opcji w menu.
	 * @param i: jest iteratorem, który wskazuje na opcje do której dopisać funkcje
	 * @param c: jest wskaźnikiem na polecenie o którym mowa wyżej, funktor do wykonania po wybraniu danej opcji.
	 */
	void setCommand(std::list<OptionType>::iterator i, ICommand* c);
	
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// wektor przechowujący wszystkie obiekty poleceń dla tejże implementacji menu.
	std::vector<ICommand*> polecenia;
    sf::Font font;
};

/**
 * Klasa pochodna po menu głównym,
 * która zmienia kilka opcji dla siebie.
 */
class PauseMenu : public MainMenu
{
public:
	PauseMenu(IGracz* g1, IGracz* g2);
	virtual ~PauseMenu() = default;
};

/// Polecenie rozpoczęcia gry z jednym graczem;
class StartOnePlayer : public ICommand
{
private:
	IGracz* gracz1;
	IGracz* si;
public:
	StartOnePlayer(IGracz* g1, IGracz* g2) : gracz1(g1), si(g2) {}
	void execute();
};

/// Polecenie rozpoczęcia gry z dwojgiem graczy.
class StartTwoPlayer : public ICommand
{
private:
	IGracz* gracz1;
	IGracz* gracz2;
public:
	StartTwoPlayer(IGracz* g1, IGracz* g2) : gracz1(g1), gracz2(g2) {}
	void execute();
};

class ZmienSterowanie : public ICommand
{
public:
	void execute(){}
};

class ViewResults : public ICommand
{
public:
	void excute(){}
};


class Resume : public ICommand
{
public:
	Resume(){}
	void execute();
};

#endif //PONG_MENU_H
