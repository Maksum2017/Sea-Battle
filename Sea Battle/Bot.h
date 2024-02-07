#pragma once
#include <iostream>
#include "Ship.h"
#include "Map.h"
using std::cout;
using std::endl;

class Bot : protected Ship, protected Map
{
protected:
	vector<Ship> ships1;
	vector<Ship> ships2;
	vector<Ship> ships3;
	Ship ships4;
	void drow_map() noexcept;

	// checking if there are ships nearby.
	bool checking_space_for_ship(const Ship& _ship) noexcept;

	// puts the ship on the map.
	void put_ship(const Ship& _ship, const bool turn) noexcept;

	// random filling of the map with ships.
	void rand_filling(Ship& _ship) noexcept;
public:
	Bot() : ships1(4, Ship(1)), ships2(3, Ship(2)), ships3(2, Ship(3)), ships4(4) {}

	// random ship selection menu.
	void map_filling() noexcept;
};