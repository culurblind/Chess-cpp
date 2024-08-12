#include "Pawn.h"

using std::string;
using namespace std;
using namespace sf;

Pawn::Pawn(int x, int y, int set_color, int did_moved, float wX, float wY) : Piece(x, y, set_color, did_moved, wX, wY) {

	//cout << "Making pawn\n";

	origin.first = x;
	origin.second = y;

	if (set_color == 1) {
		//cout << "Making pawn White\n";
		piece_tex.loadFromFile("chessTextures/WPawn.png");
	}

	else {
		piece_tex.loadFromFile("chessTextures/BPawn.png");
	}
	
	piece_sprite.setTexture(piece_tex);
	piece_sprite.setScale((wX / 8.0) / 800.0, (wY / 8) / 800.0);

}

void Pawn::Draw(sf::RenderWindow& window) {

	window.draw(piece_sprite);

}

//returns tile space pair of places pawn can move
vector <pair<int, int>> Pawn::get_Moves(vector<Piece*>& pieces, int turn) {

	int piece_x = piece_tile.first;
	int piece_y = piece_tile.second;
	vector <pair<int, int>> avail_moves;
	vector <pair<int, int>> real_moves;

	avail_moves.push_back({ piece_x, piece_y + (-1 * color)});

	if (origin.first == piece_x && origin.second == piece_y) {
		avail_moves.push_back({ piece_x, piece_y + (-2 * color) });
	}

	for (size_t i = 0; i < avail_moves.size(); i++) {
		if (!find_piece(avail_moves[i].first, avail_moves[i].second, pieces)) {
			real_moves.push_back(avail_moves[i]);
		}
	}

	if (find_piece(piece_x + 1, piece_y - (1 * color), pieces)) {
		//if (find_piece(piece_x + 1, piece_y - (1 * color), pieces)->color != color) {

			real_moves.push_back({ piece_x + 1, piece_y - (1 * color) });

		//}
	}

	if (find_piece(piece_x - 1, piece_y - (1 * color), pieces)) {
		//if (find_piece(piece_x - 1, piece_y - (1 * color), pieces)->color != color) {

			real_moves.push_back({ piece_x - 1, piece_y - (1 * color) });
		//}
	}

	for (int i = -1; i < 2; i++) {
		if (i != 0) {
			if (find_piece(piece_x + i, piece_y, pieces) && find_piece(piece_x + i, piece_y, pieces)->color != color && dynamic_cast<Pawn*>(find_piece(piece_x + i, piece_y, pieces))) {
				if (!find_piece(piece_x + i, piece_y - 1, pieces) && find_piece(piece_x + i, piece_y, pieces)->did_move == 1) {
					if (find_piece(piece_x + i, piece_y, pieces)->num_of_moves == 1 && abs(find_piece(piece_x + i, piece_y, pieces)->origin.second - find_piece(piece_x + i, piece_y, pieces)->piece_tile.second) == 2) {
						real_moves.push_back({ find_piece(piece_x + i, piece_y, pieces)->piece_tile.first, find_piece(piece_x + i, piece_y, pieces)->piece_tile.second - 1 });
					}
				}
			}
		}
	}

	return real_moves;

}