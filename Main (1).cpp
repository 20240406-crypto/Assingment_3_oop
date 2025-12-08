#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>


#include "BoardGame_Classes.h"
#include "NumericT3_Classes.h"
#include "FourByFour_Classes.h"
#include "SUS_Classes.h"
#include "5x5_Tic_Classes.h"
#include "Misere_Board.h"  
#include "Misere_UI.h"
#include "Obstacles_Board.h"  
#include "Obstacles_UI.h"
#include "Word_Tic_Classes.h"
#include "Mini_TTT_Classes.h" 
#include "Ultimate_TTT_Classes.h"


using namespace std;


void play_numeric_t3() {
    cout << "\n--- Starting Numerical T3 Game ---\n";

    UI<int>* game_ui = new Numeric_UI();
    Board<int>* num_board = new Numeric_Board();
    Player<int>** players = game_ui->setup_players();

    GameManager<int> game(num_board, players, game_ui);
    game.run();

    delete num_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;
}

void play_four_by_four() {
    cout << "\n--- Starting 4x4 Four-in-a-Row Game ---\n";

    FourByFourUI* ui = new FourByFourUI();
    FourByFourBoard* board = new FourByFourBoard();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
}


void play_sus() {
    cout << "\n--- Starting SUS Game ---\n";

    SUS_UI* ui = new SUS_UI();
    SUS_Board* board = new SUS_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
}


void play_five_by_five() {
    cout << "\n--- Starting 5x5 Tic-Tac-Toe (Count Triplets) Game ---\n";

    Tic5_UI* ui = new Tic5_UI();
    Tic5_Board* board = new Tic5_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    
    if (board->is_win(players[0])) {
        ui->display_message(players[0]->get_name() + " wins!");
    }
    else if (board->is_draw(players[0])) {
        ui->display_message("Draw!");
    }
    else {
        
        ui->display_message(players[1]->get_name() + " wins!");
    }


    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
}

void play_misere() {
    cout << "\n--- Starting Misere Tic-Tac-Toe Game (3x3) ---\n";
   

    Misere_UI* game_ui = new Misere_UI();
    Misere_Board* misere_board = new Misere_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game(misere_board, players, game_ui);
    game.run();

    delete misere_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;
}

void play_obstacles() {
    cout << "\n--- Starting Obstacles Tic-Tac-Toe Game (6x6) ---\n";
   
    Obstacles_UI* game_ui = new Obstacles_UI();
    Obstacles_Board* obstacles_board = new Obstacles_Board();
    Player<char>** players = game_ui->setup_players();
    GameManager<char> game(obstacles_board, players, game_ui);
    game.run();

    delete obstacles_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;
}
void play_word_ttt() {
    cout << "\n--- Starting Word Tic-Tac-Toe Game (3x3) ---\n";
   

    wrdTic_UI* game_ui = new wrdTic_UI();
    wrdTic_Board* board = new wrdTic_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> wrdTic_game(board, players, game_ui);
    game.run();

    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;
}
void play_ultimate_ttt_game() {

    Ultimate_TTT_UI* game_ui_ultimate = new Ultimate_TTT_UI();
    Ultimate_TTT_Board* ultimate_board = new Ultimate_TTT_Board();

    Player<char>** players = game_ui_ultimate->setup_players();
    players[0]->set_board_ptr(ultimate_board);
    players[1]->set_board_ptr(ultimate_board);

    ultimate_board->display_nested_board(game_ui_ultimate);

    GameManager<char> ultimate_ttt_game(ultimate_board, players, game_ui_ultimate);
    ultimate_ttt_game.run();

    delete ultimate_board;
    for (int i = 0; i < 2; ++i) {delete players[i];}
    delete[] players;
    delete game_ui_ultimate;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice = -1;
    while (choice != 0) {

        cout << "\n========================================\n";
        cout << "     FCAI Board Games Hub\n";
        cout << "========================================\n";
        cout << "1. Numerical Tic-Tac-Toe (3x3)\n";
        cout << "2. Misere Tic-Tac-Toe (3x3) (Disabled)\n";
        cout << "3. Obstacles Tic-Tac-Toe (6x6) (Disabled)\n";
        cout << "4. Tic-Tac-Toe (5x5) (Disabled)\n";
        cout << "5. Four-in-a-Row (4x4)\n";
        cout << "6. SUS Game\n";
        cout << "7.Word Tic-Tac-Toe Game (3x3)";
        cout << "8.Ultimate Tic-Tac-Toe Game (9x9)";

        cout << "\n0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input — numbers only.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1: play_numeric_t3(); break; 
        case 2: play_misere(); break; 
        case 3: play_obstacles(); break; 
        case 4: play_five_by_five(); break; 
        case 5: play_four_by_four(); break;
        case 6: play_sus(); break;
        case 7: play_word_ttt(); break;
        case 8: play_ultimate_ttt_game(); break;
        case 0:
            cout << "Thank you for playing!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    return 0;

}


