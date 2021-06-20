//
// Created by Christofair on 23.04.2019.
//

#pragma once

#include <SFML/Window/Event.hpp>

#include "gracz.h"
#include "IMenu.h"

#ifndef PONG_STEROWANIE_H
#define PONG_STEROWANIE_H

/**
 * Klasa sterowanie czyli klasa odpowiadająca za interakcje
 * z użytkownikiem. Opakowuje ona dane zdarzenie i przekazuje
 * je odpowiednio dla danej sytuacji w programie. Klasa ta jest
 * potrzebna ze względu na sterowanie za pomocą zdarzeń. W każdej
 * chwili można tę klasę napisać od nowa, aby wspierała inny rodzaj
 * biblioteki. Wywołuje ona odpowiednie funkcje zwrotne do zdarzeń.
 */
class Sterowanie
{
public:
    /**
     * Konstruktor parametryczny przyjmuje adresy do obiektów,
	 * z których potrzebuje odbierać dane. 
     * @param g1: wskaźnik do obiektu gracza numer 1,
	 * @param g2: wskaźnik do obiektu gracza numer 2,
	 * @param menu: wskaźnik do obiektu menu, w celu sterowania nim.
     */
	/// Wskaźniki do obiektów typu Gracz są używane do obierania ustawień
	/// klawiszy, które sobie każdy gracz spersonalizował. Oraz po to, aby
	/// pośrednio przez graczy sterować ich rakietami.
	/// Menu przekazywane jest w celu wysyłania komunikatów typu którą opcje
	/// zaznaczyć, którą odznaczyć oraz którą uruchmić. Wszystkie te metody są
	/// zadeklarowane w typie IMenu.
	Sterowanie(Gracz* g1 = nullptr, Gracz* g2 = nullptr, IMenu* menu = nullptr)
		: gracz1(g1), gracz2(g2), imenu(menu) {}

    /**
     * Games wykonuje metody na podstawie zdefiniowanych klawiszy
	 * w obiektach typu Gracz. Obiekt typu Event jest informacją
	 * o przyciśniętym klawiszu na klawiaturze.
     * @param e: ww obiekt zdarzenia.
     */
    void games();

	/**
	 * Obsługa klawiatury zgodna z interfejsem IMenu.
	 * przekazywany do niej jest argument typu Event, który posiada informacje
	 * o przyciśniętym klawiszu.
	 */
	void menus(sf::Event& e);

    /**
     * Ustawia referencje graczy do których sterowanie się będzie odnosiło.
     * @param g: jest obiektem gracza, na którego rachunek będziemy wywoływać metody.
     * @param who: jest numerem gracza w celu rozróżnienia dla klasy sterowanie.
     */
    void setGracz(Gracz *g, int who);
    
    /**
     * Przypisuje menu do którego obiekt będzie wysyłał komunikaty.
     * @param m: jest wskaźnikiem na to menu.
     */
    void setMenu(IMenu* m);
	/**
	 * Zwracanie wskaźnika na który obecnie wskazuje imenu.
	 */
	IMenu* getMenu();
	/**
	 * zwalnia zasoby utrzymywane dla obiektu menu
	 */
	void zwolnijMenu()
	{
		if(imenu)
		{
			delete imenu;
			imenu = nullptr;
		}
	}

private:
    Gracz* gracz1{nullptr};
    Gracz* gracz2{nullptr};
    IMenu* imenu{nullptr};
};


#endif //PONG_STEROWANIE_H
