//
// Created by Christofair on 23.04.2019.
//
#include "rakieta.h"
#include <SFML/Window/Keyboard.hpp>


#ifndef PONG_IGRACZ_H
#define PONG_IGRACZ_H


class IGracz
{
public:
	IGracz() = default;
	IGracz(Rakieta& r) : rakieta(&r) {}
    virtual ~IGracz() = default;

    /**
     * Pobranie rakiety od gracza i operowanie na niej.
     * Np wykonywanie operacji jak rysowanie na ekranie.
     * @return: Referencje obiektu rakiety.
     */
	virtual Rakieta& getRakieta() const { return *rakieta; }

    /**
     * Przypiuje obiekt rakiety dla gracza.
     * @param r: obiekt rakiety do przypisania dla pola.
     */
	virtual void setRakieta(Rakieta& r) { rakieta = &r; }

protected:
    Rakieta* rakieta;
};


#endif //PONG_IGRACZ_H
