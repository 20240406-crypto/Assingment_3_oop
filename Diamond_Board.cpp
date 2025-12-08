#include "Diamond_Board.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int WIN_SCORE = 1000;
const int DRAW_SCORE = 0;
const int LOSS_SCORE = -1000;
const int MAX_DEPTH = 5;

char get_opponent_symbol(char symbol) {
    return (symbol == 'X' ? 'O' : 'X');
}

int check_win_state(const vector<vector<char>>& current_board, int rows, int columns, char ai_symbol, char opponent_symbol) {

    auto is_winning = [&](char symbol) -> bool {
        // مصفوفات لتخزين هل تم تحقيق 3 أو 4 في كل اتجاه
        bool found_3_in_dir[4] = { false };
        bool found_4_in_dir[4] = { false };

        int dr[] = { 0, 1, 1, 1 }; // الاتجاهات الأربعة: أفقي، عمودي، قطري يمين، قطري يسار
        int dc[] = { 1, 0, 1, -1 };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (current_board[r][c] != symbol) continue;

                for (int d = 0; d < 4; ++d) { // d هو مؤشر الاتجاه
                    int count = 0;

                    for (int k = 0; k < 4; ++k) {
                        int nr = r + k * dr[d];
                        int nc = c + k * dc[d];

                        if (nr >= 0 && nr < rows && nc >= 0 && nc < columns &&
                            abs(nr - 3) + abs(nc - 3) <= 3 &&
                            current_board[nr][nc] == symbol) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }

                    // تسجيل الاتجاه الذي تحقق فيه الشرط
                    if (count >= 3) found_3_in_dir[d] = true;
                    if (count >= 4) found_4_in_dir[d] = true;
                }
            }
        }

        // التحقق من شرط الفوز النهائي (4 في اتجاه i و 3 في اتجاه j، و i != j)
        for (int i = 0; i < 4; ++i) {
            if (found_4_in_dir[i]) {
                for (int j = 0; j < 4; ++j) {
                    if (i != j && found_3_in_dir[j]) {
                        return true;
                    }
                }
            }
        }
        return false;
        };

    if (is_winning(ai_symbol)) return WIN_SCORE;
    if (is_winning(opponent_symbol)) return LOSS_SCORE;

    int n_moves = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (current_board[r][c] != ' ' && current_board[r][c] != '#') n_moves++;
        }
    }

    if (n_moves == 25) return DRAW_SCORE;

    return -1;
}

int minimax(vector<vector<char>>& current_board, int current_n_moves, int rows, int columns, char ai_symbol, char opponent_symbol, int depth, bool is_maximizing_player, int alpha, int beta) {

    int game_state = check_win_state(current_board, rows, columns, ai_symbol, opponent_symbol);

    if (game_state != -1 || depth == 0) {
        if (game_state == WIN_SCORE) return WIN_SCORE - (MAX_DEPTH - depth);
        if (game_state == LOSS_SCORE) return LOSS_SCORE + (MAX_DEPTH - depth);
        return game_state;
    }

    if (is_maximizing_player) {
        int max_eval = -100000;
        char current_symbol = ai_symbol;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (current_board[r][c] == ' ') {
                    current_board[r][c] = current_symbol;

                    int eval = minimax(current_board, current_n_moves + 1, rows, columns, ai_symbol, opponent_symbol, depth - 1, false, alpha, beta);

                    current_board[r][c] = ' ';

                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, max_eval);

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return max_eval;
    }
    else {
        int min_eval = 100000;
        char current_symbol = opponent_symbol;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (current_board[r][c] == ' ') {
                    current_board[r][c] = current_symbol;

                    int eval = minimax(current_board, current_n_moves + 1, rows, columns, ai_symbol, opponent_symbol, depth - 1, true, alpha, beta);

                    current_board[r][c] = ' ';

                    min_eval = min(min_eval, eval);
                    beta = min(beta, min_eval);

                    if (beta <= alpha) {
                        break;
                    }
                }
            }
            if (beta <= alpha) {
                break;
            }
        }
        return min_eval;
    }
}

// تم تغيير حجم اللوحة من 5x5 إلى 7x7
Diamond_Board::Diamond_Board() : Board(7, 7) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (is_in_diamond(i, j)) {
                board[i][j] = ' ';
            }
            else {
                board[i][j] = '#';
            }
        }
    }
}

// تم تعديل المركز من 2 إلى 3، ونصف القطر من 2 إلى 3
bool Diamond_Board::is_in_diamond(int r, int c) const {
    return abs(r - 3) + abs(c - 3) <= 3;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    if (r >= 0 && r < rows && c >= 0 && c < columns &&
        is_in_diamond(r, c) && board[r][c] == ' ') {
        board[r][c] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

bool Diamond_Board::is_win(Player<char>* p) {
    char symbol = (p) ? p->get_symbol() : (n_moves % 2 == 1 ? 'X' : 'O');
    char opponent_symbol = get_opponent_symbol(symbol);
    return check_win_state(board, rows, columns, symbol, opponent_symbol) == WIN_SCORE;
}

bool Diamond_Board::is_lose(Player<char>*) {
    return false;
}

bool Diamond_Board::is_draw(Player<char>* p) {
    return n_moves == DIAMOND_SIZE && !is_win(p);
}

bool Diamond_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

vector<Move<char>> Diamond_Board::get_valid_moves(char symbol) const {
    vector<Move<char>> valid_moves;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (is_in_diamond(r, c) && board[r][c] == ' ') {
                valid_moves.push_back(Move<char>(r, c, symbol));
            }
        }
    }
    return valid_moves;
}

Move<char> Diamond_Board::get_best_move(char symbol) const {

    char opponent_symbol = get_opponent_symbol(symbol);
    vector<Move<char>> valid_moves = get_valid_moves(symbol);
    Move<char> best_move(-1, -1, symbol);
    int max_eval = -100000;

    vector<vector<char>> temp_board = board;
    int temp_n_moves = n_moves;

    if (valid_moves.empty()) {
        return best_move;
    }

    best_move = valid_moves[0];

    for (const auto& move : valid_moves) {

        temp_board[move.get_x()][move.get_y()] = symbol;

        int eval = minimax(temp_board, temp_n_moves + 1, rows, columns, symbol, opponent_symbol, MAX_DEPTH, false, -100000, 100000);

        temp_board[move.get_x()][move.get_y()] = ' ';

        if (eval > max_eval) {
            max_eval = eval;
            best_move = move;
        }
    }

    return best_move;
}