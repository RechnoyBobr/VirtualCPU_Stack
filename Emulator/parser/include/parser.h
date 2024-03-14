#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>


namespace parser {


    class ParserError : std::exception {
    public:
        const char *what() const noexcept;
    };

    class Parser {
    private:
        std::ifstream stream;
        std::string path;
        unsigned int lineNum = 0;

    public:
        explicit Parser(const std::string &f_path);

        unsigned int getNum() const;

        std::pair<std::string, std::string> parseline();

        ~Parser();
    };
}