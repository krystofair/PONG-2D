#pragma once
#include <cmath>
#include "Ball.h"
#define part_up 1
#define part_middle  0
#define part_down -1
class Silnik
{
public:
	Silnik(float x, float y, int kat) : a(x), b(y), alfa(kat) {}
	float getA() { return a; }
	float getB() { return b; }
	int getAlfa() { return alfa; }
	void prosta();
	void gorapaletkatrue();
	void srodkowapaletka();
	void dolnapaletkatrue();//||| domyslna dodatnia rotacja
	void odbiciePaletka(bool prawa); // silnikpaletka nazwa zmieniona
	void odbicieBanda(); // silnikbanda nazwa zmieniona. (bez flagi czy dolna czy gorna)
	void dowolnapaletka(char CzescPaletki);


public:
	/// dostarczenie obiektu pilki do silnika
	void setBall(Ball* b) { ball = b; }
private:
	Ball* ball;

private:
	int alfa;
	float a, b;
	//zmienne srodowiskowe
	int bs{50}; // basic speed
	int br{15}; // basic rotation
	// jakies pomocnicze.
	int palecz{1}; // czeœæ paletki 1-up, 2-mid, 3-bottom (1, 0, -1)
};
