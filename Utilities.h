#pragma once

#include "Piece.h"
#include "Pawn.h"
#include "Queen.h"
#include "King.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <unordered_map>

using std::string;
using namespace std;
using namespace sf;


Piece* find_piece(int x, int y, vector<Piece*>& pieces);

Piece* is_in_check(int x, int y, int color, int turn, vector<Piece*>& pieces);

Piece* would_be_check(int x, int y, int color, int turn, vector<Piece*>& pieces);

vector<pair<int, int>> get_checked_row(Piece* attacking_p, int king_x, int king_y);

vector<pair<int, int>> get_checked_moves(Piece* piece, vector<Piece*> pieces, int turn);

bool is_pinned(Piece* piece, int turn, vector<Piece*> pieces);


vector<Piece*> setup(int wX, int wY);