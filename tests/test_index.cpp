#include "types/index.hpp"

#include <gtest/gtest.h>

#ifndef NDEBUG
TEST(Sudoku, Index_InvalidValue)
{
    ASSERT_THROW(sudoku::types::board::Index(-1, 0), sudoku::AssertionFailure);
    ASSERT_THROW(sudoku::types::board::Index(0, -1), sudoku::AssertionFailure);

    ASSERT_THROW(sudoku::types::board::Index(9, 0), sudoku::AssertionFailure);
    ASSERT_THROW(sudoku::types::board::Index(0, 9), sudoku::AssertionFailure);
}
#endif
