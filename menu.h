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
	MainMenu();
	virtual ~MainMenu();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Font font;
};

/**
 * Klasa przedstawiająca menu pauzy w grze.
 */
class PauseMenu : public IMenu, public sf::Drawable
{
public:
	PauseMenu();
	virtual ~PauseMenu();
protected:
	void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default)const;
private:
	sf::Font font;
};

/// Polecenie rozpoczęcia gry z jednym graczem;
class StartOnePlayer : public ICommand
{
public:
	StartOnePlayer(){}
	void execute();
};

/// Polecenie rozpoczęcia gry z dwojgiem graczy.
class StartTwoPlayer : public ICommand
{
public:
	StartTwoPlayer(){}
	void execute();
};

/// Ustawienie nowych zestawów klawiszy dla graczy.
class ZmienSterowanie : public ICommand
{
public:
	ZmienSterowanie(){}
	void execute(){};
};

/// Wyświetlanie tablicy wynikow najlepszych graczy.
class ViewResults : public ICommand
{
public:
	ViewResults(){}
	void execute(){}
};

/// Wznowienie gry poprzez zmiane stanu gry.
class Resume : public ICommand
{
public:
	Resume(){}
	void execute();
};

/// Powrot do menu głównego z pauzy.
class Powrot : public ICommand
{
public:
	Powrot(){}
	void execute();
};

/// Wyjście z gry
/**
* Polecenie zwolni wszystkie zasoby pobrane przez program.
*/
class Wyjscie : public ICommand
{
private:
	IMenu* imenu;
public:
	Wyjscie(IMenu* im) 
		: imenu(im){};
	void execute();
};

#endif //PONG_MENU_H
