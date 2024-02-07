#pragma once
#include <vector>
using std::vector;
using std::pair;

class Ship {
protected:
	vector<pair<int, int>> ship;
public:
	Ship(const int& size) : ship(size) {}
	Ship() = default;
	const vector<pair<int, int>> get_ship() noexcept {
		return ship;
	}
	const vector<pair<int, int>> get_ship() const noexcept {
		return ship;
	}
	vector<pair<int, int>>& set_ship() noexcept {
		return ship;
	}
};