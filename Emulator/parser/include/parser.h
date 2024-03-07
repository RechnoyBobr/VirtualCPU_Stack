#pragma once

#include <fstream>

namespace parser {
    class Parser {
    private:
        std::ifstream stream;
        std::string path;

    public:
        explicit Parser(const std::string& f_path);

    };
}