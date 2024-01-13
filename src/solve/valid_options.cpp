#include "solve/valid_options.hpp"

#include "types/board.hpp"
#include "utility/indices.hpp"

namespace sudoku::solve {

bool ValidOptions::is_valid(types::board::Index index, types::Tile option) const
{
    return _valid_options[hash(index)].test(option.value());
}

std::uint8_t ValidOptions::option_count(types::board::Index index) const
{
    return _valid_options[hash(index)].count();
}

void ValidOptions::add_option(types::board::Index index, types::Tile option)
{
    _valid_options[hash(index)].set(option.value());
}

void ValidOptions::remove_option(types::board::Index index, types::Tile option)
{
    _valid_options[hash(index)].reset(option.value());
}

std::size_t ValidOptions::hash(types::board::Index ind)
{
    return ind.row() * 9 + ind.col();
}

ValidOptions valid_options_from_board_state(const types::Board& board)
{
    ValidOptions result;

    // Mark 0-9 valid for all empty spaces
    for (const auto index : utility::board_indices())
    {
        if (!board[index])
        {
            for (std::uint8_t i = 1; i <= 9; ++i)
            {
                result.add_option(index, i);
            }
        }
    }

    // Update all row/column/box items for each non-empty space
    for (const auto index : utility::board_indices())
    {
        if (board[index])
        {
            const auto target_value = board[index];

            // Save to "remove_option" for the space we're looking at itself, because it
            // won't be in the valid options anyway, as it's not empty
            for (const auto adjacent_index : utility::row_indices(index.row()))
            {
                result.remove_option(adjacent_index, target_value);
            }

            for (const auto adjacent_index : utility::col_indices(index.col()))
            {
                result.remove_option(adjacent_index, target_value);
            }

            for (const auto adjacent_index : utility::box_indices(index))
            {
                result.remove_option(adjacent_index, target_value);
            }
        }
    }

    return result;
}
}  // namespace sudoku::solve
