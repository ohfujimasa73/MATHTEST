#include <gtest/gtest.h>

#include "janken.h"

namespace {

using Hand = Janken::Hand;

TEST(JankenTest, HandNameMapping) {
    EXPECT_STREQ("グー", Janken::hand_name(Hand::ROCK));
    EXPECT_STREQ("チョキ", Janken::hand_name(Hand::SCISSORS));
    EXPECT_STREQ("パー", Janken::hand_name(Hand::PAPER));
}

TEST(JankenTest, JudgeExhaustiveMatrix) {
    const Hand hands[] = {Hand::ROCK, Hand::SCISSORS, Hand::PAPER};
    const int expected[3][3] = {
        {0, 1, -1},
        {-1, 0, 1},
        {1, -1, 0},
    };

    for (int p = 0; p < 3; ++p) {
        for (int c = 0; c < 3; ++c) {
            EXPECT_EQ(expected[p][c], Janken::judge(hands[p], hands[c]))
                << "player=" << p << ", computer=" << c;
        }
    }
}

TEST(JankenTest, TryParseHandValidValues) {
    Hand out = Hand::ROCK;

    EXPECT_TRUE(Janken::try_parse_hand(0, out));
    EXPECT_EQ(Hand::ROCK, out);

    EXPECT_TRUE(Janken::try_parse_hand(1, out));
    EXPECT_EQ(Hand::SCISSORS, out);

    EXPECT_TRUE(Janken::try_parse_hand(2, out));
    EXPECT_EQ(Hand::PAPER, out);
}

TEST(JankenTest, TryParseHandInvalidValues) {
    Hand out = Hand::ROCK;

    EXPECT_FALSE(Janken::try_parse_hand(-1, out));
    EXPECT_FALSE(Janken::try_parse_hand(3, out));
    EXPECT_FALSE(Janken::try_parse_hand(999, out));
}

TEST(JankenTest, ToIntMapping) {
    EXPECT_EQ(0, Janken::to_int(Hand::ROCK));
    EXPECT_EQ(1, Janken::to_int(Hand::SCISSORS));
    EXPECT_EQ(2, Janken::to_int(Hand::PAPER));
}

TEST(JankenTest, GenerateComputerHandSameSeedProducesSameSequence) {
    constexpr unsigned int seed = 123456789u;
    Janken a(seed);
    Janken b(seed);

    for (int i = 0; i < 100; ++i) {
        const Hand ha = a.generate_computer_hand();
        const Hand hb = b.generate_computer_hand();
        EXPECT_EQ(ha, hb) << "index=" << i;
    }
}

}  // namespace
