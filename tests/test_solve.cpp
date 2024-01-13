#include "solve.hpp"

#include <gtest/gtest.h>

TEST(Sudoku, Solve_FailInvalidBoard)
{
    const auto board = sudoku::types::create_board({
        // clang-format off
        1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    });

    const auto result = sudoku::find_solution(board);
    EXPECT_FALSE(result);
}

TEST(Sudoku, Solve_SucceedSingleEmpty)
{
    const auto complete_board = sudoku::types::create_board({
        // clang-format off
        6, 5, 2, 4, 8, 3, 9, 1, 7,
        9, 7, 8, 1, 6, 2, 4, 3, 5,
        3, 1, 4, 9, 7, 5, 6, 2, 8,
        8, 2, 5, 7, 3, 6, 1, 4, 9,
        7, 9, 1, 8, 2, 4, 5, 6, 3,
        4, 3, 6, 5, 1, 9, 8, 7, 2,
        2, 6, 9, 3, 4, 8, 7, 5, 1,
        5, 4, 7, 2, 9, 1, 3, 8, 6,
        1, 8, 3, 6, 5, 7, 2, 9, 4,
        // clang-format on
    });

    auto unfinished_board = complete_board;
    unfinished_board[{0, 0}] = 0;

    const auto result = sudoku::find_solution(unfinished_board);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, complete_board);
}
