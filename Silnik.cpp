
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <conio.h>
void prosta(float &a, float &b, bool rodzaj)
{
	a = -a;
	if (rodzaj == 0) b = -b;
}
void parabola()
{

}
void wyk()
{

}
void gorapaletkatrue(int &predkosc, int &rotacja, int bs, int br)//||| domysla ujemna rotacja
{
	predkosc = predkosc + 2 * bs;
	if (rotacja == 0) rotacja = rotacja - br;//pi³ka bez rotacji
	if (rotacja != 0)// pi³ka z rotacja
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
	if (rotacja == 0) rotacja = rotacja + br;//pi³ka bez rotacji
	if (rotacja != 0)// pi³ka z rotacja
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

/*
Funkcjamodyfukuje parametry pilki

parametry:
	...
	czesc-ktora czesc paletki odbija pilke 1: gora, 0:srodek, -1 dol
*/
void ZmianaParametrowPilkiPoOdbiciuOdPaletki(int &predkosc, int &rotacja, int bs, int br, char CzescPaletki)
{	predkosc = predkosc + 2 * bs;
	if (rotacja == 0) rotacja = rotacja -(CzescPaletki*br);//pi³ka bez rotacji
	if (rotacja != 0)// pi³ka z rotacja
	{
		if ((CzescPaletki = 1 && rotacja > 0) || (CzescPaletki = -1 && rotacja < 0))
		{
			rotacja=rotacja+ CzescPaletki* br;//zwieksza bezwgledn¹ wartoœæ wspolczynnika rotacji
		}
		else
		{
			rotacja = rotacja - CzescPaletki * br;//zmniejsza bezwgledn¹ wartoœæ wspolczynnika rotacji
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

float silnik()
{

	float a, b;
	int pomocna=0, bs=50, br= 15;// bs= basic speed (wykorzystwyana w dodawaniu i odejmowaniu speeda) to samo w rotacji "basic rotacion"
	int rota=100; // rotacja dodatnia = zgodnie z wskazuwkami zegara ||rotacja ujemna == przeciwnie do wskazówek zegara
	int speed=1000;
	bool paletka=true; //true = prawa paletka || false = lewa paletka(wa¿ne do prostej)
	bool rodzaj=true; // true =w paletka || false = banda
	bool banda=true; // true = górna banda || false = dolna banda (wa¿ne do prostej)
	int palecz=1;//jaka czêœæ paletki (1=góra, 2=œrodek 3=do³)
	while (true)//TESTER
	{
		printf("\npodaj predkosc:");
		scanf_s("%d", &speed);
		printf("\npodaj rotacja:");
		scanf_s("%d", &rota);
		printf("\nrodzaj kolizji(0 do banda):");
		scanf_s("%d", &rodzaj);
		if (rodzaj == false) break;
		printf("\nktora paletka (prawa to true):");
		scanf_s("%d", &paletka);
		printf("\nkolizja pilki wspolrzêdna:");
		scanf_s("%d", &palecz);
		break;
	}
	if(!rodzaj) // kolizja z band¹
	{
		if (speed > bs*2) // algorytm na speeda
		{
			speed = speed - bs;
		}
		else
		{
			pomocna = speed - bs;
			speed = speed - pomocna;
		}
		if (rota > br || rota < -br)// sprawdza czy rot jest w przedzia³e z liczb¹ odejmowan¹ wiekszy lub mniejszy od bs(-bs)
		{
			pomocna = rota;
			rota = abs(rota) - br;
			if (rota > -br && rota < br) rota = 0;// Sprawdza czy jest w minimalnym przedziale

		}
		else 
		{
			rota = 0;
		}
		rota = rota * -1; // odwraca rotacje
	}
	else
	{
		if (paletka == true)// sprawdza która paletka (true dla prawej)
		{
			switch (palecz)
			{
			case 1:
				{
				gorapaletkatrue(speed, rota, bs, br);
					break;
				}
			case 2:
				{
				srodkowapaletka(speed, rota, bs, br);
					break;
				}
			case 3:
				{
				dolnapaletkatrue(speed, rota, bs, br);
					break;
				}
			default:
				break;
			}
		}
		else
		{
			switch (palecz)
			{
			case 1:
			{
				dolnapaletkatrue(speed, rota, bs, br);
				break;
			}
			case 2:
			{
				srodkowapaletka(speed, rota, bs, br);
				break;
			}
			case 3:
			{
				gorapaletkatrue(speed, rota, bs, br);
				break;
			}
			default:
				break;
			}
		}
	}

	rota = 0;//musi byæ aby zawsze by³¹ prosta
	if (rota== 0)
	{
		prosta(a,b,rodzaj);
	}
	else
	{

	}

	return a,b;
}

