//
// Created by Christofair on 23.04.2019.
//

#ifndef PONG_STEROWANIE_H
#define PONG_STEROWANIE_H

#include <SFML/Window/Event.hpp>
#include "gracz.h"

/**
 * Klasa sterowanie czyli klasa odpowiadająca za interakcje
 * z użytkownikiem. Opakowuje ona dane zdarzenie i przekazuje
 * je odpowiednio dla danej sytuacji w programie. Klasa ta jest
 * potrzebna ze względu na sterowanie za pomocą zdarzeń. W każdej
 * chwili można tę klasę napisać od nowa, aby wspierała inny rodzaj
 * biblioteki.
 */
class Sterowanie
{
public:
    enum STAN
    {
        MENU, ROZGRYWKA
    };
    /**
     * Operator wywołania pełni role funktora
     * klasa wykonuje odpowiednie instrukcje ze względu
     * na przekazany obiekt zdarzenia.
     * @param e: ww obiekt zdarzenia.
     */
    void operator()(sf::Event e);
    void zmienStan(STAN);
private:
    STAN stan;
    Gracz* gracz1;
    Gracz* gracz2;
    Menu* menu;

};

#endif //PONG_STEROWANIE_H
