#pragma once
#include "plansza.h"

enum STAN
{
	MENU, GRA, PAUZA
};

typedef STAN STATE;
extern STAN stan_gry;
extern Sterowanie stery;
extern sf::RenderWindow window;
extern Plansza plansza;