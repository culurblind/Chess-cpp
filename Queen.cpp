#include "Queen.h"

using std::string;
using namespace std;
using namespace sf;

Queen::Queen(int x, int y, int set_color, int did_moved, float wX, float wY) : Piece(x, y, set_color, did_moved, wX, wY) {

	if (set_color == 1) {
		//cout << "Making pawn White\n";
		piece_tex.loadFromFile("chessTextures/WQueen.png");
	}

	else {
		piece_tex.loadFromFile("chessTextures/BQueen.png");
	}

	piece_sprite.setTexture(piece_tex);
	piece_sprite.setScale((wX / 8.0) / 800.0, (wY / 8.0) / 800.0);

}

void Queen::Draw(sf::RenderWindow& window) {

	window.draw(piece_sprite);

}

//returns tile space pair of places pawn can move
vector <pair<int, int>> Queen::get_Moves(vector<Piece*>& pieces, int turn) {

	di_down_left.clear();
	di_up_left.clear();
	di_down_right.clear();
	di_up_right.clear();

	s_up.clear();
	s_down.clear();
	s_right.clear();
	s_left.clear();

	int piece_x = piece_tile.first;
	int piece_y = piece_tile.second;

	vector <pair<int, int>> real_moves;

	//diag toward the bottom right
	while (piece_x < 7 && piece_y < 7) {
		//cout << "making diag downward right\n";
		if (!find_piece(piece_x + 1, piece_y + 1, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y + 1 });
			di_down_right.push_back({ piece_x + 1, piece_y + 1 });
		}

		else if (find_piece(piece_x + 1, piece_y + 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x + 1, piece_y + 1 });
			di_down_right.push_back({ piece_x + 1, piece_y + 1 });
			break;
		}
		
		else {
			break;
		}

		++piece_x;
		++piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//diag toward the top right
	while (piece_x < 7 && piece_y > 0) {
		//cout << "making diag top right\n";
		if (!find_piece(piece_x + 1, piece_y - 1, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y - 1 });
			di_up_right.push_back({ piece_x + 1, piece_y - 1 });
		}

		else if (find_piece(piece_x + 1, piece_y - 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x + 1, piece_y - 1 });
			di_up_right.push_back({ piece_x + 1, piece_y - 1 });
			break;
		}

		else {
			break;
		}

		++piece_x;
		--piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//diag toward the top left
	while (piece_x > 0 && piece_y > 0) {
		//cout << "making diag top left\n";
		if (!find_piece(piece_x - 1, piece_y - 1, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y - 1 });
			di_up_left.push_back({ piece_x - 1, piece_y - 1 });
		}

		else if (find_piece(piece_x - 1, piece_y - 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x - 1, piece_y - 1 });
			di_up_left.push_back({ piece_x - 1, piece_y - 1 });
			break;
		}

		else {
			break;
		}

		--piece_x;
		--piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//diag toward the bottom left
	while (piece_x > 0 && piece_y < 7) {
		//cout << "making diag bottom left\n";
		if (!find_piece(piece_x - 1, piece_y + 1, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y + 1 });
			di_down_left.push_back({ piece_x - 1, piece_y + 1 });
		}

		else if (find_piece(piece_x - 1, piece_y + 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x - 1, piece_y + 1 });
			di_down_left.push_back({ piece_x - 1, piece_y + 1 });
			break;
		}

		else {
			break;
		}

		--piece_x;
		++piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//straight down
	while (piece_y < 7) {
		//cout << "making straight down\n";
		if (!find_piece(piece_x, piece_y + 1, pieces)) {
			real_moves.push_back({ piece_x, piece_y + 1 });
			s_down.push_back({ piece_x, piece_y + 1 });
		}

		else if (find_piece(piece_x, piece_y + 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x, piece_y + 1 });
			s_down.push_back({ piece_x, piece_y + 1 });
			break;
		}

		else {
			break;
		}

		++piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//straight up
	while (piece_y > 0) {
		//cout << "making straight up\n";
		if (!find_piece(piece_x, piece_y - 1, pieces)) {
			real_moves.push_back({ piece_x, piece_y - 1 });
			s_up.push_back({ piece_x, piece_y - 1 });
		}

		else if (find_piece(piece_x, piece_y - 1, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x, piece_y - 1 });
			s_up.push_back({ piece_x, piece_y - 1 });
			break;
		}

		else {
			break;
		}

		--piece_y;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//straight left
	while (piece_x > 0) {
		//cout << "making straight left\n";
		if (!find_piece(piece_x - 1, piece_y, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y });
			s_left.push_back({ piece_x - 1, piece_y });
		}

		else if (find_piece(piece_x - 1, piece_y, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x - 1, piece_y });
			s_left.push_back({ piece_x - 1, piece_y });
			break;
		}

		else {
			break;
		}

		--piece_x;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	//straight right
	while (piece_x < 7) {
		//cout << "making straight right\n";
		if (!find_piece(piece_x + 1, piece_y, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y });
			s_right.push_back({ piece_x + 1, piece_y });
		}

		else if(find_piece(piece_x + 1, piece_y, pieces)/*->color != color*/) {
			real_moves.push_back({ piece_x + 1, piece_y });
			s_right.push_back({ piece_x + 1, piece_y });
			break;
		}

		else {
			break;
		}

		++piece_x;
	}

	piece_x = piece_tile.first;
	piece_y = piece_tile.second;

	return real_moves;

}