#include "solve/solve_impl.hpp"

#include <bitset>
namespace sudoku::solve {
std::optional<types::Board> solve_impl(types::Board input)
{
    if (!is_valid(input))
    {
        return std::nullopt;
    }

    return std::nullopt;
}

bool is_valid(types::Board input)
{
    std::array<std::bitset<10>, 9> rows;
    std::array<std::bitset<10>, 9> cols;
    std::array<std::bitset<10>, 9> boxes;

    const auto box_ind = [](std::size_t row, std::size_t col) {
        return row / 3 * 3 + col / 3;
    };

    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            if (input[{i, j}])
            {
                const auto target_value = input[{i, j}].value();

                if (rows[i].test(target_value))
                {
                    return false;
                }
                rows[i].set(target_value);

                if (cols[j].test(target_value))
                {
                    return false;
                }
                cols[j].set(target_value);

                if (boxes[box_ind(i, j)].test(target_value))
                {
                    return false;
                }
                boxes[box_ind(i, j)].set(target_value);
            }
        }
    }

    return true;
}
}  // namespace sudoku::solve
