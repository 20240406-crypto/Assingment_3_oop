
#include <iostream>
#include <cctype>
#include "Mini_TTT_Classes.h"

using namespace std;

Mini_TTT_Board::Mini_TTT_Board() : Board(3, 3) {
    for (auto& row : this->board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Mini_TTT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (this->board[x][y] == blank_symbol)) {

        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

char Mini_TTT_Board::check_winner() const {
    for (char sym : {'X', 'O'}) {
        auto all_equal = [&](char a, char b, char c) {
            return a == b && b == c && a == sym;
            };
        for (int i = 0; i < rows; ++i) {
            if (all_equal(this->board[i][0], this->board[i][1], this->board[i][2]) ||
                all_equal(this->board[0][i], this->board[1][i], this->board[2][i])) {
                return sym;
            }
        }
        if (all_equal(this->board[0][0], this->board[1][1], this->board[2][2]) ||
            all_equal(this->board[0][2], this->board[1][1], this->board[2][0])) {
            return sym;
        }
    }
    if (n_moves == 9) return 'D';
    return blank_symbol;
}

bool Mini_TTT_Board::is_win(Player<char>* player) {
    return check_winner() == player->get_symbol();
}
bool Mini_TTT_Board::is_draw(Player<char>* player) {
    return check_winner() == 'D';
}
bool Mini_TTT_Board::game_is_over(Player<char>* player) {
    return check_winner() != blank_symbol;
}
