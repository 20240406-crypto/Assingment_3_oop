#include "Diamond_UI.h"
#include <limits> 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* p) {
    int r = -1, c = -1;
    char symbol = p->get_symbol();
    Diamond_Board* board_ptr = dynamic_cast<Diamond_Board*>(p->get_board_ptr());

    if (p->get_type() == PlayerType::COMPUTER) {

        cout << "Computer turn (" << p->get_name() << " - " << symbol << ") is calculating its best move using AI..." << endl;

        Move<char> best_move = board_ptr->get_best_move(symbol);

        r = best_move.get_x();
        c = best_move.get_y();

    }
    else {
        bool valid_input = false;
        while (!valid_input) {
            cout << "Player " << p->get_name() << " (" << symbol << "), enter row and column: ";

            if (!(cin >> r >> c)) {
                cout << "Invalid input. Please enter two integers." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (board_ptr && r >= 0 && r < board_ptr->get_rows() && c >= 0 && c < board_ptr->get_columns() &&
                board_ptr->is_in_diamond(r, c) && board_ptr->get_board_matrix()[r][c] == ' ') {
                valid_input = true;
            }
            else {
                cout << "Invalid move. The square is outside the diamond, or is already taken. Try again." << endl;
            }
        }
    }

    return new Move<char>(r, c, symbol);
}