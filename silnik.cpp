#include <cmath>

#include "silnik.h"


void Silnik::gorapaletkatrue()
{
	int predkosc = ball->GetSpeed();
	int rotacja = ball->GetRotation();
	
	predkosc = predkosc + 2 * bs;
	if(rotacja == 0) rotacja = rotacja - br;//piłka bez rotacji
	if(rotacja != 0)// piłka z rotacja
	{
		if(rotacja > 0)// +r
		{
			rotacja = rotacja + br;
		}
		else
		{
			rotacja = rotacja * -1;
			rotacja = rotacja - br;//zmniejsza
		}
	}
	ball->SetSpeed(predkosc);
	ball->SetRotation(rotacja);
}

void Silnik::srodkowapaletka()
{
	int predkosc = ball->GetSpeed();
	int rotacja = ball->GetRotation();
	predkosc = predkosc + (2 * bs);
	ball->SetSpeed(predkosc);
	ball->SetRotation(rotacja);
}

void Silnik::dolnapaletkatrue()
{
	int predkosc = ball->GetSpeed();
	int rotacja = ball->GetRotation();
	predkosc = predkosc + 2 * bs;
	if(rotacja == 0) rotacja = rotacja + br;//piłka bez rotacji
	if(rotacja != 0)// piłka z rotacja
	{
		if(rotacja < 0)// -r
		{
			rotacja = rotacja - br;
		}
		else
		{
			rotacja = rotacja * -1;
			rotacja = rotacja + br;//zmniejsza
		}
	}
	ball->SetSpeed(predkosc);
	ball->SetRotation(rotacja);
}



void Silnik::dowolnapaletka(char CzescPaletki)
{
	int predkosc = ball->GetSpeed();
	int rotacja = ball->GetRotation();
	predkosc = predkosc + 2 * bs;
	if (CzescPaletki == static_cast<char>(CzPaletki::part_down)
		|| CzescPaletki == static_cast<char>(CzPaletki::part_up))
	{
		if (rotacja == 0) rotacja = rotacja - CzescPaletki* br;//piłka bez rotacji
		if (rotacja != 0)// piłka z rotacja
		{
			if ((CzescPaletki == static_cast<char>(CzPaletki::part_down) && rotacja < 0) 
				|| (CzescPaletki == static_cast<char>(CzPaletki::part_up) && rotacja > 0))// -r
			{
				rotacja = rotacja + CzescPaletki * br;
			}
			else
			{
				rotacja = rotacja * -1;
				rotacja = rotacja - CzescPaletki * br;//zmniejsza
			}
		}
	}
	ball->SetSpeed(predkosc);
	ball->SetRotation(rotacja);
}


void ZmianaParametrowPilkiPoOdbiciuOdPaletki(int &predkosc, int &rotacja, int bs, int br, char CzescPaletki)
{
	predkosc = predkosc + 2 * bs;
	if (CzescPaletki == static_cast<char>(CzPaletki::part_down)
		|| CzescPaletki == static_cast<char>(CzPaletki::part_up))
	{
		if (rotacja == 0) rotacja = rotacja - (CzescPaletki*br);//pi�ka bez rotacji
		if (rotacja != 0)// pi�ka z rotacja
		{
			if ((CzescPaletki = 1 && rotacja > 0) || (CzescPaletki = -1 && rotacja < 0))
			{
				rotacja = rotacja + CzescPaletki * br;//zwieksza bezwgledn� warto�� wspolczynnika rotacji
			}
			else
			{
				rotacja = rotacja * -1;
				rotacja = rotacja - CzescPaletki * br;//zmniejsza bezwgledn� warto�� wspolczynnika rotacji
			}
		}
	}
	if (predkosc > 1000) predkosc = 1000;//nie przekraczanie wartosci maksymalnej
	if (rotacja > 100) rotacja = 100;//////
	if (rotacja < -100) rotacja = -100;////
}



void Silnik::prosta()
{
	float y = ball->GetPosition().y;
	float x = ball->GetPosition().x; // x znany z momentu kolizji.
	a = -a;
	b = y / a*x;
}

void Silnik::odbicieBanda()
{
	int pomocna;
	int rota = ball->GetRotation();
	int speed = ball->GetSpeed();
	if(speed > bs * 2) // algorytm na speeda
	{
		speed = speed - bs;
	}
	else
	{
		pomocna = speed - bs;
		speed = speed - pomocna;
	}
	if(rota > br || rota < - br)// sprawdza czy rot jest w przedziałe z liczbą odejmowaną wiekszy lub mniejszy od bs(-bs)
	{
		pomocna = rota;
		rota = abs((float)rota) - br;
		if(rota > - br && rota < br) rota = 0;// Sprawdza czy jest w minimalnym przedziale

	}
	else
	{
		rota = 0;
	}
	rota = rota * -1; // odwraca rotacje
	if(rota == 0)
	{
		prosta(); 
	}
	else
	{
		//
	}
	ball->SetSpeed(speed);
	ball->SetRotation(rota);
}

void Silnik::odbiciePaletka(bool prawa)
{
	int rota = ball->GetRotation();
	int speed = ball->GetSpeed();
	int pomocna;

	//dowolnapaletka(czesc_rakiety);

	if(prawa)// sprawdza która paletka (true dla prawej)
	{
		switch(czesc_rakiety)
		{
			case 1:
			{
				gorapaletkatrue();
				break;
			}
			case 2:
			{
				srodkowapaletka();
				break;
			}
			case 3:
			{
				dolnapaletkatrue();
				break;
			}
			default:
				break;
		}
	}
	else
	{
		switch(czesc_rakiety)
		{
			case 1:
			{
				dolnapaletkatrue();
				break;
			}
			case 2:
			{
				srodkowapaletka();
				break;
			}
			case 3:
			{
				gorapaletkatrue();
				break;
			}
			default:
				break;
		}
	}

	//rota = 0;//musi być aby zawsze byłą prosta
	if(rota == 0)
	{
		prosta();
	}
	else
	{

	}
	ball->SetSpeed(speed);
	ball->SetRotation(rota);
}

Silnik::Silnik(float _a, float _b, int kat) : a(_a), b(_b), alfa(kat){}

float Silnik::getA() const { return a; }
float Silnik::getB() const { return b; }
int Silnik::getAlfa() const { return alfa; }

void Silnik::setCzesc(int czesc) { czesc_rakiety = czesc; }