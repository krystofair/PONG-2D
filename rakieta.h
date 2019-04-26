//
// Created by Christofair on 23.04.2019.
//
#include <SFML/Graphics.hpp>

#ifndef PONG_RAKIETA_H
#define PONG_RAKIETA_H


/**
 * Klasa Rakieta reprezentuje obiekt rakiety na ekranie.
 * TODO: Rozszerzyć klasę w celu zaimplementowania w silniku.
 */
class Rakieta
{
public:
    Rakieta(unsigned int x, unsigned int y) : pos_x(x), pos_y(y) {}

    /**
     * Ustawia pozycje rakiety. Gdzie zostanie wyświetlona na ekranie.
     * @param x: pozycja na osi odciętych.
     * @param y: pozycja na osi rzędnych.
     */
    inline void setPozycja(unsigned int x, unsigned int y);

    /**
     * Metoda ustawiająca pozycje na osi X.
     * @param x: współrzędna x.
     */
    inline void setPozX(unsigned int x);

    /**
     * Metoda ustawiająca pozycje na osi Y.
     * @param y: współrzędna y.
     */
    inline void setPozY(unsigned int y);

private:
    unsigned int pos_x;
    unsigned int pos_y;
};


#endif //PONG_RAKIETA_H
