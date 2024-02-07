#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;

class Map {
protected:
	vector<string> map{
		{"   A B C D E F G H I J"},
		{"  \311\315\321\315\321\315\321\315\321\315\321\315\321\315\321\315\321\315\321\315\273"},
		{" 1\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 2\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 3\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 4\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 5\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 6\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 7\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 8\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{" 9\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \307\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\305\304\266"},
		{"10\272 \263 \263 \263 \263 \263 \263 \263 \263 \263 \272"},
		{"  \310\315\317\315\317\315\317\315\317\315\317\315\317\315\317\315\317\315\317\315\274"}
	};
public:
	Map() = default;
	const vector<string> get_map() noexcept {
		return map;
	}
	const vector<string> get_map() const noexcept {
		return map;
	}
	vector<string>& set_map() noexcept {
		return map;
	}

	// connects the maps.
	friend void operator += (Map& ob_1, vector<string>& ob_2) noexcept;

	// connects the maps.
	friend Map operator + (Map ob_1, vector<string>& ob_2) noexcept;

	// clear the map.
	void clear_map() noexcept;
};