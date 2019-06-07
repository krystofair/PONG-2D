#include "plansza.h"


IGracz* Plansza::createPlayer(Rakieta* r, int id)
{
	if(id == 1)
	{
		gracz1 = new Gracz(r, id);
		if(gracz1 != nullptr) return gracz1;
	}
	else
	{
		if(id == 2) gracz2 = new Gracz(r, id);
		else if(id == 3) gracz2 = new IGracz(r);
		if(gracz2 != nullptr) return gracz2;
	}
	return nullptr;
}

void Plansza::deletePlayer(int id)
{
	if(id == 1 && gracz1 != nullptr)
	{
		delete gracz1;
		gracz1 = nullptr;
	}
	if(id == 2 && gracz2 != nullptr)
	{
		delete gracz2;
		gracz2 = nullptr;
	}
}