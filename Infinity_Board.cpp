#include "Infinity_Board.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool InfinityBoard::check_win(char symbol) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

    return false;
}

InfinityBoard::InfinityBoard() : Board(3, 3) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = ' ';
        }
    }
}

bool InfinityBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Error: Coordinates out of bounds.\n";
        return false;
    }
    if (board[x][y] != ' ') {
        cout << "Error: Cell (" << x << ", " << y << ") is already occupied.\n";
        return false;
    }

    board[x][y] = symbol;
    n_moves++;

    move_history.push_back({ x, y });

    if (move_history.size() > MAX_MOVES_BEFORE_VANISH) {
        pair<int, int> oldest_move = move_history.front();
        move_history.erase(move_history.begin());

        int old_x = oldest_move.first;
        int old_y = oldest_move.second;

        board[old_x][old_y] = ' ';
        cout << "Rule Applied: Mark at (" << old_x << ", " << old_y << ") vanished.\n";
    }

    return true;
}

bool InfinityBoard::is_win(Player<char>* p) {
    return check_win(p->get_symbol());
}

bool InfinityBoard::is_lose(Player<char>* p) {
    return false;
}

bool InfinityBoard::is_draw(Player<char>* p) {
    bool is_full = true;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == ' ') {
                is_full = false;
                break;
            }
        }
        if (!is_full) break;
    }

    if (is_full && !check_win('X') && !check_win('O')) {
        return true;
    }

    if (n_moves >= 30 && !check_win('X') && !check_win('O')) {
        cout << "Game declared a draw after " << n_moves << " moves without a win.\n";
        return true;
    }

    return false;
}

bool InfinityBoard::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}