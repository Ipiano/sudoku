#pragma once

#include "error.hpp"

#include <concepts>
#include <cstdint>

namespace sudoku::types::board {
class Index
{
  public:
    template<std::integral T, std::integral U>
    Index(T row, U col) : _row(static_cast<std::uint8_t>(row)), _col(static_cast<std::uint8_t>(col))
    {
        SUDOKU_ASSERT(row >= 0 && row < 9);
        SUDOKU_ASSERT(col >= 0 && col < 9);
    }

    std::uint8_t row() const { return _row; }
    std::uint8_t col() const { return _col; }

  private:
    std::uint8_t _row;
    std::uint8_t _col;
};
}  // namespace sudoku::types::board
