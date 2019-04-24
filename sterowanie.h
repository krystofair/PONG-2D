//
// Created by Christofair on 23.04.2019.
//

#ifndef PONG_STEROWANIE_H
#define PONG_STEROWANIE_H

#include <SFML/Window/Event.hpp>
#include "gracz.h"
#include "IMenu.h"

/**
 * Klasa sterowanie czyli klasa odpowiadająca za interakcje
 * z użytkownikiem. Opakowuje ona dane zdarzenie i przekazuje
 * je odpowiednio dla danej sytuacji w programie. Klasa ta jest
 * potrzebna ze względu na sterowanie za pomocą zdarzeń. W każdej
 * chwili można tę klasę napisać od nowa, aby wspierała inny rodzaj
 * biblioteki. Wywołuje ona odpowiednie funkcje zwrotne do zdarzeń.
 */
template <typename T>
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
     * Operator wywołania pełni role funktora
     * klasa wykonuje odpowiednie instrukcje ze względu
     * na przekazany obiekt zdarzenia.
     * @param e: ww obiekt zdarzenia.
     */
    void operator()(sf::Event e);
    /**
     * Zmienia wartość pola stanu, który określa aktualny stan
     * rozgrywki.
     * @param s: jest innym stanem, który chcemy ustawić.
     */
    void zmienStan(STAN s);
    /**
     * Ustawia referencje graczy do których sterowanie się będzie odnosiło.
     * @param g: jest obiektem gracza, na którego rachunek będziemy wywoływać metody.
     * @param who: jest numerem gracza w celu rozróżnienia dla klasy sterowanie.
     */
    void setGracz(Gracz *g, int who);
    void setMenu(IMenu<T>* m);
private:
    STAN stan{STAN::MENU};
    Gracz* gracz1;
    Gracz* gracz2;
    IMenu<T>* menu;

};

#endif //PONG_STEROWANIE_H
