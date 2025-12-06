
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "5x5_Tic_Classes.h"

using namespace std;

// Count all 3-in-a-row windows (overlapping allowed) for given symbol on a 5x5 board.
static int count_three_in_row(const vector<vector<char>>& b, char sym) {
    int count = 0;
    const int N = 5;

    // Rows: windows of length 3 -> j = 0..2
    for (int i = 0; i < N; ++i)
        for (int j = 0; j <= N - 3; ++j)
            if (b[i][j] == sym && b[i][j + 1] == sym && b[i][j + 2] == sym)
                ++count;

    // Columns
    for (int j = 0; j < N; ++j)
        for (int i = 0; i <= N - 3; ++i)
            if (b[i][j] == sym && b[i + 1][j] == sym && b[i + 2][j] == sym)
                ++count;

    // Diagonals top-left -> bottom-right
    for (int i = 0; i <= N - 3; ++i)
        for (int j = 0; j <= N - 3; ++j)
            if (b[i][j] == sym && b[i + 1][j + 1] == sym && b[i + 2][j + 2] == sym)
                ++count;

    // Diagonals top-right -> bottom-left
    for (int i = 0; i <= N - 3; ++i)
        for (int j = 2; j < N; ++j)
            if (b[i][j] == sym && b[i + 1][j - 1] == sym && b[i + 2][j - 2] == sym)
                ++count;

    return count;
}

// ----------------------------
// Tic5_Board Implementation
// ----------------------------
Tic5_Board::Tic5_Board() : Board<char>(5, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}


//Behavior:
//- If move->get_symbol() == 0 -> treat as "no-op" and return true (used to let GameManager proceed to checks).
//- Otherwise, only allow placement on blank cells while n_moves < 24.

bool Tic5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Special sentinel: mark == 0 => no-op (used when get_move detected game already over)
    if (mark == 0) {
        return true;
    }

    // bounds check
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    // Do not allow placements after 24 moves have been made.
    if (n_moves >= 24) {
        return false;
    }

    // only allow placing on blank cell
    if (board[x][y] == blank_symbol) {
        board[x][y] = static_cast<char>(toupper(static_cast<unsigned char>(mark)));
        ++n_moves;
        return true;
    }
    return false;
}

bool Tic5_Board::is_win(Player<char>* player) {
    // A win is declared only at final state (after 24 moves)
    if (n_moves < 24) return false;

    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X';

    int player_count = count_three_in_row(board, sym);
    int other_count = count_three_in_row(board, other);

    return (player_count > other_count);
}

bool Tic5_Board::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X';

    int player_count = count_three_in_row(board, sym);
    int other_count = count_three_in_row(board, other);

    return (player_count == other_count);
}

bool Tic5_Board::game_is_over(Player<char>* player) {
    return (n_moves >= 24);
}

// ----------------------------
// Tic5_UI Implementation
// ----------------------------

Tic5_UI::Tic5_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe Game", 3) {}

Player<char>* Tic5_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}


//- If the board is already over (n_moves >= 24) we return a no-op move (mark==0) that update_board accepts.
//- Human: asks for x y (0..4).
//- Computer: picks a random empty cell (with fallback linear scan).

Move<char>* Tic5_UI::get_move(Player<char>* player) {
    Board<char>* b = player->get_board_ptr();

    // Defensive: if no board assigned, return a dummy move (will be rejected by update_board)
    if (!b) return new Move<char>(0, 0, player->get_symbol());

    // If game is over, return a no-op move so GameManager can proceed to final checks.
    if (b->game_is_over(player)) {
        return new Move<char>(0, 0, 0); // mark == 0 used as sentinel
    }

    int x = -1, y = -1;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nEnter your move x and y (0 to 4): ";
        cin >> x >> y;
    }
    else {
        // computer: choose random empty cell (with attempts and fallback)
        int attempts = 0;
        do {
            x = rand() % b->get_rows();
            y = rand() % b->get_columns();
            ++attempts;
            if (attempts > 200) { // fallback: linear scan
                bool found = false;
                for (int i = 0; i < b->get_rows() && !found; ++i)
                    for (int j = 0; j < b->get_columns() && !found; ++j)
                        if (b->get_cell(i, j) == '.') {
                            x = i; y = j; found = true;
                        }
                break;
            }
        } while (b->get_cell(x, y) != '.');
    }
    return new Move<char>(x, y, player->get_symbol());
}
