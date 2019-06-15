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
#include "AI.h"

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
sf::Event event{};

void game_loop()
{
	//window.setFramerateLimit(25);
	float X = plansza.getWidth()/2;
	float Y = plansza.getHeight()/2;
	chrono::steady_clock clk;
	auto czas_start = clk.now();
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr};
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};
	Silnik silnik(0.5, plansza.getHeight()/2, 0);
	//Trasa trace = wylicz(0,screen_height/2);
	auto update = [&]{
		auto czas_stop = clk.now();
		auto elapsed = chrono::duration<double>(czas_stop-czas_start).count();
		ball->SetPosition(X, Y);
		r1->move();
		r2->move();
		//ball->GetPosition().x = X;
		// ball move
		
		czas_start = clk.now();
	};
	g1 = plansza.getGracz(1);
	g2 = plansza.getGracz(2);
	if(g1) r1 = g1->getRakieta();
	if(g2) r2 = g2->getRakieta();
	ball = plansza.getPilka();
	if(r1 == nullptr || r2 == nullptr || ball == nullptr)
		throw("w grze musza byc te 3 obiekty inaczej to nie ma sensu.");
	while(stan_gry == STAN::GRA)
	{
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				stery.games(event);
			}

		window.clear(sf::Color::Black);
		window.draw(*r1);
		window.draw(*r2);
		ball->Draw(&window);
		window.display();
		// sekcja silnika
		silnik.setBall(ball);
		if(ball->DetectCollision(r1))
		{
			if(g2->checkSI()) static_cast<AI*>(g2)->StartAI();
		}


		X += ball->GetSpeed()*0.1; // kierunek dla prostej.
		Y += silnik.getA()*X + silnik.getB(); // prosta
		update();

		//if(X > screen_width- 2*size || X < size) kierunek *= -1;
		/*
		trace = wylicz(a,b);
		*/
	}
}
#include <fstream>
int main()
{
	window.setFramerateLimit(100);
	//thread si_thread(StartAi)
	IMenu* current_menu{nullptr};
	
	ofstream logfile("pong.log");
	// pocz¹tkowe warunki.
	stan_gry = STAN::MENU;
	stery.setMenu(new MainMenu());
	while(window.isOpen())
	{
			while(window.waitEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					window.close();

				}
				else if(event.type == sf::Event::KeyPressed)
				{
					stery.menus(event);
				}

				logfile << "[!] przed if(stan_gry == STAN::GRA)" << endl;

				if(stan_gry == STAN::GRA)
				{
					//if(plansza.getGracz(2)->checkSI()) //nope it's run without threading.
					game_loop();
					continue;
				}

				current_menu = stery.getMenu();
				if(stan_gry == STAN::MENU)
				{
					plansza.deletePilka();
					plansza.deletePlayer(1);
					plansza.deletePlayer(2);
				}
				//X = screen_width/2;
				window.clear(sf::Color::Black);
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				window.display();
			}
	}
	logfile.close();
	return 0;
}
