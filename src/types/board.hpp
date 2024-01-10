#pragma once

#include "types/index.hpp"
#include "types/tile.hpp"

#include <vector>

namespace sudoku::types {

//! Sudoku board - indexed by row, column
class Board
{
  public:
    Board();

    Tile& operator[](board::Index index);
    Tile operator[](board::Index index) const;

  private:
    std::vector<std::vector<Tile>> _tiles;
};
}  // namespace sudoku::types
