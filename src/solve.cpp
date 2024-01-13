#include "solve.hpp"

#include "solve/solve_impl.hpp"

namespace sudoku {
std::optional<types::Board> find_solution(types::Board starting_state)
{
    return solve::solve_impl(starting_state);
}

std::vector<types::Board> find_all_solutions(types::Board starting_state)
{
    return solve::solve_all_impl(starting_state);
}
}  // namespace sudoku
