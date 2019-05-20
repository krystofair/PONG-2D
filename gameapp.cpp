/*
#include "gameapp.h"
#include "menu.h"

void reset()
{
	if(gracz1 != nullptr){ delete gracz1; gracz1 = nullptr; }
	if(rakieta1 != nullptr){ delete rakieta1; rakieta1 = nullptr; }
	if(gracz2 != nullptr){ delete gracz2; gracz2 = nullptr; }
	if(rakieta2 != nullptr){ delete rakieta2; gracz1 = nullptr; }
	if(current_menu != nullptr){ delete current_menu; current_menu = nullptr; }
}
void exit()
{
	reset();
}

void gameloop(sf::RenderTarget& w)
{
	auto Y1 = rakieta1->getPozY();
	auto Y2 = rakieta2->getPozY();

	if(Y1 != rakieta1->lim_y)
	{
		if(Y1 < rakieta1->lim_y) rakieta1->setPozY(Y1+szybkosc_rakiety);
		else rakieta1->setPozY(Y1-szybkosc_rakiety);
	}
	else
	{
		if(rakieta1->lim_y > screen_height)
			rakieta1->setPozY(screen_height-rakieta1->getDlugosc/2);
		else
			rakieta1->setPozY(rakieta1->getDlugosc/2);
	}
	if(Y2 != rakieta2->lim_y)
	{
		if(Y2 < rakieta2->lim_y) rakieta2->setPozY(Y2+szybkosc_rakiety);
		else rakieta2->setPozY(Y1-szybkosc_rakiety);
	}
	else
	{
		if(rakieta2->lim_y > screen_height)
			rakieta2->setPozY(screen_height - rakieta2->getDlugosc/2);
		else
			rakieta2->setPozY(rakieta2->getDlugosc/2);
	}
	w.draw(*rakieta1);
	w.draw(*rakieta2);
}

void menu_instr(sf::RenderTarget& w)
{
	if(auto menu = dynamic_cast<MainMenu*>(current_menu))
	{
		w.draw(*menu);
	}
	else if(auto menu = dynamic_cast<PauseMenu*> (current_menu))
	{
		w.draw(*menu);
	}
}

void zmienStan(STAN nowy_stan)
{
	if(nowy_stan == MENU || nowy_stan == GRA) //validacja stanu
		stan_gry = nowy_stan;
}
*/