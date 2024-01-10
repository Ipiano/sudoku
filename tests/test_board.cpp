#include "error.hpp"
#include "types/board.hpp"

#include <gtest/gtest.h>

TEST(Sudoku, Board_InitZeros)
{
    sudoku::types::Board b;

    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            EXPECT_EQ((b[{i, j}]), 0);
        }
    }
}

TEST(Sudoku, Board_SetValues)
{
    sudoku::types::Board b;

    b[{0, 0}] = 4;
    EXPECT_EQ((b[{0, 0}]), 4);

    b[{4, 2}] = 2;
    EXPECT_EQ((b[{4, 2}]), 2);

    b[{8, 8}] = 9;
    EXPECT_EQ((b[{8, 8}]), 9);
}

TEST(Sudoku, Board_CreateInitSome)
{
    auto b = sudoku::types::create_board({{{0, 0}, 1}, {{3, 3}, 2}, {{7, 1}, 5}});

    EXPECT_EQ((b[{0, 0}]), 1);
    EXPECT_EQ((b[{3, 3}]), 2);
    EXPECT_EQ((b[{7, 1}]), 5);
}

TEST(Sudoku, Board_CreateFull)
{
    auto b = sudoku::types::create_board({
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    });

    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            EXPECT_EQ((b[{i, j}]), 1);
        }
    }
}
