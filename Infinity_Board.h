#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H

#include "BoardGame_Classes.h"
#include <queue>
#include <map>

class InfinityBoard : public Board<char> {
private:
    map<char, queue<pair<int, int>>> moves; // ·ﬂ· ·«⁄» Queue Õ—ﬂ« Â

    bool check_three(char sym);

public:
    InfinityBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};

#endif
