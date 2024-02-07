#include "Sea_Battle.h"

// showing the map while the bot is running.
void Sea_Battle::drow(const pair<int, int>& _player_point, const pair<int, int>& _bot_point) noexcept
{
	int middle = Player::map.size() / 2;
	for (int i = 0; i < Player::map.size(); i++) {
		for (int j = 0; j < Player::map[i].size(); j++) {
			if (_bot_point.first == i && _bot_point.second == j)
				cout << "\033[47;5m" << Player::map[i][j] << "\033[m";
			else if (Player::map[i][j] == '<' || Player::map[i][j] == 'V' || Player::map[i][j] == '\262')
				cout << "\033[36;5m" << Player::map[i][j] << "\033[m";
			else if (Player::map[i][j] == 'X')
				cout << "\033[31;5m" << Player::map[i][j] << "\033[m";
			else
				cout << Player::map[i][j];
		}
		if (i == middle)
			cout << "    \033[36;5m-->\033[m\t";
		else
			cout << "\t\t";
		for (int j = 0; j <= map.get_map().size(); j++) {
			if (_player_point.first == i && _player_point.second == j)
				cout << "\033[47;5m" << map.get_map()[i][j] << "\033[m";
			else if (map.get_map()[i][j] == '<' || map.get_map()[i][j] == 'V' || map.get_map()[i][j] == '\262')
				cout << "\033[36;5m" << map.get_map()[i][j] << "\033[m";
			else if (map.get_map()[i][j] == 'X')
				cout << "\033[31;5m" << map.get_map()[i][j] << "\033[m";
			else
				cout << map.get_map()[i][j];
		}
		cout << endl;
	}
}

// showing the map during the player's turn.
void Sea_Battle::drow(const pair<int, int>& _bot_point) noexcept
{
	int middle = Player::map.size() / 2;
	for (int i = 0; i < Player::map.size(); i++) {
		for (int j = 0; j < Player::map[i].size(); j++) {
			if (_bot_point.first == i && _bot_point.second == j)
				cout << "\033[47;5m" << Player::map[i][j] << "\033[m";
			else if (Player::map[i][j] == '<' || Player::map[i][j] == 'V' || Player::map[i][j] == '\262')
				cout << "\033[36;5m" << Player::map[i][j] << "\033[m";
			else if (Player::map[i][j] == 'X')
				cout << "\033[31;5m" << Player::map[i][j] << "\033[m";
			else
				cout << Player::map[i][j];
		}
		if (i == middle)
			cout << "    \033[31;5m<--\033[m\t";
		else
			cout << "\t\t";
		for (int j = 0; j <= map.get_map().size(); j++) {
			if (map.get_map()[i][j] == '<' || map.get_map()[i][j] == 'V' || map.get_map()[i][j] == '\262')
				cout << "\033[36;5m" << map.get_map()[i][j] << "\033[m";
			else if (map.get_map()[i][j] == 'X')
				cout << "\033[31;5m" << map.get_map()[i][j] << "\033[m";
			else
				cout << map.get_map()[i][j];
		}
		cout << endl;
	}
}

// function that determines whether the ship is destroyed.
bool Sea_Battle::destroy(const Ship& _ship, vector<string>& _map) noexcept
{
	for (int i = 0; i < _ship.get_ship().size(); i++) {
		if (_map[_ship.get_ship()[i].first][_ship.get_ship()[i].second] != 'X')
			return false;
	}

	// markings around the ship.
	for (int i = 0; i < _ship.get_ship().size(); i++) {
		for (int j = -2; j < 4; j += 4) {
			if (_ship.get_ship()[i].first + j <= 20) {
				if (_map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second] == ' ')
					_map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second] = '#';
				if (_ship.get_ship()[i].first + j >= 2)
					if (_map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second + j] == ' ')
						_map[_ship.get_ship()[i].first + j][_ship.get_ship()[i].second + j] = '#';
			}
			if (_map[_ship.get_ship()[i].first][_ship.get_ship()[i].second + j] == ' ')
				_map[_ship.get_ship()[i].first][_ship.get_ship()[i].second + j] = '#';
			if (_ship.get_ship()[i].first - j <= 20 && _ship.get_ship()[i].second + j <= 21)
				if (_map[_ship.get_ship()[i].first - j][_ship.get_ship()[i].second + j] == ' ')
					_map[_ship.get_ship()[i].first - j][_ship.get_ship()[i].second + j] = '#';
		}
	}
	return true;
}

