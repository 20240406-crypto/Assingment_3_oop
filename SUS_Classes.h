#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"

class SUS_Board : public Board<char> {
private:
    int player_scores[2];

public:
    SUS_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int count_sus(int r, int c);
    int get_score(int player_index) { return player_scores[player_index]; }
};

class SUS_UI : public UI<char> {
public:
    SUS_UI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // NEW: Override setup_players to assign fixed 'S' and 'U' symbols
    Player<char>** setup_players() override;
};

#endif