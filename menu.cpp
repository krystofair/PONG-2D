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

MainMenu::MainMenu(IGracz* g1, IGracz* g2)
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back("Zagraj z komputerem.", font, new StartOnePlayer(g1, g2));
	opcje.emplace_back("Zagraj z przyjacielem.", font, new StartTwoPlayer(g1, g2));
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
	stan_gry = STAN::GRA;
	Rakieta* r = new Rakieta(1, 1, 10, 100);
	gracz1 = new Gracz(*r, 1);
	Rakieta* r2 = new Rakieta(800, 1, 10, 100);
	//si = new klasaSI(*r, 2);
}


void StartTwoPlayer::execute()
{
	stan_gry = STAN::GRA;
	auto rakieta1 = new Rakieta(1, 1, 10, 100); // rakieta dla human
	auto rakieta2 = new Rakieta(800, 1, 10, 100); // rakieta dla SI
	gracz1 = new Gracz(*rakieta1, 1);
	gracz2 = new Gracz(*rakieta2, 2);
}


PauseMenu::PauseMenu(IGracz* g1, IGracz* g2)
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back(L"Odpauzuj", font, new Resume());
	opcje.emplace_back(L"Nowa gra", font, nullptr);
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

}