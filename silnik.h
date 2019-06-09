#pragma once
#include <cmath>
#include "Ball.h"

class Silnik
{
public:
	Silnik(float x, float y, int kat) : a(x), b(y), alfa(kat) {}
	float getA() { return a; }
	float getB() { return b; }
	int getAlfa() { return alfa; }
	void prosta(float&, float&, bool rodzaj);
	void gorapaletkatrue();
	void srodkowapaletka();
	void dolnapaletkatrue();//||| domyslna dodatnia rotacja
	void odbiciePaletka(); // silnikpaletka nazwa zmieniona
	void odbicieBanda(); //silnikbanda nazwa zmieniona.

private:
	Ball* ball;

private:
	int alfa;
	float a, b;
	//zmienne srodowiskowe
	int bs{50}; // basic speed
	int br{15}; // basic rotation
	// jakies pomocnicze niewiem.
	bool rodzaj; //false - banda, true - rakieta
	bool paletka{true};
	bool banda{true};
	int palecz{1}; // cze�� paletki 1-up, 2-mid, 4-bottom (1, 0, -1)
};
