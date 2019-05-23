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
	MainMenu(IGracz* g1, IGracz* g2);
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
	PauseMenu(IGracz* g1, IGracz* g2);
	/// W destruktorze menu usuwa własne opcji.
	/// W opcji jest usuwanie własnych poleceń.
	virtual ~PauseMenu();
protected:
	void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default)const;
private:
	sf::Font font;
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
	ViewResults(){}
	void excute(){}
};


class Resume : public ICommand
{
public:
	Resume(){}
	void execute();
};

class Wyjscie : public ICommand
{
private:
	IMenu* imenu;
	IGracz* gracz1;
	IGracz* gracz2;
public:
	Wyjscie(IMenu* im, IGracz* g1, IGracz* g2) 
		: imenu(im), gracz1(g1), gracz2(g2){};
	void execute()
	{
		if(imenu) delete imenu;
		if(gracz1) delete gracz1;
		if(gracz2) delete gracz2;
		exit(0);
	}

};

#endif //PONG_MENU_H
