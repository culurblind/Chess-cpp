#include "Piece.h"

using std::string;
using namespace std;
using namespace sf;

Piece::Piece(int x, int y, int set_color, int did_moved, float wX, float wY) {

    did_move = did_moved;
    
    windowX = wX;
    windowY = wY;
    piece_tile.first = x;
    piece_tile.second = y;
    color = set_color;
    num_of_moves = 0;

    piece_sprite.setPosition(piece_tile.first * (windowX / 8.0), (piece_tile.second * (windowY / 8.0)));
    //piece_sprite.setScale((windowX / 8) / 800, (windowY / 8) / 800);

}

void Piece::move_piece(int new_x, int new_y) {

    piece_tile.first = new_x;
    piece_tile.second = new_y;
    piece_sprite.setPosition(piece_tile.first * (windowX / 8.0), (piece_tile.second * (windowY / 8.0)));

}

vector <pair<int, int>> Piece::get_Moves(vector<Piece*>& pieces, int turn) {

    //cout << "getting piece moves\n";
    vector <pair<int, int>> emptystuff;
    return emptystuff;

}

void Piece::Draw(sf::RenderWindow& window) {
    //cout << "drawing in piece cpp\n";
}

bool Piece::is_check(vector<Piece*>& pieces, int turn) {
    //cout << "checking check in piece class\n";
    return false;
}
