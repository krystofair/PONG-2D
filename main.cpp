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
	window.setFramerateLimit(30);
	//float X = silnik.getA();
	//float Y = plansza.getHeight()/2; // constant value for now.
	chrono::steady_clock clk;
	auto czas_start = clk.now();
	// wskazniki do wyswietlania
	Rakieta *r1{nullptr}, *r2{nullptr}; // r1-rakieta tylko gracza, r2- albo albo.
	IGracz *g1{nullptr}, *g2{nullptr};
	Ball *ball{nullptr};

	auto trafionaCzesc = [&](Rakieta* r)->int{
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

	ofstream log_collision("coll.log");
	auto update = [&] {
		auto czas_stop = clk.now();
		auto elapsed = chrono::duration<double>(czas_stop-czas_start).count();
		
		r1->move(elapsed);
		r2->move(elapsed);
		ball->Move(0, ball->GetSpeed()*elapsed);
		log_collision << "czas*szybkosc= " << ball->GetSpeed()*elapsed << "\n";
		czas_start = clk.now();
	};

	g1 = plansza.getGracz(1);
	g2 = plansza.getGracz(2);
	if(g1) r1 = g1->getRakieta();
	if(g2) r2 = g2->getRakieta();
	ball = plansza.getPilka();
	if(r1 == nullptr || r2 == nullptr || ball == nullptr)
		throw("w grze musza byc te 3 obiekty inaczej to nie ma sensu.");

	
	ball->SetSpeed(700);
	ball->SetPosition(300, 400);

	while(stan_gry == STAN::GRA)
	{

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				log_collision << "wychodze ELO\n";
				log_collision.close();
				auto w = Wyjscie(nullptr);
				w.execute();
				//window.close();
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
		// silnik.setBall(ball);
		auto deb_pos = ball->GetPosition();
		log_collision << "ball pos x = " << deb_pos.x << "\n";
		log_collision << "lime y = " << r1->lim_y << "\n";
		if(ball->DetectCollision(r1))
		{
			log_collision << "hit the r1\n";
			if(g2->checkSI()) static_cast<AI*>(g2)->StartAI();
			//silnik.setCzesc(trafionaCzesc(r1));
			//silnik.odbiciePaletka(r1->getStrona());

			if(r1->getStrona())
				ball->SetSpeed(-1000.0);
			else
				ball->SetSpeed(1000.0);
		}
		if(ball->DetectCollision(r2))
		{
			log_collision << "hit the r2\n";
			//if(g1->checkSI()) static_cast<AI*>(g1)->StartAI();
			//silnik.setCzesc(trafionaCzesc(r2));
			//silnik.odbiciePaletka(r2->getStrona());
			if(r2->getStrona())
				ball->SetSpeed(-1000.0);
			else
				ball->SetSpeed(1000.0);
		}
		if(ball->DetectCollision())
		{
			//silnik.odbicieBanda();
			if(!gorna_banda){
				ball->SetSpeed(-300);
				log_collision<<"kolizja banda 1\n";
			}
			else{
				ball->SetSpeed(300);
				log_collision<<"kolizja banda 2\n";
			}
			if(ball->GetPosition().y >= plansza.getHeight()/2) gorna_banda=false;
			else gorna_banda=true;
		}
		if(ball->GetPosition().x < 0 || ball->GetPosition().x > plansza.getWidth())
		{
			stery.setMenu(new MainMenu());
			stan_gry = STAN::MENU;
			break;
		}
		update();
	}
	log_collision.close();
}

Silnik* engine{nullptr};

int main()
{
	window.setFramerateLimit(40);
	window.setMouseCursorVisible(false);
	//thread si_thread(StartAi)
	IMenu* current_menu{nullptr};
	
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

				//logfile << "[!] przed if(stan_gry == STAN::GRA)" << endl;			

				if(stan_gry == STAN::GRA)
				{
					//if(plansza.getGracz(2)->checkSI()) //nope it's run without threading.
					//if(engine == nullptr) engine = new Silnik(200, plansza.getHeight()/2, 0);
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
