#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "NumericT3_Classes.h"

using namespace std;

//--------------------------------------- Numeric_Board Implementation

Numeric_Board::Numeric_Board() : Board(3, 3) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            board[i][j] = 0;
        }
    }

    available_nums[1] = { 1, 3, 5, 7, 9 };
    available_nums[2] = { 2, 4, 6, 8 };
}

bool Numeric_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    board[x][y] = number;
    use_num(number);
    n_moves++;
    return true;
}

bool Numeric_Board::is_win(Player<int>* player) {
    
    return false; 
}

bool Numeric_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numeric_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}


bool Numeric_Board::is_num_available(int num, int player_symbol) {
    
    return false; 
}

void Numeric_Board::use_num(int num) {
}

vector<int> Numeric_Board::get_available_nums_for(int player_symbol) {
    return available_nums[player_symbol];
}

void Numeric_Board::print_available_nums(int player_symbol) {
    cout << "Available numbers: ";
    vector<int> nums = get_available_nums_for(player_symbol);
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << endl;
}

//--------------------------------------- Numeric_UI Implementation

Numeric_UI::Numeric_UI() : UI<int>("Welcome to Numerical Tic-Tac-Toe!", 3) {
}

Player<int>* Numeric_UI::create_player(string& name, int symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (Player " << symbol << ")\n";
    return new Player<int>(name, symbol, type);
}

Player<int>** Numeric_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1 (Odd)");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    string name2 = get_player_name("Player 2 (Even)");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);

    return players;
}

Move<int>* Numeric_UI::get_move(Player<int>* player) {
    int x = 0, y = 0, num = 0;
    cout << "\nPlayer " << player->get_symbol() << " (" << player->get_name() << ")\n";

    dynamic_cast<Numeric_Board*>(player->get_board_ptr())->print_available_nums(player->get_symbol());

    cout << "Enter your move (x y): ";
    cin >> x >> y;
    cout << "Enter the number: ";
    cin >> num;

    return new Move<int>(x, y, num);
}