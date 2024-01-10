#include "types/board.hpp"

#include "types/index.hpp"

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

Board create_board(std::initializer_list<std::pair<board::Index, Tile>> initial_tiles)
{
    Board b;

    for (const auto init : initial_tiles)
    {
        b[init.first] = init.second;
    }

    return b;
}

Board create_board(std::array<Tile, 81> initial_tiles)
{
    Board b;
    auto tile_it = initial_tiles.begin();

    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            b[{i, j}] = *tile_it++;
        }
    }

    return b;
}

}  // namespace sudoku::types
