#pragma once

enum STAN
{
	MENU, GRA, PAUZA
};
/*
struct KeysGlobalSet
{
	Klawisz up = Klawisz::Unknown;
	Klawisz down = Klawisz::Unknown;
	Klawisz left = Klawisz::Unknown;
	Klawisz right = Klawisz::Unknown;
};
extern KeysGlobalSet pl1_set;
extern KeysGlobalSet pl2_set;
*/// we'll see.

typedef STAN STATE;
extern STAN stan_gry;
extern Sterowanie stery;
extern sf::RenderWindow window;