
#ifndef ULTIMATE_TTT_CLASSES_H
#define ULTIMATE_TTT_CLASSES_H

#include "BoardGame_Classes.h"
#include "Mini_TTT_Classes.h" 
#include <iostream>

using namespace std;

class Ultimate_TTT_Board : public Board<char> {
private:
    Mini_TTT_Board* sub_boards[3][3];
    char blank_symbol = '.';

public:
    static int last_main_r;
    static int last_main_c;

    Ultimate_TTT_Board();
    ~Ultimate_TTT_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    void display_nested_board(const UI<char>* ui) const;

    Mini_TTT_Board* get_sub_board(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < columns) return sub_boards[r][c];
        return nullptr;
    }
};

class Ultimate_TTT_UI : public UI<char> {
public:
    Ultimate_TTT_UI();
    ~Ultimate_TTT_UI() {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};
#endif 