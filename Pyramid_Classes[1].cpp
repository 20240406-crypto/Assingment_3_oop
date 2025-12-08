#include "Pyramid_Classes.h"
#include <iostream>
#include <iomanip>

using namespace std;

// --- Pyramid_Board Implementation ---

Pyramid_Board::Pyramid_Board() : Board<char>(3, 5) {
    // Initialize all to 0 or space
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = '.';
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    // 1. Check general boundaries
    if (r < 0 || r >= 3 || c < 0 || c >= 5) {
        cout << "Error: Out of bounds. (Rows 0-2, Cols 0-4)\n";
        return false;
    }

    // 2. Check Valid Pyramid Geometry
    // Row 0: Only valid at col 2
    if (r == 0 && c != 2) {
        cout << "Error: In the top row (0), you can only pick column 2.\n";
        return false;
    }
    // Row 1: Only valid at cols 1, 2, 3
    if (r == 1 && (c < 1 || c > 3)) {
        cout << "Error: In the middle row (1), you can only pick columns 1, 2, or 3.\n";
        return false;
    }
    // Row 2: All cols 0-4 are valid (no check needed besides general bounds)

    // 3. Check if cell is empty
    if (board[r][c] != '.') {
        cout << "Error: Cell already occupied!\n";
        return false;
    }

    // Apply move
    board[r][c] = symbol;
    n_moves++;
    return true;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    // 1. Vertical Win (Only one possible: the center column)
    if (board[0][2] == s && board[1][2] == s && board[2][2] == s) return true;

    // 2. Horizontal Wins
    // Row 1 (1,1 -> 1,3)
    if (board[1][1] == s && board[1][2] == s && board[1][3] == s) return true;

    // Row 2 (Checking 3 possible segments: 0-2, 1-3, 2-4)
    if (board[2][0] == s && board[2][1] == s && board[2][2] == s) return true;
    if (board[2][1] == s && board[2][2] == s && board[2][3] == s) return true;
    if (board[2][2] == s && board[2][3] == s && board[2][4] == s) return true;

    // 3. Diagonal Wins
    // Left Diagonal: (0,2) -> (1,1) -> (2,0)
    if (board[0][2] == s && board[1][1] == s && board[2][0] == s) return true;

    // Right Diagonal: (0,2) -> (1,3) -> (2,4)
    if (board[0][2] == s && board[1][3] == s && board[2][4] == s) return true;

    return false;
}

bool Pyramid_Board::is_lose(Player<char>* player) {
    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    // Total valid cells = 1 + 3 + 5 = 9 cells
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// --- Pyramid_UI Implementation ---

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void Pyramid_UI::display_pyramid(Board<char>& b) {
    vector<vector<char>> matrix = b.get_board_matrix();

    cout << "\n";
    // Row 0 (Center at index 2)
    cout << "          | " << matrix[0][2] << " |" << endl;
    cout << "      -----------" << endl;

    // Row 1 (Indices 1, 2, 3)
    cout << "      | " << matrix[1][1] << " | " << matrix[1][2] << " | " << matrix[1][3] << " |" << endl;
    cout << "  -------------------" << endl;

    // Row 2 (Indices 0, 1, 2, 3, 4)
    cout << "  | " << matrix[2][0] << " | " << matrix[2][1] << " | " << matrix[2][2]
        << " | " << matrix[2][3] << " | " << matrix[2][4] << " |" << endl;
    cout << "\n";
}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int r, c;
    if (player->get_type() == PlayerType::HUMAN) {
        display_pyramid(*(player->get_board_ptr()));
        cout << "Player " << player->get_name() << " (" << player->get_symbol() << ")\n";
        cout << "Enter Row (0-2) and Column (0-4): ";
        cin >> r >> c;
    }
    else {
        // Simple Random Computer Player logic
        // It keeps guessing until the Board class accepts the move
        r = rand() % 3;
        c = rand() % 5;
    }
    return new Move<char>(r, c, player->get_symbol());
}