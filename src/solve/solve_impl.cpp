#include "solve/solve_impl.hpp"

#include "types/index.hpp"
#include "utility/indices.hpp"

#include <bitset>

namespace sudoku::solve {
std::optional<types::Board> solve_impl(types::Board input)
{
    // Make sure we haven't been giving a failing board to start
    if (!is_valid(input))
    {
        return std::nullopt;
    }

    // Build the adjacency matrix for open spaces. This represents the set of

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

}  // namespace sudoku::solve
