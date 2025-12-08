#ifndef OBSTACLES_BOARD_H
#define OBSTACLES_BOARD_H

#include "BoardGame_Classes.h"
#include <cstdlib> 

using namespace std;

class Obstacles_Board : public Board<char> {
private:
    char blank = ' ';
    char obstacle = '#';
    void add_obstacle(); 

public:
    Obstacles_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override { return false; }

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;

    bool four_in_row(char sym);
};

#endif