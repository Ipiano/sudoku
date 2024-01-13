#pragma once

#include "types/index.hpp"

#include <array>

namespace sudoku::utility {
// Get the top-left corner of a sub-box containing an index
constexpr types::board::Index box_index(types::board::Index index)
{
    // Integer rounding shenanigans
    return {index.row() / 3 * 3, index.col() / 3 * 3};
}

// Return all 81 indexes for the board starting at the top-left, going right
constexpr std::array<types::board::Index, 81> board_indices()
{
    std::array<types::board::Index, 81> indices;

    auto index_it = indices.begin();
    for (std::uint8_t i = 0; i < 9; ++i)
    {
        for (std::uint8_t j = 0; j < 9; ++j)
        {
            *index_it++ = {i, j};
        }
    }

    return indices;
}

// Return all 9 indices of a row, starting at the left
constexpr std::array<types::board::Index, 9> row_indices(std::uint8_t row)
{
    std::array<types::board::Index, 9> indices;

    auto index_it = indices.begin();
    for (std::uint8_t i = 0; i < 9; ++i)
    {
        *index_it++ = {row, i};
    }

    return indices;
}

// Return all 9 indices of a column, starting at the top
constexpr std::array<types::board::Index, 9> col_indices(std::uint8_t col)
{
    std::array<types::board::Index, 9> indices;

    auto index_it = indices.begin();
    for (std::uint8_t i = 0; i < 9; ++i)
    {
        *index_it++ = {i, col};
    }

    return indices;
}

// Return all 9 indices of a box, starting at the top-left, going right
constexpr std::array<types::board::Index, 9> box_indices(types::board::Index index)
{
    std::array<types::board::Index, 9> indices;

    auto index_it = indices.begin();

    const auto start = box_index(index);

    for (std::uint8_t i = 0; i < 3; ++i)
    {
        for (std::uint8_t j = 0; j < 3; ++j)
        {
            *index_it++ = {start.row() + i, start.col() + j};
        }
    }

    return indices;
}

}  // namespace sudoku::utility
