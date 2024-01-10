#include "solve/solve_impl.hpp"
#include "types/board.hpp"

#include <gtest/gtest.h>

using sudoku::types::create_board;

TEST(Sudoku, Solve_IsValidFails)
{
    // List of invalid case
    std::vector<sudoku::types::Board> cases{
        // Duplicates in a sub-square
        create_board({{{0, 0}, 1}, {{1, 1}, 1}}),
        create_board({{{0, 3}, 2}, {{2, 5}, 2}}),
        create_board({{{0, 6}, 3}, {{2, 7}, 3}}),
        create_board({{{3, 0}, 4}, {{4, 2}, 4}}),
        create_board({{{3, 3}, 5}, {{4, 4}, 5}}),
        create_board({{{4, 6}, 6}, {{3, 8}, 6}}),
        create_board({{{6, 0}, 7}, {{7, 1}, 7}}),
        create_board({{{7, 3}, 8}, {{8, 4}, 8}}),
        create_board({{{8, 6}, 9}, {{6, 8}, 9}}),

        // Duplicates in a row
        create_board({{{0, 0}, 1}, {{0, 3}, 1}}),
        create_board({{{1, 3}, 2}, {{1, 1}, 2}}),
        create_board({{{2, 6}, 3}, {{2, 3}, 3}}),
        create_board({{{3, 0}, 4}, {{3, 7}, 4}}),
        create_board({{{4, 3}, 5}, {{4, 6}, 5}}),
        create_board({{{5, 6}, 6}, {{5, 3}, 6}}),
        create_board({{{6, 0}, 7}, {{6, 8}, 7}}),
        create_board({{{7, 3}, 8}, {{7, 1}, 8}}),
        create_board({{{8, 6}, 9}, {{8, 5}, 9}}),

        // Duplicates in a column
        create_board({{{0, 0}, 1}, {{3, 0}, 1}}),
        create_board({{{0, 1}, 2}, {{7, 1}, 2}}),
        create_board({{{0, 2}, 3}, {{4, 2}, 3}}),
        create_board({{{3, 3}, 4}, {{1, 3}, 4}}),
        create_board({{{3, 4}, 5}, {{8, 4}, 5}}),
        create_board({{{4, 5}, 6}, {{2, 5}, 6}}),
        create_board({{{6, 6}, 7}, {{5, 6}, 7}}),
        create_board({{{7, 7}, 8}, {{2, 7}, 8}}),
        create_board({{{8, 8}, 9}, {{4, 8}, 9}}),
    };

    std::size_t i = 0;
    for (const auto& c : cases)
    {
        SCOPED_TRACE(i++);
        EXPECT_FALSE(sudoku::solve::is_valid(c));
    }
}

TEST(Sudoku, Solve_IsValidSuccess)
{
    // Taken from https://github.com/t-dillon/tdoku/blob/master/test/test_puzzles
    auto valid_board = create_board({
        6, 5, 2, 4, 8, 3, 9, 1, 7, 9, 7, 8, 1, 6, 2, 4, 3, 5, 3, 1, 4, 9, 7, 5, 6, 2, 8,
        8, 2, 5, 7, 3, 6, 1, 4, 9, 7, 9, 1, 8, 2, 4, 5, 6, 3, 4, 3, 6, 5, 1, 9, 8, 7, 2,
        2, 6, 9, 3, 4, 8, 7, 5, 1, 5, 4, 7, 2, 9, 1, 3, 8, 6, 1, 8, 3, 6, 5, 7, 2, 9, 4,
    });

    EXPECT_TRUE(sudoku::solve::is_valid(valid_board));
}
