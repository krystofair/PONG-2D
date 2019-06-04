//
// Created by Christofair on 23.04.2019.
//
#include "IGracz.h"

#ifndef PONG_GRACZ_H
#define PONG_GRACZ_H

using Klawisz = sf::Keyboard::Key;

class Gracz : public IGracz
{
public:
	/**
	 * Tworzenie obiektu gracza z odpowiednim numerkiem
	 * @param id: identyfikator gracza.
	 * @param r: obiekt rakiety dla danego gracza.
	 */
    Gracz(Rakieta*, int);
	virtual ~Gracz() = default;
	/**
	 * Zmiana ustawień klawiszy
	 * spersonalizowanych dla gracza.
	 * @param up: przesuwanie rakiety  w góre.
	 * @param down: przesuwanie rakiety w dół.
	 * @param left: przesuwanie rakiety w lewo
	 * @param right: przesuwanie rakiety w prawo.
	 */
    void setKlawisze(
            Klawisz up,
            Klawisz down,
            Klawisz left,
            Klawisz right);
    /**
	 * Zwraca klawisz przypisany dla danego gracza z tablicy klawisze
	 * @param index: wskazuje index na ktorym zapisany jest kod klawisza.
	 */
	const Klawisz& getKlawisz(unsigned int index) const
	{
		return klawisze[index];
	}



private:
	int id{1};
	Klawisz klawisze[4];

};


#endif //PONG_GRACZ_H
