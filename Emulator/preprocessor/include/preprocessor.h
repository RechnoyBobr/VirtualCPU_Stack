#pragma once

#include <stdexcept>
#include "../../parser/include/parser.h"
#include "../../../stack/include/stack.h"
#include "../../serializer/include/serializer.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace preproc {




    class PreprocessorError : std::exception {
    public:
        const char *what() const noexcept;

    };

    class Preprocessor {
    private:
        parser::Parser parser;
        std::vector<parser::Token> instructions;
        serializer::Serializer serializer;
    public:
        Preprocessor(const std::string &f_path, const std::string &s_path);


        void process_file();

        void serialize();


        static long long parse_number(const std::string &str);

        ~Preprocessor();

    };


}