#include "solve.hpp"

#include "solve/solve_impl.hpp"

namespace sudoku {
std::optional<types::Board> find_solution(types::Board starting_state)
{
    return solve::solve_impl(starting_state);
}
}  // namespace sudoku
