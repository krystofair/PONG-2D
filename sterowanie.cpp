#include "sterowanie.h"
#include "gameapp.h"


void Sterowanie::menus(sf::Event& e)
{
	/* jeśli nie ma obiektu menu, a stan gry jest w stanie MENU to wystąpi błąd. */
	if(imenu == nullptr) throw("brakuje menu");
	auto zaz = imenu->getZaz();
	switch(e.key.code)
	{
		
		case Klawisz::Enter:
			imenu->uruchomOpcje(imenu->getZaz());
			break;
		case Klawisz::Up:
			//auto zaz = imenu->getZaz();
			if(zaz != imenu->getKontOpcji().begin())
			{
				imenu->odznaczOpcje();
				imenu->zaznaczOpcje(std::prev(zaz));
			}
			else
			{
				imenu->odznaczOpcje();
				imenu->zaznaczOpcje(std::prev(imenu->getKontOpcji().end()));
			}
			break;
		case Klawisz::Down:
			//auto zaz = imenu->getZaz();
			if(std::next(zaz) != imenu->getKontOpcji().end())
			{
				imenu->odznaczOpcje();
				imenu->zaznaczOpcje(std::next(zaz));
			}
			else
			{
				imenu->odznaczOpcje();
				imenu->zaznaczOpcje(imenu->getKontOpcji().begin());
			}
			break;
		default:
			zaz->setFillColor(sf::Color::Green);
	}
}

void Sterowanie::games(sf::Event& e)
{
	if(gracz1 = dynamic_cast<Gracz*>(gracz1))
	{
		if(e.key.code == gracz1->getKlawisz(0))
		{
			Rakieta& R = gracz1->getRakieta();
			auto pozY = R.getPozY();
			auto dl = R.getDlugosc();
			R.setPozY(pozY - (dl/3+1));
			//R.moveTo(pozY+ batspeed);
		}
		else if(e.key.code == gracz1->getKlawisz(1)) {} // na razie ta instrukcja jest pusta.
	}
	if(gracz2 = dynamic_cast<Gracz*>(gracz2))
	{
		if(e.key.code == gracz2->getKlawisz(0))
		{

			Rakieta& R = gracz2->getRakieta();
			auto pozY = R.getPozY();
			auto dl = R.getDlugosc();
			R.setPozY(pozY - (dl/3+1));
		}
		else if(e.key.code == gracz2->getKlawisz(1)) {} //na razie ta instrukcja jest pusta.
	}
	if(e.key.code == Klawisz::Escape)
	{
		GameApp::stan_gry = GameApp::STAN::MENU;
		delete imenu;
		imenu = new PauseMenu(gracz1, gracz2);
	}
}

void Sterowanie::setGracz(Gracz *g, int who)
{
	switch(who)
	{
		case 1: gracz1 = g; break;
		case 2: gracz2 = g; break;
		default: gracz1 = g;
	}
}

void Sterowanie::setMenu(IMenu* m)
{
	imenu = m;
}