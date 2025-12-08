#ifndef MEMORY_CLASSES_H
#define MEMORY_CLASSES_H

#include "BoardGame_Classes.h"

class Memory_Board : public Board<char> {
protected:
    // This grid stores the ACTUAL moves (X or O).
    // The inherited 'board' variable will store what the user SEES.
    char real_board[3][3];

public:
    Memory_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // Reveals the entire board at the end of the game
    void reveal_board();
};

class Memory_Player : public Player<char> {
public:
    Memory_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::HUMAN) {}
    Memory_Player(char symbol) : Player<char>("Computer", symbol, PlayerType::COMPUTER) {}
};

class Memory_UI : public UI<char> {
public:
    Memory_UI(string msg = "Welcome to Memory Tic-Tac-Toe") : UI<char>(msg, 3) {}

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    // Custom display to show the grid cleanly
    void display_board(Board<char>& b);
};

#endif