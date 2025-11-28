#include "Obstacles_Board.h"
#include <iostream>
#include <cctype>
#include <ctime> 
#include <limits> 

using namespace std;

// ========================================================
// »«‰Ì «·ﬂ·«” (Constructor)
// ========================================================
Obstacles_Board::Obstacles_Board() : Board(6, 6) {
    srand((unsigned int)time(0));
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' '; //  „  ⁄œÌ·Â« ≈·Ï «·„”«›… «·›«—€… ' '

    add_obstacle();
    add_obstacle();
}

// ========================================================
// œ«·… ≈÷«›… ⁄«∆ﬁ ⁄‘Ê«∆Ì
// ========================================================
void Obstacles_Board::add_obstacle() {
    int r, c;
    do {
        r = rand() % 6;
        c = rand() % 6;
    } while (board[r][c] != blank);

    board[r][c] = obstacle;
}

// ========================================================
// œ«·… «· Õﬁﬁ „‰ 4 ›Ì ’›
// ========================================================
bool Obstacles_Board::four_in_row(char sym) {
    sym = toupper(sym);

    // 1. «· Õﬁﬁ „‰ «·’›Ê›
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym && board[i][j + 3] == sym)
                return true;
        }
    }
    // 2. «· Õﬁﬁ „‰ «·√⁄„œ…
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i <= rows - 4; i++) {
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym && board[i + 3][j] == sym)
                return true;
        }
    }
    // 3.1. «·√ﬁÿ«— «·‰«“·…
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 0; j <= columns - 4; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym)
                return true;
        }
    }
    // 3.2. «·√ﬁÿ«— «·’«⁄œ…
    for (int i = 0; i <= rows - 4; i++) {
        for (int j = 3; j < columns; j++) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym)
                return true;
        }
    }

    return false;
}

// ========================================================
// œ«·…  ÕœÌÀ «··ÊÕ… 
// ========================================================
bool Obstacles_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        std::cout << "!! Invalid move: Position (" << x << ", " << y << ") is out of bounds (0-5).\n";
        return false;
    }

    if (board[x][y] != blank) {
        std::cout << "!! Invalid move: Cell (" << x << ", " << y << ") is occupied by '"
            << board[x][y] << "' (Blocked or already played).\n";
        return false;
    }

    board[x][y] = toupper(sym);
    n_moves++;

    add_obstacle();
    add_obstacle();

    return true;
}

// ========================================================
// œ«·… «·›Ê“ («· Ì ﬂ«‰  „›ﬁÊœ…)
// ========================================================
bool Obstacles_Board::is_win(Player<char>* player) {
    return four_in_row(player->get_symbol());
}

// ========================================================
// œ«·… «· ⁄«œ· (·Õ· „‘ﬂ·… ⁄œ„ «·≈⁄·«‰ ⁄‰ «· ⁄«œ·)
// ========================================================
bool Obstacles_Board::is_draw(Player<char>* player) {
    int total_empty = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == blank) {
                total_empty++;
            }
        }
    }

    if (total_empty == 0) {
        // ÿ»«⁄… „»«‘—… ·÷„«‰ ŸÂÊ— «·—”«·… 
        std::cout << "\n======================================================\n";
        std::cout << "                ⁄‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹«œ·!              \n";
        std::cout << "======================================================\n";
        return true;
    }

    return false;
}

// ========================================================
// œ«·… ‰Â«Ì… «··⁄»…
// ========================================================
bool Obstacles_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}