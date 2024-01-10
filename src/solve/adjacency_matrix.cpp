#include "solve/adjacency_matrix.hpp"

#include "error.hpp"
#include "types/index.hpp"

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
        for (std::size_t i = 0; i < 9; ++i)
        {
            types::board::Index candidate(i, empty.col());
            if (i != empty.row() && !b[candidate])
            {
                m.add(empty, candidate);
            }
        }

        // Add all empty squares in the same column (at most 8)
        for (std::size_t i = 0; i < 9; ++i)
        {
            types::board::Index candidate(empty.row(), i);
            if (i != empty.col() && !b[candidate])
            {
                m.add(empty, candidate);
            }
        }

        // Add any other empty spots in the same box (at most 4)
        types::board::Index box_corner(empty.row() / 3 * 3, empty.col() / 3 * 3);
        for (std::size_t i = 0; i < 3; ++i)
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                types::board::Index candidate(box_corner.row() + i, box_corner.col() + j);
                if (candidate.row() != empty.row() && candidate.col() != empty.col() &&
                    !b[candidate])
                {
                    m.add(empty, candidate);
                }
            }
        }
    };

    for (std::size_t i = 0; i < 9; ++i)
    {
        for (std::size_t j = 0; j < 9; ++j)
        {
            if (!board[{i, j}])
            {
                add_links(board, result, {i, j});
            }
        }
    }

    return result;
}
}  // namespace sudoku::solve
