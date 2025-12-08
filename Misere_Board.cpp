#include "Misere_Board.h"
#include <iostream>
#include <cctype>



Misere_Board::Misere_Board() : Board(3, 3) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '.';
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if ((x < 0 || x > 2 || y < 0 || y > 2) || (board[x][y] != '.'))
        return false;

    board[x][y] = toupper(sym);
    n_moves++;
    return true;
}

bool Misere_Board::is_win(Player<char>* player) {
    return false;
}

bool Misere_Board::is_lose(Player<char>* player) {
    char sym = toupper(player->get_symbol());

    for (int i = 0; i < 3; i++)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym)
            return true;

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

bool Misere_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && !is_lose(player);
}

bool Misere_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_draw(player);
}