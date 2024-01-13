#include "solve/valid_options.hpp"

#include <gtest/gtest.h>

TEST(Sudoku, ValidOptions_CanSetUnset)
{
    sudoku::solve::ValidOptions options;

    EXPECT_FALSE(options.is_valid({0, 0}, 0));

    options.add_option({0, 0}, 0);

    EXPECT_TRUE(options.is_valid({0, 0}, 0));

    options.remove_option({0, 0}, 0);

    EXPECT_FALSE(options.is_valid({0, 0}, 0));
}

TEST(Sudoku, ValidOptions_BuildFromBoard)
{
    const auto board = sudoku::types::create_board({
        // clang-format off
        1, 2, 3, 0, 0, 0, 0, 0, 0,
        0, 4, 0, 0, 0, 0, 0, 0, 0,
        5, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    });

    auto options = sudoku::solve::valid_options_from_board_state(board);

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_FALSE(options.is_valid({0, i}, 1));
        EXPECT_FALSE(options.is_valid({0, i}, 2));
        EXPECT_FALSE(options.is_valid({0, i}, 3));
        EXPECT_TRUE(options.is_valid({0, i}, 4));
        EXPECT_TRUE(options.is_valid({0, i}, 5));
        EXPECT_TRUE(options.is_valid({0, i}, 6));
        EXPECT_TRUE(options.is_valid({0, i}, 7));
        EXPECT_TRUE(options.is_valid({0, i}, 8));
        EXPECT_TRUE(options.is_valid({0, i}, 9));
    }

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_TRUE(options.is_valid({1, i}, 1));
        EXPECT_TRUE(options.is_valid({1, i}, 2));
        EXPECT_TRUE(options.is_valid({1, i}, 3));
        EXPECT_FALSE(options.is_valid({1, i}, 4));
        EXPECT_TRUE(options.is_valid({1, i}, 5));
        EXPECT_TRUE(options.is_valid({1, i}, 6));
        EXPECT_TRUE(options.is_valid({1, i}, 7));
        EXPECT_TRUE(options.is_valid({1, i}, 8));
        EXPECT_TRUE(options.is_valid({1, i}, 9));
    }

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_TRUE(options.is_valid({2, i}, 1));
        EXPECT_TRUE(options.is_valid({2, i}, 2));
        EXPECT_TRUE(options.is_valid({2, i}, 3));
        EXPECT_TRUE(options.is_valid({2, i}, 4));
        EXPECT_FALSE(options.is_valid({2, i}, 5));
        EXPECT_TRUE(options.is_valid({2, i}, 6));
        EXPECT_TRUE(options.is_valid({2, i}, 7));
        EXPECT_TRUE(options.is_valid({2, i}, 8));
        EXPECT_TRUE(options.is_valid({2, i}, 9));
    }

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_FALSE(options.is_valid({i, 0}, 1));
        EXPECT_TRUE(options.is_valid({i, 0}, 2));
        EXPECT_TRUE(options.is_valid({i, 0}, 3));
        EXPECT_TRUE(options.is_valid({i, 0}, 4));
        EXPECT_FALSE(options.is_valid({i, 0}, 5));
        EXPECT_TRUE(options.is_valid({i, 0}, 6));
        EXPECT_TRUE(options.is_valid({i, 0}, 7));
        EXPECT_TRUE(options.is_valid({i, 0}, 8));
        EXPECT_TRUE(options.is_valid({i, 0}, 9));
    }

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_TRUE(options.is_valid({i, 1}, 1));
        EXPECT_FALSE(options.is_valid({i, 1}, 2));
        EXPECT_TRUE(options.is_valid({i, 1}, 3));
        EXPECT_FALSE(options.is_valid({i, 1}, 4));
        EXPECT_TRUE(options.is_valid({i, 1}, 5));
        EXPECT_TRUE(options.is_valid({i, 1}, 6));
        EXPECT_TRUE(options.is_valid({i, 1}, 7));
        EXPECT_TRUE(options.is_valid({i, 1}, 8));
        EXPECT_TRUE(options.is_valid({i, 1}, 9));
    }

    for (std::uint8_t i = 3; i < 9; ++i)
    {
        SCOPED_TRACE(static_cast<int>(i));

        EXPECT_TRUE(options.is_valid({i, 2}, 1));
        EXPECT_TRUE(options.is_valid({i, 2}, 2));
        EXPECT_FALSE(options.is_valid({i, 2}, 3));
        EXPECT_TRUE(options.is_valid({i, 2}, 4));
        EXPECT_TRUE(options.is_valid({i, 2}, 5));
        EXPECT_TRUE(options.is_valid({i, 2}, 6));
        EXPECT_TRUE(options.is_valid({i, 2}, 7));
        EXPECT_TRUE(options.is_valid({i, 2}, 8));
        EXPECT_TRUE(options.is_valid({i, 2}, 9));
    }

    EXPECT_FALSE(options.is_valid({1, 0}, 1));
    EXPECT_FALSE(options.is_valid({1, 0}, 2));
    EXPECT_FALSE(options.is_valid({1, 0}, 3));
    EXPECT_FALSE(options.is_valid({1, 0}, 4));
    EXPECT_FALSE(options.is_valid({1, 0}, 5));
    EXPECT_TRUE(options.is_valid({1, 0}, 6));
    EXPECT_TRUE(options.is_valid({1, 0}, 7));
    EXPECT_TRUE(options.is_valid({1, 0}, 8));
    EXPECT_TRUE(options.is_valid({1, 0}, 9));

    EXPECT_FALSE(options.is_valid({1, 2}, 1));
    EXPECT_FALSE(options.is_valid({1, 2}, 2));
    EXPECT_FALSE(options.is_valid({1, 2}, 3));
    EXPECT_FALSE(options.is_valid({1, 2}, 4));
    EXPECT_FALSE(options.is_valid({1, 2}, 5));
    EXPECT_TRUE(options.is_valid({1, 2}, 6));
    EXPECT_TRUE(options.is_valid({1, 2}, 7));
    EXPECT_TRUE(options.is_valid({1, 2}, 8));
    EXPECT_TRUE(options.is_valid({1, 2}, 9));

    EXPECT_FALSE(options.is_valid({2, 1}, 1));
    EXPECT_FALSE(options.is_valid({2, 1}, 2));
    EXPECT_FALSE(options.is_valid({2, 1}, 3));
    EXPECT_FALSE(options.is_valid({2, 1}, 4));
    EXPECT_FALSE(options.is_valid({2, 1}, 5));
    EXPECT_TRUE(options.is_valid({2, 1}, 6));
    EXPECT_TRUE(options.is_valid({2, 1}, 7));
    EXPECT_TRUE(options.is_valid({2, 1}, 8));
    EXPECT_TRUE(options.is_valid({2, 1}, 9));

    EXPECT_FALSE(options.is_valid({2, 2}, 1));
    EXPECT_FALSE(options.is_valid({2, 2}, 2));
    EXPECT_FALSE(options.is_valid({2, 2}, 3));
    EXPECT_FALSE(options.is_valid({2, 2}, 4));
    EXPECT_FALSE(options.is_valid({2, 2}, 5));
    EXPECT_TRUE(options.is_valid({2, 2}, 6));
    EXPECT_TRUE(options.is_valid({2, 2}, 7));
    EXPECT_TRUE(options.is_valid({2, 2}, 8));
    EXPECT_TRUE(options.is_valid({2, 2}, 9));
}
