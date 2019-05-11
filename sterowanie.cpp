#include "sterowanie.h"


void Sterowanie::operator()(sf::Event e)
{
	switch(stan)
	{
		case MENU:
		{
			/* jeśli nie ma obiektu menu, a stan gry jest w stanie MENU to wystąpi błąd. */
		    if(imenu == nullptr) throw("brakuje menu dla operacji");
			if(e.key.code == Klawisz::Enter)
			{
			    imenu->uruchomOpcje(imenu->getZaz());
			}
			else if(e.key.code == Klawisz::Up)
			{
				auto zaz = imenu->getZaz();
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
			}
			else if(e.key.code == Klawisz::Down)
			{
			    auto zaz = imenu->getZaz();
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
			}
			break;
		}
		case GRA:
		{
			if(e.key.code == gracz1->getKlawisz(0))
			{
				Rakieta& R = gracz1->getRakieta();
				auto pozY = R.getPozY();
				auto dl = R.getDlugosc();
				R.setPozY(pozY - (dl/3+1));
			}
			else if(e.key.code == gracz2->getKlawisz(0))
			{
				Rakieta& R = gracz2->getRakieta();
				auto pozY = R.getPozY();
				auto dl = R.getDlugosc();
				R.setPozY(pozY - (dl/3+1));
			}
			else if(e.key.code == gracz1->getKlawisz(1))
			{

			}
			else if(e.key.code == gracz2->getKlawisz(1))
			{

			}
			else if(e.key.code == Klawisz::Escape)
			{
				stan = STAN::MENU;
			}
			break;
		}
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

void Sterowanie::zmienStan(STAN s)
{
	stan = s;
}
