#ifndef CONNECTFOUR_CLASSES_H
#define CONNECTFOUR_CLASSES_H

#include "BoardGame_Classes.h"

// كلاس اللوحة الخاص بـ Connect Four
class ConnectFour_Board : public Board<char> {
public:
    // الكونستركتور لتحديد الأبعاد (6x7)
    ConnectFour_Board();

    // الدوال الموروثة التي يجب تطبيقها
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

// كلاس الواجهة الخاص بـ Connect Four
class ConnectFour_UI : public UI<char> {
public:
    ConnectFour_UI();

    // دالة لأخذ الحركة من اللاعب (في هذه اللعبة يختار العمود فقط)
    Move<char>* get_move(Player<char>* player) override;

    // دالة لإنشاء اللاعبين
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // دالة لتجهيز اللاعبين والرموز
    Player<char>** setup_players() override;
};

#endif