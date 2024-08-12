#include "Board.h"

using std::string;
using namespace std;
using namespace sf;


void Board::Draw(sf::RenderWindow& window, float wX, float wY) const {

    float square_X = (wX / 8);
    float square_Y = (wY / 8);

    sf::RectangleShape tile(sf::Vector2f(square_X, square_Y));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tile.setPosition(square_X * j, square_Y * i);
            tile.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color::Blue);
            window.draw(tile);
        }
    }
}

void Board::Draw_Moves(Piece* piece, int turn, bool is_checked, vector<Piece*> pieces, sf::RenderWindow& window, float wX, float wY) {

    double p_x = wX / 8;
    double p_y = wY / 8;

    float circle_rX = (wX / 8) / 2;
    float circle_rY = (wY / 8) / 2;


    sf::CircleShape current_select(1.f);
    current_select.setScale(circle_rX, circle_rY);
    current_select.setFillColor(Color::Cyan);
    sf::CircleShape can_move(1.f);
    can_move.setScale(circle_rX, circle_rY);

    can_move.setFillColor(Color::Green);

    if (is_pinned(piece, turn, pieces)) {

    }

    else if (!is_checked)
    {
        for (pair<int, int> move : piece->get_Moves(pieces, turn)) {
            if (!find_piece(move.first, move.second, pieces) || find_piece(move.first, move.second, pieces)->color != turn) {
                can_move.setPosition(p_x * move.first, p_y * move.second);
                window.draw(can_move);
            }
        }
    }

    else {
        for (pair<int, int> move : get_checked_moves(piece, pieces, turn)) {
            can_move.setPosition(p_x * move.first, p_y * move.second);
            window.draw(can_move);
        }
    }

    current_select.setPosition(p_x * (*piece).piece_tile.first, p_y * (*piece).piece_tile.second);
    window.draw(current_select);
}

void Board::move_Piece(Piece* &currentPiece, bool& is_checked, Vector2i mousePos, vector<Piece*>& pieces, int& turn, float wX, float wY) {

    vector<Piece*> Pieces_after_take{};
    int x = (mousePos.x / (wX / 8));
    int y = (mousePos.y / (wY / 8));

    //cout << "current click location: " << x << ", " << y << "\n";

    if (find_piece(x, y, pieces) && find_piece(x, y, pieces)->color == currentPiece->color) {
        if (find_piece(x, y, pieces) == currentPiece) {
            currentPiece = nullptr;
        }

        else {
            //cout << "clciked piece is the same color as the current piece\n";
            currentPiece = find_piece(x, y, pieces);
            return;
        }
    }

    else if (is_pinned(currentPiece, turn, pieces)) {
        return;
    }

    else {

        vector<pair<int, int>> moves;

        if (!is_checked) {
            moves = (*currentPiece).get_Moves(pieces, turn);
        }

        else {
            //cout << "getting its checked moves to move it\n";
            moves = get_checked_moves(currentPiece, pieces, turn);
        }


        for (pair<int, int> move : moves) {

            if (x == move.first && y == move.second) {
                //cout << "they clicked in an available move\n";
                //cout << "the click is one of the possible moves: moving now\n";
                if (find_piece(x, y, pieces) && find_piece(x, y, pieces)->color != turn) {
                    for (Piece* piece : pieces) {
                        if (piece != find_piece(x, y, pieces)) {
                            Pieces_after_take.push_back(piece);
                        }
                    }

                    pieces = Pieces_after_take;
                }

                //awwwn pawsawwwnt
                else if (dynamic_cast<Pawn*>(currentPiece)) {
                    if (find_piece(x, y + turn, pieces) && find_piece(x, y + turn, pieces)->color != turn) {
                        for (Piece* piece : pieces) {
                            if (piece != find_piece(x, y + turn, pieces)) {
                                Pieces_after_take.push_back(piece);
                            }
                        }

                        pieces = Pieces_after_take;
                    }
                }

                if (is_checked) {
                    is_checked = false;
                }

                else if (dynamic_cast<King*>(currentPiece) && abs(currentPiece->piece_tile.first - x) > 1) {
                    for (Piece* piece : pieces) {
                        if (dynamic_cast<Rook*>(piece) && piece->color == turn) {
                            if (currentPiece->piece_tile.first - x < 0 && piece->piece_tile.first > x) {
                                piece->move_piece(x - 1, y);
                            }

                            else if (currentPiece->piece_tile.first - x > 0 && piece->piece_tile.first < x) {
                                piece->move_piece(x + 1, y);
                            }

                        }
                    }
                }

                for (Piece* piece : pieces) {
                    piece->did_move = 0;
                }

                currentPiece->num_of_moves += 1;
                currentPiece->move_piece(x, y);
                currentPiece->did_move = 1;
                currentPiece = nullptr;
                turn *= -1;
                return;
            }
        }
    }

    
    currentPiece = nullptr;


}

Piece* Board::select_Piece(Piece* &currentPiece, Vector2i mousePos, vector<Piece*>& pieces, int turn, float wX, float wY) {

    int x = (mousePos.x / (wX / 8));
    int y = (mousePos.y / (wY / 8));

    //cout << "mouse tiles are: " << x << ", " << y << "\n";

    if (find_piece(x, y, pieces)) {
        //cout << "found piece\n";
        if (find_piece(x, y, pieces)->color == turn) {
            //cout << "piece color is the same as the turn\n";
            cout << "turn is: " << turn << " piece color type is: " << find_piece(x, y, pieces)->color << "\n";
            if (find_piece(x, y, pieces) != currentPiece) {
                //cout << "piece found is a new piece\n";
                return find_piece(x, y, pieces);
            }

            else {
                return nullptr;
            }
        }
        else {
            return nullptr;
        }
    }
    else {
        return nullptr;
    }
}