#ifndef JANKEN_H
#define JANKEN_H

#include <random>

class Janken {
public:
    enum class Hand {
        ROCK = 0,
        SCISSORS = 1,
        PAPER = 2,
    };

    Janken();
    explicit Janken(unsigned int seed);

    void set_seed(unsigned int seed);
    Hand generate_computer_hand();

    static const char* hand_name(Hand hand);
    static int judge(Hand player, Hand computer);
    static bool try_parse_hand(int value, Hand& out);
    static int to_int(Hand hand);

private:
    std::mt19937 engine_;
    std::uniform_int_distribution<int> distribution_;
};

#endif