// attack of all ships except the fourth.
bool Sea_Battle::attack_ship(const pair<int, int>& _point, const vector<Ship>& _ship, vector<string>& _map, int& count) noexcept
{
	for (int i = 0; i < _ship.size(); i++)
	{
		for (int j = 0; j < _ship[i].get_ship().size(); j++)
		{
			if (_point.first == _ship[i].get_ship()[j].first && _point.second == _ship[i].get_ship()[j].second) {
				_map[_point.first][_point.second] = 'X';

				// function that determines whether the ship is destroyed.
				if (destroy(_ship[i], _map))
					count--;
				return true;
			}
		}
	}
	return false;
}

// the attack of the fourth ship.
bool Sea_Battle::attack_ship(const pair<int, int>& _point, const Ship& _ship, vector<string>& _map, int& count) noexcept
{
	{
		for (int i = 0; i < _ship.get_ship().size(); i++)
		{
			if (_point.first == _ship.get_ship()[i].first && _point.second == _ship.get_ship()[i].second) {
				_map[_point.first][_point.second] = 'X';
				if (destroy(_ship, _map))
					count--;
				return true;
			}
		}
		return false;
	}
}

// bot shot test.
_NODISCARD bool Sea_Battle::bot_shot(const pair<int, int>& _point) noexcept
{
	if (attack_ship(_point, Player::ships1, Player::set_map(), ñount_player_ships))	return true;
	if (attack_ship(_point, Player::ships2, Player::set_map(), ñount_player_ships))	return true;
	if (attack_ship(_point, Player::ships3, Player::set_map(), ñount_player_ships))	return true;
	if (attack_ship(_point, Player::ships4, Player::set_map(), ñount_player_ships))	return true;
	Player::map[_point.first][_point.second] = '#';
	return false;
}

// checking the player's shot.
_NODISCARD bool Sea_Battle::player_shot(const pair<int, int>& _point) noexcept
{
	if (attack_ship(_point, Bot::ships1, map.set_map(), ñount_bot_ships))	return true;
	if (attack_ship(_point, Bot::ships2, map.set_map(), ñount_bot_ships))	return true;
	if (attack_ship(_point, Bot::ships3, map.set_map(), ñount_bot_ships))	return true;
	if (attack_ship(_point, Bot::ships4, map.set_map(), ñount_bot_ships))	return true;
	map.set_map()[_point.first][_point.second] = '#';
	return false;
}

void Sea_Battle::random_shot(pair<int, int>& _bot_point) noexcept
{
	bool flag;
	do {
		flag = false;
		_bot_point.first = rand() % 19 + 2;
		if (_bot_point.first % 2 != 0) {
			flag = true;
			continue;
		}
		_bot_point.second = rand() % 19 + 3;
		if (_bot_point.second % 2 == 0) {
			flag = true;
			continue;
		}
		if (Player::map[_bot_point.first][_bot_point.second] == '#' || Player::map[_bot_point.first][_bot_point.second] == 'X') {
			flag = true;
			continue;
		}
	} while (flag);
}

// after the first hit fires in a random direction.
void Sea_Battle::bot_move(pair<int, int>& _bot_point) noexcept
{
	bool flag;
	do {
		flag = false;
		int move = rand() % 4;
		switch (move)
		{
		case 0:
			if (_bot_point.first - 2 >= 2) {
				if (Player::map[_bot_point.first - 2][_bot_point.second] != '#') {
					_bot_point.first -= 2;
				}
				else
					flag = true;
			}
			else
				flag = true;
			break;
		case 1:
			if (_bot_point.first + 2 <= 20) {
				if (Player::map[_bot_point.first + 2][_bot_point.second] != '#') {
					_bot_point.first += 2;
				}
				else
					flag = true;
			}
			else
				flag = true;
			break;
		case 2:
			if (_bot_point.second - 2 >= 3) {
				if (Player::map[_bot_point.first][_bot_point.second - 2] != '#') {
					_bot_point.second -= 2;
				}
				else
					flag = true;
			}
			else
				flag = true;
			break;
		case 3:
			if (_bot_point.second + 2 <= 21) {
				if (Player::map[_bot_point.first][_bot_point.second + 2] != '#') {
					_bot_point.second += 2;
				}
				else
					flag = true;
			}
			else
				flag = true;
			break;
		default:
			break;
		}
	} while (flag);
}

