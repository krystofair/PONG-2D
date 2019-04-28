//
// Created by Christofair on 23.04.2019.
//

#include <SFML/Window/Event.hpp>
#include "gracz.h"
#include "IMenu.h"

#ifndef PONG_STEROWANIE_H
#define PONG_STEROWANIE_H

/**
 * Klasa sterowanie czyli klasa odpowiadaj¹ca za interakcje
 * z u¿ytkownikiem. Opakowuje ona dane zdarzenie i przekazuje
 * je odpowiednio dla danej sytuacji w programie. Klasa ta jest
 * potrzebna ze wzglêdu na sterowanie za pomoc¹ zdarzeñ. W ka¿dej
 * chwili mo¿na tê klasê napisaæ od nowa, aby wspiera³a inny rodzaj
 * biblioteki. Wywo³uje ona odpowiednie funkcje zwrotne do zdarzeñ.
 */
class Sterowanie
{
public:
	enum STAN
	{
		MENU, GRA
	};

	/**
	 *
	 * @param init_state
	 */
	Sterowanie(STAN init_state) : stan(init_state) {}

	/**
	 * Operator wywo³ania pe³ni role funktora
	 * klasa wykonuje odpowiednie instrukcje ze wzglêdu
	 * na przekazany obiekt zdarzenia.
	 * @param e: ww obiekt zdarzenia.
	 */
	void operator()(sf::Event e);

	/**
	 * Zmienia wartoœæ pola stanu, który okreœla aktualny stan
	 * rozgrywki.
	 * @param s: jest innym stanem, który chcemy ustawiæ.
	 */
	void zmienStan(STAN s);

	/**
	 * Ustawia referencje graczy do których sterowanie siê bêdzie odnosi³o.
	 * @param g: jest obiektem gracza, na którego rachunek bêdziemy wywo³ywaæ metody.
	 * @param who: jest numerem gracza w celu rozró¿nienia dla klasy sterowanie.
	 */
	void setGracz(Gracz *g, int who);

	/**
	 * Przypisuje menu do którego obiekt bêdzie wysy³a³ komunikaty.
	 * @param m: jest wskaŸnikiem na to menu.
	 */
	void setMenu(IMenu* m);

private:
	STAN stan{ STAN::MENU };
	Gracz* gracz1{ nullptr };
	Gracz* gracz2{ nullptr };
	IMenu* imenu{ nullptr };
};


#endif //PONG_STEROWANIE_H
