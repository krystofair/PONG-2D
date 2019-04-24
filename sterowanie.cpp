#include "sterowanie.h"



template <typename T>
void Sterowanie<T>::operator()(sf::Event e)
{
#define code e.key.code
	switch(stan)
	{
		case MENU:
		{
			//klawisz potwierdzający wybór
			if(e.key.code == Klawisz::Enter)
			{
			    //nic nie rób jak na razie
			}
			else if(code == Klawisz::Up)
			{
			    menu->odznaczOpcje(menu->zaz_opcja);
			    menu->zaznaczOpcje([](IMenu<T>* m)->sf::Text*
			    {
			    	for(auto i : m->opcje)
			    		if(m->zaz_opcja == i)
			    			return --i;
			    }(menu));
			}
			else if(code == Klawisz::Down)
			{
			    menu->odznaczOpcje(menu->zaz_opcja);
			    menu->zaznaczOpcje([](IMenu<T>* m)->sf::Text* {
			    	for(auto i : m->opcje)
			    		if(m->zaz_opcja == i)
			    			return ++i;
			    }(menu));
			}
			break;
		}
		case GRA:
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
template <typename T>
void Sterowanie<T>::zmienStan(STAN inny_stan) {
    stan = inny_stan;
}

template <typename T>
void Sterowanie<T>::setGracz(Gracz *g, int who)
{
	switch(who)
	{
		case 1: gracz1 = g; break;
		case 2: gracz2 = g; break;
		default: gracz1 = g;
	}
}

template <typename T>
void Sterowanie<T>::setMenu(IMenu<T>* m)
{
    menu = m;
}
