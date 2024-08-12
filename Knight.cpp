#include "Knight.h"

using std::string;
using namespace std;
using namespace sf;

Knight::Knight(int x, int y, int set_color, int did_moved, float wX, float wY) : Piece(x, y, set_color, did_moved, wX, wY) {

	if (set_color == 1) {
		//cout << "Making pawn White\n";
		piece_tex.loadFromFile("chessTextures/WKnight.png");
	}

	else {
		piece_tex.loadFromFile("chessTextures/BKnight.png");
	}

	piece_sprite.setTexture(piece_tex);
	piece_sprite.setScale((wX / 8.0) / 800.0, (wY / 8.0) / 800.0);
}

void Knight::Draw(sf::RenderWindow& window) {

	window.draw(piece_sprite);

}

//returns tile space pair of places pawn can move
vector <pair<int, int>> Knight::get_Moves(vector<Piece*>& pieces, int turn) {

	int piece_x = piece_tile.first;
	int piece_y = piece_tile.second;
	vector <pair<int, int>> real_moves;

	if (piece_x + 2 < 8 && piece_y + 1 < 8) {
		//if (!find_piece(piece_x + 2, piece_y + 1, pieces) || find_piece(piece_x + 2, piece_y + 1, pieces)->color != color) {
			real_moves.push_back({ piece_x + 2, piece_y + 1 });
		//}
	}

	if (piece_x + 2 < 8 && piece_y - 1 > -1) {
		//if (!find_piece(piece_x + 2, piece_y - 1, pieces) || find_piece(piece_x + 2, piece_y - 1, pieces)->color != color) {
			real_moves.push_back({ piece_x + 2, piece_y - 1 });
		//}
	}

	if (piece_x - 2 > -1 && piece_y - 1 > -1) {
		//if (!find_piece(piece_x - 2, piece_y - 1, pieces) || find_piece(piece_x - 2, piece_y - 1, pieces)->color != color) {
			real_moves.push_back({ piece_x - 2, piece_y - 1 });
		//}
	}

	if (piece_x - 2 > -1 && piece_y + 1 < 8) {
		//if (!find_piece(piece_x - 2, piece_y + 1, pieces) || find_piece(piece_x - 2, piece_y + 1, pieces)->color != color) {
			real_moves.push_back({ piece_x - 2, piece_y + 1 });
		//}
	}

	if (piece_x - 1 > -1 && piece_y + 2 < 8) {
		//if (!find_piece(piece_x - 1, piece_y + 2, pieces) || find_piece(piece_x - 1, piece_y + 2, pieces)->color != color) {
			real_moves.push_back({ piece_x - 1, piece_y + 2 });
		//}
	}

	if (piece_x + 1 < 8 && piece_y + 2 < 8) {
		//if (!find_piece(piece_x + 1, piece_y + 2, pieces) || find_piece(piece_x + 1, piece_y + 2, pieces)->color != color) {
			real_moves.push_back({ piece_x + 1, piece_y + 2 });
		//}
	}

	if (piece_x + 1 < 8 && piece_y - 2 > -1) {
		//if (!find_piece(piece_x + 1, piece_y - 2, pieces) || find_piece(piece_x + 1, piece_y - 2, pieces)->color != color) {
			real_moves.push_back({ piece_x + 1, piece_y - 2 });
		//}
	}

	if (piece_x - 1 > -1 && piece_y - 2 > -1) {
		//if (!find_piece(piece_x - 1, piece_y - 2, pieces) || find_piece(piece_x - 1, piece_y - 2, pieces)->color != color) {
			real_moves.push_back({ piece_x - 1, piece_y - 2 });
		//}
	}

	return real_moves;

}