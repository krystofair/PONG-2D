//
// Created by Christofair on 23.04.2019.
//

#include "rakieta.h"
#include "globals.h"

void Rakieta::setPozycja(float x, float y)
{
    pos_x = x;
    pos_y = y;
}

void Rakieta::setPozX(float x)
{ pos_x = x; }

void Rakieta::setPozY(float y)
{ pos_y = y; }

float Rakieta::getPozX() { return pos_x; }

float Rakieta::getPozY() { return pos_y; }

float Rakieta::getSzerokosc() { return szerokosc; }

float Rakieta::getDlugosc() { return dlugosc; }

void Rakieta::setSzerokosc(float s) { szerokosc = s; }

void Rakieta::setDlugosc(float dl) { dlugosc = dl; }

float Rakieta::getSzybkosc() const { return szybkosc; }

void Rakieta::moveTo(float lim)
{
	lim_y = lim;
	if(lim_y < 0) lim_y = 0;
	else if(lim_y > plansza.getHeight()-dlugosc) lim_y = plansza.getHeight()-dlugosc;
}

void Rakieta::move()
{
	//if(pos_y == lim_y);
	if(pos_y < lim_y) pos_y += szybkosc;
	else if(pos_y > lim_y) pos_y -= szybkosc;
}

void Rakieta::move(float seconds)
{
	if(pos_y < lim_y) pos_y += szybkosc*seconds;
	else if(pos_y > lim_y) pos_y -= szybkosc*seconds;
}

void Rakieta::draw(sf::RenderTarget & rt, sf::RenderStates states) const
{
	auto prostokat = sf::RectangleShape(sf::Vector2f(szerokosc, dlugosc));
	prostokat.setPosition(pos_x, pos_y);
	prostokat.setFillColor(sf::Color::White);
	rt.draw(prostokat, states);
}
