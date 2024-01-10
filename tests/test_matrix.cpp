#include "solve/adjacency_matrix.hpp"
#include "types/index.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using sudoku::types::board::Index;

TEST(Sudoku, AdjacencyMatrix_Init)
{
    sudoku::solve::AdjacencyMatrix matrix;

    const auto range = matrix.links({0, 0});
    EXPECT_EQ(range.begin(), range.end());
}

TEST(Sudoku, AdjacencyMatrix_AddLinks)
{
    sudoku::solve::AdjacencyMatrix matrix;

    matrix.add({0, 0}, {0, 1});

    auto range = matrix.links({0, 0});
    EXPECT_EQ(std::distance(range.begin(), range.end()), 1);
    EXPECT_EQ(*range.begin(), Index(0, 1));

    matrix.add({0, 0}, {0, 2});

    range = matrix.links({0, 0});
    EXPECT_EQ(std::distance(range.begin(), range.end()), 2);
    EXPECT_EQ(*range.begin(), Index(0, 1));
    EXPECT_EQ(*(range.begin() + 1), Index(0, 2));
}

TEST(Sudoku, AdjacencyMatrix_AddLinksFromEmptys)
{
    const auto board = sudoku::types::create_board({
        // clang-format off
        1, 1, 0, 1, 1, 0, 1, 1, 1,
        1, 1, 0, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 0, 1, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 0, 1,
        1, 1, 0, 1, 1, 1, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        // clang-format on
    });

    const auto matrix = sudoku::solve::adjacency_matrix_from_open_spaces(board);

    auto range = matrix.links({0, 2});
    ASSERT_EQ(std::distance(range.begin(), range.end()), 4);

    EXPECT_THAT(
        range, ::testing::UnorderedElementsAre(Index(0, 5), Index(1, 2), Index(2, 1), Index(7, 2)));

    range = matrix.links({6, 1});
    ASSERT_EQ(std::distance(range.begin(), range.end()), 3);

    EXPECT_THAT(range, ::testing::UnorderedElementsAre(Index(7, 2), Index(2, 1), Index(6, 7)));
}

TEST(Sudoku, AdjacencyMatrix_AddLinksFromEmptyBoard)
{
    const sudoku::types::Board board;
    const auto matrix = sudoku::solve::adjacency_matrix_from_open_spaces(board);

    // All items should have 20 adjacent spaces
    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            auto range = matrix.links({i, j});
            EXPECT_EQ(std::distance(range.begin(), range.end()), 20);
        }
    }
}
