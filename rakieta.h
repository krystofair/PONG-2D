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
    Rakieta(float x,
			float y,
			float szer,
			float dl)
		: pos_x(x), pos_y(y), szerokosc(szer), dlugosc(dl), lim_y(y), szybkosc(0.3){}

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
	float getPozX();

    /**
     * Metoda ustawiająca pozycje na osi Y.
     * @param y: współrzędna y.
     */
    void setPozY(float y);

	/**
	 * Metoda zwracająca pozycje na osi Y.
	 * @return: pos_y
	 */
	float getPozY();

	/**
	 * Zwracanie szerokości rakiety w pikselach
	 * @return: dlugosc
	 */
	float getSzerokosc();

	/**
	 * Zwracanie długości rakiety w pikselach
	 * @return: szerokosc
	 */
	float getDlugosc();

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
	float getSzybkosc() const;

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

	/**
	 * przesuwanie rakiety do ustalonego miejsca
	 * w okreslonym czasie.
	 */
	void move(float sekundy);

	/// override method from drawable to draw rakieta on the screen
	void draw(sf::RenderTarget& rt, sf::RenderStates states = sf::RenderStates::Default) const;

public:
	float lim_y;

private:
    float pos_x;
    float pos_y;
	float dlugosc;
	float szerokosc;
	float szybkosc;
};

#endif //PONG_RAKIETA_H
