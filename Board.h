#pragma once
#include "Pawn.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <unordered_map>

class Board {
public:
    // Define the size of the board
    static constexpr int size = 8;

    bool castling = false;

    // Draw the checkerboard on the SFML window
    void Draw(sf::RenderWindow& window, float wX, float wY) const;

    void Draw_Moves(Piece* piece, int turn, bool is_checked, vector<Piece*> pieces, sf::RenderWindow& window, float wX, float wY);

    void move_Piece(Piece* &currentPiece, bool& is_checked, Vector2i mousePos, vector<Piece*>& pieces, int& turn, float wX, float wY);

    Piece* select_Piece(Piece* &currentPiece, Vector2i mousePos, vector<Piece*>& Pieces, int turn, float wX, float wY);
};