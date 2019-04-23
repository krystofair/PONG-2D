#include "sterowanie.h"


void Sterowanie::operator()(sf::Event e)
{
#define code e.key.code
	switch(stan)
	{
		case MENU:
		{
			//klawisz potwierdzający wybór
			if(e.key.code == Klawisz::Enter)
			{
			    //wybierz obecnie ustawioną opcje
			}
			else if(code == Klawisz::Up)
			{
			    //ogarnij powyższy napis w menu
			}
			else if(code == Klawisz::Down)
			{
			    //ogarnij niższy napis w menu
			}
			break;
		}
		case ROZGRYWKA:
		{
			if(code == gracz1->getKlawisz(0))
			{

			}
			else if(code == gracz2->getKlawisz(0))
			{

			}
			else if(code == gracz1->getKlawisz(1))
			{

			}
			else if(code == gracz2->getKlawisz(1))
			{

			}
			break;
		}
	}
}
void Sterowanie::zmienStan(STAN inny_stan) {
    stan = inny_stan;
}


//na przyklad cos takiego.
//#define DEBUG_STEROWANIE
#ifdef DEBUG_STEROWANIE
int main()
{
	sf::Event event{};
	Sterowanie sterowanie;
	if(event.type == sf::Event::KeyPressed) sterowanie(event);
	return 0;
}
#endif /* DEBUG_STEROWANIE */
