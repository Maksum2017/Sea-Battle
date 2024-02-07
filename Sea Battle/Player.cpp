#include "Player.h"

void Player::drow_map(int& _menu, vector<int> _count_ships) noexcept
{
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '<' || map[i][j] == 'V' || map[i][j] == '\262')
				cout << "\033[36;5m" << map[i][j] << "\033[m";
			else
				cout << map[i][j];
		}
		if (i == 2)
			cout << "\t\t" << ((_count_ships[0]) ? "\033[37;5m" : "\033[31;5m") << _count_ships[0] << ((_menu == 1) ? " \033[47;5m" : " ") << "\033[36;5m<\262\262\262\033[m";
		else if (i == 4)
			cout << "\t\t" << ((_count_ships[1]) ? "\033[37;5m" : "\033[31;5m") << _count_ships[1] << ((_menu == 2) ? " \033[47;5m" : " ") << "\033[36;5m<\262\262\033[m";
		else if (i == 6)
			cout << "\t\t" << ((_count_ships[2]) ? "\033[37;5m" : "\033[31;5m") << _count_ships[2] << ((_menu == 3) ? " \033[47;5m" : " ") << "\033[36;5m<\262\033[m";
		else if (i == 8)
			cout << "\t\t" << ((_count_ships[3]) ? "\033[37;5m" : "\033[31;5m") << _count_ships[3] << ((_menu == 4) ? " \033[47;5m" : " ") << "\033[36;5m<\033[m";
		else if (i == 10)
			cout << "\t\t" << ((_menu == 5) ? " \033[47;5m" : " ") << "\033[35;5mRandom\033[m";
		else if (i == 12)
			cout << "\t\t" << ((_menu == 6) ? " \033[47;5m" : " ") << "\033[31;5mClear\033[m";
		else if (i == 14)
			cout << "\t\t" << ((_menu == 7) ? " \033[47;5m" : " ") << "\033[33;5mStart\033[m";
		cout << endl;
	}
}

