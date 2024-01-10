#pragma once

#include "error.hpp"

#include <compare>
#include <concepts>
#include <cstdint>

namespace sudoku::types {
class Tile
{
  public:
    template<std::integral T>
    Tile(T value) : _value(static_cast<std::uint8_t>(value))
    {
        SUDOKU_ASSERT(value >= 0 && value <= 9);
    }

    template<std::integral T>
    std::strong_ordering operator<=>(T other) const
    {
        return operator<=>(Tile(other));
    }

    std::strong_ordering operator<=>(const Tile& other) const = default;

  private:
    std::uint8_t _value;
};
}  // namespace sudoku::types
