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

sf::Event event{};

void game_loop()
{
	window.setFramerateLimit(30);
	float X = plansza.getWidth()/2;
	float Y = plansza.getHeight()/2;
	chrono::steady_clock clk;
	auto czas_start = clk.now();
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr}; // r1-rakieta tylko gracza, r2- albo albo.
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};
	Silnik silnik(0.5, plansza.getHeight()/2, 0);

	auto trafionaCzesc = [&](bool which)->int{
		float yr = 0.0;
		float dl = 0.0;
		if(which == true)
		{
			yr = r1->getPozY();
			dl = r1->getDlugosc();
		}
		else
		{
			yr = r2->getPozY();
			dl = r2->getDlugosc();
		}
		float yb = ball->GetPosition().y;
		if(yb <= dl/3) return part_up;
		else if(yb > dl/3 && yb < 2*dl/3) return part_middle;
		else if(yb > 2*dl/3) return part_down;
	};

	auto update = [&]{
		auto czas_stop = clk.now();
		auto elapsed = chrono::duration<double>(czas_stop-czas_start).count();
		ball->SetPosition(X, Y);
		r1->move(elapsed);
		r2->move(elapsed);
		//ball->GetPosition().x = X;
		// ball move
		//X += ball->GetSpeed()*elapsed;
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
		
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed)
			{
				stery.games(event);
			}
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
			silnik.setPalecz(trafionaCzesc(r1->getStrona()));
			silnik.odbiciePaletka(r1->getStrona());

		}
		else if(ball->DetectCollision(r2))
		{
			//if(g1->checkSI()) static_cast<AI*>(g1)->StartAI();
			silnik.setPalecz(trafionaCzesc(r2->getStrona()));
			silnik.odbiciePaletka(r2->getStrona());
		}
		else
		{
			silnik.odbicieBanda();
		}


		//X += ball->GetSpeed(); // kierunek dla prostej.
		//Y += silnik.getA()*X + silnik.getB(); // prosta
		update();

		//if(X > screen_width- 2*size || X < size) kierunek *= -1;
		/*
		trace = wylicz(a,b);
		*/
	}
}

int main()
{
	window.setFramerateLimit(40);
	//thread si_thread(StartAi)
	IMenu* current_menu{nullptr};
	
	//ofstream logfile("pong.log");
	// pocz¹tkowe warunki.
	stan_gry = STAN::MENU;
	stery.setMenu(new MainMenu());
	while(window.isOpen())
	{
		window.clear(sf::Color::Black);
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

				//logfile << "[!] przed if(stan_gry == STAN::GRA)" << endl;

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
				window.clear(sf::Color::Black);
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				window.display();
			}
	}
	//logfile.close();
	return 0;
}
