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

    const std::unordered_map<std::string, Tokens> token_map = {
            {"BEGIN", Tokens::BEGIN},
            {"PUSH",  Tokens::PUSH},
            {"POP",   Tokens::POP},
            {"PUSHR", Tokens::PUSHR},
            {"POPR",  Tokens::POPR},
            {"ADD",   Tokens::ADD},
            {"SUB",   Tokens::SUB},
            {"MUL",   Tokens::MUL},
            {"DIV",   Tokens::DIV},
            {"IN",    Tokens::IN},
            {"OUT",   Tokens::OUT},
            {"JMP",   Tokens::JMP},
            {"JEQ",   Tokens::JEQ},
            {"JNE",   Tokens::JNE},
            {"JA",    Tokens::JA},
            {"JAE",   Tokens::JAE},
            {"JB",    Tokens::JB},
            {"JBE",   Tokens::JBE},
            {"CALL",  Tokens::CALL},
            {"RET",   Tokens::RET},
            {"END",   Tokens::END}
    };

    Token Parser::parseline() {
        if (!stream.is_open()) {
            throw ParserError();
        }
        std::string line;
        getline(stream, line);
        if (!stream) {
            return {Tokens::FILEEND, ""};
        }
        std::smatch match, match2;
        std::regex label("^[A-Z]+:$");
        std::regex_search(line, match, label);
        if (!match.empty()) {
            return {Tokens::LABEL, match.str(0).substr(0, match.str(0).size() - 1)};
        }
        std::regex first("^[A-Z]+");
        std::regex_search(line, match, first);
        if (match.empty() || match.size() > 1) {
            throw ParserError();
        }
        if (match.str(0).size() + 1 >= line.size()) {
            try {
                Tokens token = token_map.at(match[0]);
                return {token, ""};
            } catch (std::out_of_range &e) {
                throw ParserError();
            }
        }
        line = line.substr(match.str(0).size() + 1, line.size() - match.str(0).size() - 1);
        try {
            Tokens token = token_map.at(match.str(0));
            if (token == Tokens::PUSH) {
                std::regex second("-?[0-9]+");
                std::regex_search(line, match2, second);
                if (match2.empty() || match2.size() > 1 || match2.str(0).size() < line.size()) {
                    throw ParserError();
                }
                return {token, match2.str(0)};
            } else if (token == Tokens::PUSHR || token == Tokens::POPR) {
                std::regex second("[A-Z]{2}");
                std::regex_search(line, match2, second);
                if (match2.empty() || match2.size() > 2 || match2.str(0).size() < line.size()) {
                    throw ParserError();
                }
                return {token, match2[1]};
            } else if (token == Tokens::JMP || token == Tokens::JEQ || token == Tokens::JNE || token == Tokens::JA ||
                       token == Tokens::JAE || token == Tokens::JB || token == Tokens::JBE || token == Tokens::CALL) {
                std::regex second("[A-Z]+");
                std::regex_search(line, match2, second);
                if (match2.empty() || match2.size() > 2 || match2.str(0).size() < line.size()) {
                    throw ParserError();
                }
                return {token, match2.str(0)};
            }

        } catch (std::out_of_range &e) {
            throw ParserError();
        }
    }


    Parser::~Parser() {
        stream.close();
    }
}
