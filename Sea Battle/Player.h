#pragma once
#include <conio.h>
#include "Bot.h"

class Player : protected Bot
{
protected:
	void drow_map(int& _menu, vector<int> _count_ships) noexcept;

	// filling the map with ships.
	void filling(Ship& _ship) noexcept;

	// random ship selection menu.
	void rand_map_filling(vector<int>& count_ships) noexcept;

public:
	Player() : Bot() {}

	// ship selection menu.
	void map_filling() noexcept;
};