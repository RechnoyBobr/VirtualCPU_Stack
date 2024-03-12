#include "preprocessor.h"

namespace preproc {

    const char *SyntaxError::what() const noexcept {
        return "A syntax error occurred while parsing the file";
    }
}