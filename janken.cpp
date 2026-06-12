#include "janken.h"

#include <ctime>

Janken::Janken(unsigned int seed)
    : engine_(seed), distribution_(0, 2)
{
}

Janken::Janken()
    : Janken(static_cast<unsigned int>(std::time(nullptr)))
{
}

void Janken::set_seed(unsigned int seed)
{
    engine_.seed(seed);
}

Janken::Hand Janken::generate_computer_hand()
{
    return static_cast<Hand>(distribution_(engine_));
}

const char* Janken::hand_name(Hand hand)
{
    switch (hand) {
    case Hand::ROCK:
        return "グー";
    case Hand::SCISSORS:
        return "チョキ";
    case Hand::PAPER:
        return "パー";
    default:
        return "不明";
    }
}

int Janken::judge(Hand player, Hand computer)
{
    if (player == computer) {
        return 0;
    }

    if ((player == Hand::ROCK && computer == Hand::SCISSORS) ||
        (player == Hand::SCISSORS && computer == Hand::PAPER) ||
        (player == Hand::PAPER && computer == Hand::ROCK)) {
        return 1;
    }

    return -1;
}

bool Janken::try_parse_hand(int value, Hand& out)
{
    if (value < 0 || value > 2) {
        return false;
    }

    out = static_cast<Hand>(value);
    return true;
}

int Janken::to_int(Hand hand)
{
    return static_cast<int>(hand);
}