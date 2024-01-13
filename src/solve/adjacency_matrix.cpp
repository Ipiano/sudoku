#include "solve/adjacency_matrix.hpp"

#include "error.hpp"
#include "types/index.hpp"
#include "utility/indices.hpp"

namespace sudoku::solve {

AdjacencyMatrix::AdjacencyMatrix()
{
    for (auto& adj_list : _matrix)
    {
        adj_list.first = 0;
    }
}

std::size_t AdjacencyMatrix::hash(Index ind)
{
    return ind.row() * 9 + ind.col();
}

void AdjacencyMatrix::add(Index a, Index b)
{
    auto& adj_list = _matrix[hash(a)];

    SUDOKU_ASSERT(adj_list.first < adj_list.second.size());
    adj_list.second[adj_list.first++] = b;
}

auto AdjacencyMatrix::links(Index index) const -> Range
{
    const auto& adj_list = _matrix[hash(index)];
    return {adj_list.second.begin(), adj_list.second.begin() + adj_list.first};
}

AdjacencyMatrix adjacency_matrix_from_open_spaces(const types::Board& board)
{
    AdjacencyMatrix result;

    auto add_links = [](const types::Board& b, AdjacencyMatrix& m, types::board::Index empty) {
        // Add all empty squares in the same row (at most 8)
        for (const auto index : utility::row_indices(empty.row()))
        {
            if (index != empty && !b[index])
            {
                m.add(empty, index);
            }
        }

        // Add all empty squares in the same column (at most 8)
        for (const auto index : utility::col_indices(empty.col()))
        {
            if (index != empty && !b[index])
            {
                m.add(empty, index);
            }
        }

        // Add any other empty spots in the same box (at most 4)
        for (const auto index : utility::box_indices(empty))
        {
            if (index.row() != empty.row() && index.col() != empty.col() && !b[index])
            {
                m.add(empty, index);
            }
        }
    };

    for (const auto index : utility::board_indices())
    {
        if (!board[index])
        {
            add_links(board, result, index);
        }
    }

    return result;
}
}  // namespace sudoku::solve
