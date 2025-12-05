#include "Diamond_Board.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

Diamond_Board::Diamond_Board() : Board(5, 5) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_in_diamond(i, j)) {
                board[i][j] = ' ';
            }
            else {
                board[i][j] = '#';
            }
        }
    }
}

bool Diamond_Board::is_in_diamond(int r, int c) const {
    return abs(r - 2) + abs(c - 2) <= 2;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r >= 0 && r < rows && c >= 0 && c < columns &&
        is_in_diamond(r, c) && board[r][c] == ' ') {
        board[r][c] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

bool Diamond_Board::is_win(Player<char>* p) {
    char symbol = (p) ? p->get_symbol() : (n_moves % 2 == 1 ? 'X' : 'O');

    bool found_3 = false;
    bool found_4 = false;

    int dr[] = { 0, 1, 1, 1 };
    int dc[] = { 1, 0, 1, -1 };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (board[r][c] != symbol) continue;

            for (int d = 0; d < 4; ++d) {
                int count = 0;

                for (int k = 0; k < 4; ++k) {
                    int nr = r + k * dr[d];
                    int nc = c + k * dc[d];

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < columns &&
                        is_in_diamond(nr, nc) && board[nr][nc] == symbol) {
                        count++;
                    }
                    else {
                        break;
                    }
                }

                if (count >= 3) found_3 = true;
                if (count >= 4) found_4 = true;
                if (found_3 && found_4) return true;
            }
        }
    }

    return found_3 && found_4;
}

bool Diamond_Board::is_lose(Player<char>*) {
    return false;
}

bool Diamond_Board::is_draw(Player<char>* p) {
    return n_moves == DIAMOND_SIZE && !is_win(p);
}

bool Diamond_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

vector<Move<char>> Diamond_Board::get_valid_moves(char symbol) const {
    vector<Move<char>> valid_moves;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (is_in_diamond(r, c) && board[r][c] == ' ') {
                valid_moves.push_back(Move<char>(r, c, symbol));
            }
        }
    }
    return valid_moves;
}