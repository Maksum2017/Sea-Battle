#include "Bot.h"

void Bot::drow_map() noexcept
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '<' || map[i][j] == 'V' || map[i][j] == '\262')
				cout << "\033[36;5m" << map[i][j] << "\033[m";
			else
				cout << map[i][j];
		}
		cout << endl;
	}
}

// checking if there are ships nearby.
bool Bot::checking_space_for_ship(const Ship& _ship) noexcept
{
	vector<char> symbol{ '<','V','\262' };
	for (int i = 0; i < _ship.get_ship().size(); i++) {
		for (int j = -2; j <= 2; j += 2) {
			for (int s = 0; s < symbol.size(); s++) {
				if (((_ship.get_ship()[i].first + j > 20) ? false : map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second] == symbol[s]) ||
					map[_ship.get_ship()[i].first][_ship.get_ship()[i].second + j] == symbol[s] ||
					((_ship.get_ship()[i].first + j > 20) ? false : map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second + j] == symbol[s]) ||
					((_ship.get_ship()[i].first - j > 20 || _ship.get_ship()[i].second + j > 21) ? false :
						map[_ship.get_ship()[i].first - j][_ship.get_ship()[i].second + j] == symbol[s]))
					return false;
			}
		}
	}
	return true;
}

// puts the ship on the map.
void Bot::put_ship(const Ship& _ship, const bool _turn) noexcept
{
	for (int l = 0; l < _ship.get_ship().size(); l++) {
		if (!l) {
			if (_turn)
				map[_ship.get_ship()[l].first][_ship.get_ship()[l].second] = 'V';
			else
				map[_ship.get_ship()[l].first][_ship.get_ship()[l].second] = '<';
		}
		else
			map[_ship.get_ship()[l].first][_ship.get_ship()[l].second] = '\262';
	}
}

// random filling of the map with ships.
void Bot::rand_filling(Ship& _ship) noexcept
{
	srand(time(NULL));
	bool turn;
	bool flag = true;
	do {
		do
		{
			// head creation check.
			turn = rand() % 2;
			pair<int, int> point;
			do {
				flag = true;
				point.first = rand() % 19 + 2;
				if (point.first % 2 != 0) {
					flag = false;
					continue;
				}
				point.second = rand() % 19 + 3;
				if (point.second % 2 == 0) {
					flag = false;
					continue;
				}
			} while (!flag);

			// creating tail.
			_ship.set_ship()[0].first = point.first;
			_ship.set_ship()[0].second = point.second;

			// creates the position of the ship.
			if (!turn) {
				for (int i = 1; i < _ship.get_ship().size(); i++)
				{
					_ship.set_ship()[i].first = _ship.get_ship()[i - 1].first;
					_ship.set_ship()[i].second = _ship.get_ship()[i - 1].second + 2;
					if (_ship.get_ship()[i].second < 3 || _ship.get_ship()[i].second > 21) {
						flag = false;
						break;
					}
				}
			}
			else {
				for (int i = 1; i < _ship.get_ship().size(); i++)
				{
					_ship.set_ship()[i].first = _ship.get_ship()[i - 1].first - 2;
					_ship.set_ship()[i].second = _ship.get_ship()[i - 1].second;
					if (_ship.get_ship()[i].first < 2 || _ship.get_ship()[i].first > 20) {
						flag = false;
						break;
					}
				}
			}
		} while (!flag);

		// checking if there are ships nearby.
		if (checking_space_for_ship(_ship)) {
			// puts the ship on the map
			put_ship(_ship, turn);
			return;
		}
	} while (true);
}

// random ship selection menu.
void Bot::map_filling() noexcept
{
	// count_all_ships.
	vector<int> count_ships{ 1,2,3,4 };

	int menu = 0;
	do {
		switch (menu) {
		case 0:
			if (count_ships[0] != 0) {
				--count_ships[menu];
				rand_filling(ships4);
			}
			else
				menu++;
			break;
		case 1:
			if (count_ships[menu] != 0)
				rand_filling(ships3[--count_ships[menu]]);
			else
				menu++;
			break;
		case 2:
			if (count_ships[menu] != 0)
				rand_filling(ships2[--count_ships[menu]]);
			else
				menu++;
			break;
		case 3:
			if (count_ships[menu] != 0)
				rand_filling(ships1[--count_ships[menu]]);
			else
				menu++;
			break;
		default:
			return;
		}
	} while (true);
}