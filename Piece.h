#pragma once

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

class Piece {
public:


    vector<pair<int, int>> di_up_right;
    vector<pair<int, int>> di_up_left;
    vector<pair<int, int>> di_down_right;
    vector<pair<int, int>> di_down_left;

    vector<pair<int, int>> s_up;
    vector<pair<int, int>> s_down;
    vector<pair<int, int>> s_right;
    vector<pair<int, int>> s_left;

    Texture piece_tex;
    Sprite piece_sprite;

    pair<int, int> piece_tile;
    pair<int, int> origin;

    int did_move;
    int color;
    int num_of_moves;
    float windowX;
    float windowY;

    Piece(int x, int y, int set_color, int did_moved, float wX, float wY);

    void move_piece(int new_x, int new_y);

    virtual vector <pair<int, int>> get_Moves(vector<Piece*>& pieces, int turn);

    virtual void Draw(sf::RenderWindow& window);

    virtual bool is_check(vector<Piece*>& pieces, int turn);
};