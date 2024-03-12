#pragma once

#include <stdexcept>
#include "../parser/include/parser.h"
#include <map>

namespace preproc {

    class SyntaxError : std::exception {
    public:
        const char *what() const noexcept;
    };

    class Preprocessor {
    private:

    public:
    };
}