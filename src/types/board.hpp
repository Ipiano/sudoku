#pragma once

#include "types/index.hpp"
#include "types/tile.hpp"

#include <array>
#include <initializer_list>
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

// Create a board, and set some arbitrary set of tiles to specific values
Board create_board(std::initializer_list<std::pair<board::Index, Tile>> initial_tiles);

// Create a board, and specify values for all tiles; in order (0, 0), (0, 1), (0, 2)...
Board create_board(std::array<Tile, 81> initial_tiles);

}  // namespace sudoku::types
