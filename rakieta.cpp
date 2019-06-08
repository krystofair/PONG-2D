//
// Created by Christofair on 23.04.2019.
//

#include "rakieta.h"

void Rakieta::setPozycja(float x, float y)
{
    pos_x = x;
    pos_y = y;
}

void Rakieta::setPozX(float x)
{ pos_x = x; }

void Rakieta::setPozY(float y)
{ pos_y = y; }

unsigned Rakieta::getPozX() { return pos_x; }

unsigned Rakieta::getPozY() { return pos_y; }

unsigned Rakieta::getSzerokosc() { return szerokosc; }

unsigned Rakieta::getDlugosc() { return dlugosc; }

void Rakieta::setSzerokosc(float s) { szerokosc = s; }

void Rakieta::setDlugosc(float dl) { dlugosc = dl; }

unsigned Rakieta::getSzybkosc() const { return szybkosc; }

void Rakieta::moveTo(float lim)
{
	lim_y = lim;
}

void Rakieta::move()
{
	//if(pos_y < lim_y-szybkosc*10 || pos_y > lim_y + dlugosc + szybkosc*2);
	if(pos_y < lim_y) pos_y += szybkosc;
	else pos_y -= szybkosc;
	//sf::RectangleShape::move(sf::Vector2f(pos_x, lim_y)); 
}

void Rakieta::draw(sf::RenderTarget & rt, sf::RenderStates states) const
{
	auto prostokat = sf::RectangleShape(sf::Vector2f(szerokosc, dlugosc));
	prostokat.setPosition(pos_x, pos_y);
	prostokat.setFillColor(sf::Color::White);
	rt.draw(prostokat, states);
}
