#ifndef PYRAMID_CLASSES_H
#define PYRAMID_CLASSES_H

#include "BoardGame_Classes.h"

// The board is stored in a 3x5 matrix for simplicity, 
// but we only allow moves in the "pyramid" cells.
class Pyramid_Board : public Board<char> {
public:
    Pyramid_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI(string msg = "Welcome to Pyramid Tic-Tac-Toe") : UI<char>(msg, 5) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    // Override display to show the pyramid shape nicely
    void display_pyramid(Board<char>& b);
};

#endif