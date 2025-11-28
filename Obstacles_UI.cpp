#include "Obstacles_UI.h"
#include <iostream>
#include <limits> 

using namespace std;

Obstacles_UI::Obstacles_UI()
    : UI("Welcome to Obstacles Tic Tac Toe! (6x6, 4 in row, 2 obstacles added each turn)", 1) {
}

// ÏÇáÉ ÅäÔÇÁ ÇááÇÚÈ: íÌÈ Ãä íÊã ÊÍÏíÏ äæÚ ÇááÇÚÈ ÈÔßá ÕÍíÍ ÚäÏ ÇáÇÓÊÏÚÇÁ
Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type)
{
    // íÊã ÅäÔÇÁ ÇááÇÚÈ åäÇ ÈÇÓÊÎÏÇã ÇáäæÚ ÇáĞí Êã ÇÎÊíÇÑå (HUMAN Ãæ COMPUTER)
    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_UI::get_move(Player<char>* player)
{
    // ------------------------------------------------------------------
    // 1. ãäØŞ ÇáßãÈíæÊÑ: ÅĞÇ ßÇä äæÚ ÇááÇÚÈ åæ COMPUTER¡ íáÚÈ ÊáŞÇÆíÇğ
    // ------------------------------------------------------------------
    if (player->get_type() == PlayerType::COMPUTER)
    {
        // ÇáßãÈíæÊÑ íÈÍË Úä Ãæá ÎáíÉ İÇÑÛÉ '.' Ãæ ' ' ÍÓÈ ãÇ Êã ÇÎÊíÇÑå
        auto matrix = player->get_board_ptr()->get_board_matrix();
        char blank_symbol = player->get_board_ptr()->get_board_matrix()[0][0]; // íİÊÑÖ Ãä ÇáÎáíÉ ÇáÃæáì ÊÍãá ÑãÒ ÇáİÑÇÛ Ãæ ÇáÚÇÆŞ

        // äÈÍË Úä Ãí ÎáíÉ íãßä ÇááÚÈ İíåÇ
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                // ÅĞÇ ßÇäÊ ÇáÎáíÉ áíÓÊ X æáíÓÊ O æáíÓÊ # (ÚÇÆŞ)
                if (matrix[i][j] != 'X' && matrix[i][j] != 'O' && matrix[i][j] != '#')
                {
                    cout << player->get_name() << " (Computer) plays: "
                        << i << " " << j << endl;

                    return new Move<char>(i, j, player->get_symbol());
                }
            }
        }
        // İí ÍÇáÉ ÚÏã æÌæÏ Ãí ÍÑßÉ ãÊÇÍÉ (áÇ íäÈÛí Ãä íÍÏË ÅĞÇ ßÇäÊ ÇááÚÈÉ ÊÚãá ÈÔßá ÕÍíÍ)
        return nullptr;
    }

    // ------------------------------------------------------------------
    // 2. ãäØŞ ÇááÇÚÈ ÇáÈÔÑí (íÖãä ÅÏÎÇá ÃÑŞÇã ÕÍíÍÉ Öãä ÇáÍÏæÏ)
    // ------------------------------------------------------------------
    int r, c;

    while (true) {
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter your move (row and col 0–5): ";

        if (!(cin >> r >> c)) {
            cout << "!! Error: Invalid input type. Please enter two numbers.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (r >= 0 && r <= 5 && c >= 0 && c <= 5) {
            break;
        }
        else {
            cout << "!! Invalid move: Row and column must be between 0 and 5.\n";
        }
    }

    return new Move<char>(r, c, player->get_symbol());
}