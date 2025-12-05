#ifndef NUMERICT3_CLASSES_H
#define NUMERICT3_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <map>

using namespace std;

class Numeric_Board : public Board<int> {
private:
    map<int, vector<int>> available_nums;

public:
    Numeric_Board();

    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool is_lose(Player<int>*) override { return false; };
    bool game_is_over(Player<int>* player) override;

    bool is_num_available(int num, int player_symbol);
    void use_num(int num);
    vector<int> get_available_nums_for(int player_symbol);
    void print_available_nums(int player_symbol);
};

class Numeric_UI : public UI<int> {
public:
    Numeric_UI();
    ~Numeric_UI() {};

    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    virtual Move<int>* get_move(Player<int>* player) override;
    Player<int>** setup_players() override;
};

#endif // NUMERICT3_CLASSES_H