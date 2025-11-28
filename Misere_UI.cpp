#include "Misere_UI.h"
#include <iostream>
using namespace std;

Misere_UI::Misere_UI()
    : UI("Welcome to Misere Tic Tac Toe!", 1) {
}

//-----------------------------------------------------
// Create Player
//-----------------------------------------------------
Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type)
{
    // Player Template „ÊÃÊœ »«·›⁄· ›Ì «·›—Ì„Ê—ﬂ
    // ›·«“„ ‰” Œœ„Â ﬂ„« ÂÊ
    return new Player<char>(name, symbol, type);
}

//-----------------------------------------------------
// Get Move (Human OR Computer)
//-----------------------------------------------------
Move<char>* Misere_UI::get_move(Player<char>* player)
{
    if (player->get_type() == PlayerType::COMPUTER)
    {
        // Computer chooses first empty cell found
        auto matrix = player->get_board_ptr()->get_board_matrix();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (matrix[i][j] == '.')
                {
                    cout << player->get_name() << " (Computer) plays: "
                        << i << " " << j << endl;

                    return new Move<char>(i, j, player->get_symbol());
                }
            }
        }
    }

    //-----------------------------------------------------
    // HUMAN MOVE
    //-----------------------------------------------------
    int r, c;
    cout << player->get_name() << " (" << player->get_symbol()
        << ") enter your move (row and col 0ñ2): ";
    cin >> r >> c;

    return new Move<char>(r, c, player->get_symbol());
}