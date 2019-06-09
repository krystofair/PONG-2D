#include <cmath>
struct Stala// zmienne globalne potrzebne do obróbki na silniku
{
	int bs = 50;
	int br = 15;
	bool rodzaj;// 0 = banda
	bool paletka = true; //true = prawa paletka || false = lewa paletka(ważne do prostej
	bool banda = true; // true = górna banda || false = dolna banda (ważne do prostej)
	int palecz = 1;//jaka część paletki (1=góra, 2=środek 3=doł)
};

class Silnik
{
	int alfa;
	float a, b;
public:
	Silnik(float x, float y, int kat)
	{
		a = x;
		b = y;
		alfa = kat;
	};
	float getA()
	{
		return a;
	};
	float getB()
	{
		return b;
	};
	int getAlfa()
	{
		return alfa;
	};

	void prosta(float &a, float &b, bool rodzaj)
	{
		a = -a;
		if (rodzaj == 0) b = -b;
	}
	void gorapaletkatrue(int &predkosc, int &rotacja, int bs, int br)//||| domysla ujemna rotacja
	{
		predkosc = predkosc + 2 * bs;
		if (rotacja == 0) rotacja = rotacja - br;//piłka bez rotacji
		if (rotacja != 0)// piłka z rotacja
		{
			if (rotacja > 0)// +r
			{
				rotacja = rotacja + br;
			}
			else
			{
				rotacja = rotacja * -1;
				rotacja = rotacja - br;//zmniejsza
			}
		}
		if (predkosc > 1000) predkosc = 1000;//nie przekraczanie wartosci maksymalnej
		if (rotacja > 100) rotacja = 100;/////
		if (rotacja < -100) rotacja = -100;///
	}
	void dolnapaletkatrue(int &predkosc, int &rotacja, int bs, int br)//||| domyslna dodatnia rotacja
	{
		predkosc = predkosc + 2 * bs;
		if (rotacja == 0) rotacja = rotacja + br;//piłka bez rotacji
		if (rotacja != 0)// piłka z rotacja
		{
			if (rotacja < 0)// -r
			{
				rotacja = rotacja - br;
			}
			else
			{
				rotacja = rotacja * -1;
				rotacja = rotacja + br;//zmniejsza
			}
		}
		if (predkosc > 1000) predkosc = 1000;//nie przekraczanie wartosci maksymalnej
		if (rotacja > 100) rotacja = 100;//////
		if (rotacja < -100) rotacja = -100;////
	}
	void srodkowapaletka(int &predkosc, int &rotacja, int bs, int br)
	{
		predkosc = predkosc + (2 * bs);
		if (predkosc > 1000) predkosc = 1000;//nie przekraczanie wartosci maksymalnej
		if (rotacja > 100) rotacja = 100;//////
		if (rotacja < -100) rotacja = -100;////
	}
};

/*void ZmianaParametrowPilkiPoOdbiciuOdPaletki(int &predkosc, int &rotacja, int bs, int br, char CzescPaletki)
{
	predkosc = predkosc + 2 * bs;
	if (rotacja == 0) rotacja = rotacja - (CzescPaletki*br);//pi�ka bez rotacji
	if (rotacja != 0)// pi�ka z rotacja
	{
		if ((CzescPaletki = 1 && rotacja > 0) || (CzescPaletki = -1 && rotacja < 0))
		{
			rotacja = rotacja + CzescPaletki * br;//zwieksza bezwgledn� warto�� wspolczynnika rotacji
		}
		else
		{
			rotacja = rotacja - CzescPaletki * br;//zmniejsza bezwgledn� warto�� wspolczynnika rotacji
		}

	}
	if (predkosc > 1000) predkosc = 1000;//nie przekraczanie wartosci maksymalnej
	if (rotacja > 100) rotacja = 100;//////
	if (rotacja < -100) rotacja = -100;////
}
*/


void silnikpaletka(float &a, float &b, int &alfa)
{
	Ball* ball = plansza.getPilka();
	Silnik lol(a,b,alfa);
	Stala x;
	int rota = ball.Getrotation();
	int speed = ball.GetSpeed();
	int pomocna;
	x.rodzaj = true;
	if (x.paletka == true)// sprawdza która paletka (true dla prawej)
		{
			switch (x.palecz)
			{
			case 1:
			{
				lol.gorapaletkatrue(speed, rota, x.bs, x.br);
				break;
			}
			case 2:
			{
				lol.srodkowapaletka(speed, rota, x.bs, x.br);
				break;
			}
			case 3:
			{
				lol.dolnapaletkatrue(speed, rota, x.bs, x.br);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			switch (x.palecz)
			{
			case 1:
			{
				lol.dolnapaletkatrue(speed, rota, x.bs, x.br);
				break;
			}
			case 2:
			{
				lol.srodkowapaletka(speed, rota, x.bs, x.br);
				break;
			}
			case 3:
			{
				lol.gorapaletkatrue(speed, rota, x.bs, x.br);
				break;
			}
			default:
				break;
			}
		}
	
	rota = 0;//musi być aby zawsze byłą prosta
	if (rota == 0)
	{
		lol.prosta(lol.getA, lol.getB, x.rodzaj);
	}
	else
	{

	}
	Ball->SetSpeed(speed);
	Ball->SetRotation(rota);
}
void silnikbanda(float &a, float &b, int &alfa)
{
	int pomocna;
	Silnik lol(a, b, alfa);
	Stala x;
	int rota = ball->GetRotation();
	int speed = ball->GetSpeed();
	x.rodzaj = false;
	if (speed > x.bs * 2) // algorytm na speeda
	{
		speed = speed - x.bs;
	}
	else
	{
		pomocna = speed - x.bs;
		speed = speed - pomocna;
	}
	if (rota > x.br || rota < -x.br)// sprawdza czy rot jest w przedziałe z liczbą odejmowaną wiekszy lub mniejszy od bs(-bs)
	{
		pomocna = rota;
		rota = abs(rota) - x.br;
		if (rota > -x.br && rota < x.br) rota = 0;// Sprawdza czy jest w minimalnym przedziale

	}
	else
	{
		rota = 0;
	}
	rota = rota * -1; // odwraca rotacje



	rota = 0;//musi być aby zawsze byłą prosta
	if (rota == 0)
	{
		lol.prosta(lol.getA, lol.getB, x.rodzaj);
	}
	else
	{

	}
	ball->SetSpeed(speed);
	ball->SetRotation(rota);
}