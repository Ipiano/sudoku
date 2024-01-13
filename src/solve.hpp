#pragma once

#include "types/board.hpp"

#include <optional>
#include <vector>

namespace sudoku {

//! Attempt to solve the board; return a solved board if a solution is found
std::optional<types::Board> find_solution(types::Board starting_state);

//! Return all possible solutions for the board
std::vector<types::Board> find_all_solutions(types::Board starting_state);

}  // namespace sudoku
