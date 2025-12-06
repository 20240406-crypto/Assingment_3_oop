//5x5_Tic_Classes.h

#ifndef FIVEx5_TIC_CLASSES_H
#define FIVEx5_TIC_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>

#include <vector>

using namespace std;

// Board and UI for 5x5 Tic-Tac-Toe (count all 3-in-a-row windows)

class Tic5_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    Tic5_Board();

    // mark == 0 is used as a sentinel "no-op" move (used when game already ended)
    bool update_board(Move<char>* move) override;

    // Return true only if after 24 moves this player has strictly more triplets than opponent
    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override { return false; }

    // True when after 24 moves counts are equal
    bool is_draw(Player<char>* player) override;

    // Game is considered over when 24 moves have been made
    bool game_is_over(Player<char>* player) override;
};

class Tic5_UI : public UI<char> {
public:
    Tic5_UI();
    ~Tic5_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // get_move must handle case where game already over and then return a "no-op" move (mark==0)
    Move<char>* get_move(Player<char>* player) override;
};

#endif // THREE_TIC_CLASSES_H 

