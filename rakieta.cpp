//
// Created by Christofair on 23.04.2019.
//

#include "rakieta.h"

void Rakieta::setPozycja(unsigned int x, unsigned int y)
{
    pos_x = x;
    pos_y = y;
}

void Rakieta::setPozX(unsigned int x)
{ pos_x = x; }

void Rakieta::setPozY(unsigned int y)
{ pos_y = y; }

unsigned Rakieta::getPozX() { return pos_x; }

unsigned Rakieta::getPozY() { return pos_y; }

unsigned Rakieta::getSzerokosc() { return szerokosc; }

unsigned Rakieta::getDlugosc() { return dlugosc; }

void Rakieta::setSzerokosc(unsigned s) { szerokosc = s; }

void Rakieta::setDlugosc(unsigned dl) { dlugosc = dl; }

void Rakieta::moveTo(unsigned lim)
{
	lim_y = lim;
}
