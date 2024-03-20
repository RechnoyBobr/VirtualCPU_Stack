#pragma once

#include <unordered_map>
#include <vector>
#include "../../parser/include/parser.h"
#include "../../../stack/include/stack.h"

namespace memo {
    struct Memory {
        std::unordered_map<std::string, long long> labels;
        std::unordered_map<std::string, long long> registers = {
                {"AX", 0},
                {"BX", 0},
                {"CX", 0},
                {"DX", 0},
                {"PC", 0}

        };
        std::vector<parser::Token> instructions;
        std::unordered_map<std::string, std::vector<parser::Token>> functions;
        lib::Stack<long long> stack = lib::Stack<long long>(131072);
    };
}