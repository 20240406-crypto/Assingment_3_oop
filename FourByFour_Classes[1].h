#ifndef FOURBYFOUR_CLASSES_H
#define FOURBYFOUR_CLASSES_H

#include "BoardGame_Classes.h"
#include <cmath> 

class FourByFourMove : public Move<char> {
    int from_r, from_c;
public:
    FourByFourMove(int fr, int fc, int tr, int tc, char symbol)
        : Move<char>(tr, tc, symbol), from_r(fr), from_c(fc) {}

    int get_from_r() const { return from_r; }
    int get_from_c() const { return from_c; }
};

class FourByFourBoard : public Board<char> {
public:
    FourByFourBoard(); 
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override;

    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class FourByFourUI : public UI<char> {
public:
    FourByFourUI(string msg = "Welcome to 4x4 Tic-Tac-Toe") : UI<char>(msg, 4) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif