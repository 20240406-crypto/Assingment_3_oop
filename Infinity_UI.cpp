#include "Infinity_UI.h"

InfinityUI::InfinityUI()
    : UI<char>("=== Infinity Tic-Tac-Toe (AI) ===", 3) {
    display_message("Rules:");
    display_message("- Board is 3x3");
    display_message("- Each player keeps only 3 moves");
    display_message("- 4th move deletes the oldest one");
    display_message("- First to align 3 wins\n");
}

// ================= HELPERS =================
bool InfinityUI::is_winning_move(Board<char>* b, char s, int x, int y) {

    if (b->get_cell(x, y) != ' ') return false;

    // simulate
    char backup = b->get_cell(x, y);
    const_cast<vector<vector<char>>&>(b->get_board_matrix())[x][y] = s;

    bool win =
        (b->get_cell(x, 0) == s && b->get_cell(x, 1) == s && b->get_cell(x, 2) == s) ||
        (b->get_cell(0, y) == s && b->get_cell(1, y) == s && b->get_cell(2, y) == s) ||
        (x == y && b->get_cell(0, 0) == s && b->get_cell(1, 1) == s && b->get_cell(2, 2) == s) ||
        (x + y == 2 && b->get_cell(0, 2) == s && b->get_cell(1, 1) == s && b->get_cell(2, 0) == s);

    // undo
    const_cast<vector<vector<char>>&>(b->get_board_matrix())[x][y] = backup;

    return win;
}

// ================= AI MOVE =================
Move<char>* InfinityUI::get_ai_move(Player<char>* p) {

    Board<char>* b = p->get_board_ptr();
    char me = p->get_symbol();
    char enemy = (me == 'X') ? 'O' : 'X';

    // 1️⃣ win
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (is_winning_move(b, me, i, j))
                return new Move<char>(i, j, me);

    // 2️⃣ block
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (is_winning_move(b, enemy, i, j))
                return new Move<char>(i, j, me);

    // 3️⃣ center
    if (b->get_cell(1, 1) == ' ')
        return new Move<char>(1, 1, me);

    // 4️⃣ corners
    int corners[4][2] = { {0,0},{0,2},{2,0},{2,2} };
    for (auto& c : corners)
        if (b->get_cell(c[0], c[1]) == ' ')
            return new Move<char>(c[0], c[1], me);

    // 5️⃣ any empty
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b->get_cell(i, j) == ' ')
                return new Move<char>(i, j, me);

    return nullptr;
}

// ================= UI =================
Move<char>* InfinityUI::get_move(Player<char>* p) {

    if (p->get_type() == PlayerType::COMPUTER) {
        cout << p->get_name() << " (AI) is thinking...\n";
        return get_ai_move(p);
    }

    int x, y;
    cout << p->get_name() << " (" << p->get_symbol() << ") enter row col: ";
    cin >> x >> y;
    return new Move<char>(x, y, p->get_symbol());
}

Player<char>* InfinityUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
