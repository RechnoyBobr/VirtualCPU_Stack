#include "preprocessor.h"
#include <stdexcept>


namespace preproc {

    Preprocessor::Preprocessor(const std::string &f_path, const std::string &s_path) : parser(parser::Parser(f_path)),
                                                                                       serializer(
                                                                                               serializer::Serializer(
                                                                                                       s_path)) {
    }

    Preprocessor::~Preprocessor() {

    }

    long long Preprocessor::parse_number(const std::string &str) {
        return std::stoll(str);
    }

    void Preprocessor::process_file() {
        parser::Token token;
        token = parser.parseline();
        while (token.type != parser::Tokens::BEGIN && token.type != parser::Tokens::FILEEND) {
            token = parser.parseline();
        }
        while (token.type != parser::Tokens::END) {
            if (token.type == parser::Tokens::FILEEND) {
                throw PreprocessorError();
            }
            instructions.emplace_back(token);
        }
        instructions.emplace_back(token);
    }

    void Preprocessor::serialize() {
        for (const parser::Token &i: instructions) {
            serializer.serialize(i);
        }
    }

    const char *PreprocessorError::what() const noexcept {
        return "Preprocessor error occurred!";
    }
}