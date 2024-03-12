#include "include/parser.h"
#include <stdexcept>
#include <regex>

namespace parser {

    Parser::Parser(const std::string &f_path) : path(f_path) {
        stream.open(f_path);
    }

    const char *ParserError::what() const noexcept {
        return "ParserError: I think the file you tried to read from is closed or do not exist";
    }

    std::string Parser::parseline() {
        if (!stream.is_open()) {
            throw ParserError();
        }
        std::string word, other;
        stream >> word;
        std::regex first("^[A-Z]+ ");
        std::smatch match;
        std::regex_search(word, match, first);
        if (match.empty()) {
            throw ParserError();
        }else {

        }
    }


    Parser::~Parser() {
        stream.close();
    }
}