// checking in which direction to shoot.
bool Sea_Battle::bot_move_next(pair<int, int>& _bot_point) noexcept
{
	bool rep = true;
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			if (_bot_point.first > 2) {
				while (Player::map[_bot_point.first - 2][_bot_point.second] == 'X') {
					_bot_point.first -= 2;
					if (_bot_point.first > 2)
					{
						if (Player::map[_bot_point.first - 2][_bot_point.second] == 'X')
							continue;
						else if (Player::map[_bot_point.first - 2][_bot_point.second] == '#')
							break;
						else {
							_bot_point.first -= 2;
							return true;
						}
					}
					else
						break;
				}
			}
			break;
		case 1:
			if (_bot_point.first < 20) {
				while (Player::map[_bot_point.first + 2][_bot_point.second] == 'X') {
					_bot_point.first += 2;
					if (_bot_point.first < 20)
					{
						if (Player::map[_bot_point.first + 2][_bot_point.second] == 'X')
							continue;
						else if (Player::map[_bot_point.first + 2][_bot_point.second] == '#' && rep) {
							rep = false;
							i = -1;
							break;
						}
						else {
							_bot_point.first += 2;
							return true;
						}
					}
					else {
						rep = false;
						i = -1;
						break;
					}
				}
			}
			break;
		case 2:
			if (_bot_point.second > 3) {
				while (Player::map[_bot_point.first][_bot_point.second - 2] == 'X') {
					_bot_point.second -= 2;
					if (_bot_point.second > 3)
					{
						if (Player::map[_bot_point.first][_bot_point.second - 2] == 'X')
							continue;
						else if (Player::map[_bot_point.first][_bot_point.second - 2] == '#')
							break;
						else {
							_bot_point.second -= 2;
							return true;
						}
					}
					else
						break;
				}
			}
			break;
		case 3:
			if (_bot_point.second < 21) {
				while (Player::map[_bot_point.first][_bot_point.second + 2] == 'X') {
					_bot_point.second += 2;
					if (_bot_point.second < 21)
					{
						if (Player::map[_bot_point.first][_bot_point.second + 2] == 'X')
							continue;
						else if (Player::map[_bot_point.first][_bot_point.second + 2] == '#' && rep) {
							rep = false;
							i = 1;
							break;
						}
						else {
							_bot_point.second += 2;
							return true;
						}
					}
					else {
						rep = false;
						i = 1;
						break;
					}
				}
			}
			break;
		}
	}
	return false;
}

// bot attack logic.
void Sea_Battle::bot_attack(pair<int, int>& _bot_point, bool& _hit_ship) noexcept
{
	srand(time(NULL));
	bool hit = true;
	do {
		system("cls");
		drow(_bot_point);
		Sleep(1000);
		int count_ships = ñount_player_ships;
		if (hit) {
			if (_hit_ship) {
				// checking in which direction to shoot.
				if (!bot_move_next(_bot_point)) {
					// after the first hit fires in a random direction.
					bot_move(_bot_point);
				}
			}
			else
				random_shot(_bot_point);
		}
		if (hit = bot_shot(_bot_point))
			_hit_ship = true;
		if (count_ships != ñount_player_ships) {
			_hit_ship = false;
			count_ships = ñount_player_ships;
		}
	} while (hit && ñount_player_ships);
	system("cls");
}

// player attack logic.
void Sea_Battle::player_attack(pair<int, int>& _player_point, const pair<int, int>& _bot_point) noexcept
{
	bool hit = true;
	do {
		bool flag;
		drow(_player_point, _bot_point);
		do {
			flag = false;

			// move.
			switch (_getch()) {
			case 'w':
				if (_player_point.first != 2)
					_player_point.first -= 2;
				else
					_player_point.first = 20;
				break;
			case 's':
				if (_player_point.first != 20)
					_player_point.first += 2;
				else
					_player_point.first = 2;
				break;
			case 'a':
				if (_player_point.second != 3)
					_player_point.second -= 2;
				else
					_player_point.second = 21;
				break;
			case 'd':
				if (_player_point.second != 21)
					_player_point.second += 2;
				else
					_player_point.second = 3;
				break;
			case ' ':
				if (map.get_map()[_player_point.first][_player_point.second] == ' ')
					hit = player_shot(_player_point);
				else
					flag = true;
				break;
			default:
				flag = true;
				break;
			}
		} while (flag);
		system("cls");
	} while (hit && ñount_bot_ships);
}

void Sea_Battle::game() noexcept
{
	Player::map_filling();
	Bot::map_filling();
	pair<int, int> point_player({ 2,3 });
	pair<int, int> point_bot({ -1,-1 });
	bool hit_ship = false;
	do {
		player_attack(point_player, point_bot);
		if (!ñount_bot_ships || !ñount_player_ships)
			break;
		bot_attack(point_bot, hit_ship);
	} while (ñount_bot_ships && ñount_player_ships);

	// connects the maps.
	map += Bot::map;

	drow({ -1,-1 });
	if (!ñount_bot_ships)
		cout << "\t\t\t\033[36;5mYou Win\033[m";
	else
		cout << "\t\t\t\033[31;5mYou lose\033[m";
	cout << endl << "\033[35;5mPress space\033[m";
	while (_getch() != ' ') {}
}