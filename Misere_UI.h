#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"

class Misere_UI : public UI<char> {
public:
    Misere_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;

    ~Misere_UI() {}
};

#endif