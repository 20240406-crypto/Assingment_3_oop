#include "Infinity_UI.h"
#include "Infinity_Board.h"

using namespace std;

// --- AI Logic ---
pair<int, int> InfinityUI::get_ai_move(Player<char>* p) {
    Board<char>* board = p->get_board_ptr();
    char ai_symbol = p->get_symbol();
    char opponent_symbol = (ai_symbol == 'X') ? 'O' : 'X';
    int rows = board->get_rows();
    int cols = board->get_columns();

    vector<pair<int, int>> available_moves;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board->get_cell(i, j) == ' ') {
                available_moves.push_back({ i, j });
            }
        }
    }

    if (available_moves.empty()) {
        return { -1, -1 };
    }

    // 1. Check for immediate winning move
    for (const auto& move : available_moves) {
        // Temporarily place the move
        board->get_board_matrix()[move.first][move.second] = ai_symbol;
        if (static_cast<InfinityBoard*>(board)->is_win(p)) {
            board->get_board_matrix()[move.first][move.second] = ' ';
            return move;
        }
        board->get_board_matrix()[move.first][move.second] = ' '; 
    }

    // 2. Block opponent's winning move
    Player<char> opponent("", opponent_symbol, PlayerType::HUMAN);
    for (const auto& move : available_moves) {
        // Temporarily place the opponent's move
        board->get_board_matrix()[move.first][move.second] = opponent_symbol;
        if (static_cast<InfinityBoard*>(board)->is_win(&opponent)) {
            board->get_board_matrix()[move.first][move.second] = ' '; 
            return move;
        }
        board->get_board_matrix()[move.first][move.second] = ' '; 
    }


    if (board->get_cell(1, 1) == ' ') {
        return { 1, 1 };
    }

    // 4. Take a corner randomly
    vector<pair<int, int>> corners = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    random_shuffle(corners.begin(), corners.end());
    for (const auto& corner : corners) {
        if (board->get_cell(corner.first, corner.second) == ' ') {
            return corner;
        }
    }

    // 5. Random move
    int rand_index = rand() % available_moves.size();
    return available_moves[rand_index];
}

// --- UI Implementation ---
InfinityUI::InfinityUI() : UI("Welcome to Infinity Tic-Tac-Toe! The oldest mark vanishes after 3 moves.", 1) {
    srand(time(0));
}

Move<char>* InfinityUI::get_move(Player<char>* p) {
    if (p->get_type() == PlayerType::AI) {
        cout << p->get_name() << " is thinking...\n";
        pair<int, int> coords = get_ai_move(p);

        if (coords.first == -1) {
            // Should not happen if is_draw is checked correctly
            return new Move<char>(0, 0, p->get_symbol());
        }
        return new Move<char>(coords.first, coords.second, p->get_symbol());
    }

    // Human Player
    int x, y;
    cout << p->get_name() << "'s turn (" << p->get_symbol() << "). Enter row and column (e.g., 1 2): ";
    cin >> x >> y;
    return new Move<char>(x, y, p->get_symbol());
}

Player<char>* InfinityUI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::HUMAN) {
        return new HumanPlayer(name, symbol);
    }
    else {
        // Handles both COMPUTER (deprecated) and AI
        return new AIPlayer(name, symbol);
    }
}

Player<char>** InfinityUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "AI/Computer" };

    string nameX = get_player_name("Player X");
    cout << "Choose Player X type:\n";
    for (size_t i = 0; i < type_options.size(); ++i)
        cout << i + 1 << ". " << type_options[i] << "\n";
    int choiceX;
    cin >> choiceX;
    PlayerType typeX = (choiceX == 2) ? PlayerType::AI : PlayerType::HUMAN;
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    cout << "Choose Player O type:\n";
    for (size_t i = 0; i < type_options.size(); ++i)
        cout << i + 1 << ". " << type_options[i] << "\n";
    int choiceO;
    cin >> choiceO;
    PlayerType typeO = (choiceO == 2) ? PlayerType::AI : PlayerType::HUMAN;
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}