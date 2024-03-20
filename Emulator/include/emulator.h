#pragma once

#include <unordered_map>
#include "../preprocessor/include/preprocessor.h"
#include "../../stack/include/stack.h"
#include "../parser/include/parser.h"
#include "../Operations/include/operations.h"
#include <utility>
#include <vector>
#include <string>


namespace emu {


    class Emulator {
    private:
        preproc::Preprocessor preprocessor;
        const int stack_size = 131072;
        lib::Stack<long long> stack;
        std::unordered_map<parser::Tokens, std::shared_ptr<op::Operation>> operations;
        memo::Memory cpu_memory;
        serializer::Deserializer deserializer;
    public:
        explicit Emulator(const std::string &f_path, const std::string &s_path);

        void preprocess();

        void execute(std::vector<parser::Token> ins);

        bool has_label(const std::vector<parser::Token> &ins, const std::string &a);

        void run();

    };


}