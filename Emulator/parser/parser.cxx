#include "include/parser.h"
#include <iostream>
#include <stdexcept>
#include <regex>
#include <format>

namespace parser {

    Parser::Parser(const std::string &f_path) : path(f_path) {
        stream.open(f_path);
    }

    const char *ParserError::what() const noexcept {
        return "ParserError: There is syntax error in the file. Please check the file and try again.";
    }

    std::pair<std::string, std::string> Parser::parseline() {
        if (!stream.is_open()) {
            throw ParserError();
        }
        std::string line;
        getline(stream, line);
        if (!stream) {
            return {"\0", ""};
        }
        std::regex first("^[A-Z]+");
        std::smatch match, match1;
        std::regex_search(line, match, first);

        if (match.empty() || match.size() > 1) {
            throw ParserError();
        } else {
        }
        if (match.str(0) == "BEGIN") {
            return {"BEGIN", ""};
        } else if (match.str(0) == "END") {
            return {"END", ""};
        } else if (match.str(0) == "PUSH") {
            std::regex second("(-?[0-9]+)");
            std::regex_search(line, match1, second);
            if (match1.empty() || match1.size() > 2) {
                throw ParserError();
            }
            this->lineNum++;
            return {match.str(0), match1.str(0)};
        } else if (match.str(0) == "PUSHR" || match.str(0) == "POPR") {
            std::regex second("(?!PUSHR )(?!POPR)(\\b[A-Z]{2})");
            std::regex_search(line, match1, second);
            if (match1.empty() || match1.size() > 2) {
                throw ParserError();
            }
            this->lineNum++;
            return {match.str(0), match1.str(0)};
        } else {
            this->lineNum++;
            return {match.str(0), ""};
        }
    }


    unsigned int Parser::getNum() const {
        return this->lineNum;
    }

    Parser::~Parser() {
        stream.close();
    }
}
