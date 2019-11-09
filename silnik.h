#pragma once
#include "Ball.h"

enum class CzPaletki
{
	part_up = 1,
	part_middle = 0,
	part_down = -1
};


class Silnik
{
public:
	Silnik(float x, float y, int kat);
	float getA() const;
	float getB() const;
	int getAlfa() const;
	void prosta();
	void gorapaletkatrue();
	void srodkowapaletka();
	void dolnapaletkatrue();//||| domyslna dodatnia rotacja
	void odbiciePaletka(bool prawa); // silnikpaletka nazwa zmieniona
	void odbicieBanda(); // silnikbanda nazwa zmieniona. (bez flagi czy dolna czy gorna)
	void dowolnapaletka(char CzescPaletki);
	void setCzesc(int);


public:
	/// dostarczenie obiektu pilki do silnika
	void setBall(Ball* b) { ball = b; }
private:
	Ball* ball; //weak pointer;

private:
	int alfa;
	float a, b;
	//zmienne srodowiskowe
	int bs{50}; // basic speed
	int br{15}; // basic rotation
	// jakies pomocnicze.
	int czesc_rakiety{2}; // czeœæ paletki 1-up, 2-mid, 3-bottom (1, 0, -1)
};