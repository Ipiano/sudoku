#pragma once

#include "types/board.hpp"

#include <optional>

namespace sudoku::solve {
std::optional<types::Board> solve_impl(types::Board input);


}  // namespace sudoku::solve
