#include "SUS_Classes.h"
#include <iostream>
#include <cctype>

using namespace std;

// -------------------------------------------------------------------------
// SUS_Board Implementation
// -------------------------------------------------------------------------

SUS_Board::SUS_Board() : Board(3, 3) {
    player_scores[0] = 0;
    player_scores[1] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }
}

int SUS_Board::count_sus(int r, int c) {
    int count = 0;
    char current = board[r][c];

    int dr[] = { 0, 0, 1, -1, 1, -1, 1, -1 };
    int dc[] = { 1, -1, 0, 0, 1, -1, -1, 1 };

    if (current == 'S') {
        for (int i = 0; i < 8; i++) {
            int r1 = r + dr[i];
            int c1 = c + dc[i];
            int r2 = r + 2 * dr[i];
            int c2 = c + 2 * dc[i];

            if (r1 >= 0 && r1 < rows && c1 >= 0 && c1 < columns &&
                r2 >= 0 && r2 < rows && c2 >= 0 && c2 < columns) {
                if (board[r1][c1] == 'U' && board[r2][c2] == 'S') {
                    count++;
                }
            }
        }
    }
    else if (current == 'U') {
        if (c - 1 >= 0 && c + 1 < columns && board[r][c - 1] == 'S' && board[r][c + 1] == 'S') count++;
        if (r - 1 >= 0 && r + 1 < rows && board[r - 1][c] == 'S' && board[r + 1][c] == 'S') count++;
        if (r - 1 >= 0 && c - 1 >= 0 && r + 1 < rows && c + 1 < columns &&
            board[r - 1][c - 1] == 'S' && board[r + 1][c + 1] == 'S') count++;
        if (r - 1 >= 0 && c + 1 < columns && r + 1 < rows && c - 1 >= 0 &&
            board[r - 1][c + 1] == 'S' && board[r + 1][c - 1] == 'S') count++;
    }

    return count;
}

bool SUS_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = toupper(move->get_symbol());

    if (r >= 0 && r < rows && c >= 0 && c < columns && board[r][c] == 0) {
        board[r][c] = symbol;
        int points = count_sus(r, c);
        player_scores[n_moves % 2] += points;
        n_moves++;
        return true;
    }
    return false;
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return n_moves >= 9;
}

bool SUS_Board::is_win(Player<char>* player) {
    if (n_moves < 9) return false;
    int last_player_index = (n_moves - 1) % 2;
    int other_player_index = 1 - last_player_index;
    return player_scores[last_player_index] > player_scores[other_player_index];
}

bool SUS_Board::is_lose(Player<char>* player) {
    if (n_moves < 9) return false;
    int last_player_index = (n_moves - 1) % 2;
    int other_player_index = 1 - last_player_index;
    return player_scores[last_player_index] < player_scores[other_player_index];
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    return player_scores[0] == player_scores[1];
}

// -------------------------------------------------------------------------
// SUS_UI Implementation
// -------------------------------------------------------------------------

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game", 3) {
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// NEW: Customized setup to enforce 'S' and 'U' assignment
Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    // Set up Player 1 as 'S'
    string name1 = get_player_name("Player 1 (will play 'S')");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'S', type1);

    // Set up Player 2 as 'U'
    string name2 = get_player_name("Player 2 (will play 'U')");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'U', type2);

    return players;
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    char symbol = player->get_symbol();

    SUS_Board* board = dynamic_cast<SUS_Board*>(player->get_board_ptr());
    if (board) {
        cout << "Current Scores -> P1: " << board->get_score(0)
            << " | P2: " << board->get_score(1) << endl;
    }

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << symbol << "), enter coordinate (x y): ";
        cin >> x >> y;
    }
    else {
        x = rand() % 3;
        y = rand() % 3;
    }

    return new Move<char>(x, y, symbol);
}