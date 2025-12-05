#ifndef INFINITY_UI_H
#define INFINITY_UI_H

#include "BoardGame_Classes.h" //  „  ⁄œÌ· «”„ «·„·› Â‰« ·Ì ÿ«»ﬁ „⁄ (BoardGame_Classes.h)
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>

class HumanPlayer : public Player<char> {
public:
    HumanPlayer(std::string n, char s) : Player(n, s, PlayerType::HUMAN) {}
};

class AIPlayer : public Player<char> {
public:
    AIPlayer(std::string n, char s) : Player(n, s, PlayerType::AI) {}
};

class InfinityUI : public UI<char> {
private:
    std::pair<int, int> get_ai_move(Player<char>* p);

public:
    InfinityUI();

    Move<char>* get_move(Player<char>* p) override;

    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    Player<char>** setup_players() override;
};

#endif // INFINITY_UI_H