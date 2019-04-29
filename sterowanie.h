//
// Created by Christofair on 23.04.2019.
//

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
    
    /**
     * Przypisuje menu do którego obiekt będzie wysyłał komunikaty.
     * @param m: jest wskaźnikiem na to menu.
     */
    void setMenu(IMenu* m);

private:
    STAN stan{STAN::MENU};
    Gracz* gracz1{nullptr};
    Gracz* gracz2{nullptr};
    IMenu* imenu{nullptr};
};


#endif //PONG_STEROWANIE_H
