#pragma once

#include <stdexcept>

namespace sudoku {
class Error : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class AssertionFailure : Error
{
  public:
    AssertionFailure(const char* file, int line, const char* assertion) :
        Error("Assertion failed '" + std::string(assertion) + "' @ " + std::string(file) + ":" +
              std::to_string(line))
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
