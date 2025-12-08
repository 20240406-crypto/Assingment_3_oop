#include "Misere_UI.h"
#include "Misere_Board.h"
#include <iostream>
#include <limits>
#include <algorithm> // for max and min

using namespace std;

Misere_UI::Misere_UI() : UI("Welcome to Misere Tic Tac Toe! (To win, force opponent to make 3-in-a-row)", 1) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

int minimax_algo(Misere_Board b, int depth, bool isMax, char cpuSym, char humanSym) {
    Player<char> cpu("CPU", cpuSym, PlayerType::COMPUTER);
    Player<char> human("Human", humanSym, PlayerType::HUMAN);

    // ‘—Êÿ «· Êﬁ› (Base Cases)
    // ›Ì Misere: ·Ê «··«⁄» «·Õ«·Ì Œ”—«‰° Ì»ﬁÏ «·Œ’„ ﬂ”»«‰
    if (b.is_lose(&cpu)) return -10 + depth; // «·ﬂ„»ÌÊ — Œ”—
    if (b.is_lose(&human)) return 10 - depth; // «·»‘— Œ”— (Ì⁄‰Ì «·ﬂ„»ÌÊ — ﬂ”»)

    // ›Õ’ «· ⁄«œ· ÌœÊÌ« ·√‰ œ«·… is_draw «·√’·Ì… ﬁœ  ⁄ „œ ⁄·Ï ⁄œœ «·Õ—ﬂ«  «·√’·Ì
    bool isFull = true;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b.get_cell(i, j) == '.') isFull = false;

    if (isFull) return 0; //  ⁄«œ·

    if (isMax) { // œÊ— «·ﬂ„»ÌÊ — ( ⁄ŸÌ„ «·„ﬂ”»)
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.get_cell(i, j) == '.') {
                    Misere_Board next_board = b; // ‰”Œ… · Ã—»… «·Õ—ﬂ…
                    Move<char> m(i, j, cpuSym);
                    next_board.update_board(&m);

                    best = max(best, minimax_algo(next_board, depth + 1, false, cpuSym, humanSym));
                }
            }
        }
        return best;
    }
    else { // œÊ— «·»‘— ( ﬁ·Ì· „ﬂ”» «·ﬂ„»ÌÊ —)
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (b.get_cell(i, j) == '.') {
                    Misere_Board next_board = b; // ‰”Œ… · Ã—»… «·Õ—ﬂ…
                    Move<char> m(i, j, humanSym);
                    next_board.update_board(&m);

                    best = min(best, minimax_algo(next_board, depth + 1, true, cpuSym, humanSym));
                }
            }
        }
        return best;
    }
}

Move<char>* Misere_UI::get_move(Player<char>* player)
{
    // --- œÊ— «·ﬂ„»ÌÊ — (AI) ---
    if (player->get_type() == PlayerType::COMPUTER) {
        Misere_Board* originalBoard = static_cast<Misere_Board*>(player->get_board_ptr());
        char cpuSym = player->get_symbol();
        char humanSym = (cpuSym == 'X') ? 'O' : 'X';

        int bestVal = -1000;
        int bestX = -1, bestY = -1;

        //  Ã—»… Ã„Ì⁄ «·Œ·«Ì« «·›«—€… Ê«Œ Ì«— «·√›÷·
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (originalBoard->get_cell(i, j) == '.') {
                    Misere_Board tempBoard = *originalBoard; // ‰”Œ «··ÊÕ…
                    Move<char> m(i, j, cpuSym);
                    tempBoard.update_board(&m);

                    int moveVal = minimax_algo(tempBoard, 0, false, cpuSym, humanSym);

                    if (moveVal > bestVal) {
                        bestVal = moveVal;
                        bestX = i;
                        bestY = j;
                    }
                }
            }
        }

        // ›Ì Õ«·… ‰«œ—… (»œ«Ì… «··⁄»… „À·« √Ê Œÿ√ „«)° ‰Œ «— √Ê· „ﬂ«‰ ›«—€
        if (bestX == -1) {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (originalBoard->get_cell(i, j) == '.') { bestX = i; bestY = j; goto end_search; }
        }
    end_search:

        cout << player->get_name() << " (AI) plays: " << bestX << " " << bestY << endl;
        return new Move<char>(bestX, bestY, cpuSym);
    }

    // --- œÊ— «·»‘— (Human) ---
    int r, c;
    cout << "\n" << player->get_name() << " (" << player->get_symbol()
        << ") enter move (row col): ";
    while (!(cin >> r >> c) || r < 0 || r > 2 || c < 0 || c > 2) {
        cout << "Invalid input. Try again (0-2): ";
        cin.clear(); cin.ignore(10000, '\n');
    }
    return new Move<char>(r, c, player->get_symbol());
}