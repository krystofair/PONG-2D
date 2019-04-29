#include "sterowanie.h"


void Sterowanie::operator()(sf::Event e)
{
	switch(stan)
	{
		case MENU:
		{
			/* jeśli nie ma obiektu menu, a stan gry jest w stanie MENU to wystąpi błąd. */
		    if(imenu == nullptr) exit(-1);
			/* klawisz potwierdzający wybór */
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
			}
			else if(e.key.code == Klawisz::Down)
			{
			    auto zaz = imenu->getZaz();
				if (std::next(zaz) != imenu->getKontOpcji().end())
				{
					imenu->odznaczOpcje();
					imenu->zaznaczOpcje(std::next(zaz));
				}
			}
			break;
		}
		case GRA:
		{
			if(e.key.code == gracz1->getKlawisz(0))
			{

			}
			else if(e.key.code == gracz2->getKlawisz(0))
			{

			}
			else if(e.key.code == gracz1->getKlawisz(1))
			{

			}
			else if(e.key.code == gracz2->getKlawisz(1))
			{

			}
			break;
		}
	}
}

void Sterowanie::zmienStan(STAN inny_stan) {
    stan = inny_stan;
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
