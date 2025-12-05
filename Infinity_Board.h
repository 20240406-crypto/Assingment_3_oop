#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H

#include "BoardGame_Classes.h" //  „  ⁄œÌ· «”„ «·„·› Â‰« ·Ì ÿ«»ﬁ „⁄ (BoardGame_Classes.h)
#include <vector>
#include <utility> 

class InfinityBoard : public Board<char> {
private:
    std::vector<std::pair<int, int>> move_history;
    const int MAX_MOVES_BEFORE_VANISH = 3;
    const int BOARD_SIZE = 3;

    bool check_win(char symbol);

public:
    InfinityBoard();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* p) override;
    bool is_lose(Player<char>* p) override;
    bool is_draw(Player<char>* p) override;
    bool game_is_over(Player<char>* p) override;
};

#endif // INFINITY_BOARD_H