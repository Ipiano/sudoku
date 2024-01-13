#include "error.hpp"
#include "solve.hpp"
#include "solve/solve_impl.hpp"
#include "types/board.hpp"
#include "utility/indices.hpp"

#include <iostream>

struct Args
{
    bool silent = false;
    bool all = false;
};

void usage(const char* argv0);
Args parse_args(int argc, char** argv);

void solve_board(sudoku::types::Board input, bool silent = false, bool all = false);
void print_board(sudoku::types::Board input);

int main(int argc, char** argv)
{
    const auto args = parse_args(argc, argv);

    sudoku::types::Board current_board;

    const auto board_indices = sudoku::utility::board_indices();
    auto next_board_index = board_indices.begin();

    char next_c;
    while (std::cin.get(next_c))
    {
        if (next_c >= '0' && next_c <= '9')
        {
            current_board[*next_board_index++] = next_c - '0';

            if (next_board_index == board_indices.end())
            {
                solve_board(current_board, args.silent, args.all);
                next_board_index = board_indices.begin();
            }
        }
    }

    return 0;
}

Args parse_args(int argc, char** argv)
{
    Args result;

    if (argc > 1)
    {
        bool show_usage = false;
        bool error = false;
        bool exit = false;

        for (std::size_t i = 1; i < argc; ++i)
        {
            std::string argi(argv[i]);
            if (argi == "-h")
            {
                show_usage = true;
                exit = true;
            } else if (argi == "--silent")
            {
                result.silent = true;
            } else if (argi == "--all")
            {
                result.all = true;
            } else
            {
                std::cerr << "Invalid argument: " << argi << std::endl;

                exit = true;
                error = true;
                show_usage = true;
            }
        }

        if (show_usage)
        {
            usage(argv[0]);
        }

        if (exit)
            std::exit(error ? 1 : 0);
    }

    return result;
}

void usage(const char* argv0)
{
    std::cout << R"usage(
Usage: ssolve [-h]

  -h          See this help
  --silent    Do not print output (used for benchmarking)
  --all       Find all solutions, instead of only 1

ssolve will read from stdin until the end of the stream is reached. All
characters which are not numeric digits will be ignored. Every group
of 81 digits read will be treated as a sudoku starting state to solve.
The digit 0 is used to represent an empty space on the board that must
be filled.
)usage" << std::endl;
}

void print_board(sudoku::types::Board input)
{
    auto print_row = [input](std::size_t row) {
        printf(" %hhd %hhd %hhd | %hhd %hhd %hhd | %hhd %hhd %hhd \n",
               input[{row, 0}].value(),
               input[{row, 1}].value(),
               input[{row, 2}].value(),
               input[{row, 3}].value(),
               input[{row, 4}].value(),
               input[{row, 5}].value(),
               input[{row, 6}].value(),
               input[{row, 7}].value(),
               input[{row, 8}].value());
    };

    print_row(0);
    print_row(1);
    print_row(2);
    printf("-------+-------+-------\n");
    print_row(3);
    print_row(4);
    print_row(5);
    printf("-------+-------+-------\n");
    print_row(6);
    print_row(7);
    print_row(8);
}

void solve_board(sudoku::types::Board input, bool silent, bool all)
{
    if (!silent)
    {
        std::cout << "=======================\nInitial State:\n\n";
        print_board(input);
    }

    try
    {
        if (all)
        {
            std::vector<sudoku::types::Board> solutions = sudoku::find_all_solutions(input);

            if (!silent)
                std::cout << "\n Solutions: " << solutions.size() << std::endl;
        } else
        {
            const auto result = sudoku::find_solution(input);

            if (result)
            {
                if (!sudoku::solve::is_valid(*result))
                {
                    if (!silent)
                        std::cout << "\nInvalid Solution Returned:\n\n";
                } else
                {
                    if (!silent)
                        std::cout << "\nSolution:\n\n";
                }
                print_board(*result);
            } else
            {
                if (!silent)
                    std::cout << "\nNo Solution!" << std::endl;
            }
        }
    } catch (const sudoku::AssertionFailure& ex)
    {
        std::cout << "\n" << ex.what() << std::endl;
        return;
    }
}
