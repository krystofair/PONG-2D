//
// Created by Christofair on 23.04.2019.
//

#include "gracz.h"

Gracz::Gracz(Rakieta& r, int _id) : IGracz(r), id(_id)
{
	switch(id)
	{
		case 1:
			setKlawisze(Klawisz::P, Klawisz::L, Klawisz::Unknown, Klawisz::Unknown);
			break;
		case 2:
			setKlawisze(Klawisz::W, Klawisz::A, Klawisz::Unknown, Klawisz::Unknown);
			break;
	}
}

void Gracz::setKlawisze(Klawisz up, Klawisz down, Klawisz left, Klawisz right)
{
    klawisze[0] = up;
    klawisze[1] = down;
    klawisze[2] = left;
    klawisze[3] = right;
}
