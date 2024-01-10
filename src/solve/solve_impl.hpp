#pragma once

#include "types/board.hpp"

#include <optional>

namespace sudoku::solve {
std::optional<types::Board> solve_impl(types::Board input);

// Check if a given board state is valid - meaning that it does not
// contain any invalid moves (but may contain empty spaces)
//
// Not cheap - don't use frequently in the solution
bool is_valid(types::Board input);

}  // namespace sudoku::solve
