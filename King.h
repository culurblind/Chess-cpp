#pragma once

#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <cstdlib>

using std::string;
using namespace std;
using namespace sf;

class King : public Piece
{
public:

	King(int x, int y, int set_color, int did_moved, float wX, float wY);

	void Draw(sf::RenderWindow& window);

	vector <pair<int, int>> get_Moves(vector<Piece*>& pieces, int turn);

	bool is_check(vector<Piece*>& pieces, int turn);
};

