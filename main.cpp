#include "Board.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <unordered_map>

using std::string;
using namespace std;
using namespace sf;

int main() {

    bool picking_window = false;

    float window_choiceX;
    float window_choiceY;

    float windowX = 600;
    float windowY= 600;

    if (picking_window) {
        cout << "tell me what pixel size you want for the width, or press enter for default\n";
        cin >> window_choiceX;

        if (cin.fail()) {
            windowX = 600.0;
            windowY = 600.0;
        }

        else {
            windowX = window_choiceX;
        }

        cout << "tell me what pixel size you want for the height, or press enter for default\n";
        cin >> window_choiceY;

        if (cin.fail()) {
            windowX = 600.0;
            windowY = 600.0;
        }

        else {
            windowY = window_choiceY;
        }
    }

    // Setup the SFML window
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Chess");
    window.setFramerateLimit(60);

    bool checked = false;
    bool mated = false;
    string winner = "";
    int turn = 1;
    Piece *currentPiece = nullptr;

    vector<Piece*> Pieces = setup(windowX, windowY);

    //win screen text
    sf::Font font;
    font.loadFromFile("Candal/Candal.ttf");
    sf::Text win_screen;
    win_screen.setString(winner);
    win_screen.setFont(font);
    win_screen.setPosition(windowX / 8.0, windowY /8.0);
    win_screen.setCharacterSize(((windowX + windowY) / 2) / 8);
    win_screen.setFillColor(sf::Color::Magenta);

    // Initialize board and pieces
    Board board;

    while (window.isOpen()) {

        window.clear();

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && winner == "") {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (currentPiece != nullptr) {
                    //cout << "trying to move piece\n";
                    board.move_Piece(currentPiece, checked, mousePos, Pieces, turn, windowX, windowY);
                }

                else {
                    //cout << "selecting piece\n";
                    currentPiece = board.select_Piece(currentPiece, mousePos, Pieces, turn, windowX, windowY);
                }

                //checking for a check after each move
                for (Piece* piece : Pieces) {
                    if (piece->color == turn && piece->is_check(Pieces, turn)) {
                        checked = true;
                        //cout << "In check\n";
                        break;
                    }
                }

                //if player has no moves -> checkmate
                if (checked) {
                    mated = true;
                    for (Piece* piece : Pieces) {
                        if (piece->color == turn) {
                            if (get_checked_moves(piece, Pieces, turn).size() != 0) {
                                //cout << "got piece moves in check for the king\n";
                                mated = false;
                            }
                        }

                        //cout << "piece location is " << piece->piece_tile.first << ", " << piece->piece_tile.second << "\n";
                    }
                }

                //setting the winner and the text
                if (mated) {
                    //cout << "checkmate!\n";
                    if (turn == -1) {
                        winner = "Winner is\n"
                            "   White";
                        win_screen.setString(winner);
                    }

                    else {
                        winner = "Winner is\n"
                            "   Black";
                        win_screen.setString(winner);
                    }
                }

            }
        }

        //draws chess board
        board.Draw(window, windowX, windowY);

        //draws the moves of a piece if theres one selected
        if (currentPiece != nullptr) {
            board.Draw_Moves(currentPiece, turn, checked, Pieces, window, windowX, windowY);
        }

        //draws all pieces
        for (size_t i = 0; i < Pieces.size(); ++i) {
            Pieces[i]->Draw(window);
        }

        //draws winscreen
        if (winner != "") {
            window.draw(win_screen);
        }

        window.display();
    }
    return 0;
}
