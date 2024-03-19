#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>


namespace parser {
    enum class Tokens {
        BEGIN,
        PUSH,
        POP,
        PUSHR,
        POPR,
        ADD,
        SUB,
        MUL,
        DIV,
        IN,
        OUT,
        JMP,
        JEQ,
        JNE,
        JA,
        JAE,
        LABEL,
        JB,
        JBE,
        CALL,
        RET,
        END,
        FILEEND

    };

    struct Token {
        Tokens type;
        std::string value;
    };

    class ParserError : std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class Parser {
    private:
        std::ifstream stream;
        std::string path;

    public:
        explicit Parser(const std::string &f_path);

        Token parseline();

        ~Parser();
    };
}