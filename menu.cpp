//
// Created by Christofair on 23.04.2019.
//

#include <list>
#include <cassert>
#include <algorithm>
#include <fstream>

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
	rsi->setStrona(false);
	Rakieta* rh = new Rakieta(786, middle, 10, 100); // rakieta dla human.
	rh->setStrona(true);
	auto gracz1 = plansza.createPlayer(rh, 1);
	
	plansza.createPlayer(rsi, 3);
	stery.setGracz(static_cast<Gracz*>(gracz1), 1);
	plansza.createPilka();
	stery.zwolnijMenu();
	stan_gry = STAN::GRA;
}


void StartTwoPlayer::execute()
{
	auto middle = plansza.getHeight()/2-50;
	auto rakieta1 = new Rakieta(786, middle, 10, 100); // rakieta dla pierwszego gracza.
	auto rakieta2 = new Rakieta(4, middle, 10, 100); // rakieta dla drugiego gracza.
	rakieta1->setStrona(true);
	rakieta2->setStrona(false);
	auto g1 = plansza.createPlayer(rakieta1, 1);
	auto g2 = plansza.createPlayer(rakieta2, 2);
	static_cast<Gracz*>(g1)->loadKeyboardSet();
	static_cast<Gracz*>(g2)->loadKeyboardSet();
	stery.setGracz(static_cast<Gracz*> (g1), 1);
	stery.setGracz(static_cast<Gracz*> (g2), 2);
	plansza.createPilka();
	stery.zwolnijMenu();
	stan_gry = STAN::GRA;
}


PauseMenu::PauseMenu()
{
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	opcje.emplace_back(L"Odpauzuj", font, new Resume());
	opcje.emplace_back(L"PrzejdŸ do menu g³ównego",font, new Powrot());
	opcje.emplace_back(L"Zmieñ sterowanie", font, new ZmienSterowanie());
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
	stery.zwolnijMenu();
	stan_gry = STAN::GRA;
}

void Powrot::execute()
{
	auto g1 = plansza.getGracz(1);
	auto g2 = plansza.getGracz(2);
	if(g1) if(g1->getRakieta()) {
		delete g1->getRakieta();
		g1->setRakieta(nullptr);
	}
	if(g2) if(g2->getRakieta()) {
		delete g2->getRakieta(); g2->setRakieta(nullptr);
	}
	plansza.deletePlayer(1);
	plansza.deletePlayer(2);
	plansza.deletePilka();
	stery.zwolnijMenu();
	stery.setMenu(new MainMenu());
	stan_gry = STAN::MENU;
}

void Wyjscie::execute()
{
	auto g1 = plansza.getGracz(1);
	auto g2 = plansza.getGracz(2);
	auto pilka = plansza.getPilka();
	if(g1) if(g1->getRakieta()) {
		delete g1->getRakieta();
		g1->setRakieta(nullptr);
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

void ZmienSterowanie::execute()
{
	bool koniec = false;
	sf::Font font;
	sf::Event eve{};
	int sch = plansza.getHeight();
	int scw = plansza.getWidth();
	if(!font.loadFromFile("C:\\WINDOWS\\Fonts\\calibri.ttf"))
		throw("brakuje czcionki w zasobach systemu.");
	sf::Text texts[] = {
		sf::Text(L"klawisz góra gracz 1.", font),
		sf::Text(L"klawisz dó³ gracz 1.", font),
		sf::Text(L"klawisz góra gracz 2.", font),
		sf::Text(L"klawisz dó³ gracz 2.", font)
	};
	int coY = 0;
	for(auto& item : texts)
	{
		item.setPosition(scw/3, sch/4+coY);
		coY += 35;
	}
	auto display = [&]{
		for(auto& item : texts)
		{
			window.draw(item);
		}
		window.display();
	};
	auto podaj_klawisz = [&](){
		sf::Event eve;
		auto text_klawisz = sf::Text(L"Wciœnij klawisz teraz...", font);
		text_klawisz.setPosition(plansza.getWidth()/3, plansza.getHeight()/2);
		while(true) {
			window.clear(sf::Color::Black);
			window.draw(text_klawisz);
			window.display();
			window.waitEvent(eve);
			if(eve.type == sf::Event::KeyPressed) return eve.key.code;
		}
	};
	auto zaznacz = [](sf::Text& t) {
		t.setFillColor(sf::Color::Red);
	};
	auto odznacz = [&]{
		for(auto& item : texts)
			if(item.getFillColor() == sf::Color::Red) item.setFillColor(sf::Color::White);
	};
	window.clear(sf::Color::Black);
	int index = 0;
	zaznacz(texts[index]);
	while(!koniec){
		while(window.waitEvent(eve))
		{
			if(eve.type == sf::Event::KeyPressed)
			{
				if(eve.key.code == Klawisz::Escape)
				{
					koniec = true;
					break;
				}
				if(eve.key.code == Klawisz::Up)
				{
					if(index > 0)
					{
						odznacz();
						zaznacz(texts[--index]);
					}
					else
					{
						index = 3;
						odznacz();
						zaznacz(texts[index]);
					}
				}
				if(eve.key.code == Klawisz::Down)
				{
					if(index < 3)
					{
						odznacz();
						zaznacz(texts[++index]);
					}
					else
					{
						index = 0;
						odznacz();
						zaznacz(texts[index]);
					}
				}
				if(eve.key.code == Klawisz::Enter)
				{
					auto kod = podaj_klawisz();
					if(index == 0 || index == 1)
					{
						Gracz* gracz1 = static_cast<Gracz*>(plansza.getGracz(1));
						if(gracz1)
						{
							if(index == 0)
								gracz1->setKlawisze(kod, gracz1->getKlawisz(1));
							else if(index == 1)
								gracz1->setKlawisze(gracz1->getKlawisz(0), kod);
							gracz1->saveKeyboardSet();
						}
						else
						{
							gracz1 = new Gracz(nullptr, 1);
							auto keys_set = gracz1->loadKeyboardSet();
							if(index == 0) keys_set.up = kod;
							else keys_set.down = kod;
							gracz1->setKlawisze(keys_set);
							gracz1->saveKeyboardSet();
							delete gracz1;
						}
					}
					else
					{
						IGracz* gracz = plansza.getGracz(2);
						if(gracz)
						{
							if(!gracz->checkSI())
							{
								auto player = static_cast<Gracz*>(gracz);
								if(index == 2)
									player->setKlawisze(kod, player->getKlawisz(1));
								else if(index == 3)
									player->setKlawisze(player->getKlawisz(0), kod);
								player->saveKeyboardSet();
							}
							else
							{
								auto player = new Gracz(nullptr, 1);
								auto keys_set = player->loadKeyboardSet();
								if(index == 2) keys_set.up = kod;
								else keys_set.down = kod;
								player->setKlawisze(keys_set);
								player->saveKeyboardSet();
								delete player;
							}
						}
					}
					
				}
			}
			window.clear(sf::Color::Black);
			display();
		}
	}
}