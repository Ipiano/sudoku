#include "types/tile.hpp"

#include <gtest/gtest.h>

#ifndef NDEBUG
TEST(Sudoku, Tile_InvalidValue)
{
    ASSERT_THROW(sudoku::types::Tile(-1), sudoku::AssertionFailure);
    ASSERT_THROW(sudoku::types::Tile(10), sudoku::AssertionFailure);
}
#endif

TEST(Sudoku, Tile_Comparisons)
{
    EXPECT_EQ(sudoku::types::Tile(0), 0);
    EXPECT_LT(sudoku::types::Tile(3), sudoku::types::Tile(5));
}

TEST(Sudoku, Tile_Assignment)
{
    sudoku::types::Tile t(0);

    t = 4;
    EXPECT_EQ(t, 4);

    t = sudoku::types::Tile(9);
    EXPECT_EQ(t, 9);
}

TEST(Sudoku, Tile_0IsSet)
{
    EXPECT_TRUE(sudoku::types::Tile(1));
    EXPECT_FALSE(sudoku::types::Tile(0));
}
