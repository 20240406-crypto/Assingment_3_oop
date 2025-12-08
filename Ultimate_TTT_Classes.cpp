
#include "Ultimate_TTT_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits> 
#include <algorithm>
#include <vector>
#include <cstdlib>


using namespace std;

int Ultimate_TTT_Board::last_main_r = -1;
int Ultimate_TTT_Board::last_main_c = -1;

Ultimate_TTT_Board::Ultimate_TTT_Board() : Board<char>(3, 3) {
	last_main_r = -1;
	last_main_c = -1;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < columns; ++c) {
			sub_boards[r][c] = new Mini_TTT_Board();
			this->board[r][c] = blank_symbol;
		}
	}
}
Ultimate_TTT_Board::~Ultimate_TTT_Board() {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < columns; ++c) {
			delete sub_boards[r][c];
		}
	}
}

void Ultimate_TTT_Board::display_nested_board(const UI<char>* ui_ptr) const {
	cout << "\n=====================================\n";

	for (int r_start = 0; r_start < rows; ++r_start) {
		for (int i = 0; i < 3; ++i) {
			//cout <<" Main " << r_start << " |";
			cout << " Main " << r_start << " |";
			for (int c_start = 0; c_start < columns; ++c_start) {
				Mini_TTT_Board* current_sub = sub_boards[r_start][c_start];
				vector<vector<char>> sub_matrix = current_sub->get_board_matrix();
				
				for (int j = 0; j < 3; ++j) {
					cout << " " << sub_matrix[i][j] << " ";
				}
				cout << " | "; 
			}
			cout << "\n";
		}
		cout << string(45, '-') << "\n";
	}
}

bool Ultimate_TTT_Board::update_board(Move<char>* move) {
	int r1 = last_main_r;
	int c1 = last_main_c;
	int r2 = move->get_x();
	int c2 = move->get_y();
	char mark = move->get_symbol();

	if (r1 < 0 || r1 >= 3 || c1 < 0 || c1 >= 3) return false;

	Mini_TTT_Board* target_board = sub_boards[r1][c1];

	Move<char> sub_move(r2, c2, mark);
	if (target_board->update_board(&sub_move)) {
		this->n_moves++;

		char winner_sub = target_board->check_winner();
		if (winner_sub != '.' ) {
			this->board[r1][c1] = (winner_sub == 'D') ? 'T' : winner_sub;
		}
		return true;
	}
	return false;
}

bool Ultimate_TTT_Board::is_win(Player<char>* player) {
	const char sym = player->get_symbol();
	const vector<vector<char>>& main_state = this->board;

	auto all_equal = [&](char a, char b, char c) {
		return a == b && b == c && (a == 'X' || a == 'O');
		};

	// Check rows, columns, and diagonals for main board win
	for (int i = 0; i < rows; ++i) {
		if ((all_equal(main_state[i][0], main_state[i][1], main_state[i][2]) && main_state[i][0] == sym) ||
			(all_equal(main_state[0][i], main_state[1][i], main_state[2][i]) && main_state[0][i] == sym))
			return true;
	}
	if ((all_equal(main_state[0][0], main_state[1][1], main_state[2][2]) && main_state[1][1] == sym) ||
		(all_equal(main_state[0][2], main_state[1][1], main_state[2][0]) && main_state[1][1] == sym))
		return true;

	return false;
}
bool Ultimate_TTT_Board::is_draw(Player<char>* player) {
	if (is_win(player)) return false;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (this->board[i][j] == blank_symbol) return false;
		}
	}
	return true;
}

bool Ultimate_TTT_Board::game_is_over(Player<char>* player) {
	return is_win(player) || is_draw(player);
}

Ultimate_TTT_UI::Ultimate_TTT_UI() : UI<char>("Welcome to Ultimate Tic-Tac-Toe", 3) {}

Player<char>* Ultimate_TTT_UI::create_player(string& name, char symbol, PlayerType type) {
	return new Player<char>(name, symbol, type);
}

struct PossibleMove {
	int r1, c1, r2, c2;
};

Move<char>* Ultimate_TTT_UI::get_move(Player<char>* player) {
	int r1, c1, r2, c2;
	char mark = player->get_symbol();

	Ultimate_TTT_Board* u_board = static_cast<Ultimate_TTT_Board*>(player->get_board_ptr());
	
	if (player->get_type() == PlayerType::HUMAN) {

		//u_board->display_nested_board(this);

		while (true) {
			cout << "\nFREE MOVE (" << player->get_name() << "): Choose ANY Main Board and Sub Cell.\n";
			cout << "Enter: Main-Row Main-Col Sub-Row Sub-Col ( _ , _ , _ , _ ) : ";

			if (!(cin >> r1 >> c1 >> r2 >> c2)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter 4 numbers.\n";
				continue;
			}

			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (r1 < 0 || r1 > 2 || c1 < 0 || c1 > 2 || r2 < 0 || r2 > 2 || c2 < 0 || c2 > 2) {
				cout << "Coordinates must be between 0 and 2.\n";
				continue;
			}

			if (u_board->get_board_matrix()[r1][c1] != '.') {
				cout << "Main Board (" << r1 << "," << c1 << ") is already finished. Choose another.\n";
				continue;
			}

			if (u_board->get_sub_board(r1, c1)->get_board_matrix()[r2][c2] != '.') {
				cout << "Cell (" << r2 << "," << c2 << ") is already taken.\n";
				continue;
			}

			break;
		}
	}
	else {
		vector<PossibleMove> moves;
		for (int mr = 0; mr < 3; ++mr) {
			for (int mc = 0; mc < 3; ++mc) {
				if (u_board->get_board_matrix()[mr][mc] == '.') {
					Mini_TTT_Board* sub = u_board->get_sub_board(mr, mc);
					for (int sr = 0; sr < 3; ++sr) {
						for (int sc = 0; sc < 3; ++sc) {
							if (sub->get_board_matrix()[sr][sc] == '.') {
								moves.push_back({ mr, mc, sr, sc });
							}
						}
					}
				}
			}
		}

		if (!moves.empty()) {
			int idx = rand() % moves.size();
			r1 = moves[idx].r1;
			c1 = moves[idx].c1;
			r2 = moves[idx].r2;
			c2 = moves[idx].c2;
		}
		else {
			r1 = -1; c1 = -1; r2 = -1; c2 = -1 ;
		}
		u_board->display_nested_board(this);
		cout << "\nCOMPUTER (" << player->get_name() << ") played at Main: (" << r1 << "," << c1 << ") Sub: (" << r2 << "," << c2 << ")\n";
	}

	Ultimate_TTT_Board::last_main_r = r1;
	Ultimate_TTT_Board::last_main_c = c1;

	return new Move<char>(r2, c2, mark);
}