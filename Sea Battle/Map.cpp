#include "Map.h"

void operator+=(Map& ob_1, vector<string>& ob_2) noexcept
{
	for (int i = 2; i < ob_1.map.size(); i++) {
		for (int j = 3; j < ob_1.map[i].size(); j++)
		{
			if ((ob_2[i][j] == '<' || ob_2[i][j] == 'V' || ob_2[i][j] == '\262') && ob_1.map[i][j] == ' ')
				ob_1.map[i][j] = ob_2[i][j];
		}
	}
}

Map operator+(Map ob_1, vector<string>& ob_2) noexcept
{
	for (int i = 2; i < ob_1.map.size(); i++) {
		for (int j = 3; j < ob_1.map[i].size(); j++)
		{
			if ((ob_2[i][j] == '<' || ob_2[i][j] == 'V' || ob_2[i][j] == '\262') && ob_1.map[i][j] == ' ')
				ob_1.map[i][j] = ob_2[i][j];
		}
	}
	return ob_1;
}

void Map::clear_map() noexcept
{
	for (int i = 2; i <= map.size() - 2; i += 2)
		for (int j = 3; j <= map[i].size() - 2; j += 2)
			if (map[i][j] != ' ')
				map[i][j] = ' ';
}