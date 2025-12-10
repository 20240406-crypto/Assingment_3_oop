#include "Infinity_Board.h"

InfinityBoard::InfinityBoard() : Board<char>(3, 3) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

bool InfinityBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;
    if (board[x][y] != ' ')
        return false;

    // لو اللاعب عنده 3 حركات → امسح أقدم واحدة
    if (moves[s].size() == 3) {
        auto old = moves[s].front();
        moves[s].pop();
        board[old.first][old.second] = ' ';
    }

    board[x][y] = s;
    moves[s].push({ x,y });
    n_moves++;

    return true;
}

bool InfinityBoard::check_three(char sym) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym)
            return true;
        if (board[0][i] == sym && board[1][i] == sym && board[2][i] == sym)
            return true;
    }
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym)
        return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

bool InfinityBoard::is_win(Player<char>* p) {
    return check_three(p->get_symbol());
}

bool InfinityBoard::is_lose(Player<char>*) {
    return false; // لا يوجد خسارة مباشرة
}

bool InfinityBoard::is_draw(Player<char>*) {
    return false; // لا يوجد تعادل (لعبة لا نهائية)
}

bool InfinityBoard::game_is_over(Player<char>* p) {
    return is_win(p);
}
