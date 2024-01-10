#pragma once

#include "types/board.hpp"
#include "types/index.hpp"

#include <array>
#include <utility>

namespace sudoku::solve {
// Bookkeeper for the adjacency matrix of the sudoku puzzle.
//
// This tracks what squares need to be considered when touching
// any given other square
class AdjacencyMatrix
{
    using Index = sudoku::types::board::Index;

  public:
    using Iterator = std::array<Index, 20>::const_iterator;

    class Range
    {
      public:
        using iterator = Iterator;
        using const_iterator = Iterator;
        using value_type = std::iterator_traits<Iterator>::value_type;
        Range(Iterator begin, Iterator end) : _begin(begin), _end(end) {}

        Iterator begin() const { return _begin; }
        Iterator end() const { return _end; }

      private:
        Iterator _begin;
        Iterator _end;
    };

    AdjacencyMatrix();

    // Add a link indicating that a has an effect on b (but _not_ the inverse)
    //
    // Behavior is undefined if more than 20 links are added for any given index
    void add(Index a, Index b);

    // Get a pair of begin/end iterators for the set of links of a given index
    Range links(Index index) const;

  private:
    static std::size_t hash(Index ind);

    std::array<std::pair<std::size_t, std::array<Index, 20>>, 81> _matrix;
};

AdjacencyMatrix adjacency_matrix_from_open_spaces(const types::Board& board);
}  // namespace sudoku::solve
