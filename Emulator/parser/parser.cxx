#include "include/parser.h"

namespace parser {

    Parser::Parser(const std::string &f_path) : path(f_path) {
        stream.open(f_path);
    }

}
