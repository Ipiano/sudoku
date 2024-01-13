#pragma once

#include "error.hpp"

#include <concepts>
#include <cstdint>

namespace sudoku::types::board {
class Index
{
  public:
    constexpr Index() : Index(0, 0){};

    template<std::integral T, std::integral U>
    constexpr Index(T row, U col) :
        _row(static_cast<std::uint8_t>(row)), _col(static_cast<std::uint8_t>(col))
    {
        SUDOKU_ASSERT(row >= 0 && row < 9);
        SUDOKU_ASSERT(col >= 0 && col < 9);
    }

    constexpr std::uint8_t row() const { return _row; }
    constexpr std::uint8_t col() const { return _col; }

    constexpr bool operator==(const Index& other) const = default;
    constexpr bool operator!=(const Index& other) const = default;

  private:
    std::uint8_t _row;
    std::uint8_t _col;
};
}  // namespace sudoku::types::board
