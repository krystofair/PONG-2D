//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <cassert>
#include <algorithm>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "menu.h"
#include "globals.h"

// usuwanie swoich opcji
MainMenu::~MainMenu()
{
	std::for_each(opcje.begin(), opcje.end(),
				  [](auto option){ if(option.polecenie) delete option.polecenie; });
}

MainMenu::MainMenu()
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back("Zagraj z komputerem.", font, new StartOnePlayer());
	opcje.emplace_back("Zagraj z przyjacielem.", font, new StartTwoPlayer());
	opcje.emplace_back(L"Zmieñ sterowanie", font, new ZmienSterowanie());
	opcje.emplace_back(L"Poka¿ wyniki", font, nullptr);
	opcje.emplace_back(L"Wyjœcie", font, new Wyjscie(this));
    int i=200;
    for(auto& item : opcje)
    {
        item.setPosition(300, i);
        i+=item.getCharacterSize()+5;
    }
	zaznaczOpcje(opcje.begin());
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const
{
	for (auto& item : opcje)
		target.draw(item, states);
}


//commands to MainMenu

void StartOnePlayer::execute()
{
	auto middle = plansza.getHeight()/2-50;
	Rakieta* rsi = new Rakieta(4, middle, 10, 100); // rakieta dla si.
	Rakieta* rh = new Rakieta(786, middle, 10, 100); // rakieta dla human.
	auto gracz1 = plansza.createPlayer(rh, 1);
	
	plansza.createPlayer(rsi, 3);
	stery.setGracz(static_cast<Gracz*>(gracz1), 1);
	plansza.createPilka();
	stan_gry = STAN::GRA;
}


void StartTwoPlayer::execute()
{
	auto middle = plansza.getHeight()/2-50;
	auto rakieta1 = new Rakieta(786, middle, 10, 100); // rakieta dla pierwszego gracza.
	auto rakieta2 = new Rakieta(4, middle, 10, 100); // rakieta dla drugiego gracza.
	auto g1 = plansza.createPlayer(rakieta2, 1);
	auto g2 = plansza.createPlayer(rakieta1, 2);
	static_cast<Gracz*>(g1)->setKlawisze(Klawisz::W, Klawisz::A);
	static_cast<Gracz*>(g2)->setKlawisze(Klawisz::P, Klawisz::L);
	stery.setGracz(static_cast<Gracz*> (g1), 1);
	stery.setGracz(static_cast<Gracz*> (g2), 2);
	plansza.createPilka();
	stan_gry = STAN::GRA;
}


PauseMenu::PauseMenu()
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back(L"Odpauzuj", font, new Resume());
	opcje.emplace_back(L"PrzejdŸ do menu g³ównego",font, new Powrot());
	//opcje.emplace_back(L"Nowa gra", font, nullptr);
	opcje.emplace_back(L"Wyjœcie", font, new Wyjscie(this));
	int i=200;
	for(auto& item : opcje)
	{
		item.setPosition(300, i);
		i+=item.getCharacterSize()+5;
	}
	zaznaczOpcje(opcje.begin());
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	for(auto& opcja : opcje)
		target.draw(opcja, states);
}

PauseMenu::~PauseMenu()
{
	for_each(opcje.begin(), opcje.end(),
			 [](auto opcja){ if(opcja.polecenie) delete opcja.polecenie; });
}

void Resume::execute()
{
	stan_gry = STAN::GRA;
}

void Powrot::execute()
{
	auto g1 = plansza.getGracz(1);
	auto g2 = plansza.getGracz(2);
	if(g1) if(g1->getRakieta()) {
		delete g1->getRakieta(); g1->setRakieta(nullptr);
		plansza.deletePlayer(1);
	}
	if(g2) if(g2->getRakieta()) {
		delete g2->getRakieta(); g2->setRakieta(nullptr);
		plansza.deletePlayer(2);
	}
	if(plansza.getPilka()) plansza.deletePilka();
	stery.setMenu(new MainMenu());
	stan_gry = STAN::MENU;
}

void Wyjscie::execute()
{
	auto g1 = plansza.getGracz(1);
	auto g2 = plansza.getGracz(2);
	auto pilka = plansza.getPilka();
	if(g1) if(g1->getRakieta()) {
		delete g1->getRakieta(); g1->setRakieta(nullptr);
		plansza.deletePlayer(1);
	}
	if(g2) if(g2->getRakieta()) {
		delete g2->getRakieta(); g2->setRakieta(nullptr);
		plansza.deletePlayer(2);
	}
	if(pilka) delete pilka;
	delete imenu;
	//window.close();
	exit(0);
}