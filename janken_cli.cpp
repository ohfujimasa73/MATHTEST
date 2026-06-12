#include "janken.h"

#include <iostream>

int main()
{
    Janken game;
    int player_input = -1;

    std::cout << "じゃんけんプログラム\n";
    std::cout << "0: グー  1: チョキ  2: パー\n";
    std::cout << "あなたの手を入力してください: ";
    std::cin >> player_input;

    Janken::Hand player;
    if (!std::cin || !Janken::try_parse_hand(player_input, player)) {
        std::cerr << "0 から 2 の数値を入力してください。\n";
        return 1;
    }

    Janken::Hand computer = game.generate_computer_hand();
    int result = Janken::judge(player, computer);

    std::cout << "あなた: " << Janken::hand_name(player) << "\n";
    std::cout << "コンピューター: " << Janken::hand_name(computer) << "\n";

    if (result == 0) {
        std::cout << "結果: あいこです。\n";
    } else if (result > 0) {
        std::cout << "結果: あなたの勝ちです。\n";
    } else {
        std::cout << "結果: あなたの負けです。\n";
    }

    return 0;
}
