#pragma once
#include <Windows.h>
#include "Player.h"
#include "Bot.h"

class Sea_Battle : protected Player, protected Bot {
protected:
	// creating empty map.
	Map map;

	// creating a total number of ships for the playerand the bot.
	int ñount_player_ships, ñount_bot_ships;

	// showing the map during the player's turn.
	void drow(const pair<int, int>& _player_point, const pair<int, int>& _bot_point) noexcept;

	// showing the map while the bot is running.
	void drow(const pair<int, int>& _bot_point) noexcept;

	// function that determines whether the ship is destroyed.
	bool destroy(const Ship& _ship, vector<string>& _map) noexcept;

	// attack of all ships except the fourth.
	bool attack_ship(const pair<int, int>& _point, const vector<Ship>& _ship, vector<string>& _map, int& count) noexcept;

	// the attack of the fourth ship.
	bool attack_ship(const pair<int, int>& _point, const Ship& _ship, vector<string>& _map, int& count) noexcept;
	
	// bot shot test.
	_NODISCARD bool bot_shot(const pair<int, int>& _point) noexcept;
	
	// checking the player's shot.
	_NODISCARD bool player_shot(const pair<int, int>& _point) noexcept;
	
	void random_shot(pair<int, int>& _bot_point) noexcept;
	
	// after the first hit fires in a random direction.
	void bot_move(pair<int, int>& _bot_point) noexcept;

	// checking in which direction to shoot.
	bool bot_move_next(pair<int, int>& _bot_point) noexcept;

	// player attack logic.
	void player_attack(pair<int, int>& _player_point, const pair<int, int>& _bot_point) noexcept;
	
	// bot attack logic.
	void bot_attack(pair<int, int>& _bot_point, bool& _hit_ship) noexcept;
public:
	Sea_Battle() : ñount_player_ships{ 10 }, ñount_bot_ships{ 10 } {}
	void game() noexcept;
};