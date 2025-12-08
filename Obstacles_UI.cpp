#include "Obstacles_UI.h"
#include "Obstacles_Board.h" // ‰Õ «ÃÂ ·⁄„· Casting
#include <iostream>
#include <limits> 
#include <cstdlib>

using namespace std;

Obstacles_UI::Obstacles_UI()
    : UI("Welcome to Obstacles Tic Tac Toe! (6x6, 4 in row)", 1) {
}

Player<char>* Obstacles_UI::create_player(string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}

Move<char>* Obstacles_UI::get_move(Player<char>* player)
{
    // --- œÊ— «·ﬂ„»ÌÊ — «·–ﬂÌ ---
    if (player->get_type() == PlayerType::COMPUTER)
    {
        Obstacles_Board* b = static_cast<Obstacles_Board*>(player->get_board_ptr());
        char cpu = player->get_symbol();
        char human = (cpu == 'X') ? 'O' : 'X';

        // 1. Â· Ì„ﬂ‰‰Ì «·›Ê“ «·¬‰ø (Winning Move)
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (b->get_cell(i, j) == ' ') { // „ﬂ«‰ ›«—€
                    Obstacles_Board temp = *b; // ‰”Œ
                    Move<char> m(i, j, cpu);
                    temp.update_board(&m);
                    if (temp.is_win(player)) {
                        cout << player->get_name() << " (AI-Win) plays: " << i << " " << j << endl;
                        return new Move<char>(i, j, cpu);
                    }
                }
            }
        }

        // 2. Â· «·Œ’„ ”Ì›Ê“ø ÌÃ» „‰⁄Â (Blocking Move)
        Player<char> enemy("Enemy", human, PlayerType::HUMAN);
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (b->get_cell(i, j) == ' ') {
                    Obstacles_Board temp = *b; // ‰”Œ
                    Move<char> m(i, j, human);
                    temp.update_board(&m); // Ã—» Õ—ﬂ… «·Œ’„
                    if (temp.is_win(&enemy)) {
                        cout << player->get_name() << " (AI-Block) plays: " << i << " " << j << endl;
                        return new Move<char>(i, j, cpu); // «·⁄» Â‰« ·„‰⁄Â
                    }
                }
            }
        }

        // 3. «··⁄» «·⁄‘Ê«∆Ì ›Ì „ﬂ«‰ ›«—€
        int r, c;
        int attempts = 0;
        do {
            r = rand() % 6;
            c = rand() % 6;
            attempts++;
            if (attempts > 500) break; // √„«‰ ÷œ «·Õ·ﬁ… «··«‰Â«∆Ì…
        } while (b->get_cell(r, c) != ' ');

        cout << player->get_name() << " (AI-Random) plays: " << r << " " << c << endl;
        return new Move<char>(r, c, cpu);
    }

    // --- œÊ— «·»‘— ---
    int r, c;
    while (true) {
        cout << player->get_name() << " (" << player->get_symbol()
            << ") enter your move (row and col 0ñ5): ";
        if (!(cin >> r >> c)) {
            cout << "Invalid input.\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (r >= 0 && r <= 5 && c >= 0 && c <= 5) break;
        cout << "Invalid move (out of bounds).\n";
    }

    return new Move<char>(r, c, player->get_symbol());
}