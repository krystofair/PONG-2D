//
// Created by Christofair on 23.04.2019.
//

#include "rakieta.h"
#include "globals.h"

void Rakieta::setPozX(float x)
{
	auto y = getPosition().y;
	setPosition(x, y);
}

void Rakieta::setPozY(float y)
{
	auto x = getPosition().x;
	setPosition(x, y);
}

float Rakieta::getPozX() { return getPosition().x; }

float Rakieta::getPozY() { return getPosition().y; }

float Rakieta::getSzerokosc() { return getSize().x; }

float Rakieta::getDlugosc() { return getSize().y; }

void Rakieta::setSzerokosc(float s) 
{
	auto dlugosc = getDlugosc();
	setSize(sf::Vector2f(s, dlugosc));
}

void Rakieta::setDlugosc(float dl) 
{
	auto szerokosc = getSzerokosc();
	setSize(sf::Vector2f(szerokosc, dl)); 
}

float Rakieta::getSzybkosc() const { return szybkosc; }

void Rakieta::moveTo(float lim)
{
	auto dlugosc = getDlugosc();
	lim_y = lim;
	if(lim_y < 0) lim_y = 0;
	else if(lim_y > plansza.getHeight()-dlugosc) lim_y = plansza.getHeight()-dlugosc;
}

void Rakieta::move()
{
	auto pos_x = getPozX();
	auto pos_y = getPozY();
	//if(pos_y == lim_y);
	if(pos_y < lim_y) pos_y += szybkosc;
	else if(pos_y > lim_y) pos_y -= szybkosc;
	setPosition(pos_x, pos_y);
}

void Rakieta::move(double seconds)
{
	auto pos_y = getPozY();
	if(abs(pos_y-lim_y) < 5) return;
	if(pos_y < lim_y) pos_y += szybkosc*seconds;
	else if(pos_y > lim_y) pos_y -= szybkosc*seconds;
	setPozY(pos_y);
}

void Rakieta::setStrona(bool _prawa)
{
	prawa = _prawa;
}