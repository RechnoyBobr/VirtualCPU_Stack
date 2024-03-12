#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>


namespace parser {
    enum class OperationType {
        SUM,
        SUB,
        MUL,
        DIV,
        PUSH,
        POP
    };

    template<class T>
    class Operation {
    private:
    public:
        Operation() = default;

        virtual T exec();
    };

    template<class T>
    class Sum : Operation<T> {
    public:
        T exec(T a, T b) {
            return a + b;
        }
    };

    template<class T>
    class Sub : Operation<T> {
    public:
        T exec(T a, T b) {
            return a - b;
        }
    };

    template<class T>
    class Mul : Operation<T> {
    public:
        T exec(T a, T b) {
            return a * b;
        }

    };

    template<class T>
    class Div : Operation<T> {
    public:
        T exec(T a, T b) {
            return a / b;
        }
    };

    template<class T>
    class Push : Operation<T> {
    public:
        // TODO: finish
//        T exec(T a, T b) {
//            return a - b;
//        }
    };

    template<class T>
    class Pop : Operation<T> {
    public:
        // TODO: finish
        T exec(T a) {
//            return a - b;
        }
    };

    template<class T>
    std::unordered_map<std::string, Operation<T>> operations = {
            {"SUM",  Sum<T>()},
            {"SUB",  Sub<T>()},
            {"MUL",  Mul<T>()},
            {"DIV",  Div<T>()},
            {"PUSH", Push<T>()},
            {"POP",  Pop<T>()}
    };

    class ParserError : std::exception {
    public:
        const char *what() const noexcept;
        const char *what(const char& msg) const noexcept;
    };

    class Parser {
    private:
        std::ifstream stream;
        std::string path;
        unsigned int lineNum = 0;

    public:
        explicit Parser(const std::string &f_path);

        std::string parseline();

        ~Parser();
    };
}