// filling the map with ships.
void Player::filling(Ship& _ship) noexcept
{
	vector<char> symbol{ '<','V','\262' };
	bool turn = false;
	bool flag = true;

	// creating head.
	_ship.set_ship()[0].first = 2;
	_ship.set_ship()[0].second = 3;

	// creating tail.
	for (int i = 1; i < _ship.get_ship().size(); i++)
	{
		_ship.set_ship()[i].first = _ship.get_ship()[i - 1].first;
		_ship.set_ship()[i].second = _ship.get_ship()[i - 1].second + 2;
	}
	do {
		// show map and ships.
		if (flag) {
			system("cls");
			for (int i = 0; i < map.size(); i++) {
				for (int j = 0; j <= map.size(); j++) {
					bool flag = true;
					for (int l = 0; l < _ship.get_ship().size(); l++) {
						if (_ship.get_ship()[l].first == i && _ship.get_ship()[l].second == j) {
							if (!l) {
								if (turn)
									cout << "\033[47;5m\033[36;5m" << 'V' << "\033[m";
								else
									cout << "\033[47;5m\033[36;5m" << '<' << "\033[m";
							}
							else
								cout << "\033[47;5m\033[36;5m" << '\262' << "\033[m";
							flag = false;
						}
					}
					if (flag) {
						if (map[i][j] == '<' || map[i][j] == 'V' || map[i][j] == '\262')
							cout << "\033[36;5m" << map[i][j] << "\033[m";
						else
							cout << map[i][j];
					}
				}
				if (i == 2)
					cout << "\t\tTurn --> r";
				cout << endl;
			}
		}

		// variable in order not to draw the map one more time.
		flag = true;

		// ship movement.
		switch (_getch()) {
		case 'w':
			if (_ship.get_ship()[_ship.get_ship().size() - 1].first == 2) {
				flag = false;
				break;
			}
			for (int i = 0; i < _ship.get_ship().size(); i++)
				_ship.set_ship()[i].first -= 2;
			break;
		case 's':
			if (_ship.get_ship()[0].first == 20) {
				flag = false;
				break;
			}
			for (int i = 0; i < _ship.get_ship().size(); i++)
				_ship.set_ship()[i].first += 2;
			break;
		case 'a':
			if (_ship.get_ship()[0].second == 3) {
				flag = false;
				break;
			}
			for (int i = 0; i < _ship.get_ship().size(); i++)
				_ship.set_ship()[i].second -= 2;
			break;
		case 'd':
			if (_ship.get_ship()[_ship.get_ship().size() - 1].second == 21) {
				flag = false;
				break;
			}
			for (int i = 0; i < _ship.get_ship().size(); i++)
				_ship.set_ship()[i].second += 2;
			break;
		case'r':

			// turn ship.
			if (!turn) {
				turn = true;
				for (int i = 1; i < _ship.get_ship().size(); i++)
				{
					_ship.set_ship()[i].first = _ship.get_ship()[i - 1].first - 2;
					_ship.set_ship()[i].second = _ship.get_ship()[i - 1].second;
				}
				do {
					if (_ship.get_ship()[_ship.get_ship().size() - 1].first < 2)
						for (int i = 0; i < _ship.get_ship().size(); i++)
							_ship.set_ship()[i].first = _ship.get_ship()[i].first + 2;
					else
						break;
				} while (true);
			}
			else {
				turn = false;
				for (int i = 1; i < _ship.get_ship().size(); i++)
				{
					_ship.set_ship()[i].first = _ship.get_ship()[i - 1].first;
					_ship.set_ship()[i].second = _ship.get_ship()[i - 1].second + 2;
				}
				do {
					if (_ship.set_ship()[_ship.get_ship().size() - 1].second > 21)
						for (int i = 0; i < _ship.get_ship().size(); i++)
							_ship.set_ship()[i].second = _ship.get_ship()[i].second - 2;
					else
						break;
				} while (true);
			}
			break;
		case ' ':
			// checking if there are ships nearby.
			if (checking_space_for_ship(_ship)) {
				// puts the ship on the map.
				put_ship(_ship, turn);
				return;
			}
			flag = false;
			break;
		default:
			flag = false;
			break;
		}
	} while (true);
}

// random ship selection menu.
void Player::rand_map_filling(vector<int>& count_ships) noexcept
{
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
			break;
		}
	} while (true);
}

// ship selection menu.
void Player::map_filling() noexcept
{
	// count_all_ships.
	vector<int> count_ships{ 1,2,3,4 };

	int menu = 1;
	do {
		bool flag = false;
		drow_map(menu, count_ships);
		do {
			flag = false;
			switch (_getch()) {
			case 'w':
				if (menu > 1)
					menu--;
				else
					flag = true;
				break;
			case 's':
				if (menu < 7)
					menu++;
				else
					flag = true;
				break;
			case ' ':
				if (menu == 1 && count_ships[0] != 0) {
					count_ships[0]--;
					filling(ships4);
				}
				else if (menu == 2 && count_ships[1] != 0)
					filling(ships3[--count_ships[1]]);
				else if (menu == 3 && count_ships[2] != 0)
					filling(ships2[--count_ships[2]]);
				else if (menu == 4 && count_ships[3] != 0)
					filling(ships1[--count_ships[3]]);
				else if (menu == 5)
					rand_map_filling(count_ships);
				else if (menu == 6) {
					Player::Map::clear_map();
					for (int i = 0; i < count_ships.size(); i++)
						count_ships[i] = i + 1;
				}
				else if (menu == 7 && count_ships[0] + count_ships[1] + count_ships[2] + count_ships[3] == 0) {
					system("cls");
					return;
				}
				else
					flag = true;
				break;
			default:
				flag = true;
				break;
			}
		} while (flag);
		system("cls");
	} while (true);
}