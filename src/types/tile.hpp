#pragma once

#include "error.hpp"

#include <compare>
#include <concepts>
#include <cstdint>

namespace sudoku::types {

//! Tile on the sudoku board. Can be 0-9 where 0 represents unset
class Tile
{
  public:
    template<std::integral T>
    Tile(T value) : _value(static_cast<std::uint8_t>(value))
    {
        SUDOKU_ASSERT(value >= 0 && value <= 9);
    }

    std::strong_ordering operator<=>(const Tile& other) const = default;

    explicit operator bool() const { return _value != 0; }
    std::uint8_t value() const { return _value; }

  private:
    std::uint8_t _value;
};
}  // namespace sudoku::types
