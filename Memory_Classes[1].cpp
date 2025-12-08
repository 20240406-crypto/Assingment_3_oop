#include "Memory_Classes.h"
#include <iostream>

using namespace std;

// --- Memory_Board Implementation ---

Memory_Board::Memory_Board() : Board<char>(3, 3) {
    // Initialize the real_board with dots (empty)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            real_board[i][j] = '.';
            // The VISIBLE board shows coordinates so players can choose cells.
            // Unlike normal Tic-Tac-Toe, these numbers WON'T change to X/O immediately.
            board[i][j] = (char)('0' + (i * 3 + j));
        }
    }
}

bool Memory_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    // 1. Check Bounds
    if (r < 0 || r >= 3 || c < 0 || c >= 3) {
        return false; // Invalid index
    }

    // 2. Check Validity against REAL board (Memory aspect)
    if (real_board[r][c] != '.') {
        // The cell is already occupied, but the player might not have realized 
        // because the board hides it!
        return false;
    }

    // 3. Update the REAL board (Logic layer)
    real_board[r][c] = symbol;
    n_moves++;

    // 4. Update the VISIBLE board (Display layer)
    // To fit the "Memory" theme, we do NOT show X or O.
    // We can either:
    // A. Leave it as the number (Total invisible)
    // B. Change it to a '?' or '#' to show "Something is here" but not WHO.

    // Based on "marks are hidden after being placed", leaving it as the number 
    // or changing it to a generic hidden symbol is best. 
    // Let's use the number to keep the coordinate reference available, 
    // OR change it to ' ' (space) to mimic the "hidden" nature.

    // Let's go with keeping the number (so they can't visually see it changed),
    // effectively forcing them to remember "I played 4, he played 5".
    // (No change to board[r][c])

    return true;
}

bool Memory_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    // Check rows on REAL board
    for (int i = 0; i < 3; i++) {
        if (real_board[i][0] == s && real_board[i][1] == s && real_board[i][2] == s) return true;
    }
    // Check columns on REAL board
    for (int i = 0; i < 3; i++) {
        if (real_board[0][i] == s && real_board[1][i] == s && real_board[2][i] == s) return true;
    }
    // Check diagonals on REAL board
    if (real_board[0][0] == s && real_board[1][1] == s && real_board[2][2] == s) return true;
    if (real_board[0][2] == s && real_board[1][1] == s && real_board[2][0] == s) return true;

    return false;
}

bool Memory_Board::is_lose(Player<char>* player) {
    return false;
}

bool Memory_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Memory_Board::game_is_over(Player<char>* player) {
    if (is_win(player) || is_draw(player)) {
        reveal_board(); // Reveal everything when game ends
        return true;
    }
    return false;
}

void Memory_Board::reveal_board() {
    // Copy real X/O values to the visible board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = real_board[i][j];
        }
    }
}

// --- Memory_UI Implementation ---

Player<char>* Memory_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

void Memory_UI::display_board(Board<char>& b) {
    // Custom display to make it look clean
    vector<vector<char>> matrix = b.get_board_matrix();
    cout << "\n";
    cout << " " << matrix[0][0] << " | " << matrix[0][1] << " | " << matrix[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << matrix[1][0] << " | " << matrix[1][1] << " | " << matrix[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << matrix[2][0] << " | " << matrix[2][1] << " | " << matrix[2][2] << "\n";
    cout << "\n";
}

Move<char>* Memory_UI::get_move(Player<char>* player) {
    int r, c;
    if (player->get_type() == PlayerType::HUMAN) {
        // We cast to our specific UI class to use the custom display method
        display_board(*(player->get_board_ptr()));

        cout << "Player " << player->get_name() << " (" << player->get_symbol() << ")\n";
        cout << "Enter coordinate (0-8): "; // Simplified input for 3x3
        int choice;
        cin >> choice;

        // Convert 0-8 to row/col
        r = choice / 3;
        c = choice % 3;

    }
    else {
        // Computer (Random guesser)
        // It blindly picks spots until one works.
        // (The game manager loop will handle re-tries if it picks an occupied spot)
        r = rand() % 3;
        c = rand() % 3;
    }
    return new Move<char>(r, c, player->get_symbol());
}