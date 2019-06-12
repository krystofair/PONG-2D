#include "plansza.h"
#include "AI.h"

IGracz* Plansza::createPlayer(Rakieta* r, int id)
{
	if(id == 1)
	{
		gracz1 = new Gracz(r, id);
		return gracz1;
	}
	else
	{
		if(id == 2) gracz2 = new Gracz(r, id);
		else if(id == 3) gracz2 = new AI(r);
		return gracz2;
	}
}

void Plansza::deletePlayer(int id)
{
	if(id == 1 && gracz1 != nullptr)
	{
		auto r = gracz1->getRakieta();
		if(r != nullptr)
		{
			delete r;
			gracz1->setRakieta(nullptr);
		}
		delete gracz1;
		gracz1 = nullptr;
	}
	if(id == 2 && gracz2 != nullptr)
	{
		auto r = gracz2->getRakieta();
		if(r != nullptr)
		{
			delete r;
			gracz2->setRakieta(nullptr);
		}
		delete gracz2;
		gracz2 = nullptr;
	}
}

Ball* Plansza::createPilka()
{
	pilka = new Ball();
	return pilka;
}

void Plansza::deletePilka()
{
	if(pilka)
	{
		delete pilka;
		pilka = nullptr;
	}
}
