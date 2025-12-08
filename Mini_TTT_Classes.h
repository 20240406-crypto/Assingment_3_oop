

#ifndef MINI_TTT_CLASSES_H
#define MINI_TTT_CLASSES_H

#include <iostream>
#include <string>
#include "BoardGame_Classes.h"
using namespace std;

class Mini_TTT_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Mini_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    char check_winner() const;
};

#endif 