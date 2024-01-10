#include "types/board.hpp"

#include "error.hpp"

namespace sudoku::types {
Board::Board() : _tiles(9, std::vector<Tile>(9, Tile(0)))
{
}

Tile& Board::operator[](board::Index index)
{
    return _tiles[index.row()][index.col()];
}

Tile Board::operator[](board::Index index) const
{
    return _tiles[index.row()][index.col()];
}

}  // namespace sudoku::types
