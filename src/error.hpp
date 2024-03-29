#pragma once

#include <stdexcept>

namespace sudoku {
class Error : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class AssertionFailure : public Error
{
  public:
    AssertionFailure(const char* file, int line, const char* assertion) :
        Error("Assertion failed @ " + std::string(file) + ":" + std::to_string(line) + "\n" +
              std::string(assertion))
    {
    }
};

#ifdef NDEBUG
    #define SUDOKU_ASSERT(x)                                                                       \
        do                                                                                         \
        {                                                                                          \
        } while (false)
#else
    #define SUDOKU_ASSERT(x)                                                                       \
        do                                                                                         \
        {                                                                                          \
            if (!(x))                                                                              \
            {                                                                                      \
                throw sudoku::AssertionFailure(__FILE__, __LINE__, #x);                            \
            }                                                                                      \
        } while (false)
#endif
}  // namespace sudoku
