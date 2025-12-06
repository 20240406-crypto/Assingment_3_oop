
// Word_Tic.cpp

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include <limits>



#include "Word_Tic_Classes.h"

using namespace std;


// ----------------------------
// wrdTic_Board Implementation
// ----------------------------
set <string> wrdTic_Board::valid_words;

void wrdTic_Board::initialize_dic(const  std::string& filename) {
    if (!valid_words.empty()) { return; }

    ifstream file("dic.txt");
    string word;
    if (file.is_open()) {
        while (getline(file, word)) {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            if (word.length() == 3) {
                valid_words.insert(word);
            }

        }
        file.close();
    }
    else {
        cout << "ERROR: Could not open dic.txt! Check file path and name.\n";
    }
}


wrdTic_Board::wrdTic_Board() : Board<char>(3, 3) {
    initialize_dic("dic.txt");

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            this->board[i][j] = blank_symbol;
}

/*
 Behavior:
 - If move->get_symbol() == 0 -> treat as "no-op" and return true (used to let GameManager proceed to checks).
*/
bool wrdTic_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Validate move and apply if valid
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }
    if (this->board[x][y] == blank_symbol) {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

bool wrdTic_Board::is_win(Player<char>* player) {
    int N = 3;

    // Check rows and columns
    for (int i = 0; i < N; ++i) {
        string row_word, col_word;
        for (int j = 0; j < N; ++j) {
            row_word += this->board[i][j];
            col_word += this->board[j][i];
        }
        if (row_word.find(blank_symbol) == string::npos && valid_words.count(row_word)) {
            return true;
        }
        if (col_word.find(blank_symbol) == string::npos && valid_words.count(col_word)) {
            return true;
        }
    }

    // Check diagonals
    string diag1;
    for (int i = 0; i < N; ++i) {
        diag1 += this->board[i][i];
    }
    if (diag1.find(blank_symbol) == string::npos && valid_words.count(diag1)) {
        return true;
    }

    string diag2;
    for (int i = 0; i < N; ++i) {
        diag2 += this->board[i][i];
    }
    if (diag2.find(blank_symbol) == string::npos && valid_words.count(diag2)) {
        return true;
    }
    return false;
}

bool wrdTic_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool wrdTic_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ----------------------------
// wrdTic_UI Implementation
// ----------------------------
wrdTic_UI::wrdTic_UI() : UI<char>("Welcome to Word_Tic-Tac-Toe Game", 3) {}

Player<char>* wrdTic_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}


Move<char>* wrdTic_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;

    if (player->get_type() == PlayerType::HUMAN) {
        //cout << "\n" << player->get_name() << " turn (Symbol: " << player->get_symbol() << " ) :\n";
        //cout << "Please enter your move x and y (0 to 2) and letter (A to Z ) : ";
        //cin >> x >> y >> letter;
        do {
            cout << "\n player " << player->get_name() << " enter row(0 to 2), col(0 to 2), and letter (A to Z ): ";
            if (!(cin >> x >> y >> letter)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR: invaled input type \n";
                x = -1;
            }
            else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                letter = toupper(letter);
            }
        } while (x < 0 || x >= player->get_board_ptr()->get_rows() ||
            y < 0 || y >= player->get_board_ptr()->get_columns() || !isalpha(letter));
        return new Move<char>(x, y, letter);
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != '.');
        letter = 'A' + (rand() % 26);
        letter = toupper(letter);

        return new Move<char>(x, y, letter);
    }

}
