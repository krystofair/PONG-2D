#include <cassert>
#include <chrono>
#include <thread>
#include <mutex>

#include <fstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "plansza.h"
#include "sterowanie.h"
#include "silnik.h"
#include "AI.h"

#include "globals.h"

using namespace std;


unsigned int screen_width = 800;
unsigned int screen_height = 600;

STAN stan_gry = STATE::MENU;
Sterowanie stery;
Plansza plansza(screen_width, screen_height);
sf::RenderWindow window(
	sf::VideoMode(screen_width, screen_height), "xPONG 2D"
);

sf::Event event{};


void game_loop(Silnik& silnik)
{
	window.setFramerateLimit(40);
	//float X = silnik.getA();
	//float Y = plansza.getHeight()/2; // constant value for now.
	chrono::steady_clock clk;
	auto czas_start = clk.now();
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr}; // r1-rakieta tylko gracza, r2- albo albo.
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};

	auto trafionaCzesc = [&](Rakieta* r)->int
	{
		float yr = 0.0;
		float dl = 0.0;
		float yb = ball->GetPosition().y;
		yr = r->getPozY();
		dl = r->getDlugosc();
		if(yb <= yr+dl/3) return 1; // part_up
		else if(yb > yr+dl/3 && yb < yr+2*dl/3) return 2; // part_middle
		else if(yb > yr+2*dl/3) return 3; // part_down
	};
	bool gorna_banda = false;

	auto update = [&] {
		auto czas_stop = clk.now();
		auto elapsed = chrono::duration<double>(czas_stop-czas_start).count();
		r1->move(elapsed);
		r2->move(elapsed);
		ball->Move(ball->GetSpeed()*elapsed, ball->GetRotation()*elapsed);
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
				auto w = Wyjscie(nullptr);
				w.execute();
				//window.close();
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
			silnik.setCzesc(trafionaCzesc(r1));
			silnik.odbiciePaletka(r1->getStrona());
			// if(r1->getStrona()) zobacz detect(r2)
				//ball->SetSpeed(-ball->GetSpeed());
		}
		else if(ball->DetectCollision(r2))
		{
			//if(g1->checkSI()) static_cast<AI*>(g1)->StartAI();
			silnik.setCzesc(trafionaCzesc(r2));
			silnik.odbiciePaletka(r2->getStrona());
			
			//if(r2->getStrona())
				//ball->SetSpeed(-ball->GetSpeed());
			//else
				//ball->SetSpeed();
				
		}
		else if(ball->DetectCollision())
		{
			silnik.odbicieBanda();
			/*
			if(!gorna_banda){
				ball->SetRotation(-ball->GetRotation());
				log_collision<<"kolizja banda 1\n";
			}
			else{
				ball->SetRotation(ball->GetRotation());
				log_collision<<"kolizja banda 2\n";
			}
			if(ball->GetPosition().y >= plansza.getHeight()/2) gorna_banda=false;
			else gorna_banda=true;*/
		}
		if(ball->GetPosition().x < 0 || ball->GetPosition().x > plansza.getWidth())
		{
			stery.setMenu(new MainMenu());
			stan_gry = STAN::MENU;
			break;
		}
		update();
		stery.games();
	}
}


int main()
{
	window.setFramerateLimit(30);
	window.setMouseCursorVisible(false);
	//thread si_thread(StartAi)
	IMenu* current_menu{nullptr};
	Silnik* engine{nullptr};
	
	// pocz¹tkowe warunki.
	stan_gry = STAN::MENU;
	stery.setMenu(new MainMenu());
	while(window.isOpen())
	{
		current_menu = stery.getMenu();
		window.clear(sf::Color::Black);
		window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
		window.display();
			while(window.waitEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					auto w = Wyjscie(stery.getMenu());
					w.execute();
					//window.close();
				}
				else if(event.type == sf::Event::KeyPressed)
				{
					stery.menus(event);
				}

				if(stan_gry == STAN::GRA)
				{
					//if(plansza.getGracz(2)->checkSI()) /*start thread AI */; //nope it's run without threading.
					if(engine == nullptr) engine = new Silnik(0, 0, 0);
					game_loop(*engine);
				}

				current_menu = stery.getMenu();
				if(stan_gry == STAN::MENU)
				{
					plansza.deletePilka();
					plansza.deletePlayer(1);
					plansza.deletePlayer(2);
					if(engine)
					{
						delete engine;
						engine = nullptr;
					}
				}
				window.clear(sf::Color::Black);
				window.draw(*dynamic_cast<sf::Drawable*>(current_menu));
				window.display();
			} 
	}
	return 0;
}
