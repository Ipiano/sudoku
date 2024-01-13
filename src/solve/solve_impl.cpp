#include "solve/solve_impl.hpp"

#include "error.hpp"
#include "solve/adjacency_matrix.hpp"
#include "solve/valid_options.hpp"
#include "types/index.hpp"
#include "utility/indices.hpp"

#include <bitset>

namespace sudoku::solve {

// Return true if the board has been filled
// Otherwise
//   Find empty tile with fewest options
//   For each option
//     Fill tile
//     Mark that value invalid in neighbors
//     Recurse (check for completion)
//     Unmark value in neighbors
bool recursive_solve(types::Board& board_state,
                     std::vector<types::board::Index>& empty_tiles,
                     ValidOptions& valid_options,
                     const AdjacencyMatrix& adj_matrix);

std::optional<types::Board> solve_impl(types::Board input)
{
    // Make sure we haven't been giving a failing board to start
    if (!is_valid(input))
    {
        return std::nullopt;
    }

    // Build the adjacency matrix for open spaces. This contains links between
    // all the spaces open on the board to begin with that can affect each
    // other.
    const auto adj_matrix = adjacency_matrix_from_open_spaces(input);

    // Build the "valid options" table. This represents, for each of the tiles
    // that's open at the beginning, what are all the numbers you could
    // potentially set it to. We update this as we recurse up and down the
    // search tree so that it's trivial to know what options are valid to fill
    // spaces with.
    auto options = valid_options_from_board_state(input);

    // Build out a list of the tiles we might need to recurse through. As we step in and out
    // of tiles, they'll be added and removed from this list. But that should be cheap to do
    // because it's shuffling around like 200 bytes without any allocations
    auto empties = empty_list(input);

    const auto original = input;
    if (recursive_solve(input, empties, options, adj_matrix))
    {
        SUDOKU_ASSERT(is_valid(input));
        SUDOKU_ASSERT([input] {
            for (const auto index : utility::board_indices())
            {
                if (!input[index])
                {
                    return false;
                }
            }
            return true;
        }());
        SUDOKU_ASSERT(([original, input] {
            for (const auto index : utility::board_indices())
            {
                if (original[index] && original[index] != input[index])
                {
                    return false;
                }
            }
            return true;
        }()));

        static_cast<void>(original);
        return input;
    }

    return std::nullopt;
}

bool is_valid(types::Board input)
{
    std::array<std::bitset<10>, 9> rows;
    std::array<std::bitset<10>, 9> cols;
    std::array<std::bitset<10>, 9> boxes;

    const auto box_bitset_ind = [](types::board::Index index) {
        return index.row() / 3 * 3 + index.col() / 3;
    };

    for (const auto index : utility::board_indices())
    {
        if (input[index])
        {
            const auto target_value = input[index].value();

            if (rows[index.row()].test(target_value))
            {
                return false;
            }
            rows[index.row()].set(target_value);

            if (cols[index.col()].test(target_value))
            {
                return false;
            }
            cols[index.col()].set(target_value);

            if (boxes[box_bitset_ind(index)].test(target_value))
            {
                return false;
            }
            boxes[box_bitset_ind(index)].set(target_value);
        }
    }

    return true;
}

std::vector<types::board::Index> empty_list(const types::Board& board)
{
    std::vector<types::board::Index> list;
    list.reserve(81);

    for (const auto index : utility::board_indices())
    {
        if (!board[index])
        {
            list.push_back(index);
        }
    }

    return list;
}

bool recursive_solve(types::Board& board_state,
                     std::vector<types::board::Index>& empty_tiles,
                     ValidOptions& valid_options,
                     const AdjacencyMatrix& adj_matrix)
{
    if (empty_tiles.empty())
    {
        return true;
    }

    const auto [next_index_it, next_index_count] = [&] {
        std::vector<types::board::Index>::iterator best_it;
        std::uint8_t best_count = 10;

        for (auto it = empty_tiles.begin(); it != empty_tiles.end(); ++it)
        {
            const auto avail = valid_options.option_count(*it);
            if (avail < best_count)
            {
                best_count = avail;
                best_it = it;
            }
        }

        return std::make_pair(best_it, best_count);
    }();

    if (!next_index_count)
    {
        return false;
    }

    const auto next_index = *next_index_it;
    empty_tiles.erase(next_index_it);

    SUDOKU_ASSERT(!board_state[next_index]);

    std::array<types::board::Index, 20> updated_neighbors;

    for (std::uint8_t value = 1; value <= 9; ++value)
    {
        if (valid_options.is_valid(next_index, value))
        {
            std::size_t updated_neighbors_count = 0;

            for (const auto neighbor : adj_matrix.links(next_index))
            {
                if (valid_options.is_valid(neighbor, value))
                {
                    valid_options.remove_option(neighbor, value);
                    updated_neighbors[updated_neighbors_count++] = neighbor;
                }
            }

            board_state[next_index] = value;
            if (recursive_solve(board_state, empty_tiles, valid_options, adj_matrix))
            {
                return true;
            }
            board_state[next_index] = 0;

            for (std::size_t i = 0; i < updated_neighbors_count; ++i)
            {
                valid_options.add_option(updated_neighbors[i], value);
            }
        }
    }

    empty_tiles.push_back(next_index);

    return false;
}

}  // namespace sudoku::solve
