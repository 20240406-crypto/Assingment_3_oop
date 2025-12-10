#ifndef INFINITY_UI_H
#define INFINITY_UI_H

#include "BoardGame_Classes.h"

class InfinityUI : public UI<char> {
private:
    bool is_winning_move(Board<char>* b, char s, int x, int y);
    Move<char>* get_ai_move(Player<char>* p);

public:
    InfinityUI();
    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif
