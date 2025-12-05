#ifndef DIAMOND_UI_H
#define DIAMOND_UI_H

#include "Diamond_Board.h"
#include <cstdlib> 
#include <ctime>   
#include <string>

using namespace std;

class Diamond_UI : public UI<char> {
public:
    Diamond_UI() : UI("Starting Diamond Tic-Tac-Toe (Game 6). Win condition: a line of 3 AND a line of 4!", 3) {
        srand(time(0));
    }

    Move<char>* get_move(Player<char>* p) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif