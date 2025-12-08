#include "ConnectFour_Classes.h"
#include <iostream>
#include <string>

using namespace std;

// -------------------------------------------------------------------------
// ConnectFour_Board Implementation
// -------------------------------------------------------------------------

ConnectFour_Board::ConnectFour_Board() : Board(6, 7) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0; 
        }
    }
}

bool ConnectFour_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char symbol = toupper(move->get_symbol());
 
    if (c < 0 || c >= columns) {
        return false;
    }


    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][c] == 0) { 
            r = i; 
            board[i][c] = symbol; 
            n_moves++; 
            return true; 
        }
    }

    
    return false;
}

bool ConnectFour_Board::is_win(Player<char>* player) {
   
    char symbol = player->get_symbol(); // نأخذ رمز اللاعب الحالي (X أو O)

    // 1. الفحص الأفقي (Horizontal)
    // نتأكد أننا لا نخرج عن حدود الأعمدة (j < columns - 3)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == symbol &&
                board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol &&
                board[i][j + 3] == symbol) {
                return true;
            }
        }
    }

    // 2. الفحص الرأسي (Vertical)
    // نتأكد أننا لا نخرج عن حدود الصفوف (i < rows - 3)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol &&
                board[i + 3][j] == symbol) {
                return true;
            }
        }
    }

    // 3. الفحص القطري (Diagonal Down-Right) (\)
    for (int i = 0; i < rows - 3; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol &&
                board[i + 3][j + 3] == symbol) {
                return true;
            }
        }
    }

    // 4. الفحص القطري العكسي (Diagonal Up-Right) (/)
    // نبدأ من الصف الثالث لأننا سنطرح من الـ index (نصعد للأعلى)
    for (int i = 3; i < rows; i++) {
        for (int j = 0; j < columns - 3; j++) {
            if (board[i][j] == symbol &&
                board[i - 1][j + 1] == symbol &&
                board[i - 2][j + 2] == symbol &&
                board[i - 3][j + 3] == symbol) {
                return true;
            }
        }
    }

    return false;
}

bool ConnectFour_Board::is_lose(Player<char>* player) {
    return false;
}

bool ConnectFour_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool ConnectFour_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// -------------------------------------------------------------------------
// ConnectFour_UI Implementation
// -------------------------------------------------------------------------

ConnectFour_UI::ConnectFour_UI() : UI<char>("Welcome to Connect Four Game", 3) {
    
}

Player<char>* ConnectFour_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** ConnectFour_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 'X', type1);

    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 'O', type2); 

    return players;
}

Move<char>* ConnectFour_UI::get_move(Player<char>* player) {
    // ?? Connect 4 ?????? ????? "??????" ???
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter column (0-6): ";
        cin >> col;
        // ??????: ???? ??? ????? ??? ????? ???? ?????? ?? update_board
        // ????? 0 ?????? ????? ????
        return new Move<char>(0, col, player->get_symbol());
    }
    else {
        // ???? ????????? ????????? (??????)
        col = rand() % 7;
        return new Move<char>(0, col, player->get_symbol());
    }
}