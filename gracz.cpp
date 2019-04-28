//
// Created by Christofair on 23.04.2019.
//

#include "gracz.h"

void Gracz::setRakieta(const Rakieta& r)
{
	*rakieta = r;
}

Rakieta& Gracz::getRakieta() const
{
	return *rakieta;
}

void Gracz::setKlawisze(Klawisz up, Klawisz down, Klawisz left, Klawisz right)
{
	klawisze[0] = up;
	klawisze[1] = down;
	klawisze[2] = left;
	klawisze[3] = right;
}

const Klawisz& Gracz::getKlawisz(unsigned int index) const
{
	return klawisze[index];
}

Gracz::~Gracz()
{
	delete rakieta;
}
