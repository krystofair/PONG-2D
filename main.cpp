#include <cassert>
#include <chrono>
#include <thread>
#include <mutex>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "plansza.h"
#include "sterowanie.h"

#include "globals.h"

using namespace std;

int screen_width = 800;
int screen_height = 600;

STAN stan_gry = STATE::MENU;
Sterowanie stery;
Plansza plansza(screen_width, screen_height);
sf::RenderWindow window(
	sf::VideoMode(screen_width, screen_height), "xPONG 2D"
);

/*

//fast and furious function - only for test
bool detectCollision(Ball& b, Rakieta& r)
{
	float pktRy = (r.getPozY() + r.getDlugosc())/2;
	float pktBy = (b.GetPosition().y + b.GetSize().y)/2;
	float pktRx = (r.getPozX() + r.getSzerokosc())/2;
	float pktBx = (b.GetPosition().x + b.GetSize().x)/2;

	float dX = pktBx - pktRx;
	dX = (dX<0) ? -dX : dX;
	float dY = pktBy - pktRy;
	dY = (dY<0) ? -dY : dY;
	if(dY >= (r.getDlugosc()/2 + b.GetSize().y/2) || dX > (r.getSzerokosc()/2 + b.GetSize().x/2))
		return false;
	else
		return true;
}

bool detectCollision(Ball& b)
{
	if(b.GetPosition().y + b.GetSize().y/2 <= 0) return true;
	else return false;
	if(b.GetPosition().y + b.GetSize().y/2 >= screen_height) return true;
	else return false;
}

struct Silnik{};

struct Trasa
{
	Silnik *s;
	Trasa(float _a, float _b, float(Silnik::*f)(float a, float b, float x), Silnik *sil)
		: a(_a), b(_b), function_trace(f), s(sil){}
	float a;
	float b;
	float (Silnik::*function_trace)(float, float, float);
	float operator()(float x)
	{
		return (s->*function_trace)(a, b, x);
	}
};


float prosta(float a, float b, float x)
{
	return (a*x + b)-200;
}

Trasa wylicz(float a, float b)
{
	return Trasa(a, b, prosta);
}
*/

int main()
{
	float kierunek = 1;
	float X;
	float a=0.5, b=300;
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr};
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};
	IMenu* current_menu{nullptr};
	//Trasa trace = wylicz(0,screen_height/2);

	sf::Event event{};
	//sf::Clock time;

	// pocz¹tkowe warunki.
	stan_gry = STAN::MENU;
	stery.setMenu(new MainMenu());

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				switch(stan_gry)
				{
					case STATE::PAUZA:
					case STATE::MENU:
						stery.menus(event);
						break;
					case STATE::GRA:
						stery.games(event);
						break;
				}
			}
		}

		//drawing
		window.clear(sf::Color::Black);
		current_menu = stery.getMenu();
		g1 = plansza.getGracz(1);
		g2 = plansza.getGracz(2);
		if(g1) r1 = g1->getRakieta();
		if(g2) r2 = g2->getRakieta();
		ball = plansza.getPilka();
		

		switch(stan_gry)
		{
			case STATE::PAUZA:
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::MENU:
				plansza.deletePilka();
				plansza.deletePlayer(1);
				plansza.deletePlayer(2);
				X = screen_width/2;
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::GRA:
			{
				if(r1 == nullptr || r2 == nullptr || ball == nullptr)
					throw("w grze musza byc te 3 obiekty inaczej to nie ma sensu.");
				else
				{
					//r1
					r1->move();
					window.draw(*r1);
					//r2
					r2->move();
					window.draw(*r2);
					//ball
					ball->Draw(&window);
					//ball->SetPosition(X, trace(X));
					//ball->Move(10, 10);
					auto size = ball->GetSize().x;
					X += 0.4*kierunek;
					//if(X > screen_width- 2*size || X < size) kierunek *= -1;
					/*
					if(detectCollision(*ball, *r1) || detectCollision(*ball, *r2))
					{
						kierunek*=-1;
						a= -a;
					}
					if(detectCollision(*ball))
					{
						a =-a;
						b= -b;
					}
					trace = wylicz(a,b);
					*/
				}
				break;
			}
		}
		window.display();
	}
	return 0;
}
