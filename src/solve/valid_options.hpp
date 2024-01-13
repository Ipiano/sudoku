#pragma once

#include "types/board.hpp"
#include "types/index.hpp"
#include "types/tile.hpp"

#include <array>
#include <bitset>

namespace sudoku::solve {
class ValidOptions
{
  public:
    bool is_valid(types::board::Index index, types::Tile option) const;
    std::uint8_t option_count(types::board::Index index) const;

    void add_option(types::board::Index index, types::Tile option);
    void remove_option(types::board::Index index, types::Tile option);

  private:
    static std::size_t hash(types::board::Index ind);

    std::array<std::bitset<10>, 81> _valid_options;
};

ValidOptions valid_options_from_board_state(const types::Board& board);
}  // namespace sudoku::solve
