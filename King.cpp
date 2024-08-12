#include "King.h"

King::King(int x, int y, int set_color, int did_moved, float wX, float wY) : Piece(x, y, set_color, did_moved, wX, wY) {

	if (set_color == 1) {
		//cout << "Making pawn White\n";
		piece_tex.loadFromFile("chessTextures/WKing.png");
	}

	else {
		piece_tex.loadFromFile("chessTextures/BKing.png");
	}

	piece_sprite.setTexture(piece_tex);
	piece_sprite.setScale((wX / 8.0) / 800.0, (wY / 8.0) / 800.0);

}

void King::Draw(sf::RenderWindow& window) {

	window.draw(piece_sprite);

}

//returns tile space pair of places pawn can move
vector <pair<int, int>> King::get_Moves(vector<Piece*>& pieces, int turn) {

	int piece_x = piece_tile.first;
	int piece_y = piece_tile.second;
	vector <pair<int, int>> real_moves;
	Piece* king_piece;

	if (turn == color) {
		if (piece_y - 1 > -1 && (!find_piece(piece_x, piece_y - 1, pieces) || find_piece(piece_x, piece_y - 1, pieces)->color != color) && !would_be_check(piece_x, piece_y - 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x, piece_y - 1 });
		}

		if (piece_x - 1 > -1 && piece_y - 1 > -1 && (!find_piece(piece_x - 1, piece_y - 1, pieces) || find_piece(piece_x - 1, piece_y - 1, pieces)->color != color) && !would_be_check(piece_x - 1, piece_y - 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y - 1 });
		}

		if (piece_x + 1 < 8 && piece_y - 1 > -1 && (!find_piece(piece_x + 1, piece_y - 1, pieces) || find_piece(piece_x + 1, piece_y - 1, pieces)->color != color) && !would_be_check(piece_x + 1, piece_y - 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y - 1 });
		}

		if (piece_x + 1 < 8 && piece_y + 1 < 8 && (!find_piece(piece_x + 1, piece_y + 1, pieces) || find_piece(piece_x + 1, piece_y + 1, pieces)->color != color) && !would_be_check(piece_x + 1, piece_y + 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y + 1 });
		}

		if (piece_x - 1 > -1 && piece_y + 1 < 8 && (!find_piece(piece_x - 1, piece_y + 1, pieces) || find_piece(piece_x - 1, piece_y + 1, pieces)->color != color) && !would_be_check(piece_x - 1, piece_y + 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y + 1 });
		}

		if (piece_y + 1 < 8 && (!find_piece(piece_x, piece_y + 1, pieces) || find_piece(piece_x, piece_y + 1, pieces)->color != color) && !would_be_check(piece_x, piece_y + 1, color, turn, pieces)) {
			real_moves.push_back({ piece_x, piece_y + 1 });
		}

		if (piece_x + 1 < 8 && (!find_piece(piece_x + 1, piece_y, pieces) || find_piece(piece_x + 1, piece_y, pieces)->color != color) && !would_be_check(piece_x + 1, piece_y, color, turn, pieces)) {
			real_moves.push_back({ piece_x + 1, piece_y });
		}

		if (piece_x - 1 > -1 && (!find_piece(piece_x - 1, piece_y, pieces) || find_piece(piece_x - 1, piece_y, pieces)->color != color) && !would_be_check(piece_x - 1, piece_y, color, turn, pieces)) {
			real_moves.push_back({ piece_x - 1, piece_y });
		}

		if (num_of_moves == 0) {
			for (Piece* piece : pieces) {
				if (dynamic_cast<Rook*>(piece) && piece->color == this->color && piece->num_of_moves == 0) {
					if (piece->piece_tile.first > 4) {
						if (!find_piece(piece_x + 1, piece_y, pieces) && !would_be_check(piece_x + 1, piece_y, color, turn, pieces)) {
							if (!find_piece(piece_x + 2, piece_y, pieces) && !would_be_check(piece_x + 2, piece_y, color, turn, pieces)) {
								real_moves.push_back({ piece_x + 2, piece_y });
							}
						}
					}

					if (piece->piece_tile.first < 4) {
						if (!find_piece(piece_x - 1, piece_y, pieces) && !would_be_check(piece_x - 1, piece_y, color, turn, pieces)) {
							if (!find_piece(piece_x - 2, piece_y, pieces) && !would_be_check(piece_x - 2, piece_y, color, turn, pieces)) {
								if (!find_piece(piece_x - 3, piece_y, pieces) && !would_be_check(piece_x - 3, piece_y, color, turn, pieces)) {
									real_moves.push_back({ piece_x - 2, piece_y });
								}
							}
						}
					}
				}
			}
		}
	}

	else {
		if (piece_y - 1 > -1 && (!find_piece(piece_x, piece_y - 1, pieces) || find_piece(piece_x, piece_y - 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x, piece_y - 1 });
		}

		if (piece_x - 1 > -1 && piece_y - 1 > -1 && (!find_piece(piece_x - 1, piece_y - 1, pieces) || find_piece(piece_x - 1, piece_y - 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x - 1, piece_y - 1 });
		}

		if (piece_x + 1 < 8 && piece_y - 1 > -1 && (!find_piece(piece_x + 1, piece_y - 1, pieces) || find_piece(piece_x + 1, piece_y - 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x + 1, piece_y - 1 });
		}

		if (piece_x + 1 < 8 && piece_y + 1 < 8 && (!find_piece(piece_x + 1, piece_y + 1, pieces) || find_piece(piece_x + 1, piece_y + 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x + 1, piece_y + 1 });
		}

		if (piece_x - 1 > -1 && piece_y + 1 < 8 && (!find_piece(piece_x - 1, piece_y + 1, pieces) || find_piece(piece_x - 1, piece_y + 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x - 1, piece_y + 1 });
		}

		if (piece_y + 1 < 8 && (!find_piece(piece_x, piece_y + 1, pieces) || find_piece(piece_x, piece_y + 1, pieces)->color != color)) {
			real_moves.push_back({ piece_x, piece_y + 1 });
		}

		if (piece_x + 1 < 8 && (!find_piece(piece_x + 1, piece_y, pieces) || find_piece(piece_x + 1, piece_y, pieces)->color != color)) {
			real_moves.push_back({ piece_x + 1, piece_y });
		}

		if (piece_x - 1 > -1 && (!find_piece(piece_x - 1, piece_y, pieces) || find_piece(piece_x - 1, piece_y, pieces)->color != color)) {
			real_moves.push_back({ piece_x - 1, piece_y });
		}
	}

	return real_moves;

}

bool King::is_check(vector<Piece*>& pieces, int turn) {

	int piece_x = piece_tile.first;
	int piece_y = piece_tile.second;

	//cout << "seeing if king is in check\n";
	if (is_in_check(piece_x, piece_y, color, turn, pieces)) {
		//cout << "king is in check wow\n";
		return true;
	}
}