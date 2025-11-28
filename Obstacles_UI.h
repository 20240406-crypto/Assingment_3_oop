#ifndef OBSTACLES_UI_H
#define OBSTACLES_UI_H

#include "BoardGame_Classes.h"

class Obstacles_UI : public UI<char> {
public:
    Obstacles_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    Move<char>* get_move(Player<char>* player) override;

    ~Obstacles_UI() {}
};

#endif