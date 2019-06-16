//
// Created by Christofair on 23.04.2019.
//

#include <fstream>

#include "gracz.h"

Gracz::Gracz(Rakieta* r, int _id) : IGracz(r), id(_id)
{
	SI = false;
	std::ifstream configkeys;
	switch(id)
	{
		case 1:
			configkeys.open("gracz1.cfg");
			if(!configkeys.good())
			{
				setKlawisze(Klawisz::P, Klawisz::L);
				saveKeyboardSet();
			}
			else
			{
				loadKeyboardSet();
			}
			configkeys.close();
			break;
		case 2:
			configkeys.open("gracz2.cfg");
			if(!configkeys.good())
			{
				setKlawisze(Klawisz::W, Klawisz::A);
				saveKeyboardSet();
			}
			else
			{
				loadKeyboardSet();
			}
			configkeys.close();
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

void Gracz::setKlawisze(KeysSet keys_set)
{
	klawisze[0] = keys_set.up;
	klawisze[1] = keys_set.down;
	klawisze[2] = keys_set.left;
	klawisze[3] = keys_set.right;
}

void Gracz::saveKeyboardSet()
{
	std::ofstream config;
	switch(id)
	{
		case 1: config.open("gracz1.cfg", std::ios_base::trunc); break;
		case 2: config.open("gracz2.cfg", std::ios_base::trunc); break;
		default: 
			config.open("pong.log");
			config << "Nie uda³o siê zapisaæ konfiguracji. Z powodu b³êdnego id";
			config << std::endl << "W Gracz::saveKeyboardSet" << std::endl;
			config.close();
	}
	if(config.is_open())
	{
		config << static_cast<int>(klawisze[0]) << std::endl
			<< static_cast<int>(klawisze[1]) << std::endl
			<< static_cast<int>(klawisze[2]) << std::endl
			<< static_cast<int>(klawisze[3]) << std::endl;
		config.close();
	}
}

KeysSet Gracz::loadKeyboardSet()
{
	int kl;
	std::ifstream config;
	if(id == 1) config.open("gracz1.cfg");
	else if(id == 2) config.open("gracz2.cfg");
	if(config.good())
	{
		config >> kl;
		klawisze[0] = static_cast<Klawisz>(kl);
		config >> kl;
		klawisze[1] = static_cast<Klawisz>(kl);
		config >> kl;
		klawisze[2] = static_cast<Klawisz>(kl);
		config >> kl;
		klawisze[3] = static_cast<Klawisz>(kl);
		config.close();
		try{
			for(auto& key : klawisze)
				if(key < -1 || key > Klawisz::KeyCount)
					throw("Houston we have a problem. (in Gracz::loadKeyboardSet)");
			return {klawisze[0], klawisze[1], klawisze[2], klawisze[3]};
		}
		catch(const char* error)
		{
			std::ofstream log_file("pong.log");
			log_file << error << std::endl;
			log_file.close();
		}
	}
	else
	{
		auto log_file = std::ofstream("pong.log");
		log_file << "Nie uda³o siê za³adowaæ ustawieñ "
			<< "klawiszy w Gracz::loadKey.Set" << std::endl
			<< "z powodu b³êdu otwacia pliku." << std::endl;
		log_file.close();
	}
	
}