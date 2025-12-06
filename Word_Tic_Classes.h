

// Word_Tic.h

#ifndef WORD_TIC_CLASSES_H
#define WORD_TIC_CLASSES_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

// Board and UI for 5x5 Tic-Tac-Toe (count all 3-in-a-row windows)

class  wrdTic_Board : public Board<char> {
private:
    char blank_symbol = '.';

    static set<string> valid_words;
    static void initialize_dic(const string& filename);

public:
    wrdTic_Board();
    ~wrdTic_Board() override = default;

    bool update_board(Move<char>* move) override;

    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char>* player) override { return false; }

    bool is_draw(Player<char>* player) override;

    bool game_is_over(Player<char>* player) override;
};

class  wrdTic_UI : public UI<char> {
public:
    wrdTic_UI();
    ~wrdTic_UI() override = default;

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // get_move must handle case where game already over and then return a "no-op" move (mark==0)
    Move<char>* get_move(Player<char>* player) override;
};

#endif //  WORD_TIC_CLASSES_H


