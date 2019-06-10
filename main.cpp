#include <cassert>
#include <chrono>
#include <thread>
#include <mutex>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "plansza.h"
#include "sterowanie.h"
#include "silnik.h"

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

struct Trasa
{
	Trasa(float _a, float _b, float(*f)(float a, float b, float x))
		: a(_a), b(_b), function_trace(f){}
	float a;
	float b;
	float (*function_trace)(float, float, float);
	float operator()(float x)
	{
		return function_trace(a, b, x);
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

int main()
{
	float X = plansza.getWidth()/2;
	float Y = plansza.getHeight()/2;
	bool kolizjaB = false, kolizjaR = false;
	chrono::steady_clock clk;
	auto czas_start = clk.now();
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr};
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};
	IMenu* current_menu{nullptr};
	Silnik silnik(0.5, plansza.getHeight()/2, 0);
	//Trasa trace = wylicz(0,screen_height/2);

	sf::Event event{};
	//sf::Clock time;

	auto update = [&]{
		auto czas_stop = clk.now();
		auto elapsed = chrono::duration<double>(czas_stop-czas_start).count();
		ball->SetPosition(X, Y);
		r1->move();
		r2->move();
		//ball->GetPosition().x = X;
		// ball move
		if(!(kolizjaR = ball->DetectCollision(r1) || ball->DetectCollision(r2)))
			kolizjaB = ball->DetectCollision();
		czas_start = clk.now();
	};

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
		switch(stan_gry)
		{
			case STATE::PAUZA:
				current_menu = stery.getMenu();
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::MENU:
				current_menu = stery.getMenu();
				plansza.deletePilka();
				plansza.deletePlayer(1);
				plansza.deletePlayer(2);
				X = screen_width/2;
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				break;
			case STATE::GRA:
			{
				// do nowej funkcji.
				g1 = plansza.getGracz(1);
				g2 = plansza.getGracz(2);
				if(g1) r1 = g1->getRakieta();
				if(g2) r2 = g2->getRakieta();
				ball = plansza.getPilka();
				if(r1 == nullptr || r2 == nullptr || ball == nullptr)
					throw("w grze musza byc te 3 obiekty inaczej to nie ma sensu.");
				window.draw(*r1);
				window.draw(*r2);
				ball->Draw(&window);
				// sekcja silnika
				silnik.setBall(ball);
				if(kolizjaR)
				{
					if(ball->GetPosition().x <= 0) 
						silnik.odbiciePaletka(false);
					if(ball->GetPosition().x >= plansza.getWidth()) 
						silnik.odbiciePaletka(true);
				}
				if(kolizjaB)
				{
					silnik.odbicieBanda();
				}
				
				X += ball->GetSpeed()*silnik.getA(); // kierunek dla prostej.
				Y += silnik.getA()*X + silnik.getB(); // prosta
				update();

				//if(X > screen_width- 2*size || X < size) kierunek *= -1;
				/*
				trace = wylicz(a,b);
				*/
				break;
			}
		}
		window.display();
	}
	return 0;
}
