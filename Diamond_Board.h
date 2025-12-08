#ifndef DIAMOND_BOARD_H
#define DIAMOND_BOARD_H

#include "BoardGame_Classes.h"
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Diamond_Board : public Board<char> {
private:
	const int DIAMOND_SIZE = 25;

public:
	Diamond_Board();

	bool update_board(Move<char>* move) override;
	bool is_win(Player<char>*) override;
	bool is_lose(Player<char>*) override;
	bool is_draw(Player<char>*) override;
	bool game_is_over(Player<char>*) override;

	vector<Move<char>> get_valid_moves(char symbol) const;

	Move<char> get_best_move(char symbol) const;

	bool is_in_diamond(int r, int c) const;

	const vector<vector<char>>& get_board_matrix() const {
		return board;
	}

	int get_rows() const { return rows; }
	int get_columns() const { return columns; }
};

#endif