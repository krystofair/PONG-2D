//
// Created by Christofair on 23.04.2019.
//
#include <SFML/Graphics.hpp>

#ifndef PONG_RAKIETA_H
#define PONG_RAKIETA_H


/**
 * Klasa Rakieta reprezentująca obiekt rakiety na ekranie.
 */
class Rakieta : public sf::Drawable
{
public:
    Rakieta(unsigned x,
			unsigned y,
			unsigned szer,
			unsigned dl)
		: pos_x(x), pos_y(y), szerokosc(szer), dlugosc(dl), lim_y(y), szybkosc(0.3) {}

    /**
     * Ustawia pozycje rakiety. Gdzie zostanie wyświetlona na ekranie.
     * @param x: pozycja na osi odciętych.
     * @param y: pozycja na osi rzędnych.
     */
    inline void setPozycja(float x, float y);

    /**
     * Metoda ustawiająca pozycje na osi X.
     * @param x: współrzędna x.
     */
    void setPozX(float x);

	/**
	 * Metoda zwracająca pozycje na osi X
	 * @return: pos_x
	 */
	unsigned getPozX();

    /**
     * Metoda ustawiająca pozycje na osi Y.
     * @param y: współrzędna y.
     */
    void setPozY(float y);

	/**
	 * Metoda zwracająca pozycje na osi Y.
	 * @return: pos_y
	 */
	unsigned getPozY();

	/**
	 * Zwracanie szerokości rakiety w pikselach
	 * @return: dlugosc
	 */
	unsigned getSzerokosc();

	/**
	 * Zwracanie długości rakiety w pikselach
	 * @return: szerokosc
	 */
	unsigned getDlugosc();

	/**
     * Ustawianie szerokości rakiety w pikselach,
	 * pomimo tego że ta wielkość raczej jest stała.
	 * @param s: nowa szerokosc dla rakiety
	 */
	void setSzerokosc(float s);

	/**
	 * Ustawianie długości rakiety w pikselach
	 * @param d: nowa długość dla rakiety
	 */
	void setDlugosc(float d);

	/**
	 * Zwracanie szybkosci rakiety w trakcie trwania rozgrywki.
	 * @return : this->szybkosc.
	 */
	unsigned getSzybkosc() const;

	/**
	 * powiadamia o przesunięciu rakiety do pewnego etapu
	 * @param lim: jest granicą do której maksymalnie
	 * przesunie się rakieta na osi OY.
	 */
	void moveTo(float lim);
	/**
	 * przesuwanie rakiety do ustalonego miejsca
	 */
	void move();

	// override method from drawable to draw rakieta on the screen
	void draw(sf::RenderTarget& rt, sf::RenderStates states = sf::RenderStates::Default) const;

public:
	unsigned lim_y;

private:
    float pos_x;
    float pos_y;
	float dlugosc;
	float szerokosc;
	float szybkosc;
};

#endif //PONG_RAKIETA_H
