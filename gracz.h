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
    Gracz(Rakieta&, int);
	virtual ~Gracz() = default;
    
    /**
     * Opis metody zgodny z opisem w interfejsie `IGracz`.
     * @param r: obiekt rakiety, której będzie używała klasa `Gracz`.
     */
    void setRakieta(const Rakieta& r) override;
    Rakieta& getRakieta() override;
	/**
	 * Zmiana ustawień klawiszy
	 * spersonalizowanych dla gracza.
	 * @params up, down: przesuwanie rakiety w góre i w dół
	 * @params left, right: przesuwanie rakiety w lewo i prawo
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
