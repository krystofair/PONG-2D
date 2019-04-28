#include "sterowanie.h"


void Sterowanie::operator()(sf::Event e)
{
	switch (stan)
	{
	case MENU:
	{
		/* jeœli nie ma obiektu menu, a stan gry jest w stanie MENU to wyst¹pi b³¹d. */
		if (imenu == nullptr) exit(-1);
		/* klawisz potwierdzaj¹cy wybór */
		if (e.key.code == Klawisz::Enter)
		{
			//nic nie rób jak na razie
		}
		else if (e.key.code == Klawisz::Up)
		{
			auto zaz = imenu->getZaz();
			for (int i = 0; i < imenu->getKontOpcji().size(); ++i)
			{
				if (zaz == &imenu->getKontOpcji()[i])
				{
					if (i >= 1)
					{
						imenu->odznaczOpcje();
						imenu->zaznaczOpcje(&imenu->getKontOpcji()[i - 1]);
					}
				}
			}
		}
		else if (e.key.code == Klawisz::Down)
		{
			auto zaz = imenu->getZaz();
			for (int i = 0; i < imenu->getKontOpcji().size(); ++i)
			{
				if (zaz == &imenu->getKontOpcji()[i])
				{
					if (i < imenu->getKontOpcji().size() - 1)
					{
						imenu->odznaczOpcje();
						imenu->zaznaczOpcje(&imenu->getKontOpcji()[i + 1]);
					}
				}
			}
		}
		break;
	}
	case GRA:
	{
		if (e.key.code == gracz1->getKlawisz(0))
		{

		}
		else if (e.key.code == gracz2->getKlawisz(0))
		{

		}
		else if (e.key.code == gracz1->getKlawisz(1))
		{

		}
		else if (e.key.code == gracz2->getKlawisz(1))
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
	switch (who)
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
