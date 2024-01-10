#pragma once

#include "types/board.hpp"

#include <optional>

namespace sudoku {

//! Attempt to solve the board; return a solved board if a solution is found
std::optional<types::Board> find_solution(types::Board starting_state);
}  // namespace sudoku
