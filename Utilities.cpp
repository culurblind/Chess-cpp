#include "Utilities.h"


Piece* find_piece(int x, int y, vector<Piece*>& pieces)
{

	//cout << "finding piece at: " << x << ", " << y << "\n";

	for (Piece* piece : pieces) {
		//cout << "there is a piece at: " << (*piece).piece_tile.first << ", " << (*piece).piece_tile.second << "\n";
		if ((*piece).piece_tile.first == x && (*piece).piece_tile.second == y) {
			return piece;
		}
	}

	return nullptr;
}

Piece* is_in_check(int x, int y, int color, int turn, vector<Piece*>& pieces) {


    for (Piece* piece : pieces) {
        if (piece->color != color) {
            //cout << "color at is in check is " << color << "\n";
            //cout << "it's not the same color, its " << piece->color << "\n";
            for (pair<int, int> move : piece->get_Moves(pieces, turn)) {
                //cout << move.first << ", " << move.second << "\n";
                if (move.first == x && move.second == y) {
                    return piece;
                }
            }
        }
    }

    return nullptr;

}

Piece* would_be_check(int x, int y, int color, int turn, vector<Piece*>& pieces) {

    vector<Piece*> temp_pieces;

    if (find_piece(x, y, pieces)) {
        for (Piece* piece : pieces) {
            if (find_piece(piece->piece_tile.first, piece->piece_tile.second, pieces)) {
                if (piece != find_piece(x, y, pieces)) {
                    temp_pieces.push_back(piece);
                    //cout << "pushing back piece into tempPiece\n";
                }
            }   
        }

        //cout << "color at would check if " << color << "\n";
        return is_in_check(x, y, color, turn, temp_pieces);
    }

    else {
        //cout << "color at would check else is " << color << "\n";
        return is_in_check(x, y, color, turn, pieces);
    }

}

vector<pair<int, int>> get_checked_row(Piece* attacking_p, int king_x, int king_y) {

    vector <pair<int, int>> check_row;

    for (pair<int, int> a_moves : attacking_p->di_down_left) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->di_down_left;
        }
    }

    for (pair<int, int> a_moves : attacking_p->di_down_right) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->di_down_right;
        }
    }

    for (pair<int, int> a_moves : attacking_p->di_up_left) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->di_up_left;
        }
    }

    for (pair<int, int> a_moves : attacking_p->di_up_right) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->di_up_right;
        }
    }

    for (pair<int, int> a_moves : attacking_p->s_down) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->s_down;
        }
    }

    for (pair<int, int> a_moves : attacking_p->s_up) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->s_up;
        }
    }

    for (pair<int, int> a_moves : attacking_p->s_right) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->s_right;
        }
    }

    for (pair<int, int> a_moves : attacking_p->s_left) {
        if (king_x == a_moves.first && king_y == a_moves.second) {
            check_row = attacking_p->s_left;
        }
    }

    return check_row;
}


vector<pair<int, int>> get_checked_moves(Piece* piece, vector<Piece*> pieces, int turn) {


    vector <pair<int, int>> check_moves;
    vector <pair<int, int>> check_row;
    bool avail_move = true;

    int king_cantX = -1;
    int king_cantY = -1;
    int king_x;
    int king_y;
    int king_color;

    Piece* attacking_p;

    //gets the position and color of the king thats in check
    for (Piece* piece : pieces) {
        if (dynamic_cast<King*>(piece) && piece->color == turn) {
            king_x = piece->piece_tile.first;
            king_y = piece->piece_tile.second;
            king_color = piece->color;
        }
    }

    //cout << "king cords are , " << king_x << ", " << king_y << "\n";
    
    //finds the piece attacking the king 
    attacking_p = is_in_check(king_x, king_y, king_color, turn, pieces);

    //finds the isle the attacking piece is attacking the king on
    check_row = get_checked_row(attacking_p, king_x, king_y);

    //finds moves if the piece is a king
    if (dynamic_cast<King*>(piece)) {

        king_x = piece->piece_tile.first;
        king_y = piece->piece_tile.second;
        king_color = piece->color;

        //finds which tile the king cannot move to if its being attacked not 
        if (!dynamic_cast<Knight*>(attacking_p) && !dynamic_cast<Pawn*>(attacking_p)) {
            if (attacking_p->piece_tile.first - king_x > 0) {
                king_cantX = king_x - 1;
            }

            else if (attacking_p->piece_tile.first - king_x < 0) {
                king_cantX = king_x + 1;
            }

            else {
                king_cantX = king_x;
            }

            if (attacking_p->piece_tile.second - king_y > 0) {
                king_cantY = king_y - 1;
            }

            else if (attacking_p->piece_tile.second - king_y < 0) {
                king_cantY = king_y + 1;
            }

            else {
                king_cantY = king_y;
            }
        }

        for (pair<int, int> king_moves : piece->get_Moves(pieces, turn)) {
            for (Piece* other_piece : pieces) {
                if (abs(piece->piece_tile.first - king_moves.first) > 1) {
                    avail_move = false;
                }

                for (pair<int, int> piece_moves : other_piece->get_Moves(pieces, turn * -1)) {
                    if (other_piece->color != piece->color && king_moves.first == piece_moves.first && king_moves.second == piece_moves.second) {
                        avail_move = false;
                    }
                }
            }

            if (king_moves.first == king_cantX && king_moves.second == king_cantY) {
                avail_move = false;
            }

            if (avail_move) {
                check_moves.push_back(king_moves);
            }

            else {
                avail_move = true;
            }
        }

        return check_moves;
    }

    for (pair<int, int> moves : piece->get_Moves(pieces, turn)) {
        for (pair<int, int> a_moves : check_row) {
            if (moves.first == a_moves.first && moves.second == a_moves.second) {
                if (find_piece(moves.first, moves.second, pieces) && find_piece(moves.first, moves.second, pieces)->color == turn) {
                    continue;
                }

                else {
                    check_moves.push_back(moves);
                }
            }
        }

        if (moves.first == attacking_p->piece_tile.first && moves.second == attacking_p->piece_tile.second) {
            check_moves.push_back(moves);
        }
    }

    return check_moves;
}

