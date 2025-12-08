#include "FourByFour_Classes.h"
#include <iostream>

using namespace std;

// --- FourByFourBoard Implementation ---


FourByFourBoard::FourByFourBoard() : Board<char>(4, 4) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            board[i][j] = '.';

    for (int j = 0; j < 4; ++j) {
        board[0][j] = 'X'; 
        board[3][j] = 'O'; 
    }
}

bool FourByFourBoard::update_board(Move<char>* move) {
    FourByFourMove* m = static_cast<FourByFourMove*>(move);

    int fr = m->get_from_r();
    int fc = m->get_from_c();
    int tr = m->get_x();
    int tc = m->get_y(); 
    char symbol = m->get_symbol();

    if (fr < 0 || fr >= 4 || fc < 0 || fc >= 4 || tr < 0 || tr >= 4 || tc < 0 || tc >= 4) {
        cout << "Error: Coordinates out of range!\n";
        return false;
    }

    if (board[fr][fc] != symbol) {
        cout << "Error: You can only move your own pieces (" << symbol << ")!\n";
        return false;
    }

    if (board[tr][tc] != '.') {
        cout << "Error: Destination is not empty!\n";
        return false;
    }
    
    int dist = abs(tr - fr) + abs(tc - fc);
    if (dist != 1) {
        cout << "Error: Invalid move! You can only move to an ADJACENT square (1 step).\n";
        return false;
    }

    board[tr][tc] = symbol;
    board[fr][fc] = '.';   
    n_moves++;

    return true;
}

bool FourByFourBoard::is_win(Player<char>* player) {
    char s = player->get_symbol();

    for (int i = 0; i < 4; i++) {

        if (s == 'X' && i == 0) continue;
        if (s == 'O' && i == 3) continue;

        if ((board[i][0] == s && board[i][1] == s && board[i][2] == s) ||
            (board[i][1] == s && board[i][2] == s && board[i][3] == s)) return true;
    }

    for (int i = 0; i < 4; i++) {
        if ((board[0][i] == s && board[1][i] == s && board[2][i] == s) ||
            (board[1][i] == s && board[2][i] == s && board[3][i] == s)) return true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (board[i][j] == s && board[i + 1][j + 1] == s && board[i + 2][j + 2] == s) return true;
        }
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 2; j <= 3; j++) {
            if (board[i][j] == s && board[i + 1][j - 1] == s && board[i + 2][j - 2] == s) return true;
        }
    }

    return false;
}

bool FourByFourBoard::is_lose(Player<char>* player) {
    return false;
}

bool FourByFourBoard::is_draw(Player<char>* player) {
    return (n_moves > 100);
}

bool FourByFourBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// --- FourByFourUI Implementation ---

Player<char>* FourByFourUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* FourByFourUI::get_move(Player<char>* player) {
    int fr, fc, tr, tc;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlayer " << player->get_name() << " (" << player->get_symbol() << ")\n";
        cout << "Move From (row col): ";
        cin >> fr >> fc;
        cout << "Move To   (row col): ";
        cin >> tr >> tc;
    }
    else {
        int attempts = 0;
        Board<char>* board = player->get_board_ptr();
        do {
            fr = rand() % 4;
            fc = rand() % 4;
            int dir = rand() % 4; // 0:up, 1:down, 2:left, 3:right
            tr = fr; tc = fc;
            if (dir == 0) tr--;
            else if (dir == 1) tr++;
            else if (dir == 2) tc--;
            else if (dir == 3) tc++;

            attempts++;
            if (attempts > 5000) break;
        } while (tr < 0 || tr >= 4 || tc < 0 || tc >= 4 ||
            board->get_cell(fr, fc) != player->get_symbol() ||
            board->get_cell(tr, tc) != '.');
    }

    return new FourByFourMove(fr, fc, tr, tc, player->get_symbol());
}