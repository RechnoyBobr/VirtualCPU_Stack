#pragma once

#include <stdexcept>
#include "../../../stack/include/stack.h"
#include <unordered_map>
#include <optional>
#include <mutex>

namespace preproc {

    class PreprocessorError : std::exception {
    public:
        const char *what() const noexcept;

    };

    class Preprocessor {
    private:
        lib::Stack<long long> stack;
        unsigned int stackSize;
        std::unordered_map<std::string, long long> registers = {
                {"AX", 0},
                {"BX", 0},
                {"CX", 0},
                {"DX", 0},
                {"PC", 0},
                {"SP", 0},
                {"BP", 0},
                {"SI", 0},
                {"DI", 0}
        };
    public:
        Preprocessor();

        void Add();

        void Substract();

        void Multiply();

        void Divide();

        void Push(long long a);

        void Pop();

        void PopR(const std::string &reg);

        void PushR(const std::string &reg);

        void Out();

        void In();

        long long get_reg(const std::string &reg);

        std::optional<long long> parse_number(const std::string &str);

        ~Preprocessor();

    };
}