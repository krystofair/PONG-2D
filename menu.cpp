//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <cassert>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "menu.h"
#include "gameapp.h"

// usuwanie swoich poleceñ.
MainMenu::~MainMenu()
{
	for(auto& i : polecenia)
	{
		if(i != nullptr);
		delete i;
	}
}

MainMenu::MainMenu(IGracz* g1, IGracz* g2)
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	polecenia.push_back(new StartOnePlayer(g1, g2));
	polecenia.push_back(new StartTwoPlayer(g1, g2));
	polecenia.push_back(new ZmienSterowanie());
	opcje.emplace_back("Zagraj z komputerem.", font, polecenia[0]);
	opcje.emplace_back("Zagraj z przyjacielem.", font, polecenia[1]);
	opcje.emplace_back("Zmien sterowanie", font, polecenia[2]);
	opcje.emplace_back("Pokaz wyniki", font, nullptr);
	opcje.emplace_back("Wyjscie", font, nullptr);
    int i=200;
    for(auto& item : opcje)
    {
        item.setPosition(300, i);
        i+=item.getCharacterSize()+5;
    }
	zaznaczona = opcje.begin();
	zaznaczona->setFillColor(sf::Color::Red);
}

bool MainMenu::zaznaczOpcje(std::list<OptionType>::iterator t)
{
    t->setFillColor(sf::Color::Red);
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

void MainMenu::setCommand(std::list<OptionType>::iterator ito, ICommand* command)
{
	if(ito->polecenie != nullptr)
		ito->polecenie = command;
	else
	{
		delete ito->polecenie;
		ito->polecenie = command;
	}
}

//commands to MainMenu

void StartOnePlayer::execute()
{
	GameApp::stan_gry = GameApp::GRA;
	Rakieta* r = new Rakieta(1, 1, 10, 100);
	gracz1 = new Gracz(*r, 1);
	Rakieta* r2 = new Rakieta(800, 1, 10, 100);
	//si = new klasaSI(*r, 2);
}


void StartTwoPlayer::execute()
{
	GameApp::stan_gry = GameApp::GRA;
	auto rakieta1 = new Rakieta(1, 1, 10, 100); // rakieta dla human
	auto rakieta2 = new Rakieta(800, 1, 10, 100); // rakieta dla SI
	gracz1 = new Gracz(*rakieta1, 1);
	gracz2 = new Gracz(*rakieta2, 2);
}


PauseMenu::PauseMenu(IGracz* g1, IGracz* g2) : MainMenu(g1, g2)
{
	delete opcje.begin()->polecenie;
	opcje.pop_front();
	delete opcje.begin()->polecenie;
	setCommand(opcje.begin(), new Resume());
	opcje.begin()->setString("Resume");
	zaznaczona = opcje.begin();
	zaznaczona->setFillColor(sf::Color::Red);
}

void Resume::execute()
{

}