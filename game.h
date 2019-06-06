#include "IMenu.h"

#pragma once

class Game
{
	IMenu* current_menu;
public:
	void changeMenu(IMenu* new_menu)
	{
		current_menu = new_menu;
	}

};