bool is_pinned(Piece* piece, int turn, vector<Piece*> pieces) {

    int piece_x = piece->piece_tile.first;
    int piece_y = piece->piece_tile.second;
    int tile_diff_x;
    int tile_diff_y;
    Piece* attacking_p;

    if (is_in_check(piece_x, piece_y, piece->color, turn, pieces)) {
        attacking_p = is_in_check(piece_x, piece_y, piece->color, turn, pieces);
        if (!dynamic_cast<Knight*>(attacking_p) && !dynamic_cast<Pawn*>(attacking_p)) {
            if (attacking_p->piece_tile.first - piece_x > 0) {
                tile_diff_x = -1;
            }

            else if (attacking_p->piece_tile.first - piece_x < 0) {
                tile_diff_x = 1;
            }

            else {
                tile_diff_x = 0;
            }

            if (attacking_p->piece_tile.second - piece_y > 0) {
                tile_diff_y = -1;
            }

            else if (attacking_p->piece_tile.second - piece_y < 0) {
                tile_diff_y = 1;
            }

            else {
                tile_diff_y = 0;
            }

            while (piece_x < 8 && piece_x > 0 && piece_y < 8 && piece_y > 0) {
                if (find_piece(piece_x + tile_diff_x, piece_y + tile_diff_y, pieces)) {
                    if (find_piece(piece_x + tile_diff_x, piece_y + tile_diff_y, pieces)->color == piece->color && dynamic_cast<King*>(find_piece(piece_x + tile_diff_x, piece_y + tile_diff_y, pieces))) {
                        return true;
                    }

                    return false;
                }
            }
        }
    }

    return false;
}

vector<Piece*> setup(int wX, int wY) {

	vector<Piece*> Pieces{};

    //black pawns
    Pieces.push_back(new Pawn(0, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(1, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(2, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(3, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(4, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(5, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(6, 1, -1, 0, wX, wY));
    Pieces.push_back(new Pawn(7, 1, -1, 0, wX, wY));

    Pieces.push_back(new Queen(3, 0, -1, 0, wX, wY));
    Pieces.push_back(new King(4, 0, -1, 0, wX, wY));
    Pieces.push_back(new Rook(0, 0, -1, 0, wX, wY));
    Pieces.push_back(new Rook(7, 0, -1, 0, wX, wY));
    Pieces.push_back(new Knight(1, 0, -1, 0, wX, wY));
    Pieces.push_back(new Knight(6, 0, -1, 0, wX, wY));
    Pieces.push_back(new Bishop(2, 0, -1, 0, wX, wY));
    Pieces.push_back(new Bishop(5, 0, -1, 0, wX, wY));

    //white pawns
    Pieces.push_back(new Pawn(0, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(1, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(2, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(3, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(4, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(5, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(6, 6, 1, 0, wX, wY));
    Pieces.push_back(new Pawn(7, 6, 1, 0, wX, wY));

    Pieces.push_back(new Queen(3, 7, 1, 0, wX, wY));
    Pieces.push_back(new King(4, 7, 1, 0, wX, wY));
    Pieces.push_back(new Rook(0, 7, 1, 0, wX, wY));
    Pieces.push_back(new Rook(7, 7, 1, 0, wX, wY));
    Pieces.push_back(new Knight(6, 7, 1, 0, wX, wY));
    Pieces.push_back(new Knight(1, 7, 1, 0, wX, wY));
    Pieces.push_back(new Bishop(2, 7, 1, 0, wX, wY));
    Pieces.push_back(new Bishop(5, 7, 1, 0, wX, wY));

    return Pieces;


}